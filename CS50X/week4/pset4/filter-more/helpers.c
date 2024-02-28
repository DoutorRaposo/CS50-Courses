#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // I'm using the same code that I used for the less version.
    // Very similar to the lab! Now we need to substitute the value of each subpixel by the average of all pixels.
    for (int i = 0; i < height; i++) // After a row, then next row.
    {
        for (int j = 0; j < width; j++) // First, every row!
        {
            float average_value = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0; //casting a float there (3.0);
            image[i][j].rgbtRed = round(average_value);
            image[i][j].rgbtGreen = round(average_value);
            image[i][j].rgbtBlue = round(average_value);
        } // The trick is remembering to divide as a float then rounding.
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // I'm using the same code as my LESS version.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; //copying everything
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - 1 - j]; //writing back to the image. important: width - 1!
        }
    }
    return;;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // I'm using the same filter as my LESS version here.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; //copying everything
        }
    }

    // So, we need to check for all special cases for this case, that is: all four corners that have the average of four and then all the edges that have the average of 6. Then the rest is average of 9.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) // Top left corner
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            if (i == 0 && j == width - 1) // Top right corner
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                               copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            if (i == height - 1 && j == 0) // Bottom left corner
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4.0);
            }
            if (i == height - 1 && j == width - 1) // Bottom right corner
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                               copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                              copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4.0);

            }
            if (i == 0 && j > 0 && j < width - 1) // Every upper edge except corners
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.0);

            }
            if (i == height - 1 && j > 0 && j < width - 1) // Every bottom edge except corners
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / 6.0);
            }
            if (i > 0 && i < height - 1 && j == 0) // Every left edge except corners
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
            }
            if (i > 0 && i < height - 1 && j == width - 1) // Every right edge except corners
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy [i + 1][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                               copy [i + 1][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                              copy [i + 1][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);

            }
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1) // Every pixel that is not corner nor edge.
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen
                                               + copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                               copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}

// Detect edges
// I did the same approach that I did for blur, but now that I've debugged this, I think there must be a more concise way of writing that I didn't have yet the skill to make. Using a 3x3 grid inside each iteration of pixel [i][j], somehow connecting to the matrix gy and gx, but
// I can't think of a way to do this in the edge and corner cases.
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //First of all, I will define the matrix for GX and GY
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Then, an int for every channel.

    int gx_red = 0;
    int gx_green = 0;
    int gx_blue = 0;
    int gy_red = 0;
    int gy_green = 0;
    int gy_blue = 0;

    int finalRed = 0;
    int finalGreen = 0;
    int finalBlue = 0;

    // Copying all the data to a secondary array. Just so the calculations doesn't interfere with each other, as it would if the edit directly in the original.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; //copying everything
        }
    }
    // So, we need to check for all special cases for this case, similar to the other case. Then multiply by GX and GY the surrounding pixels (since the edges are black pixels, is the same as not including nothing).
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) // Top left corner
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i + 1][j + 1].rgbtRed * gx[2][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i + 1][j + 1].rgbtGreen * gx[2][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i + 1][j + 1].rgbtBlue * gx[2][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i + 1][j + 1].rgbtRed * gy[2][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i + 1][j + 1].rgbtGreen * gy[2][2]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i + 1][j + 1].rgbtBlue * gy[2][2]);


                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i == 0 && j == width - 1) // Top right corner
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtRed * gx[2][0]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtGreen * gx[2][0]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtBlue * gx[2][0]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtRed * gy[2][0]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtGreen * gy[2][0]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtBlue * gy[2][0]);

                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i == height - 1 && j == 0) // Bottom left corner
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i - 1][j + 1].rgbtRed * gx[0][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i - 1][j + 1].rgbtGreen * gx[0][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i - 1][j + 1].rgbtBlue * gx[0][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i - 1][j + 1].rgbtRed * gy[0][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i - 1][j + 1].rgbtGreen * gy[0][2]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i - 1][j + 1].rgbtBlue * gy[0][2]);

                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i == height - 1 && j == width - 1) // Bottom right corner
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gx[0][0]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gx[0][0]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gx[0][0]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gy[0][0]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gy[0][0]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gy[0][0]);


                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i == 0 && j > 0 && j < width - 1) // Every upper edge except corners
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtRed * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtRed * gx[2][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtGreen * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtGreen * gx[2][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i + 1][j - 1].rgbtBlue * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtBlue * gx[2][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtRed * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtRed * gy[2][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtGreen * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtGreen * gy[2][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i + 1][j - 1].rgbtBlue * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtBlue * gy[2][2]);

                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i == height - 1 && j > 0 && j < width - 1) // Every bottom edge except corners
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtRed * gx[0][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtGreen * gx[0][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtBlue * gx[0][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtRed * gy[0][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtGreen * gy[0][2]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtBlue * gy[0][2]);

                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i > 0 && i < height - 1 && j == 0) // Every left edge except corners
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i - 1][j + 1].rgbtRed * gx[0][2]) +
                    (copy[i + 1][j + 1].rgbtRed * gx[2][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i - 1][j + 1].rgbtGreen * gx[0][2]) +
                    (copy[i + 1][j + 1].rgbtGreen * gx[2][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i - 1][j + 1].rgbtBlue * gx[0][2]) +
                    (copy[i + 1][j + 1].rgbtBlue * gx[2][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i - 1][j + 1].rgbtRed * gy[0][2]) +
                    (copy[i + 1][j + 1].rgbtRed * gy[2][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i - 1][j + 1].rgbtGreen * gy[0][2]) +
                    (copy[i + 1][j + 1].rgbtGreen * gy[2][2]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i - 1][j + 1].rgbtBlue * gy[0][2]) +
                    (copy[i + 1][j + 1].rgbtBlue * gy[2][2]);


                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
            if (i > 0 && i < height - 1 && j == width - 1) // Every right edge except corners
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gx[0][0]) +
                    (copy[i + 1][j - 1].rgbtRed * gx[2][0]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gx[0][0]) +
                    (copy[i + 1][j - 1].rgbtGreen * gx[2][0]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gx[0][0]) +
                    (copy[i + 1][j - 1].rgbtBlue * gx[2][0]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gy[0][0]) +
                    (copy[i + 1][j - 1].rgbtRed * gy[2][0]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gy[0][0]) +
                    (copy[i + 1][j - 1].rgbtGreen * gy[2][0]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gy[0][0]) +
                    (copy[i + 1][j - 1].rgbtBlue * gy[2][0]);

                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }

            if (i > 0 && i < height - 1 && j > 0 && j < width - 1) // Every pixel that is not corner nor edge.
            {
                gx_red =
                    (copy[i][j].rgbtRed * gx[1][1]) +
                    (copy[i][j + 1].rgbtRed * gx[1][2]) +
                    (copy[i][j - 1].rgbtRed * gx[1][0]) +
                    (copy[i - 1][j].rgbtRed * gx[0][1]) +
                    (copy[i + 1][j].rgbtRed * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtRed * gx[0][2]) +
                    (copy[i + 1][j - 1].rgbtRed * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtRed * gx[2][2]);

                gx_green =
                    (copy[i][j].rgbtGreen * gx[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gx[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gx[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gx[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtGreen * gx[0][2]) +
                    (copy[i + 1][j - 1].rgbtGreen * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtGreen * gx[2][2]);

                gx_blue =
                    (copy[i][j].rgbtBlue * gx[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gx[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gx[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gx[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gx[2][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gx[0][0]) +
                    (copy[i - 1][j + 1].rgbtBlue * gx[0][2]) +
                    (copy[i + 1][j - 1].rgbtBlue * gx[2][0]) +
                    (copy[i + 1][j + 1].rgbtBlue * gx[2][2]);

                gy_red =
                    (copy[i][j].rgbtRed * gy[1][1]) +
                    (copy[i][j + 1].rgbtRed * gy[1][2]) +
                    (copy[i][j - 1].rgbtRed * gy[1][0]) +
                    (copy[i - 1][j].rgbtRed * gy[0][1]) +
                    (copy[i + 1][j].rgbtRed * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtRed * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtRed * gy[0][2]) +
                    (copy[i + 1][j - 1].rgbtRed * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtRed * gy[2][2]);

                gy_green =
                    (copy[i][j].rgbtGreen * gy[1][1]) +
                    (copy[i][j + 1].rgbtGreen * gy[1][2]) +
                    (copy[i][j - 1].rgbtGreen * gy[1][0]) +
                    (copy[i - 1][j].rgbtGreen * gy[0][1]) +
                    (copy[i + 1][j].rgbtGreen * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtGreen * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtGreen * gy[0][2]) +
                    (copy[i + 1][j - 1].rgbtGreen * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtGreen * gy[2][2]);

                gy_blue =
                    (copy[i][j].rgbtBlue * gy[1][1]) +
                    (copy[i][j + 1].rgbtBlue * gy[1][2]) +
                    (copy[i][j - 1].rgbtBlue * gy[1][0]) +
                    (copy[i - 1][j].rgbtBlue * gy[0][1]) +
                    (copy[i + 1][j].rgbtBlue * gy[2][1]) +
                    (copy[i - 1][j - 1].rgbtBlue * gy[0][0]) +
                    (copy[i - 1][j + 1].rgbtBlue * gy[0][2]) +
                    (copy[i + 1][j - 1].rgbtBlue * gy[2][0]) +
                    (copy[i + 1][j + 1].rgbtBlue * gy[2][2]);


                // Now we need to get the square root of the sum of the squares of gx_channels. It's the same as getting the hypotenuse, so we will use the function for that.
                finalRed = round(hypot(gx_red, gy_red));
                finalGreen = round(hypot(gx_green, gy_green));
                finalBlue = round(hypot(gx_blue, gy_blue));

                if (finalRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = finalRed;
                }
                if (finalGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = finalGreen;
                }
                if (finalBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = finalBlue;
                }
            }
        }
    }
    return;
}
