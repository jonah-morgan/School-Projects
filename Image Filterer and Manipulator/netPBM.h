/** **********************************************************************
* @file
*
* @brief Function and Structure Prototypes. Typedefs..
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;


/************************************************************************
 *             Constant Variables, defines and Enums
 ***********************************************************************/
#ifndef __NETPBM__H__
#define __NETPBM__H__


typedef unsigned char pixel;

struct image
{
    string magicNumber;

    string comment;

    int rows;

    int cols;

    pixel** redGray;

    pixel** green;

    pixel** blue;
};

/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/

// File I/O, Argument checking functions.
void checkArgs( int argc, char** argv, string options[] );
void printUsageStatement();

bool openInputFile( ifstream &file, string name );
bool openOutputFile( ofstream& fout, string name );

void readImageHCD( ifstream &file, image &thisImage, string tempStr );
void readImageAscii( ifstream& file, image thisImage );
void readImageBinary( ifstream& file, image thisImage );

void outputAscii( ofstream& fout, image thisImage, bool isGray );
void outputBinary( ofstream& fout, image thisImage, bool isGray );

void mainOutput( ofstream& fout, image thisImage, bool isGray, string type );

// Allocation, Closing functions.
pixel** alloc2d( int rows, int cols );
void allocateAllArr( image& thisImage );

void deleteAllArr( image &thisImage );
void delete2d( pixel** &arr, int rows );

void closeEverything( ifstream& file, ofstream& fout, image& thisImage );

// Image Operation Functions.
void applyOption( image &thisImage, string option );

void flipImageX( image &thisImage );
void flipImageY( image &thisImage );

void rotateImageCW( image &thisImage );
void rotateImageCCW( image& thisImage );

void grayscaleImage( image &thisImage );
void sepiaImage( image& thisImage );

#endif

