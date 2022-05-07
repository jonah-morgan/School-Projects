/** **********************************************************************
* @file
* 
* @brief Argument checking and I/O for Ascii/Binary files..
************************************************************************/
#include "netPBM.h"



void checkArgs(int argc, char** argv, string options[])
{
    int i;
    bool checkOptions = false;

    // Checks the amount of arguments from the command line.
    if (argc < 4 || argc > 5)
    {
        printUsageStatement();
    }

    /* If there was an option input. It will check if it matches 
    one of the options. */
    if (argc == 5)
    {
        for (i = 0; i < 6; i++)
        {
            if (argv[1] == options[i])
            {
                checkOptions = true;
            }
        }

        // If one of the options wasn't selected, print the usage statement.
        if (!checkOptions)
        {
            printUsageStatement();
        }
        // Checks if the outputtype is correct.
        else if ((strcmp(argv[2], "--binary") != 0) && 
            (strcmp(argv[2], "--ascii") != 0))
            printUsageStatement();
    }
    // If there wasn't an option put in. Checks outputtype.
    else if (argc == 4)
        if ((strcmp(argv[1],"--binary") != 0) && 
            (strcmp(argv[1], "--ascii") != 0))
            printUsageStatement();
   
}



void printUsageStatement()
{
    cout << "Usage: thpExam1.exe [option] --outputtype basename image.ppm" << 
        endl << endl << "Output Type" << endl << "      " <<
        setw(16) << left << "--ascii" << setw(30) << left <<
        "integer text numbers will be written for the data" << endl;
    cout << "      " << setw(16) << left << "--binary";
    cout << setw(30) << left << "integer numbers will be written in " <<
        "binary form" << endl << endl << "Option Code" << "           " <<
        "Option Description" << endl << "      " << setw(16) << left <<
        "--flipX" << setw(30) << left << "Flip the image on the X axis" << endl;
    cout << "      " << setw(16) << left << "--flipY" << setw(30) << 
        left << "Flip the image on the Y axis" << endl;
    cout << "      " << setw(16) << left << "--rotateCw" << setw(30) <<
        left << "Rotate the image clockwise" << endl;
    cout << "      " << setw(16) << left << "--rotateCCW" << setw(30) <<
        left << "Rotate the image counterclockwise" << endl;
    cout << "      " << setw(16) << left << "--grayscale" << setw(30) <<
        left << "Convert the image to grayscale" << endl;
    cout << "      " << setw(16) << left << "--sepia" << setw(30) <<
        left << "Antique a color image" << endl;
    exit(0);
}



bool openInputFile(ifstream &file, string name)
{
    // Opens the file in input or binary mode.
    file.open(name , ios::in | ios::binary);

    // If it doesn't open, it will return a false.
    if( !file.is_open() )
    {
        cout << "Unable to open the input file " << name << endl;
        return false;
    }

    return true;
}



void readImageHCD(ifstream& file, image &thisImage, string tempStr)
{
    // Reads in the header.
    file >> thisImage.magicNumber;
    file.ignore();

    // Reads in the comment(s).
    if (file.peek() == '#')
        getline(file, tempStr);

    (thisImage.comment).append(tempStr);

    while (file.peek() == '#')
    {
        getline(file, tempStr);
        (thisImage.comment).append("\n" + tempStr);
    }

    // Reads in the dimensions.
    file >> thisImage.cols;
    file >> thisImage.rows;

}



void readImageAscii(ifstream &file, image thisImage)
{
    int i, j;
    string tempStr;
    int tempInt;
    int maxNumber;

    //Reads in data before the ascii data.
    file.ignore();
    file >> maxNumber;
    file.ignore();

    file.clear(0);

    //Nested for loop that reads in all the integers in ascii.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            
            getline(file, tempStr);
            tempInt = stoi(tempStr);
            thisImage.redGray[i][j] = tempInt;
            getline(file, tempStr);
            tempInt = stoi(tempStr);
            thisImage.green[i][j] = tempInt;
            getline(file, tempStr);
            tempInt = stoi(tempStr);
            thisImage.blue[i][j] = tempInt;
            
        }
        
    }

    file.clear(0);
}



void outputAscii(ofstream& fout, image thisImage, bool isGray)
{
    int i, j;
    int tempInt;
    int tempStr;

    // Outputs magic number.
    fout << thisImage.magicNumber << endl;

    // Outputs the comments.
    if (thisImage.comment > "")
        fout << thisImage.comment << endl;

    // Outputs the dimensions.
    fout << thisImage.cols << " " << thisImage.rows << endl;
    // Outputs the max data value.
    fout << 255 << endl;

    /* Nested for loop that will output the array values. If isGray is true,
       it will only output the redGray array.*/
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {
            // It will always output this array.
            tempInt = (int)thisImage.redGray[i][j];
            tempStr = tempInt;
            fout << tempStr << endl;

            /* If the outputted image isn't going to be gray, it will output 
               all the arrays.*/
            if (!isGray)
            {
                tempInt = (int)thisImage.green[i][j];
                tempStr = tempInt;
                fout << tempStr << endl;
                tempInt = (int)thisImage.blue[i][j];
                tempStr = tempInt;
                fout << tempStr << endl;
            }
        }
    }
}



bool openOutputFile(ofstream& fout, string name)
{
    fout.open(name, ios::out | ios::binary | ios::ate);

    if (!fout.is_open())
    {
        cout << "Unable to open the output file " << name << endl;
        return false;
    }

    return true;
}



void readImageBinary(ifstream& file, image thisImage)
{
    int i, j;
    int maxNumber;

    // Reads in the data before the binary data.
    file.ignore();
    file >> maxNumber;
    file.ignore();


    file.clear(0);

    // Nested for loop used to read in every data value needed for the arrays.
    for (i = 0; i < thisImage.rows; i++)
    {
        for (j = 0; j < thisImage.cols; j++)
        {

            file.read((char*)&thisImage.redGray[i][j], sizeof(char));
            file.read((char*)&thisImage.green[i][j], sizeof(char));
            file.read((char*)&thisImage.blue[i][j], sizeof(char));

        }

    }

    file.clear(0);
}



void outputBinary( ofstream& fout, image thisImage, bool isGray )
{
    int i, j;

    // Ouputs the magic number.
    fout << thisImage.magicNumber << endl;
    
    // Outputs the comments.
    if ( thisImage.comment > "" )
        fout << thisImage.comment << endl;

    // Outputs the dimensions.
    fout << thisImage.cols << " " << thisImage.rows << endl;

    // Outputs the maximum pixel value.
    fout << 255 << '\n';

    // Nested forloop that's used to write the data.
    for ( i = 0; i < thisImage.rows; i++ )
    {
        for ( j = 0; j < thisImage.cols; j++ )
        {
            fout.write( (char*)&thisImage.redGray[i][j], sizeof(char) );
            // Will only output these two arrays if the image is grayscaled.
            if ( !isGray )
            {
                fout.write( (char*)&thisImage.green[i][j], sizeof(char) );
                fout.write( (char*)&thisImage.blue[i][j], sizeof(char) );
            }
            

        }
    }
}



void mainOutput( ofstream& fout, image thisImage, bool isGray, string type )
{
    if ( type == "--ascii" )
    {   
        thisImage.magicNumber = "P3";
        if ( isGray )
            thisImage.magicNumber[1] = thisImage.magicNumber[1] - 1;
        outputAscii(fout, thisImage, isGray);
    }

    else if ( type == "--binary" )
    {   
        thisImage.magicNumber = "P6";
        if ( isGray )
            thisImage.magicNumber[1] = thisImage.magicNumber[1] - 1;
        outputBinary( fout, thisImage, isGray );
    }
}