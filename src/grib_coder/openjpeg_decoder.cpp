#include "openjpeg_decoder.h"
#include "openjpeg_helper.h"

#include <cassert>


void openjpeg_warning(const char* msg, void* client_data)
{
}

void openjpeg_error(const char* msg, void* client_data)
{
}

void openjpeg_info(const char* msg, void* client_data)
{
}

std::vector<double> decodeJPEG2000Values(unsigned char* buf, size_t raw_data_length, size_t data_count) {
	int err = 0;
	unsigned long  mask;
	std::vector<double> val;

	opj_dparameters_t parameters = { 0, };	/* decompression parameters */
	opj_stream_t* stream = nullptr;
	opj_memory_stream mstream;
	opj_image_t* image = nullptr;
	opj_codec_t* codec = nullptr;
	opj_image_comp_t comp = { 0, };

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
	mstream.pData = buf;
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

	if (data_count > image->comps[0].w * image->comps[0].h) {
		err = 5;
		goto cleanup;
	}
	if ((image->numcomps != 1) || (image->x1 * image->y1) == 0) {
		err = 6;
		goto cleanup;
	}

	assert(image->comps[0].sgnd == 0);
	assert(comp.prec <= sizeof(image->comps[0].data[0]) * 8 - 1); /* BR: -1 because I don't know what happens if the sign bit is set */

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
	if (codec)  opj_destroy_codec(codec);
	if (stream) opj_stream_destroy(stream);
	if (image)  opj_image_destroy(image);

	return val;
}