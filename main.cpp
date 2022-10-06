#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

double readToken(ifstream randFile);

struct GraphNode{
    int val;
    bool beenVisited = false;
};

int main(int argc, char* argv[]){
    if(argc != 4){
        cerr << "Error: Should have 3 parameters passed into SIM. Check project description to determine the 3 inputs." << endl;
        exit(-1);
    }

    // reading in file names for SIM and opening files
    string randNumFileName = argv[1];
    int numReplications = stoi(argv[2]);
    string sanFileName = argv[3];

    ifstream randNums(randNumFileName);
    if(randNums.fail()){
        cerr << "Error: Failure opening file with random values." << endl;
        exit(-1);
    }

    ifstream sanFile(sanFileName);
    if(sanFile.fail()){
        cerr << "Error: Failure opening SAN description file." << endl;
        exit(-1);
    }

    double origin, dest, upper_bound;

    map<int, vector< pair<int, int> > > graph;

    while(sanFile >> origin >> dest >> upper_bound){
        pair<int, int> newPair(dest, upper_bound);

        graph[origin].push_back(newPair);
    }
}