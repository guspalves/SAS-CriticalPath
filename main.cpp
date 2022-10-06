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

vector< pair<vector<int>, double> > possiblePaths;
map<int, vector< pair<int, double> > > graph;

double readNextNum(double weight);
void findPaths(int origin, int dest);
void DFS(int origin, int dest, double runningSum, vector<int>& path);

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
        pair<int, double> newPair(dest, upper_bound);

        graph[origin].push_back(newPair);
        graph[dest];
        
        // finding the origin and destination for the graph
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

    int pathSize = possiblePaths.size();

    vector<int> counterArray(pathSize, 0);

    // figuring out which path had the max distance
    double maxDistance = -DBL_MAX;
    int maxIndex = 0;
    int currIndex = 0;

    for(auto path : possiblePaths){
        if(path.second > maxDistance){
            maxIndex = currIndex;
            maxDistance = path.second;
        }
        currIndex++;
    
    }

    counterArray[maxIndex]++;

    // /**
    //  * @brief Delete this
    //  * 
    //  */
    // for(int i = 0; i < numReplications; i++){
    //     int maxIndx = 0;
    //     double currMax = -DBL_MAX;

    //     for(int j = 0; j < possiblePaths.size(); j++){
    //         vector<int> currPath = possiblePaths[j].first;

    //         double currentSum = 0.0;

    //         for(int k = 0; k < currPath.size() - 1; k++){
    //             int origin = currPath[k];
    //             int dest = currPath[k+1];
    //             vector< pair<int, double> > adjList = graph[origin];
    //             for(auto x : adjList){
    //                 if(x.first == dest){
    //                     currentSum += readNextNum(x.second);
    //                     break;
    //                 }
    //             }
    //         }

    //         if(currentSum > currMax){
    //             currMax = currentSum;
    //             maxIndx = j;
    //         }
    //     }

    //     counterArray[maxIndx]++;
    // }
    

    for(int i = 1; i < numReplications; i++){
        possiblePaths.clear();
        findPaths(min, max); // always find paths in the exact same order

        // figuring out which path had the max distance
        maxDistance = -DBL_MAX;
        maxIndex = 0;
        currIndex = 0;

        for(auto path : possiblePaths){
            if(path.second > maxDistance){
                maxIndex = currIndex;
                maxDistance = path.second;
            }

            currIndex++;
        }

        counterArray[maxIndex]++;
    }

    // printing output
    for(int i = 0; i < counterArray.size(); i++){
        cout << "OUTPUT    :";

        vector<int> temp = possiblePaths[i].first;

        for(int i = 1; i < temp.size(); i++){
            cout << "a" << temp[i-1] << "/" << temp[i];

            if(i + 1 >= temp.size()) cout << ":";
            else cout << ",";
        }

        cout << "\t" << (double) counterArray[i] / (double) numReplications << endl;
    }

    // closing the random number file
    randNums.close();
}

double readNextNum(double weight){
    double test = 0.0;
    if(randNums >> test) return (test * weight);
    else{
        cerr << "Ran out of random numbers." << endl;
        exit(1);
    }
}

void findPaths(int origin, int dest){
    vector<int> currPath;
    currPath.push_back(origin);
    double runningSum = 0.0;
    DFS(origin, dest, runningSum, currPath);
}

void DFS(int origin, int dest, double runningSum, vector<int>& path){
    if(origin == dest){
        pair<vector<int>, double> temp(path, runningSum);
        possiblePaths.push_back(temp);
        return;
    }
    
    for (auto node : graph[origin]){
        path.push_back(node.first);
        double randNum = readNextNum(node.second);
        // double randNum = 0.0;
        runningSum += randNum;
        DFS(node.first, dest, runningSum, path);
        runningSum -= randNum;
        path.pop_back();
    }
}