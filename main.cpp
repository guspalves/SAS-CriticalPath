/**
 * @authors Gus Alves, Riley Barton
 * 
 * @ref
 * To generate all paths from a graph, the following implementation was used:
 * https://www.algotree.org/algorithms/tree_graph_traversal/depth_first_search/all_paths_in_a_graph/
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <float.h>

using namespace std;

ifstream randNums;
ifstream sanFile;

vector< vector<int> > possiblePaths;
map<int, vector< pair<int, int> > > graph;

double readNextNum();
void findPaths(int origin, int dest);
void DFS(int origin, int dest, vector<int>& path);

int main(int argc, char* argv[]){
    if(argc != 4){
        cerr << "Error: Should have 3 parameters passed into SIM. Check project description to determine the 3 inputs." << endl;
        exit(-1);
    }

    // reading in file names for SIM and opening files
    string randNumFileName = argv[1];
    int numReplications = stoi(argv[2]);
    string sanFileName = argv[3];

    randNums.open(randNumFileName);
    if(randNums.fail()){
        cerr << "Error: Failure opening file with random values." << endl;
        exit(-1);
    }

    sanFile.open(sanFileName);
    if(sanFile.fail()){
        cerr << "Error: Failure opening SAN description file." << endl;
        exit(-1);
    }

    double origin, dest, upper_bound;
    double min(DBL_MAX), max(-DBL_MAX);

    while(sanFile >> origin >> dest >> upper_bound){
        pair<int, int> newPair(dest, upper_bound);

        graph[origin].push_back(newPair);
        graph[dest];

        if(origin < min){
            min = origin;
        }
        if(dest < min){
            min = dest;
        }

        if(origin > max){
            max = origin;
        }
        if (dest > max){
            max = dest;
        }
    }

    // closing san file since we no longer need to read in the paths
    sanFile.close();

    findPaths(min, max);
    cout << min << " " << max << endl;

    for(auto x : possiblePaths){
        cout << "Path: ";
        for(auto node : x){
            cout << node << " ";
        }
        cout << endl;
    }
}

double readNextNum(){
    double test = 0.0;
    if(randNums >> test) return test;
    else exit(1);
}

void findPaths(int origin, int dest){
    possiblePaths.clear();

    vector<int> currPath;
    currPath.push_back(origin);
    DFS(origin, dest, currPath);
}

void DFS(int origin, int dest, vector<int>& path){
    if(origin == dest){
        possiblePaths.push_back(path);
    } else {
        for (auto node : graph[origin]){
            path.push_back(node.first);
            DFS(node.first, dest, path);
            path.pop_back();
        }
    }
}