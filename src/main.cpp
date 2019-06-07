#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

#include "openjpeg_coder.h"

void openjpeg_warning(const char* msg, void* client_data)
{
}

void openjpeg_error(const char* msg, void* client_data)
{
}

void openjpeg_info(const char* msg, void* client_data)
{
}

float convertToFloat(uint32_t v) {
	return *(reinterpret_cast<float*>(&v));
}

std::vector<double> decodeValues(unsigned char* buf, size_t raw_data_length, size_t data_count) {
	int err = 0;
	unsigned long  mask;
	std::vector<double> val;

	opj_dparameters_t parameters = { 0, };	/* decompression parameters */
	opj_stream_t* stream = NULL;
	opj_memory_stream mstream;
	opj_image_t* image = NULL;
	opj_codec_t* codec = NULL;
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

	if (!(data_count <= image->comps[0].w * image->comps[0].h)) {
		err = 5;
		goto cleanup;
	}
	if ((image->numcomps != 1) || (image->x1 * image->y1) == 0) {
		err = 6;
		goto cleanup;
	}

	_ASSERT(image->comps[0].sgnd == 0);
	_ASSERT(comp.prec <= sizeof(image->comps[0].data[0]) * 8 - 1); /* BR: -1 because I don't know what happens if the sign bit is set */

	_ASSERT(image->comps[0].prec < sizeof(mask) * 8 - 1);

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

cleanup:
	/* close the byte stream */
	if (codec)  opj_destroy_codec(codec);
	if (stream) opj_stream_destroy(stream);
	if (image)  opj_image_destroy(image);

	return val;
}

int main() {
    std::string grib_file_path{"D:/windroc/project/2019/grib2/nwpc-codes-cpp/dist/data/t.850hpa.000.grb2"};

    auto start_pos = 0xB1;
    auto raw_data_length = 0x98998 - 0xB1 + 1;
	auto data_count = 1036800;

	int binary_scale_factor = 0x0;
	int decimal_scale_factor = 0x2;
	float reference_value = convertToFloat(0x46B1298E);

    auto buf = new unsigned char[raw_data_length];

	std::FILE* f = std::fopen(grib_file_path.c_str(), "rb");
	std::fseek(f, start_pos, SEEK_SET);
	std::fread(buf, 1, raw_data_length, f);
	std::fclose(f);

    // std::ifstream f(grib_file_path, std::ios::binary);
	// f.seekg(start_pos);
	// f.read(reinterpret_cast<char*>(buf), raw_data_length);
	// f.close();

	auto val = decodeValues(buf, raw_data_length, data_count);

    delete[] buf;

	if (val.size() == 0) {
		std::cerr << "value decode has error." << std::endl;
		return 1;
	}
	
	for (auto i = 0; i < data_count; i++) {
		val[i] = (reference_value + val[i] * std::pow(2, binary_scale_factor)) / std::pow(10, decimal_scale_factor);
	}

	
    return 0;
}