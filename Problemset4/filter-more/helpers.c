#include "helpers.h"
#include "math.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            double avg = (double) round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0);
            image[j][i].rgbtBlue = avg;
            image[j][i].rgbtGreen = avg;
            image[j][i].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < (width / 2); i++)
        {
            tmp[j][i] = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 - i] = tmp[j][i];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            tmp[c][d].rgbtBlue = image[c][d].rgbtBlue;
            tmp[c][d].rgbtGreen = image[c][d].rgbtGreen;
            tmp[c][d].rgbtRed = image[c][d].rgbtRed;
        }
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            double bxcount = 9;
            double sumBlue = 0;
            double sumGreen = 0;
            double sumRed = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if ((j - 1 + k) < 0 || (j - 1 + k) >= height || (i - 1 + l) < 0 || (i - 1 + l) >= width)
                    {
                        bxcount -= 1;
                    }
                    else
                    {
                        sumBlue += tmp[j - 1 + k][i - 1 + l].rgbtBlue;
                        sumGreen += tmp[j - 1 + k][i - 1 + l].rgbtGreen;
                        sumRed += tmp[j - 1 + k][i - 1 + l].rgbtRed;
                    }
                }
            }
            image[j][i].rgbtBlue = round(sumBlue / bxcount);
            image[j][i].rgbtGreen = round(sumGreen / bxcount);
            image[j][i].rgbtRed = round(sumRed / bxcount);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            tmp[c][d].rgbtBlue = image[c][d].rgbtBlue;
            tmp[c][d].rgbtGreen = image[c][d].rgbtGreen;
            tmp[c][d].rgbtRed = image[c][d].rgbtRed;
        }
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
            int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
            double GxBlue = 0;
            double GxGreen = 0;
            double GxRed = 0;
            double GyBlue = 0;
            double GyGreen = 0;
            double GyRed = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if ((j - 1 + k) < 0 || (j - 1 + k) >= height || (i - 1 + l) < 0 || (i - 1 + l) >= width)
                    {
                    }
                    else
                    {
                        GxBlue += tmp[j - 1 + k][i - 1 + l].rgbtBlue * Gx[k][l];
                        GxGreen += tmp[j - 1 + k][i - 1 + l].rgbtGreen * Gx[k][l];
                        GxRed += tmp[j - 1 + k][i - 1 + l].rgbtRed * Gx[k][l];
                        GyBlue += tmp[j - 1 + k][i - 1 + l].rgbtBlue * Gy[k][l];
                        GyGreen += tmp[j - 1 + k][i - 1 + l].rgbtGreen * Gy[k][l];
                        GyRed += tmp[j - 1 + k][i - 1 + l].rgbtRed * Gy[k][l];
                    }
                }
            }
            if (round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))) > 255)
                image[j][i].rgbtBlue = 255;
            else
                image[j][i].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            if (round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))) > 255)
                image[j][i].rgbtGreen = 255;
            else
                image[j][i].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            if (round(sqrt(pow(GxRed, 2) + pow(GyRed, 2))) > 255)
                image[j][i].rgbtRed = 255;
            else
                image[j][i].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
        }
    }
    return;
}
