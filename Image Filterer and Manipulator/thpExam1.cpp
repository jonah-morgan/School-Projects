/** ***************************************************************************
* @file
* 
* @brief Main Function..
******************************************************************************/
#include "netPBM.h"



int main(int argc, char** argv)
{
    string option;
    string type;
    string newName;
    string inputImage;
    string tempStr;
    string options[6] = { "--flipX", "--flipY", "--rotateCW", 
                          "--rotateCCW", "--grayscale", "--sepia" };
    ifstream file;
    ofstream fout;

    bool isOpen;
    bool isFoutOpen;
    bool isGray = false;

    image thisImage;

    // Checking the command line arguments.
    checkArgs(argc, argv, options);
    inputImage = argv[argc - 1];
    newName = argv[argc - 2];
    type = argv[argc - 3];

    if (argc == 5)
    {
        option = argv[argc - 4];
    }
    
    if (option == "--grayscale")
        isGray = true;

    // Opening the image.
    isOpen = openInputFile( file, inputImage );
    if (!isOpen)
    {
        return 0;
    }

    // Reading in the Header, Comments and Dimensions.
    readImageHCD(file, thisImage, tempStr);

    // Dynamically allocating 3 2d arrays: redgray, green, and blue. 
    allocateAllArr(thisImage);

    //Reading in the pixels.
    if (thisImage.magicNumber == "P3")
        readImageAscii(file, thisImage);
    else
        readImageBinary(file, thisImage);

    //Formulate new magic number(p2,p3,p5,p6) and file name.
    applyOption(thisImage, option);

    /* Determines if the image output will be grayscale or not and will
    open the appropriate file.*/
    if (isGray)
        newName.append(".pgm");
    else
        newName.append(".ppm");

    // Open output file.
    isFoutOpen = openOutputFile(fout, newName);
    if (!isFoutOpen)
    {
        deleteAllArr(thisImage);
        file.close();
        return 0;
    }

    // Output based on the option.
    mainOutput(fout, thisImage, isGray, type);

    //Clean up(free all memory, close all files.
    closeEverything(file, fout, thisImage);
    return 0;
}
