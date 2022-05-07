/** **********************************************************************
* @file
* 
* @brief Image Operations: FlipX, FlipY, Clockwise Rotation (90 Degrees),
  Counter Clockwise Rotation (90 Degrees), Grayscale, and Sepia..
************************************************************************/
#include "netPBM.h"


void applyOption(image& thisImage, string option)
{
    // Total of six options. Will apply the option based on the string 'option'
    if (option == "--flipX")
        flipImageX(thisImage);

    else if (option == "--flipY")
        flipImageY(thisImage);

    else if (option == "--rotateCW")
        rotateImageCW(thisImage);

    else if (option == "--rotateCCW")
        rotateImageCCW(thisImage);

    else if (option == "--grayscale")
        grayscaleImage(thisImage);

    else if (option == "--sepia")
        sepiaImage(thisImage);

}



void flipImageX(image &thisImage)
{
    // Reverses each pixel array which will flip the image on it's x axis.
    reverse(&thisImage.redGray[0], &thisImage.redGray[thisImage.rows]);

    reverse(&thisImage.green[0], &thisImage.green[thisImage.rows]);

    reverse(&thisImage.blue[0], &thisImage.blue[thisImage.rows]);
}



void flipImageY(image &thisImage)
{
    int i;

    /* For loop that goes through every row and reverses the pixel arrays to flip it
      on it's Y axis. */
    for (i = 0; i < thisImage.rows; i++)
    {
        reverse(&thisImage.redGray[i][0], &thisImage.redGray[i][thisImage.cols]);
        reverse(&thisImage.green[i][0], &thisImage.green[i][thisImage.cols]);
        reverse(&thisImage.blue[i][0], &thisImage.blue[i][thisImage.cols]);
    }
}



void rotateImageCW(image& thisImage)
{
    // Initialize and allocate all the variables needed for this function.
    pixel** redGrayCW = alloc2d(thisImage.cols, thisImage.rows);
    pixel** greenCW = alloc2d(thisImage.cols, thisImage.rows);
    pixel** blueCW = alloc2d(thisImage.cols, thisImage.rows);

    int i, j;
    int tempNum;

    // Loop that goes through and assigns values for the three new arrays.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            redGrayCW[j][thisImage.rows - i - 1] = thisImage.redGray[i][j];
            greenCW[j][thisImage.rows - i - 1] = thisImage.green[i][j];
            blueCW[j][thisImage.rows - i - 1] = thisImage.blue[i][j];
        }
    }

    // Delete all the old arrays and assign the new ones to our image structure
    deleteAllArr(thisImage);
    thisImage.redGray = redGrayCW;
    thisImage.green = greenCW;
    thisImage.blue = blueCW;

    // Update the column and row values.
    tempNum = thisImage.rows;
    thisImage.rows = thisImage.cols;
    thisImage.cols = tempNum;

}



void rotateImageCCW(image& thisImage)
{
    pixel** redGrayCW = alloc2d(thisImage.cols, thisImage.rows);
    pixel** greenCW = alloc2d(thisImage.cols, thisImage.rows);
    pixel** blueCW = alloc2d(thisImage.cols, thisImage.rows);

    int i, j;
    int tempNum;

    // Loop that goes through and assigns values for the three new arrays.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            redGrayCW[thisImage.cols - j - 1][i] = thisImage.redGray[i][j];
            greenCW[thisImage.cols - j - 1][i] = thisImage.green[i][j];
            blueCW[thisImage.cols - j - 1][i] = thisImage.blue[i][j];
        }
    }

    // Delete all the old arrays and assign the new ones to our image structure
    deleteAllArr(thisImage);
    thisImage.redGray = redGrayCW;
    thisImage.green = greenCW;
    thisImage.blue = blueCW;

    // Update the column and row values.
    tempNum = thisImage.rows;
    thisImage.rows = thisImage.cols;
    thisImage.cols = tempNum;
}



void grayscaleImage(image& thisImage)
{
    int i, j;
    string tempStr;

    // Nested for loop that goes through every pixel and determines 
    // its new value.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            thisImage.redGray[i][j] = (int)((.3 * thisImage.redGray[i][j]) +
                                           (.6 * thisImage.green[i][j]) +
                                           (.1 * thisImage.blue[i][j]));
            

        }
    }
}



void sepiaImage(image &thisImage)
{
    int i, j;
    int tr, tg, tb;

    // Nested for loop that goes through every pixel and gives it a new value.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            tr = (int)((.393 * thisImage.redGray[i][j]) +
                 (.769 * thisImage.green[i][j]) +
                 (.189 * thisImage.blue[i][j]));

            tg = (int)((.349 * thisImage.redGray[i][j]) +
                 (.686 * thisImage.green[i][j]) +
                 (.168 * thisImage.blue[i][j]));

            tb = (int)((.272 * thisImage.redGray[i][j]) +
                 (.534 * thisImage.green[i][j]) +
                 (.131 * thisImage.blue[i][j]));

            if (tr > 255)
                thisImage.redGray[i][j] = 255;

            else
                thisImage.redGray[i][j] = tr;

            if (tg > 255)
                thisImage.green[i][j] = 255;

            else
                thisImage.green[i][j] = tg;

            if (tb > 255)
                thisImage.blue[i][j] = 255;

            else
                thisImage.blue[i][j] = tb;
        }
    }
}