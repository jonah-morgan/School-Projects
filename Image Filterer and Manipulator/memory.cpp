/** **********************************************************************
* @file
* 
* @brief Allocation and deletion of arrays. Closing of files..
************************************************************************/
#include "netPBM.h"



pixel** alloc2d(int rows, int cols)
{
    int i, j;
    pixel** ptr2d = nullptr;
    ptr2d = new (nothrow) pixel * [rows];

    if (ptr2d == nullptr)
    {
        cout << "Memory Allocation Error." << endl;
        exit(0);
    }

    for (i = 0; i < rows; i++)
    {
        ptr2d[i] = new (nothrow) pixel[cols];

        if (ptr2d[i] == nullptr)
        {
            cout << "Memory Allocation Error." << endl;
            for (j = 0; j < i; j++)
                delete[] ptr2d[j];
            delete[] ptr2d;
            exit(0);
        }
    }

    return ptr2d;
}



void delete2d(pixel** &arr, int rows)
{
   int i;
   if (arr == nullptr)
       return;

   for (i = 0; i < rows; i++)
    {
        delete [] arr[i]; 
        arr[i] = nullptr;
    }
    
    delete [] arr;
    arr = nullptr;
}



void deleteAllArr(image& thisImage)
{
    // The three function calls that free up all memory for the pixel arrays.
    delete2d(thisImage.redGray, thisImage.rows);
    delete2d(thisImage.green, thisImage.rows);
    delete2d(thisImage.blue, thisImage.rows);
}



void allocateAllArr(image& thisImage)
{
    // The three function calls which allocate all the 2D pixel arrays.
    thisImage.redGray = alloc2d(thisImage.rows, thisImage.cols);
    thisImage.green = alloc2d(thisImage.rows, thisImage.cols);
    thisImage.blue = alloc2d(thisImage.rows, thisImage.cols);
}



void closeEverything(ifstream& file, ofstream& fout, image& thisImage)
{
    file.close();
    fout.close();

    deleteAllArr(thisImage);
}