#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"


Status open_decode_files(DecodeInfo *decInfo)
{
    // open stego image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");

    // check file opened or not
    if(decInfo->fptr_stego_image == NULL)
    {
        // print error message
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n",
                decInfo->stego_image_fname);

        // return e_failure
        return e_failure;
    }

    // return e_success
    return e_success;
}

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    char *ext = strrchr(argv[2], '.');

    // check in argv[2] .bmp present or not
    if(ext != NULL && strcmp(ext, ".bmp") == 0)
    {
        // update into structure
        decInfo->stego_image_fname = argv[2];
    }
    else
    {
        // return e_failure
        return e_failure;
    }

    // check argv[3] is NULL or not
    if(argv[3] != NULL)
    {
        // update into structure
        strcpy(decInfo->output_fname, argv[3]);
    }
    else
    {
        // store default output file name
        strcpy(decInfo->output_fname, "output");
    }

    // return e_success
    return e_success;
}


Status do_decoding(DecodeInfo *decInfo)
{
    // open required files
    if(open_decode_files(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Unable to open files\n");

        // return e_failure
        return e_failure;
    }

    // skip bmp header
    if(skip_bmp_header(decInfo->fptr_stego_image) == e_failure)
    {
        // print error message
        printf("ERROR: Failed to skip BMP header\n");

        // return e_failure
        return e_failure;
    }

    // decode magic string
    if(decode_magic_string(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Magic string mismatch\n");

        // return e_failure
        return e_failure;
    }

    // decode extension size
    if(decode_secret_file_extn_size(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Failed to decode extension size\n");

        // return e_failure
        return e_failure;
    }

    // decode extension
    if(decode_secret_file_extn(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Failed to decode extension\n");

        // return e_failure
        return e_failure;
    }

    // decode secret file size
    if(decode_secret_file_size(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Failed to decode file size\n");

        // return e_failure
        return e_failure;
    }

    // decode secret file data
    if(decode_secret_file_data(decInfo) == e_failure)
    {
        // print error message
        printf("ERROR: Failed to decode file data\n");

        // return e_failure
        return e_failure;
    }

    // close stego image file
    fclose(decInfo->fptr_stego_image);

    // return e_success
    return e_success;
}

Status skip_bmp_header(FILE *fptr_stego_image)
{
    // skip first 54 bytes bmp header
    fseek(fptr_stego_image, 54, SEEK_SET);

    // return e_success
    return e_success;
}


Status decode_lsb_to_byte(char *data, char *image_buffer)
{
    // initialize data to 0
    *data = 0;

    // loop for 8 times
    for(int i = 0; i < 8; i++)
    {
        // left shift data by 1
        *data = *data << 1;

        // get lsb from image buffer and store into data
        *data = *data | (image_buffer[i] & 1);
    }

    // return e_success
    return e_success;
}

Status decode_lsb_to_int(int *size, char *image_buffer)
{
    // initialize size to 0
    *size = 0;

    // loop for 32 times
    for(int i = 0; i < 32; i++)
    {
        // left shift size by 1
        *size = *size << 1;

        // get lsb from image buffer and store into size
        *size = *size | (image_buffer[i] & 1);
    }

    // return e_success
    return e_success;
}

Status decode_magic_string(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char data;
    char magic_string[3];

    // loop for 2 times
    for(int i = 0; i < 2; i++)
    {
        // read 8 bytes from stego image
        fread(image_buffer, 8, 1, decInfo->fptr_stego_image);

        // decode one character
        decode_lsb_to_byte(&data, image_buffer);

        // store decoded character
        magic_string[i] = data;
    }

    // add null character
    magic_string[2] = '\0';

    // compare decoded string with MAGIC_STRING
    if(strcmp(magic_string, MAGIC_STRING) == 0)
    {
        // return e_success
        return e_success;
    }
    else
    {
        // return e_failure
        return e_failure;
    }
}

Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char image_buffer[32];

    // read 32 bytes from stego image
    fread(image_buffer, 32, 1, decInfo->fptr_stego_image);

    // decode extension size
    decode_lsb_to_int((int *)&decInfo->extn_size, image_buffer);

    // return e_success
    return e_success;
}

Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char data;

    // loop for extension size times
    for(int i = 0; i < decInfo->extn_size; i++)
    {
        // read 8 bytes from stego image
        fread(image_buffer, 8, 1, decInfo->fptr_stego_image);

        // decode one character
        decode_lsb_to_byte(&data, image_buffer);

        // store decoded character
        decInfo->extn_output_file[i] = data;
    }

    // add null character
    decInfo->extn_output_file[decInfo->extn_size] = '\0';

    // return e_success
    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char image_buffer[32];

    // read 32 bytes from stego image
    fread(image_buffer, 32, 1, decInfo->fptr_stego_image);

    // decode secret file size
    decode_lsb_to_int(&decInfo->size_output_file, image_buffer);

    //printf("Decoded file size = %d\n", decInfo->size_output_file);

    // return e_success
    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char data;

    // create output file name with extension
    strcat(decInfo->output_fname, decInfo->extn_output_file);

    // open output file
    decInfo->fptr_output = fopen(decInfo->output_fname, "w");

    // check file opened or not
    if(decInfo->fptr_output == NULL)
    {
        // return e_failure
        return e_failure;
    }

    //printf("File size = %d\n", decInfo->size_output_file);

    // loop for secret file size times
    for(int i = 0; i < decInfo->size_output_file; i++)
    {
        // read 8 bytes from stego image
        fread(image_buffer, 8, 1, decInfo->fptr_stego_image);

        // decode one character
        decode_lsb_to_byte(&data, image_buffer);

        // print decoded character
        //printf("Decoded char = %c  ASCII = %d\n", data, data);

        // write character into output file
        fputc(data, decInfo->fptr_output);
    }

    // close output file
    fclose(decInfo->fptr_output);

    // return e_success
    return e_success;
}



