#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double red = image[i][j].rgbtRed;
            double green = image[i][j].rgbtGreen;
            double blue = image[i][j].rgbtBlue;


            double average = round((red + green + blue)/3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < (width/2); j++)
            {
                RGBTRIPLE buffer = image[i][j];
                image[i][j] = image[i][width - (1 + j)];
                image[i][width - (1 + j)] = buffer;
            }
        }
    }

    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < ((width - 1)/2); j++)
            {
                RGBTRIPLE buffer = image[i][j];
                image[i][j] = image[i][width - (1 + j)];
                image[i][width - (1 + j)] = buffer;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Define arrays to store the color values so you don't change them as they go
    double redvalues[height][width];
    double greenvalues[height][width];
    double bluevalues[height][width];

    // Populate the new color arrays so you have static arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redvalues [i][j] = image[i][j].rgbtRed;
            greenvalues [i][j] = image[i][j].rgbtGreen;
            bluevalues [i][j] = image[i][j].rgbtBlue;
        }
    }

    /*
    printf("%i\n", redvalues[0][0]);
    */

    // Iterate over each pixel one at a time
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define total values that can be changed to find an average value. Resets for each pixel
            double totalred = 0;
            double totalgreen = 0;
            double totalblue = 0;

            // Counts the number of pixels around the pixel in question. Resets for each pixel
            double pixelcount = 0;

            // If not an edge or corner case
            if (i > 0 && i < height && j > 0 && j < width)
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If top row
            else if (i == 0)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If left row
            else if (j == 0)
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If right row
            else if (j == width - 1)
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 1; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If bottom row
            else if (i == height - 1)
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If top left corner
            else if (i == 0 && j == 0)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If top right corner
            else if (i == 0 && j == width - 1)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = -1; l < 1; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If bottom left corner
            else if (i == height - 1 && j == 0)
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // If bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = -1; l < 1; l++)
                   {
                        totalred += redvalues[i + k][j + l];
                        totalgreen += greenvalues[i + k][j + l];
                        totalblue += bluevalues[i + k][j + l];

                        pixelcount++;
                    }
                }
            }

            // Find the average RGB values for
            double averagered = round(totalred/pixelcount);
            double averagegreen = round(totalgreen/pixelcount);
            double averageblue = round(totalblue/pixelcount);

            image[i][j].rgbtRed = averagered;
            image[i][j].rgbtGreen = averagegreen;
            image[i][j].rgbtBlue = averageblue;
        }

    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
