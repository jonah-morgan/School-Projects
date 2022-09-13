// 				Christer Karlsson
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long int count = 0;

long long int puzzle(long long int N) {
    count++;

    if (N==1)
        return (1);
    if ((N%2) == 0)
        return puzzle(N/2);
    else
        return puzzle(3*N+1);
}

int main() {
    long int N=0;
    long long int answer;

    do {
        count = -1;
        cout << "Enter an N: ", cin >> N, cout << N << "\t";

        auto start = high_resolution_clock::now();
        answer=puzzle(N);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);


        cout << count << " , " << answer << endl;
        cout << "Running time: " << duration.count() << " microseconds"
            << endl;
    } while(cin);

    return(0);
}

/*       ////// ANSWERS TO QUESTIONS //////
 *      ///////////////////////////////////
 *
 *
 *  1.  What does the variable count do?
 *
 *      - It counts the amount of recursive calls the function does.
 *
 *  2.  What are the run times for all the test cases in longest.txt?
 *
 *      - In order: 0m, 1m, 1m, 5m, 7m
 *
 *  3.  Is it possible to say anything about the order (Big-Oh) of the
 *      puzzle function?
 *
 *      -
 *
 *
 *
 *
 *
 */