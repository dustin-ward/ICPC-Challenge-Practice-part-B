// ICPC Challenge Practice 2020 Solution 2
// Author: Dustin Ward
//
// This is my second solution to the ICPC Challenge Practice part B.
//
// The problem was to find the largest possible independent set in a given
// graph. (Independent meaning the set cannot contain two vertices that are
// directly connected by an edge in the graph). The score you receive is 
// based on the size of the set you find.
//
// The problem with my initial attempt was that node 1 HAD to be included in
// the set. With the large input size, the chance that node 1 was part of the
// large solution wasn't 100%. The work around seemed to be that If I could
// start my search on a bunch of random nodes, I could then just take the max
// score I recieve. The array 'r' serves as an ordering of nodes to visit. I
// then just shuffle the array and the result is a new ordering to try.
//
// I've also added an iteration feature to this one, so you can control the
// number of times a result is generated. I usually run the smaller sets
// around 1000 times. This really didnt seem to improve my initial scores.
// Finding the correct starting node is really hard, and even then, there is
// probably a better way to generate the rest of the set. 
// Here are the scores I got:
//
// B1: 2488
// B2: 31835
// B3: 30447
// B4: 50481

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    // Getting problem set from the command line
    string filename;
    int N;
    if(argc == 3) {
        filename = argv[1];
        N = atoi(argv[2]);
    }
    else {
        cout<<"Error! Not enough arguments supplied."<<endl;
        cout<<"Usage: ./Bv2 <problem> <iterations>"<<endl;
        return 0;
    }
    
    // Show filename and iterations
    cout<<"Filename: "<<filename+".in/out"<<endl;
    cout<<"Iterations: "<<N<<endl;

    // Opening input and output filestreams
    ifstream ifs;
    ifs.open(filename + ".in");
    ofstream ofs;
    ofs.open(filename + ".out");

    // Input Vertices and Edges
    int V, E; ifs>>V>>E;

    // Building the Graph
    vector<vector<int>> G(V);
    for(int i=0; i<E; i++) {
        int x, y; ifs>>x>>y;

        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    // Storage for the best solution
    int maxK = 0;
    vector<int> maxX(V);

    // Random Number Generation
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine e(seed);

    // For N iterations...
    while(N--) {
        int K = 0;
        vector<int> X(V, -1);

        // Fill 'r' array with 1..V
        vector<int> r(V);
        for(int i=0; i<V; i++)
            r[i]=i;
        
        // Shuffle the array
        shuffle(begin(r), end(r), e);

        // Generate the rest of the set using 'r' as an ordering
        for(int i=0; i<V; i++) {
            if(X[r[i]] == 0) continue;
            X[r[i]] = 1;
            K++;
            for(int j=0; j<G[r[i]].size(); j++) {
                X[G[r[i]][j]] = 0;
            }    
        }

        // Compare score to current max
        if(K > maxK) {
            maxK = K;
            copy(X.begin(), X.end(), maxX.begin());
        }

    }

    // Output the largest answer
    ofs<<maxK<<endl;
    for(int i=0; i<V; i++)
        ofs<<maxX[i]<<" ";

    // Close filestreams
    ifs.close();
    ofs.close();
}