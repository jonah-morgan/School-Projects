#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

// Function Interface
void printShortestPath(int n, std::vector<int> pred, int &cost);
void solveMaze(std::vector<int> &pred, std::vector<std::vector<int>> &vertices,
               int &forwardPos, int &exitPos, int &locationPos);



// Main Function
int main(int argc, char **argv) {
    std::ifstream fin;
    std::string filename = argv[1];

    // I'm using a 2D int vector to store my vertices.
    std::vector<std::vector<int>> vertices;
    std::vector<int> pred;

    // The first location will always be 0.
    int locationPos = 0;
    int exitPos;
    int forwardPos;

    // Opens the file specified in argv[1], quits the program if it doesn't open.
    fin.open(filename);
    if(!fin.is_open()){
        std::cout << "Couldn't open the file " << filename << "\n";
        return 1;
    }

    // Get the first position to step into, and the position to exit the maze.
    fin >> forwardPos;
    fin >> exitPos;

    // Update vertices with the first step input from the file.
    std::vector<int> firstStep;
    firstStep.push_back(forwardPos);
    pred.push_back(-1);
    vertices.push_back(firstStep);


    /* While loop goes through each vertice given by a file. Also initializes
     * Predecessor array to all -1's.                                       */
    int idx, connection;
    while(fin >> idx){
        std::vector<int> thisIndex;
        while((fin >> connection) && connection != -1){
            thisIndex.push_back(connection);
        }
        thisIndex.push_back(-1);
        vertices.push_back(thisIndex);
        pred.push_back(-1);
    }

    // Solve the maze.
    solveMaze(pred, vertices, forwardPos, exitPos, locationPos);

    // Use recursive function to print out the shortest path.
    int cost = 0;
    std::cout << "\nShortest path in the maze: " << filename << "\n";
    std::cout << "\nStart -> ";
    printShortestPath(exitPos, pred, cost);
    std::cout << "Exit\n\n" << "Cost: " << cost << "\n";

    fin.close();
    return 0;
}


void printShortestPath(int n, std::vector<int> pred, int &cost){
    if(n == 0){
        cost++;
        return;
    }
    printShortestPath(pred[n], pred, cost);
    if(cost % 10 + 1 == 1)
        std::cout << "\n";
    std::cout << n << " -> ";
    cost++;
}


void solveMaze(std::vector<int> &pred, std::vector<std::vector<int>> &vertices,
               int &forwardPos, int &exitPos, int &locationPos) {
    // I use a queue of integer vectors to store my work orders.
    std::queue<std::vector<int>> workOrders;
    while(locationPos != exitPos){

        /*  This first for loop creates work orders based on the forward position.
         *  If the location has already been visited, then we don't need to add it
         *  as a work order. */
        std::vector<int> workOrder;
        for(int i = 0; vertices[forwardPos][i] != -1 && pred[forwardPos] == -1; i++){
            workOrder.push_back(forwardPos);
            workOrder.push_back(vertices[forwardPos][i]);
            workOrders.push(workOrder);
            workOrder.clear();
        }

        // Update the predecessor array.
        if(pred[forwardPos] == -1)
            pred[forwardPos] = locationPos;

        // No more work orders = DONE!
        if(workOrders.empty())
            break;

        // Update variables with the next work order.
        locationPos = workOrders.front()[0];
        forwardPos = workOrders.front()[1];

        workOrders.pop();
    }
}
