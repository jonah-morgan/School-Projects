/** **********************************************************************
* @file
*
* @author Jonah Morgan
* @brief Main .cpp File
************************************************************************/

/** ***************************************************************************
* @mainpage thpe3 - Knights Tour
*
* @section sec1 Course Information:
*
* @author Jonah Morgan
*
* @date Due: 4 / 20 / 22
*
* @par Professor:
* Roger Schrader
*
* @par Course:
* CSC-215 "Programming Techniques"
*
* @par Assignment:
* thpExam3
*
* @par Location:
* Classroom Building - 329
*
* @section sec2 Program Information:
*
* @details
* @par
* The goal of the program is to find the solution for the "Knights Tour" 
* Problem. It will brute force a solution to see if it's possible for the
* knight to hit every position on the chess board, and it will display the
* output of the solution found (if it was found).
* @par
* First, the program checks the arguments the user input on the command line.
 *  If the arguments satisfy the usage statement, it will run one of two 
 *  algorithms. The first algorithm will output a menu the user can use to
 *  manipulate the size of the chess board and the starting position for the 
 *  knight. After the user exits the menu, they will be met with the solution
 *  (if one exists).
 * 
 *  @par
 *  If the user input a input file name on the command line. The second
 *  algorithm will be executed. This algorithm will open an output file called
 *  "Solution.tours" in the directory of the program. It will then read from the
 *  input file and run however many tours are specified from that input, and will
 *  output them to the output file. 
 * 
 *  @par
 *  After the program has ran one of the two algorithms. It will close files if
 *  needed and clean up all dynamic memory.
*
* @section sec3 Compiling and Usage:
*
* @par Usage:
* @verbatim
  Usage Statement
  Usage: thpe3.exe tourfile

    tourfile (optional): The file with tour data.
    If no tour file specified, a menu will be used.



  @endverbatim
* @par Compiling:
*   None.
*
* @section tb_timeline_section Todo, Bugs, Timeline:
* @par Modifications and Development Timeline:
* Visit gitlab commit log for timeline
* <a href="https://gitlab.cse.sdsmt.edu/7503314/csc215s22programs/-/pipelines">
* here.</a>
******************************************************************************/



// Start of code
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

//prototypes
void startMenu(int& n, int& x, int& y);
int mainMenu(int& n, int& x, int& y);

void openInput(fstream& fin, string name);
void openOutput(ofstream& fout, string name);

int** alloc2d(int n);
void delete2d(int** arr, int n);
void padArr(int** arr, int n);
void printArr(int** arr, int n, stringstream& fout);

void move(int** arr, int n, int x, int y, int& count,
          bool& found, stringstream& fout);

void printUsage();
void algoOne();
void algoTwo(char** argv);



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  This function checks the arguments the user input on the command line.
 *  If the arguments satisfy the usage statement, it will run one of two 
 *  algorithms. The first algorithm will output a menu the user can use to
 *  manipulate the size of the chess board and the starting position for the 
 *  knight. After the user exits the menu, they will be met with the solution
 *  (if one exists).
 * 
 *  @par
 *  If the user input a input file name on the command line. The second
 *  algorithm will be executed. This algorithm will open an output file called
 *  "Solution.tours" in the directory of the program. It will then read from the
 *  input file and run however many tours are specified from that input, and will
 *  output them to the output file. 
 * 
 *  @par
 *  After the program has ran one of the two algorithms. It will close files if
 *  needed and clean up all dynamic memory.
 *
 *
 *  @param[in] argc the amount of arguments used to run the program.
 *  @param[in] argv the 2D character array that contains the arguments.
 *
 *  @returns An int that will always be zero to show the program has stopped.
 *
 *  @par Example
 *  @verbatim
 
    See usage statement on the mainpage.

    @endverbatim
 ************************************************************************/
int main(int argc, char** argv)
{
    // arg check
    if (argc < 1 || argc > 2)
        printUsage();
    // option 1
    if (argc == 1)
        algoOne();
    // option 2
    else if (argc == 2)
        algoTwo(argv);

    return 0;
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  First, this algorithm will output a menu to the user so that the user can
 *  manipulate the size of the chess board and the position of the knight. 
 *  After the user exits the menu, the correct dynamic memory will be allocated
 *  for the board. Then, the board will be "padded" with -1's around the border
 *  so that the knight doesn't escape the array and create an error. Then 
 *  the knight will test every move possible on the provided board and starting
 *  position. If every position on the board is touched, it will be outputted to
 *  the console (it will also output a statement if there was no solution). Finally,
 *  the dynamic memory will be cleaned.
 *
 *
 *
 *  @par Example
 *  @verbatim
 
    if(argc == 1)
        algoOne(); // The first algorithm is ran.

    @endverbatim
 ************************************************************************/
void algoOne()
{
    int n = 8;
    int x = 7;
    int y = 7;
    int** arr = nullptr;
    int count = 1;
    int tour = 1;
    stringstream fout;
    bool found = false;

    // shows the main menu
    startMenu(n, x, y);
    n += 4;
    x += 2;
    y += 2;

    arr = alloc2d(n);
    padArr(arr, n);

    cout << endl << "Tour: " << tour << endl;
    cout << "        " << n - 4 << "x" << n - 4 << " starting " <<
        "(" << x - 2 << "," << y - 2 << ")";

    // finds the first solution of knight moves
    move(arr, n, x, y, count, found, fout);

    cout << fout.str();

    if (!found)
        cout << endl << "        No solutions for this case." << endl;

    // cleans array
    delete2d(arr, n);

}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  First, the algorithm will open the input and output files. Then, it
 *  will enter a while loop that will keep looping until there is no more
 *  input to be had from the file. Inside this while loop, it will
 *  get inputs for the size of the board, and the position for the knight.
 *  After getting input, the algorithm will allocate memory for the 2D 
 *  board array, and pad the board with -1's so that the knight doesn't 
 *  go out of bounds. The algorithm will then run the move function which
 *  uses a brute force algorithm to find a single solution where the knight
 *  lands on every position. It will then output the solution (if it exists)
 *  to "Solution.tours" file, making sure all output is appended. Finally, 
 *  at the end of the while loop, it will reset all counters and increment 
 *  i, which represents the tours. When there is no more input, the algorithm
 *  will close both of the files.
 *
 *
 *  @param[in] argv the 2D character array that contains the arguments.
 * 
 *  @par Example
 *  @verbatim
 
    if(argc == 2)
        algoTwo(); // The second algorithm is ran.

    @endverbatim
 ************************************************************************/
void algoTwo(char** argv)
{
    int n, x, y;
    int count = 1;
    int tour = 1;
    bool found = false;
    int** arr = nullptr;
    stringstream fout;
    fstream fin;
    ofstream foutFile;

    // opens input and output files
    openInput(fin, argv[1]);
    openOutput(foutFile, "Solutions.tours");

    // while loop that runs while there is input
    int i = 1;
    while (fin >> n)
    {
        // input from the file
        fin.ignore();
        fin >> x; fin >> y;
        fin.ignore();
        n += 4; x += 2; y += 2;

        arr = alloc2d(n);
        padArr(arr, n);
        // finds the solution if it exists
        move(arr, n, x, y, count, found, fout);

        foutFile << "Tour: " << i << endl;
        foutFile << "        " << n - 4 << "x" << n - 4 << " starting " <<
            "(" << x - 2 << "," << y - 2 << ")";

        // outputs the solution if it existed
        foutFile << fout.str();
        if (!found)
            foutFile << endl << "        No solutions for this case." << endl;

        foutFile << endl;
        fout.str("");
        fout.clear();

        // cleans memory and resets counters
        delete2d(arr, n);
        count = 1;
        found = false;

        i++;
    }

    // closes files
    fin.close();
    foutFile.close();
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Opens the file for input.
 *
 *
 *  @param[in, out] fin the input stream to open the file to.
 *  @param[in] name the name of the file to open.
 *
 *  @par Example
 *  @verbatim
 
    fstream fin;
    string name = "filename.txt";
    openInput(fin, name); // will open the input file.

    @endverbatim
 ************************************************************************/
void openInput(fstream& fin, string name)
{
    fin.open(name + ".pz", ios::in | ios::out | ios::app);
    if (!fin.is_open())
    {
        cout << "Could not open file: " << name << endl;
        exit(0);
    }
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Opens the file for output.
 *
 *
 *  @param[in, out] fout the output stream to write to.
 *  @param[in] name the name of the file to open.
 *
 *  @par Example
 *  @verbatim
 
    ofstream fout;
    string name = "filename.txt";
    openOutput(fout, name); // will open the output file.

    @endverbatim
 ************************************************************************/
void openOutput(ofstream& fout, string name)
{
    fout.open(name, ios::app);
    if (!fout.is_open())
    {
        cout << "Could not open file: " << name << endl;
        exit(0);
    }
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Prints the usage statement.
 *
 *  @par Example
 *  @verbatim
 
    printUsage(); // will print the usage statement.

    @endverbatim
 ************************************************************************/
void printUsage()
{
    // prints the usage statement
    cout << "Usage: thpe3.exe tourfile\n\n" <<
        "    tourfile (optional): The file with tour data.\n" <<
        "    If no tour file specified, a menu will be used.\n";
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  While the input is invalid, it will output the main menu which displays
 *  all valid options the user could input. If the input is valid, it will
 *  return the choice the user input.
 *
 *
 *  @param[in, out] n the size of the board
 *  @param[in, out] x the x coordinate for the starting position.
 *  @param[in, out] y the y coordinate for the starting position.
 *
 *  @returns an integer that represents the valid choice the user made.
 * 
 *  @par Example
 *  @verbatim
 
    int n = 6;
    int x = 0;
    int y = 4;
    mainMenu(n, x, y); // Will open the main menu.

    @endverbatim
 ************************************************************************/
int mainMenu(int& n, int& x, int& y)
{
    string choice;
    int i;
    int choiceInt;
    bool invalid = true;

    // base case is that input is invalid
    while (invalid)
    {
        invalid = false;

        // outputs the main menu
        cout << "  1) Change Board Size from " << n << "x" << n << '\n' <<
            "  2) Change starting location from [" << x << "," <<
            y << "]" << endl << "  3) Exit and Solve Tour" << endl <<
            "Enter Choice: ";

        // gets input from the user
        cin >> choice; cout << endl;
        cin.clear();
        cin.ignore(256, '\n');

        // checks if the input is valid
        for (i = 0; i < choice.length(); i++)
        {
            if (!isdigit(choice[i]) && !(choice[i] == ' '))
            {
                cout << "Unusable input. Please try again." << endl;
                invalid = true;
                break;
            }
        }
    }

    invalid = true;
    // returns the valid choice the user inputted
    return (choiceInt = stoi(choice));
}                                  



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  This function will open the main menu using the mainMenu function. Which
 *  will get input from the user to decide which case in the switch statement
 *  to execute. If the choice is 1, it will allow the user to 
 *  change the size of the board. If the choice is 2, it will allow the user
 *  to change the starting postion of the knight. Finally, if the choice is
 *  3, it will exit the menu to continue the program.
 *
 *
 *  @param[in, out] n the size of the board
 *  @param[in, out] x the x coordinate for the starting position.
 *  @param[in, out] y the y coordinate for the starting position.
 *
 *
 *  @par Example
 *  @verbatim

    int n = 6;
    int x = 0;
    int y = 4;
    startMenu(n, x, y); // Will open the start menu.

    @endverbatim
 ************************************************************************/
void startMenu(int& n, int& x, int& y)
{
    int originN = n;
    int originX = x;
    int originY = y;

    string strN;
    string choice;
    int choiceInt;
    bool menu = true;

    // loop will run until case 3 is executed
    while (menu)
    {
        // gets input from the user
        choiceInt = mainMenu(n, x, y);

        switch (choiceInt)
        {
        // this case allows the user to change the size of the board
        case 1:
            cout << "enter the size of the nxn board (>3): ";
            cin >> n;
            cout << endl;
            if ((n < x || n < y) || n < 4)
            {
                cout << "n cannot be set to that. try again..." << "\n\n";
                n = originN;
            }
            break;

        // this case allows the user to change the starting position
        case 2:
            cout << "Enter Starting Coordinates [ row , col ]: ";
            cin >> x >> y;
            cout << endl;
            if ((x > n) || (y > n))
            {
                cout << "The position can't be set to that. Try again..." << "\n\n";
                x = originX;
                y = originY;
            }
            break;

        // this case will exit the menu
        case 3:
            menu = false;
            break;
        }
    }
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Creates a dynamic 2d array.
 *
 *
 *  @param[in] n the size of the board
 *
 *  @returns a dynamic 2D integer array of size n * n.
 *
 *  @par Example
 *  @verbatim
 
    int n = 10;
    int** arr = nullptr;
    arr = alloc2d(n); // will allocate a dynamic 2d array.

    @endverbatim
 ************************************************************************/
int** alloc2d(int n)
{
    int i, j;
    int** arr2d = new (nothrow) int* [n];

    if (arr2d == nullptr)
    {
        cout << "Memory Allocation Error." << endl;
        exit(0);
    }

    for (i = 0; i < n; i++)
    {
        arr2d[i] = new (nothrow) int[n];
        if (arr2d[i] == nullptr)
        {
            cout << "Memory Allocation Error." << endl;
            for (j = 0; j < i; j++)
                delete arr2d[j];
            delete *arr2d;
        }
    }

    return arr2d;
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Deletes a dynamic 2d array.
 *
 *
 *  @param[in] n the size of the board
 *  @param[in, out] arr the array to be deleted
 *
 *
 *  @par Example
 *  @verbatim

    int n = 10;
    int** arr = nullptr;
    arr = alloc2d(n); // will allocate a dynamic 2d array.
    delete2d(arr); // will delete the array.

    @endverbatim
 ************************************************************************/
void delete2d(int** arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
        delete arr[i];
    delete arr;
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Pads the 2d that represents the chess board with -1's around the edges.
 *  The thickness of the padding is always 2. If it's not a padded spot, it
 *  will be designated with a 0.
 *
 *
 *  @param[in] n the size of the board
 *  @param[in, out] arr the array to be padded
 *
 *
 *  @par Example
 *  @verbatim

    int n = 10;
    int** arr = nullptr;
    arr = alloc2d(n); // will allocate a dynamic 2d array.
    padArr(arr, n); // will pad the array.

    @endverbatim
 ************************************************************************/
void padArr(int** arr, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            // check rows
            if (i == 0 || i == 1 || i == n - 2 || i == n - 1)
                arr[i][j] = -1;

            // check columns
            else if (j == 0 || j == 1 || j == n - 2 || j == n - 1)
                arr[i][j] = -1;

            // not a padded spot
            else
                arr[i][j] = 0;
        }
    }
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Prints the 2d dynamic array.
 *
 *
 *  @param[in] n the size of the board
 *  @param[in, out] arr the array to be printed
 *  @param[in, out] fout the stringstream to be written to
 *
 *
 *  @par Example
 *  @verbatim

    int n = 10;
    stringstream fout;
    int** arr = nullptr;
    arr = alloc2d(n); // will allocate a dynamic 2d array.
    printArr(arr, n, fout); // will print the array.

    @endverbatim
 ************************************************************************/
void printArr(int** arr, int n, stringstream& fout)
{
    int i, j;
    fout.clear();
    fout.str("");
    // nested for loop that only outputs the inner array
    for (i = 2; i < n - 2; i++)
    {
        for (j = 2; j < n - 2; j++)
        {
            
            if (j == 2)
                fout << '\n' << "        ";
            fout << setw(4) << left << arr[i][j];
        }
    }

    fout << endl;
}



/** **********************************************************************
 * @author Jonah Morgan
 *
 *  @par Description
 *  Will go through every possible move the knight can do on the specified
 *  chess board. If the solution is found. The function will return. If the
 *  solution isn't found and the current amount of moves the knight has done
 *  is larger than the preestablished maximum, it will the new maximum equal
 *  to the current amount of moves. If the amount of moves equals 
 *  (n-4) * (n-4) + 1, that means a solution has been found. This sets the
 *  boolean to true so that all subsequent calls know not to gather anymmore
 *  permutations. It will also print the solution. However, if the array
 *  at the current position is 0, it will try to move in every possible
 *  direction a knight can move in.
 * 
 *
 *
 *  @param[in] n the size of the board
 *  @param[in] x the x coordinate of the starting position
 *  @param[in] y the y coordinate of the starting position
 *  @param[in, out] arr the array to be printed
 *  @param[in, out] fout the stringstream to be written to
 *  @param[in, out] count the count to be checked
 *  @param[in, out] found the boolean to be checked
 *
 *
 *  @par Example
 *  @verbatim

    int n = 10;
    int count = 0;
    bool found = false;
    stringstream fout;

    int** arr = nullptr;
    arr = alloc2d(n); // will allocate a dynamic 2d array

    move(arr, n, x, y, count, found, fout); // will find the solution.

    @endverbatim
 ************************************************************************/
void move(int** arr, int n, int x, int y, int& count,          
    bool& found, stringstream& fout)
{
    // if a solution was already found, just exit this function
    if (found)
        return;

    // if the count is equal to the condition below, a solution was found
    if (count == ((n - 4) * (n - 4)) + 1)
    {
        found = true;
        // print the array
        printArr(arr, n, fout);
        return;
    }

    if(arr[x][y] == 0)
    {
        // set the position to the counter and then increment it
        arr[x][y] = count;
        count++;

        // tests all movement positions
        move(arr, n, x + 1, y - 2, count, found, fout);
        move(arr, n, x + 2, y - 1, count, found, fout);
        move(arr, n, x + 2, y + 1, count, found, fout);
        move(arr, n, x + 1, y + 2, count, found, fout);
        move(arr, n, x + 1, y + 2, count, found, fout);
        move(arr, n, x - 1, y + 2, count, found, fout);
        move(arr, n, x - 2, y + 1, count, found, fout);
        move(arr, n, x - 2, y - 1, count, found, fout);
        move(arr, n, x - 1, y - 2, count, found, fout);

        // resets the position to not used and decrement the counter
        count--;
        arr[x][y] = 0;
    }
}



