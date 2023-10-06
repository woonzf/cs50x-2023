// Recover JPEGs

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // Check input file memory
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Create a buffer for reading
    BYTE buffer[BLOCK_SIZE];
    int image = 0;

    // Allocate memory for output file name
    char *outfile = malloc(8 * sizeof(char));
    FILE *outptr = NULL;

    // Read through the file in a size of 512 bytes
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check for type .jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a previous file is opened, close it
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Create an output file "###.jpg"
            sprintf(outfile, "%03i.jpg", image);
            outptr = fopen(outfile, "w");

            // Check output file memory
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", outfile);
                fclose(inptr);
                free(outfile);
                return 1;
            }

            image++;
        }

        // If a file is already opened, continue writing
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    // Close files and free memory
    fclose(outptr);
    fclose(inptr);
    free(outfile);

    return 0;
}