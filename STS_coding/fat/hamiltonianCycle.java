class HamiltonianCycle {
    final int V = 5;
    int path[];

    // Check if vertex v can be added at position pos
    boolean isSafe(int v, int graph[][], int path[], int pos) {

        // 1. Check adjacency
        if (graph[path[pos - 1]][v] == 0)
            return false;

        // 2. Check if already included
        for (int i = 0; i < pos; i++)
            if (path[i] == v)
                return false;

        return true;
    }

    // Utility function for Hamiltonian cycle
    boolean hamCycleUtil(int graph[][], int path[], int pos) {

        // Base Case: full cycle built
        if (pos == V) {
            return graph[path[pos - 1]][path[0]] == 1;
        }

        // Try all vertices except 0 (since 0 is starting point)
        for (int v = 1; v < V; v++) {

            if (isSafe(v, graph, path, pos)) {
                path[pos] = v;

                if (hamCycleUtil(graph, path, pos + 1))
                    return true;

                // BACKTRACK
                path[pos] = -1;
            }
        }

        return false;
    }

    // Main function to solve
    int hamCycle(int graph[][]) {

        path = new int[V];

        // initialize path with -1
        for (int i = 0; i < V; i++)
            path[i] = -1;

        // start at vertex 0
        path[0] = 0;

        if (!hamCycleUtil(graph, path, 1)) {
            System.out.println("Solution does not exist");
            return 0;
        }

        printSolution(path);
        return 1;
    }

    // print solution
    void printSolution(int path[]) {
        System.out.println("Solution Exists: Following is one Hamiltonian Cycle");
        for (int i = 0; i < V; i++)
            System.out.print(" " + path[i] + " ");
        System.out.println(" " + path[0] + " ");
    }

    // MAIN
    public static void main(String args[]) {

        HamiltonianCycle hamiltonian = new HamiltonianCycle();

        int graph1[][] = {
                {0, 1, 0, 1, 0},
                {1, 0, 1, 1, 1},
                {0, 1, 0, 0, 1},
                {1, 1, 0, 0, 1},
                {0, 1, 1, 1, 0}
        };

        hamiltonian.hamCycle(graph1);
    }
}
