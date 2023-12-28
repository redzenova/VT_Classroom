public class GraphClient {

    private static boolean[] marked;    // marked[v] = is there an s-v path?
    private static int count = 0;           // number of vertices connected to s
    private static int numNodes = 0;
    private static Queue<Integer> allNodesVisited;

    // maximum degree 
    public static int maxDegree(Graph G) {
        int max = 0;
        for (int v = 0; v < G.V(); v++)
            if (G.degree(v) > max)
                max = G.degree(v);
        return max;
    }

    // average degree
    public static int avgDegree(Graph G) {
        // each edge incident on two vertices
        return 2 * G.E() / G.V();
    }

    // number of self-loops
    public static int numberOfSelfLoops(Graph G) {
        int count = 0;
        for (int v = 0; v < G.V(); v++)
            for (int w : G.adj(v))
                if (v == w) count++;
        return count/2;   // self loop appears in adjacency list twice
    }

    public static void DepthFirstSearch(Graph G, int s) {
        marked = new boolean[G.V()];
        allNodesVisited = new Queue<Integer>();
        numNodes = G.V();
        count = 0;
        dfs(G, s);
    }

    // depth first search from v
    private static void dfs(Graph G, int v) {
        count++;
        //System.out.print(v + " ");
        allNodesVisited.enqueue(v);
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                dfs(G, w);
            }
        }
    }

    public static void printDFS(Graph G, int s) {
        DepthFirstSearch(G, s);
        for (int v : allNodesVisited) {
            System.out.print(v + " ");
        }
    }

    public static boolean isConnected(Graph G) {
        DepthFirstSearch(G, 0);
        if (count != numNodes) return false;
        else return true;
    }

    // Add-on Final Exam
    // isTree to check if the graph is a tree
    public static boolean isTree(Graph G) {
        // Check if the graph is connected
        DepthFirstSearch(G, 0);
        
        // Check if the graph has no cycles
        if (count != numNodes) return false;
        
        // Check if the graph has V-1 edges
        if (G.E() != G.V() - 1) return false; 
        
        // Check if the graph has self loops
        if (numberOfSelfLoops(G) > 0) return false;
        return true;
    }


    // minHop to find the minimum number of hops between two vertices
    public static int minHop(Graph G, int u, int v) {
        boolean visited[] = new boolean[G.V()];
        int dist[] = new int[G.V()];
        Queue<Integer> q = new Queue<Integer>();
        int hop = 0;

        visited[u] = true;
        dist[u] = 0;
        q.enqueue(u);

        while (!q.isEmpty()) {
            int x = q.dequeue();
            for (int w : G.adj(x)) {
                if (w == v) {
                    hop = dist[x] + 1;
                    return hop;
                }
                if (!visited[w]) {
                    visited[w] = true;
                    dist[w] = dist[x] + 1;
                    q.enqueue(w);
                }
            }
        }
        return hop;

    }

}
