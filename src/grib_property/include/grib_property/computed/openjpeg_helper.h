#pragma once

#include <openjpeg.h>

struct j2k_encode_helper {
    size_t buffer_size;

    long width;     // ni
    long height;    // nj
    long bits_per_value;    // bits_per_value
    
    // type_of_compression_used:
    //  false: 0 (target_compression_ratio == 255)
    //  true: target_compression_ratio (target_compression_ratio != 0 or 255)
    float compression;  

    long no_values;     // number of values
    const double* values;   // original values
    double reference_value;     // reference value
    double divisor;     // 2^(-binary_scale_factor)
    double decimal;     // 10^(decimal_scale_factor)

    long jpeg_length;
    unsigned char* jpeg_buffer;
};

/* OpenJPEG 2.1 version of grib_openjpeg_encoding.c */

/* opj_* Helper code from https://groups.google.com/forum/#!topic/openjpeg/8cebr0u7JgY */
/* These routines are added to use memory instead of a file for input and output */
/* struct need to treat memory as a stream */
struct opj_memory_stream {
    OPJ_UINT8* pData; /* our data */
    OPJ_SIZE_T dataSize; /* how big is our data */
    OPJ_SIZE_T offset; /* where we are currently in our data */
    j2k_encode_helper* helper;
};

/* This will read from our memory to the buffer */
OPJ_SIZE_T opj_memory_stream_read(void* buffer, OPJ_SIZE_T nb_bytes, void* p_user_data);

/* Write from the buffer to our memory */
OPJ_SIZE_T opj_memory_stream_write(void* buffer, OPJ_SIZE_T nb_bytes, void* user_data);

/* Moves the pointer forward, but never more than we have */
OPJ_OFF_T opj_memory_stream_skip(OPJ_OFF_T nb_bytes, void* user_data);

/* Sets the pointer to anywhere in the memory */
OPJ_BOOL opj_memory_stream_seek(OPJ_OFF_T nb_bytes, void* user_data);

void opj_memory_stream_do_nothing(void* p_user_data);

/* Create a stream to use memory as the input or output */
opj_stream_t* opj_stream_create_default_memory_stream(opj_memory_stream* memoryStream, OPJ_BOOL is_read_stream);
