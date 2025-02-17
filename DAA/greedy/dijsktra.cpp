#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Dijkstra Algorithm
// Returns the shortest distance of all nodes from the source node
// V: Number of vertices
// adj: Adjacency list of the graph
// src: Source node

// example adjList:
// means there is an edge from 0 to 1 with weight 10 and from 0 to 4 with weight 5 (for adj[0])
// adj[0] = { {1, 10}, {4, 5} } -> { {adjNode, edgeWeight}, ... }
// adj[1] = { {2, 1}, {4, 2} }
// adj[2] = { {3, 4} }
// adj[3] = { {0, 7}, {2, 6} }
// adj[4] = { {1, 3}, {2, 9}, {3, 2} }

vector<int> dijkstra(int V, vector<vector<int>> adj[], int src)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, INT_MAX);

    // Distance of source vertex from itself is 0
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        // Get the node with the shortest distance
        // from the priority queue
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node])
        {
            // Get the adjacent node and the edge weight
            // of the current node
            int adjNode = it[0];
            int edgeWeight = it[1];

            // If a shorter path is found
            if (dis + edgeWeight < dist[adjNode])
            {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

int main()
{
    int V = 5; // Number of vertices
    vector<vector<int>> adj[V];

    // Hardcoded graph
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 5});
    adj[1].push_back({2, 1});
    adj[1].push_back({4, 2});
    adj[2].push_back({3, 4});
    adj[3].push_back({0, 7});
    adj[3].push_back({2, 6});
    adj[4].push_back({1, 3});
    adj[4].push_back({2, 9});
    adj[4].push_back({3, 2});

    int src = 0; // Source node

    vector<int> dist = dijkstra(V, adj, src);

    cout << "Shortest distances from source node " << src << ":\n";
    for (int i = 0; i < V; i++)
    {
        cout << "Node " << i << " : ";
        if (dist[i] == INT_MAX)
            cout << "Unreachable" << endl;
        else
            cout << dist[i] << endl;
    }

    return 0;
}
