import java.util.*;

public class Main {

    // Edge class
    static class Edge {
        int src, dest, weight;

        Edge(int s, int d, int w) {
            this.src = s;
            this.dest = d;
            this.weight = w;
        }
    }

    // Graph class
    static class Graph {
        int V, E;
        Edge[] edges;

        Graph(int v, int e) {
            V = v;
            E = e;
            edges = new Edge[E];
        }

        // Bellman-Ford Algorithm
        void bellmanFord(int source) {
            int[] dist = new int[V];

            // Step 1: Initialize distances
            Arrays.fill(dist, Integer.MAX_VALUE);
            dist[source] = 0;

            // Step 2: Relax edges V-1 times
            for (int i = 1; i < V; i++) {
                for (int j = 0; j < E; j++) {
                    int u = edges[j].src;
                    int v = edges[j].dest;
                    int w = edges[j].weight;

                    if (dist[u] != Integer.MAX_VALUE && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                    }
                }
            }

            // Step 3: Check for negative weight cycle
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int w = edges[j].weight;

                if (dist[u] != Integer.MAX_VALUE && dist[u] + w < dist[v]) {
                    System.out.println("Negative weight cycle detected");
                    return;
                }
            }

            // Print result
            printDistances(dist);
        }

        void printDistances(int[] dist) {
            System.out.println("Vertex\tDistance from Source");
            for (int i = 0; i < V; i++) {
                if (dist[i] == Integer.MAX_VALUE)
                    System.out.println(i + "\tINF");
                else
                    System.out.println(i + "\t" + dist[i]);
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        int V = sc.nextInt();

        System.out.print("Enter number of edges: ");
        int E = sc.nextInt();

        Graph graph = new Graph(V, E);

        System.out.println("Enter edges (src dest weight):");
        for (int i = 0; i < E; i++) {
            int src = sc.nextInt();
            int dest = sc.nextInt();
            int weight = sc.nextInt();

            graph.edges[i] = new Edge(src, dest, weight);
        }

        System.out.print("Enter source vertex: ");
        int source = sc.nextInt();

        graph.bellmanFord(source);

        sc.close();
    }
}