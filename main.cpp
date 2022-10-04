#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4){
        cerr << "Error: Should have 3 parameters passed into SIM. Check project description to determine the 3 inputs." << endl;
        exit(-1);
    }

    // reading in file names for SIM
    string randNumFileName = argv[1];
    int numReplications = stoi(argv[2]);
    string sanFileName = argv[3];
}