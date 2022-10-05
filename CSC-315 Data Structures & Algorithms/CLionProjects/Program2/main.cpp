#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int main(int argc, char **argv) {
    std::ifstream fin;
    std::string filename = argv[1];
    std::vector<std::vector<int>> workOrders;
    std::vector<int> temp;
    temp.push_back(-1);
    workOrders.push_back(temp);
    int i, j;
    int size = 1;

    fin.open(filename);
    if(!fin.is_open()){
        std::cout << "Couldn't open the file " << filename << "\n";
        exit(1);
    }

    int idx, connection;
    while(fin >> idx){
        std::vector<int> thisIndex;
        while((fin >> connection) && connection != -1){
//            std::cout << "\nindex: "<< idx << "\nConnections: " <<
//                connection << std::endl;
            thisIndex.push_back(connection);
        }
        thisIndex.push_back(-1);
        workOrders.push_back(thisIndex);
        size++;
    }

    int* pred = new int(size);
    for(i = 0; i < size; i++){
        pred[i] = -1;
    }



    return 0;
}
