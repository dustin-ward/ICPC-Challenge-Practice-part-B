// ICPC Challenge Practice 2020 Judging Program
// Author: Dustin Ward
//
// A simple program to check the correctness of any given solution to the
// 2020 ICPC Challenge Practice part B. This problem involved finding the
// largest independant set in a given graph. The official contest stopped
// judging solutions after the time was up, so I made this program to help
// me continue work on better solutions.

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    // Getting problem set from command line
    string filename;
    if(argc > 1)
        filename = argv[1];
    else {
        cout<<"Error! No problem name supplied."<<endl;
        cout<<"Usage: ./Judge <problem>"<<endl;
        return 0;
    }

    // Opening the input and answer filestreams
    ifstream ifs1;
    ifs1.open(filename + ".in");
    ifstream ifs2;
    ifs2.open(filename + ".out");

    // Input vertices and Edges
    int V, E; ifs1>>V>>E;

    // Building the Graph
    vector<vector<int>> G(V);
    for(int i=0; i<E; i++) {
        int x, y; ifs1>>x>>y;

        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    // Gathering the supposed answer from file
    int K; ifs2>>K;
    vector<int> X(V);
    for(int i=0; i<V; i++)
        ifs2>>X[i];

    // Look through each node in the set, and make sure its neighbors do not
    // also exist in the set. If the answer passes this criteria, then it is
    // considered correct.
    bool correct = true;
    for(int i=0; i<V; i++) {
        if(!correct) break;
        if(X[i]) {
            for(int j=0; j<G[i].size(); j++) {
                if(X[G[i][j]]) {
                    correct = false;
                    break;
                }
            }
        }
    }

    // Output Verdict
    if(correct)
        cout<<"Correct Solution!\n"<<"Score: "<<K<<endl;
    else
        cout<<"Incorrect Solution :("<<endl;

    // Closing filestreams
    ifs1.close();
    ifs2.close();

    return 0;
}