// ICPC Challenge Practice 2020 Solution 1
// Author: Dustin Ward
//
// This is my first solution to the ICPC Challenge Practice part B.
//
// The problem was to find the largest possible independent set in a given
// graph. (Independent meaning the set cannot contain two vertices that are
// directly connected by an edge in the graph). The score you receive is 
// based on the size of the set you find.
//
// My approach in this version was to simply include node 1 in my set, then
// mark all its neighbors as unavailable. I would then scan for the next
// unmarked node, and repeat the process. The end result would be a maximal
// independent set that includes node 1. The scores I acheived with this
// program are as follows:
//
// B1: 2480
// B2: 31736
// B3: 30301
// B4: 50316

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    // Getting problem set from the command line
    string filename;
    if(argc < 2) {
        cout<<"Error! No problem name supplied."<<endl;
        cout<<"Usage: ./Bv1 <problem>"<<endl;
        return 0;
    }
    else
        filename = argv[1];
    
    // Show filename
    cout<<"Filename: "<<filename+".in/out"<<endl;

    // Opening input and output filestreams
    ifstream ifs;
    ifs.open(filename + ".in");
    ofstream ofs;
    ofs.open(filename + ".out");

    // Input vertices and Edges
    int V, E; ifs>>V>>E;

    // Building the Graph
    vector<vector<int>> G(V);
    for(int i=0; i<E; i++) {
        int x, y; ifs>>x>>y;

        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    // Generating the set with the process described at the top of this file
    int K = 0;
    vector<int> X(V, -1);
    for(int i=V-1; i>=0; i--) {
        if(X[i] == 0) continue;
        X[i] = 1;
        K++;
        for(int j=0; j<G[i].size(); j++) {
            X[G[i][j]] = 0;
        }    
    }

    // Writing answer to file
    ofs<<K<<endl;
    for(int i=0; i<V; i++)
        ofs<<X[i]<<" ";

    // Closing filestream
    ifs.close();
    ofs.close();
}