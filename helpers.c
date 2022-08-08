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

            // If top row
            if (i == 0 && j != 0 && j != width - 1)
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
            else if (j == 0 && i != 0 && i != height - 1)
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
            else if (j == (width - 1) && i != 0 && i != height - 1)
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
            else if (i == (height - 1) && j != 0 && j != width - 1)
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
            else if (i == 0 && j == (width - 1))
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
            else if (i == (height - 1) && j == 0)
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
            else if (i == (height - 1) && j == (width - 1))
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

            // If not an edge or corner case
            else
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
    // Define arrays to store the color values so you don't change them as they go
    double redvalues[height][width];
    double greenvalues[height][width];
    double bluevalues[height][width];

    // Define arrays to store Gx and Gy kernels
    double Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    double Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Test Print
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f\n", Gx[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f\n", Gy[i][j]);
        }
    }
    */


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


    // Iterate over each pixel one at a time
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Counts the number of pixels around the pixel in question. Resets for each pixel
            double pixelcount = 0;

            // Define Gx and Gy for RGB. Resets for each pixel
            double Gxred = 0;
            double Gyred = 0;
            double Gxgreen = 0;
            double Gygreen = 0;
            double Gxblue = 0;
            double Gyblue = 0;


            // If top row
            if (i == 0 && j != 0 && j != width - 1)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If left row
            else if (j == 0 && i != 0 && i != height - 1)
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If right row
            else if (j == (width - 1) && i != 0 && i != height - 1)
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 1; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If bottom row
            else if (i == (height - 1) && j != 0 && j != width - 1)
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
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
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If top right corner
            else if (i == 0 && j == (width - 1))
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = -1; l < 1; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If bottom right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                for (int k = -1; k < 1; k++)
                {
                    for (int l = -1; l < 1; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // If not an edge or corner case. Iterates all around the current pixel.
            else
            /*if (i != 0 && i != height - 1 && j != 0 && j != width - 1) */
            {
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        Gxred += redvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyred += redvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxgreen += greenvalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gygreen += greenvalues[i + k][j + l] * Gy[k + 1][l + 1];
                        Gxblue += bluevalues[i + k][j + l] * Gx[k + 1][l + 1];
                        Gyblue += bluevalues[i + k][j + l] * Gy[k + 1][l + 1];
                    }
                }
            }

            // Calculate Sobel values for RGB
            double sobelred = round(sqrt((Gxred * Gxred) + (Gyred * Gyred)));
            double sobelgreen = round(sqrt((Gxgreen * Gxgreen) + (Gygreen * Gygreen)));
            double sobelblue = round(sqrt((Gxblue * Gxblue + Gyblue * Gyblue)));

            if (sobelred > 255)
            {
                sobelred = 255;
            }

            if (sobelgreen > 255)
            {
                sobelgreen = 255;
            }

            if (sobelblue > 255)
            {
                sobelblue = 255;
            }

            image[i][j].rgbtRed = sobelred;
            image[i][j].rgbtGreen = sobelgreen;
            image[i][j].rgbtBlue = sobelblue;
        }

    }

    return;
}
