import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

public class Graph {
    private final int V;
    private int E;
    private SList<Integer>[] adj;
    
    /**
     * Initializes an empty graph with V vertices and 0 edges.
     * param V the number of vertices
     */
    public Graph(int V) {
        if (V < 0) throw new IllegalArgumentException("Number of vertices must be nonnegative");
        this.V = V;
        this.E = 0;
        adj = (SList<Integer>[]) new SList[V];
        for (int v = 0; v < V; v++) {
            adj[v] = new SList<Integer>();
        }
    }

    /**  
     * Initializes a graph by reading data from a file
     * The file format is the number of vertices V,
     * followed by the number of edges E,
     * followed by E pairs of vertices, with each entry separated by whitespace.
     */
    public Graph(Scanner in) {
        this(in.nextInt());
        int E = in.nextInt();
        if (E < 0) throw new IllegalArgumentException("Number of edges must be nonnegative");
        for (int i = 0; i < E; i++) {
            int v = in.nextInt();
            int w = in.nextInt();
            addEdge(v, w);
        }
    }

    /**
     * Initializes a new graph that is a deep copy of G.
     */
    public Graph(Graph G) {
        this(G.V());
        this.E = G.E();
        for (int v = 0; v < G.V(); v++) {
            for (int w : G.adj[v]) {
                adj[v].add(w);
            }
        }
    }

    /**
     * Returns the number of vertices in the graph.
     */
    public int V() {
        return V;
    }

    /**
     * Returns the number of edges in the graph.
     */
    public int E() {
        return E;
    }

    // throw an IndexOutOfBoundsException unless 0 <= v < V
    private void validateVertex(int v) {
        if (v < 0 || v >= V)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
    }

    /**
     * Adds the undirected edge v-w to the graph.
     */
    public void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        E++;
        adj[v].add(w);
        adj[w].add(v);
    }


    /**
     * Returns the vertices adjacent to vertex v.
     */
    public Iterable<Integer> adj(int v) {
        validateVertex(v);
        return adj[v];
    }

    /**
     * Returns the degree of vertex v.
     */
    public int degree(int v) {
        validateVertex(v);
        return adj[v].size();
    }


    /**
     * Returns a string representation of the graph.
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        String NEWLINE = System.getProperty("line.separator");
        s.append(V + " vertices, " + E + " edges " + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append(v + ": ");
            for (int w : adj[v]) {
                s.append(w + " ");
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }

    public static void main(String[] args) {
		Scanner scanner;
		String CHARSET_NAME = "UTF-8";
		Locale LOCALE = Locale.US;
		File file = new File(args[0]);
		Graph G = null;
	    try {
            scanner = new Scanner(file, CHARSET_NAME);
            scanner.useLocale(LOCALE);
	        G = new Graph(scanner);
        }
        catch (IOException ioe) {
            System.err.println("Could not open " + file);
        }
		System.out.println(G);
		System.out.println("Make a deep copy and show:");
		System.out.println();
		Graph G1 = new Graph(G);
        System.out.println(G1);
        System.out.println("Vertex with maximum degree is " + GraphClient.maxDegree(G1));
        System.out.println("Average degree is " + GraphClient.avgDegree(G1));
        System.out.println("Number of self loops is " + GraphClient.numberOfSelfLoops(G1));
        System.out.print("DFS on 0: ");
        GraphClient.printDFS(G1, 0);
        System.out.println();
        System.out.print("DFS on 9: ");
        GraphClient.printDFS(G1, 9);
        System.out.println();
        System.out.print("DFS on 7: ");
        GraphClient.printDFS(G1, 7);
        System.out.println();
        if (GraphClient.isConnected(G1)) System.out.println("Connected");
        else System.out.println("Not connected");

        // Add-on for Final Exam
        // isTree to check if the graph is a tree
        if (GraphClient.isTree(G)) System.out.println("This graph is Tree: True");
        else System.out.println("This graph is Tree: False");
        
        // minHop to find the minimum number of hops between two vertices
        int minHops = GraphClient.minHop(G, 86, 154);
        System.out.println("Minimum number of hops is : " + minHops);
    }

}
