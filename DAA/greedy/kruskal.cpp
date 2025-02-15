#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Kruskal's Algorithm
// find minimum spanning tree's sum of weight

// Disjoint Set Data Structure
class DisjointSets
{
    vector<int> parent, rank, size;
    // resized to n+1, so it can handle both 0-based and 1-based indexing
public:
    DisjointSets(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }
    int findParent(int node)
    {
        // base case
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node]);
    }
    void unionByRank(int u, int v)
    {
        int ultp_u = findParent(u);
        int ultp_v = findParent(v);
        if (ultp_u == ultp_v)
            return;
        // lower rank one attached to higher rank
        if (rank[ultp_v] < rank[ultp_u])
        {
            parent[ultp_v] = ultp_u;
        }
        else if (rank[ultp_v] > rank[ultp_u])
        {
            parent[ultp_u] = ultp_v;
        }
        else // can be attached to any one
        {
            parent[ultp_v] = ultp_u;
            rank[ultp_u]++;
        }
    }
    void unionBySize(int u, int v)
    {
        int ultp_u = findParent(u);
        int ultp_v = findParent(v);
        if (ultp_v == ultp_u)
            return;
        // smaller size one attached to larger size
        if (size[ultp_v] < size[ultp_u])
        {
            parent[ultp_v] = ultp_u;
            size[ultp_u] += size[ultp_v];
        }
        else
        {
            parent[ultp_u] = ultp_v;
            size[ultp_v] += size[ultp_u];
        }
    }
};

// example adjList:
// means there is an edge from 0 to 1 with weight 10 and from 0 to 4 with weight 5 (for adj[0])
// adj[0] = { {1, 10}, {4, 5} } -> { {adjNode, edgeWeight}, ... }
// adj[1] = { {2, 1}, {4, 2} }
// adj[2] = { {3, 4} }
// adj[3] = { {0, 7}, {2, 6} }
// adj[4] = { {1, 3}, {2, 9}, {3, 2} }

int MST_kruskal(int V, vector<vector<int>> adj[])
{
    // This edges vector will store the edges with their weights
    // pair<int, pair<int, int>> -> {weight, {u, v}}
    // example: {3, {1, 2}} -> edge between 1 and 2 with weight 3
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < V; i++)
    {
        for (auto it : adj[i])
        {
            int adjNode = it[0];
            int weight = it[1];
            int node = i;

            edges.push_back({weight, {node, adjNode}});
        }
    }
    // sort the edges according to their weights
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    int mstWeight = 0;
    // In kruskal's algorithm, we will start from the smallest edge
    // and keep adding the smallest edge to the MST if it doesn't form a cycle
    // until we have V-1 edges in the MST
    // we will use either unionByRank or unionBySize
    // they will handle the cycle detection
    for (auto it : edges)
    {
        int u = it.second.first;
        int v = it.second.second;
        int wt = it.first;
        if (ds.findParent(u) != ds.findParent(v))
        {
            mstWeight += wt;
            ds.unionBySize(u, v);
        }
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

    int mstWeight = MST_kruskal(V, adj);
    cout << "The weight of the Minimum Spanning Tree is: " << mstWeight << endl;

    return 0;
}
