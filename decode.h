#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Source Image info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /* Output File Info */
    char output_fname[50];
    FILE *fptr_output;

    /* Secret File Info */
    int extn_size;
    char extn_output_file[MAX_FILE_SUFFIX + 1];
    int size_output_file;

} DecodeInfo;


/* Read and validate decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_decode_files(DecodeInfo *decInfo);

/* Skip bmp header */
Status skip_bmp_header(FILE *fptr_stego_image);

/* Decode a byte from LSB of image data array */
Status decode_lsb_to_byte(char *data, char *image_buffer);

/* Decode an integer from LSB of image data array */
Status decode_lsb_to_int(int *size, char *image_buffer);

/* Get Magic String */
Status decode_magic_string(DecodeInfo *decInfo);

/* Decode secret file extension size */
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* Decode secret file extension */
Status decode_secret_file_extn(DecodeInfo *decInfo);

/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

#endif