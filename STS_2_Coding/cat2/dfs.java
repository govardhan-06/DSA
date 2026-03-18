import java.util.*;

class Graph {
    public int V;
    public LinkedList<Integer>[] adj;

    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; i++) {
            adj[i] = new LinkedList<>();
        }
    }

    void addEdge(int src, int dest) {
        adj[src].add(dest);
    }

    void DFSUtil(int vertex, boolean[] visited) {
        visited[vertex] = true;
        System.out.print(vertex + " ");

        for (int a : adj[vertex]) {
            if (!visited[a]) {
                DFSUtil(a, visited);
            }
        }
    }

    void DFS(int start) {
        boolean visited[] = new boolean[V];
        DFSUtil(start, visited);
    }

    public static void main(String args[]) {
        Graph g = new Graph(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        g.addEdge(2, 3);

        g.DFS(2);
    }
}