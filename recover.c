#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[])
{

    typedef uint8_t BYTE;

    // Check for proper usage!
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the card.raw file for reading and check to see if it's able to be opened
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Image cannot be opened for reading.\n");
        return 1;
    }

    const int BLOCK_SIZE = 512;
    int jpgnumber = 0;
    BYTE block_buffer[BLOCK_SIZE];
    FILE *outfile;
    if (outfile == NULL)
    {
        printf("Image cannot be opened for reading.\n");
        return 1;
    }
    char filename[8];
    bool file_is_open = false;

    // Repeat this process. fread will return BLOCK_SIZE if it can read 512 block chunks, until it can't and returns 0
    while (fread(block_buffer, 1, BLOCK_SIZE, f))
    {
        // Check the first four values of the block_array to see if it's a JPEG
        if (block_buffer[0] == 0xff && block_buffer[1] == 0xd8 && block_buffer[2] == 0xff && (block_buffer[3] & 0xf0) == 0xe0)
        {
            // If this is the very first JPEG EVER FOUND!
            if (file_is_open == false)
            {
                sprintf(filename, "%03i.jpg", jpgnumber);
                outfile = fopen(filename, "a");
                fwrite(block_buffer, 1, BLOCK_SIZE, outfile);

                file_is_open = true;

                jpgnumber++;
            }

            // If this is NOT the first JPEG found
            else
            {
                fclose(outfile);

                sprintf(filename, "%03i.jpg", jpgnumber);
                outfile = fopen(filename, "a");
                fwrite(block_buffer, 1, BLOCK_SIZE, outfile);

                jpgnumber++;
            }


        }

        else
        {
            if (file_is_open == true)
            {
                fwrite(block_buffer, 1, BLOCK_SIZE, outfile);
            }
        }

    }

    fclose(outfile);
    fclose(f);
}