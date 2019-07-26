#include "openjpeg_helper.h"
#include <cstring>

/* This will read from our memory to the buffer */
OPJ_SIZE_T opj_memory_stream_read(void* buffer, OPJ_SIZE_T nb_bytes, void* p_user_data)
{
	auto mstream = (opj_memory_stream*)p_user_data; /* Our data */
	OPJ_SIZE_T nb_bytes_read = nb_bytes; /* Amount to move to buffer */

	/* Check if the current offset is outside our data buffer */
	if (mstream->offset >= mstream->dataSize)
		return (OPJ_SIZE_T)-1;

	/* Check if we are reading more than we have */
	if (nb_bytes > (mstream->dataSize - mstream->offset))
		nb_bytes_read = mstream->dataSize - mstream->offset;

	memcpy(buffer, &(mstream->pData[mstream->offset]), nb_bytes_read);
	mstream->offset += nb_bytes_read; /* Update the pointer to the new location */
	return nb_bytes_read;
}

/* Write from the buffer to our memory */
OPJ_SIZE_T opj_memory_stream_write(void* buffer, OPJ_SIZE_T nb_bytes, void* user_data)
{
	auto mstream = (opj_memory_stream*)user_data; /* our data */
	OPJ_SIZE_T nb_bytes_write = nb_bytes; /* Amount to move to buffer */

	/* Check if the current offset is outside our data buffer */
	if (mstream->offset >= mstream->dataSize)
		return (OPJ_SIZE_T)-1;

	/* Check if we are writing more than we have space for */
	if (nb_bytes > (mstream->dataSize - mstream->offset))
		nb_bytes_write = mstream->dataSize - mstream->offset;

	/* Copy the data from the internal buffer */
	memcpy(&(mstream->pData[mstream->offset]), buffer, nb_bytes_write);
	mstream->offset += nb_bytes_write; /* Update the pointer to the new location */
	return nb_bytes_write;
}

/* Moves the pointer forward, but never more than we have */
OPJ_OFF_T opj_memory_stream_skip(OPJ_OFF_T nb_bytes, void* user_data)
{
	auto mstream = (opj_memory_stream*)user_data;
	OPJ_SIZE_T l_nb_bytes;

	if (nb_bytes < 0)
		return -1; /* No skipping backwards */
	l_nb_bytes = (OPJ_SIZE_T)nb_bytes; /* Allowed because it is positive */
	/* Do not allow jumping past the end */
	if (l_nb_bytes > mstream->dataSize - mstream->offset)
		nb_bytes = mstream->dataSize - mstream->offset;
	mstream->offset += l_nb_bytes;
	return l_nb_bytes; /* Returm how far we jumped */
}

/* Sets the pointer to anywhere in the memory */
OPJ_BOOL opj_memory_stream_seek(OPJ_OFF_T nb_bytes, void* user_data)
{
	opj_memory_stream* mstream = (opj_memory_stream*)user_data;

	if (nb_bytes < 0)
		return OPJ_FALSE; /* Not before the buffer */
	if (nb_bytes > (OPJ_OFF_T) mstream->dataSize)
		return OPJ_FALSE; /* Not after the buffer */
	mstream->offset = (OPJ_SIZE_T)nb_bytes; /* Move to new position */
	return OPJ_TRUE;
}

void opj_memory_stream_do_nothing(void* p_user_data)
{
	OPJ_ARG_NOT_USED(p_user_data);
}

/* Create a stream to use memory as the input or output */
opj_stream_t* opj_stream_create_default_memory_stream(opj_memory_stream* memoryStream, OPJ_BOOL is_read_stream)
{
	opj_stream_t* stream;

	if (!(stream = opj_stream_default_create(is_read_stream)))
		return nullptr;
	/* Set how to work with the frame buffer */
	if (is_read_stream)
		opj_stream_set_read_function(stream, opj_memory_stream_read);
	else
		opj_stream_set_write_function(stream, opj_memory_stream_write);

	opj_stream_set_seek_function(stream, opj_memory_stream_seek);
	opj_stream_set_skip_function(stream, opj_memory_stream_skip);
	opj_stream_set_user_data(stream, memoryStream, opj_memory_stream_do_nothing);
	opj_stream_set_user_data_length(stream, memoryStream->dataSize);
	return stream;
}