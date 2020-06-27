// ICPC Challenge Practice 2020 Solution 3
// Author: Dustin Ward
//
// This is my third solution to the ICPC Challenge Practice part B.
//
// The problem was to find the largest possible independent set in a given
// graph. (Independent meaning the set cannot contain two vertices that are
// directly connected by an edge in the graph). The score you receive is 
// based on the size of the set you find.
//
// After randomizing the starting node in my last attemp didn't yeild much of
// an improvement, I needed to generate my sets in a different way. The easiest
// way would be to always choose the lowest degree node instead of a random
// one. This way I don't mark off as many nodes initially. So on input, I keep
// track of the cannections to any given node, then I cn just sort my ordering
// based on the degree of each node and always choose the lowest one available.
//
// B1: 2740
// B2: 35502
// B3: 34934
// B4: 58233

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    // Getting problem set from the command line
    string filename;
    if(argc < 2) {
        cout<<"Error! No problem name supplied."<<endl;
        cout<<"Usage: ./Bv3 <problem>"<<endl;
        return 0;
    }
    else
        filename = argv[1];

    // Show filename
    cout<<"Filename: "<<filename+".in/out"<<endl;

    // Open input and output streams
    ifstream ifs;
    ifs.open(filename + ".in");
    ofstream ofs;
    ofs.open(filename + ".out");

    // Input Vertices and Edges
    int V, E; ifs>>V>>E;

    // Creating list of pairs (node, degree)
    vector<pair<int,int>> r;
    for(int i=0; i<V; i++)
        r.push_back(make_pair(i, 0));

    // Build the Graph
    vector<vector<int>> G(V);
    for(int i=0; i<E; i++) {
        int x, y; ifs>>x>>y;

        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);

        r[x-1].second++;
        r[y-1].second++;
    }

    // Sort by the degree of each node
    sort(r.begin(), r.end(), 
        [](pair<int,int> &a, pair<int,int> &b) {return a.second < b.second;});

    // Run my regular generation with the new order
    int K = 0;
    vector<int> X(V, -1);
    for(int i=0; i<V; i++) {
        if(X[r[i].first] == 0) continue;
        X[r[i].first] = 1;
        K++;
        for(int j=0; j<G[r[i].first].size(); j++) {
            X[G[r[i].first][j]] = 0;
        }    
    }

    // Output answer to file
    ofs<<K<<endl;
    for(int i=0; i<V; i++)
        ofs<<X[i]<<" ";

    // Close output streams
    ifs.close();
    ofs.close();
}