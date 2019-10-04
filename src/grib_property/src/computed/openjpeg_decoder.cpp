#include "grib_property/computed/openjpeg_decoder.h"
#include "grib_property/computed/openjpeg_helper.h"

#include <cassert>


void openjpeg_warning(const char* msg, void* client_data) {
}

void openjpeg_error(const char* msg, void* client_data) {
}

void openjpeg_info(const char* msg, void* client_data) {
}

namespace grib_coder {

std::vector<double> decode_jpeg2000_values(std::byte* buf, size_t raw_data_length, size_t data_count) {
    int err = 0;
    unsigned long mask;
    std::vector<double> val;

    opj_dparameters_t parameters = {0,}; /* decompression parameters */
    opj_stream_t* stream = nullptr;
    opj_memory_stream mstream;
    opj_image_t* image = nullptr;
    opj_codec_t* codec = nullptr;
    opj_image_comp_t comp = {0,};

    /* set decoding parameters to default values */
    opj_set_default_decoder_parameters(&parameters);
    parameters.decod_format = 1; /* JP2_FMT */

    /* get a decoder handle */
    codec = opj_create_decompress(OPJ_CODEC_J2K);

    /* catch events using our callbacks and give a local context */
    opj_set_info_handler(codec, openjpeg_info, nullptr);
    opj_set_warning_handler(codec, openjpeg_warning, nullptr);
    opj_set_error_handler(codec, openjpeg_error, nullptr);

    /* initialize our memory stream */
    mstream.pData = reinterpret_cast<unsigned char*>(buf);
    mstream.dataSize = raw_data_length;
    mstream.offset = 0;
    /* open a byte stream from memory stream */
    stream = opj_stream_create_default_memory_stream(&mstream, OPJ_STREAM_READ);

    /* setup the decoder decoding parameters using user parameters */
    if (!opj_setup_decoder(codec, &parameters)) {
        err = 2;
        goto cleanup;
    }
    if (!opj_read_header(stream, codec, &image)) {
        err = 3;
        goto cleanup;
    }
    if (!opj_decode(codec, stream, image)) {
        err = 4;
        goto cleanup;
    }

    if (data_count > (size_t(image->comps[0].w) * size_t(image->comps[0].h))) {
        err = 5;
        goto cleanup;
    }
    if ((image->numcomps != 1) || (image->x1 * image->y1) == 0) {
        err = 6;
        goto cleanup;
    }

    assert(image->comps[0].sgnd == 0);
    assert(comp.prec <= sizeof(image->comps[0].data[0]) * 8 -
        1); /* BR: -1 because I don't know what happens if the sign bit is set */

    assert(image->comps[0].prec < sizeof(mask) * 8 - 1);

    {
        auto data = image->comps[0].data;
        mask = (1 << image->comps[0].prec) - 1;

        auto count = image->comps[0].w * image->comps[0].h;

        val.resize(count);
        for (auto i = 0; i < count; i++) {
            auto v = data[i];
            val[i] = v & mask;
        }

        if (!opj_end_decompress(codec, stream)) {
            err = 7;
        }
    }


cleanup:
    /* close the byte stream */
    if (codec) opj_destroy_codec(codec);
    if (stream) opj_stream_destroy(stream);
    if (image) opj_image_destroy(image);

    return val;
}

bool encode_jpeg2000_values(j2k_encode_helper* helper) {
    auto flag = true;
    const int numcomps = 1;
    int i;

    const auto values = helper->values;
    auto  no_values = helper->no_values;
    auto reference_value = helper->reference_value;
    auto divisor = helper->divisor;
    auto decimal = helper->decimal;

    int* data;

    opj_cparameters_t parameters = { 0, };	/* compression parameters */
    opj_codec_t* codec = nullptr;
    opj_image_t* image = nullptr;
    opj_image_cmptparm_t cmptparm = { 0, };
    opj_stream_t* stream = nullptr;
    opj_memory_stream memory_stream;

    /* set encoding parameters to default values */
    opj_set_default_encoder_parameters(&parameters);
    
    parameters.tcp_numlayers = 1;
    parameters.cp_disto_alloc = 1;
    /* parameters.numresolution =  1; */
    parameters.tcp_rates[0] = helper->compression;

    /* By default numresolution = 6 (must be between 1 and 32)
     * This may be too large for some of our datasets, eg. 1xn, so adjust ...
     */
    parameters.numresolution = 6;
    while ((helper->width < (OPJ_UINT32)(1 << (parameters.numresolution - 1U))) ||
        (helper->height < (OPJ_UINT32)(1 << (parameters.numresolution - 1U))))
    {
        parameters.numresolution--;
    }

    /* initialize image component */
    cmptparm.prec = helper->bits_per_value;
    cmptparm.bpp = helper->bits_per_value; /* Not sure about this one and the previous. What is the difference? */
    cmptparm.sgnd = 0;
    cmptparm.dx = 1;
    cmptparm.dy = 1;
    cmptparm.w = helper->width;
    cmptparm.h = helper->height;

    /* create the image */
    image = opj_image_create(numcomps, &cmptparm, OPJ_CLRSPC_GRAY);
    if (!image) {

        flag = false;
        goto cleanup;
    }
    image->x0 = 0;
    image->y0 = 0;
    image->x1 = helper->width;
    image->y1 = helper->height;

    assert(cmptparm.prec <= sizeof(image->comps[0].data[0]) * 8 - 1); /* BR: -1 because I don't know what happens if the sign bit is set */
    assert(helper->no_values == image->comps[0].h * image->comps[0].w);

    /* Simple packing */
    data = image->comps[0].data;
    for (i = 0; i < no_values; i++) {
        auto unsigned_val = (unsigned long)((((values[i] * decimal) - (reference_value)) * divisor) + 0.5);
        data[i] = unsigned_val;
    }

    /* get a J2K compressor handle */
    codec = opj_create_compress(OPJ_CODEC_J2K);

    opj_set_info_handler(codec, openjpeg_info, nullptr);
    opj_set_warning_handler(codec, openjpeg_warning, nullptr);
    opj_set_error_handler(codec, openjpeg_error, nullptr);

    /* setup the encoder parameters using the current image and user parameters */
    if (!opj_setup_encoder(codec, &parameters, image)) {
        // grib_context_log(c, GRIB_LOG_ERROR, "openjpeg: failed to setup encoder");
        flag = false;
        goto cleanup;
    }

    /* open a byte stream for writing */
    memory_stream.helper = helper;
    memory_stream.pData = (OPJ_UINT8*)helper->jpeg_buffer;
    memory_stream.offset = 0;
    memory_stream.dataSize = helper->buffer_size;
    stream = opj_stream_create_default_memory_stream(&memory_stream, OPJ_STREAM_WRITE);
    if (stream == nullptr) {
        // grib_context_log(c, GRIB_LOG_ERROR, "openjpeg: failed create default memory stream");
        flag = false;
        goto cleanup;
    }
    if (!opj_start_compress(codec, image, stream)) {
        // grib_context_log(c, GRIB_LOG_ERROR, "openjpeg: failed to setup encoder");
        flag = false;
        goto cleanup;
    }

    /* encode image */
    if (!opj_encode(codec, stream)) {
        // grib_context_log(c, GRIB_LOG_ERROR, "openjpeg: opj_encode failed");
        flag = false;
        goto cleanup;
    }

    if (!opj_end_compress(codec, stream)) {
        // grib_context_log(c, GRIB_LOG_ERROR, "openjpeg: opj_end_compress failed");
        flag = false;
        goto cleanup;
    }
    helper->jpeg_length = memory_stream.offset;

cleanup:
    if (codec)   opj_destroy_codec(codec);
    if (stream) opj_stream_destroy(stream);
    if (image) opj_image_destroy(image);

    return flag;
}

} // namespace grib_coder
