#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        fclose(inptr);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    char *outfile = argv[2];
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        printf("Could not open output file.\n");
        fclose(inptr);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];

    // Move to last block for reading
    fseek(inptr, -block_size, SEEK_END);
    int pos_cur = ftell(inptr);

    // Copy every block in reverse after header file
    while (pos_cur > 44 + block_size)
    {
        fread(buffer, block_size, 1, inptr);
        fwrite(buffer, block_size, 1, outptr);

        // Update current position and move back 2 blocks
        pos_cur = ftell(inptr);
        fseek(inptr, -2 * block_size, SEEK_CUR);
    }

    // Close files
    fclose(outptr);
    fclose(inptr);

    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] != 0x57 || header.format[1] != 0x41 || header.format[2] != 0x56 || header.format[3] != 0x45)
    {
        return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int channel = header.numChannels;
    int bytepersample = header.bitsPerSample / 8;
    int blocksize = channel * bytepersample;

    return blocksize;
}