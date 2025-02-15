#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Prims Algorithm
// find minimum spanning tree's sum of weight

// example adjList:
// means there is an edge from 0 to 1 with weight 10 and from 0 to 4 with weight 5 (for adj[0])
// adj[0] = { {1, 10}, {4, 5} } -> { {adjNode, edgeWeight}, ... }
// adj[1] = { {2, 1}, {4, 2} }
// adj[2] = { {3, 4} }
// adj[3] = { {0, 7}, {2, 6} }
// adj[4] = { {1, 3}, {2, 9}, {3, 2} }

int MST_prims(int V, vector<vector<int>> adj[])
{
    // priority queue to store the edges with their weights
    // pair<int, int> -> {weight, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> visited(V, 0);
    int mstWeight = 0;
    // start from 0th node
    pq.push({0, 0});
    while (!pq.empty())
    {
        // get the edge with the smallest weight
        auto it = pq.top();
        pq.pop();
        int wt = it.first;
        int node = it.second;
        // if already visited, skip it
        if (visited[node])
            continue;
        // if not, mark as visited and add it to MST
        visited[node] = 1;
        mstWeight += wt;
        // add all the adjacent nodes to the priority queue
        for (auto it : adj[node])
        {
            int adjNode = it[0];
            int weight = it[1];
            if (!visited[adjNode])
                pq.push({weight, adjNode});
        }
        // dont mark it as visited here
    }
    return mstWeight;
}

int main()
{
    int V = 4; // Number of vertices

    // Adjacency list representation of graph
    vector<vector<int>> adj[V];

    // Hardcoded edges with their weights (u, v, weight)
    adj[0].push_back({1, 10});
    adj[1].push_back({0, 10}); // Since it's undirected

    adj[0].push_back({2, 6});
    adj[2].push_back({0, 6});

    adj[0].push_back({3, 5});
    adj[3].push_back({0, 5});

    adj[1].push_back({3, 15});
    adj[3].push_back({1, 15});

    adj[2].push_back({3, 4});
    adj[3].push_back({2, 4});

    int mstWeight = MST_prims(V, adj);
    cout << "The weight of the Minimum Spanning Tree is: " << mstWeight << endl;

    return 0;
}