// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // Here we are copying one massive chunk of data. We copy the massive HEADER_SIZE 44-byte long chunk all at once! 
    uint8_t *header_array = malloc(sizeof(uint8_t) * HEADER_SIZE);
    fread(header_array, HEADER_SIZE, 1, input);
    fwrite(header_array, HEADER_SIZE, 1, output);
    free(header_array);

    // TODO: Read samples from input file and write updated data to output file

    int16_t buffer;

    // Read the buffer one at a time
    // Important - every time one of the sizeof(int16_t) is read, the &buffer address changes to the next byte over
    // So, we can read first, then change that specific value at that byte to multiply it times the factor, then write it into the output file
    // This continues until fread is 0; if it is 0, that means it read 0 bytes and therefore it's at EOF
    while (fread(&buffer, sizeof(int16_t), 1, input) > 0)
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
