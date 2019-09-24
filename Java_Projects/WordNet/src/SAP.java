import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.BreadthFirstDirectedPaths;

//import java.util.HashSet;
//import java.util.Set;

public class SAP {
    private Digraph G;
    private final int V;
    private int cachedAncestor;
    private int cachedLength;
    private int cachedV;
    private int cachedW;

    // constructor takes a digraph
    public SAP(Digraph G) {
        this.G = new Digraph(G);
        this.V = G.V();
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w)
    {
        if (v < 0 || w < 0 || v >= V || w >= V)
            throw new IllegalArgumentException("Wrong vertices index");
        if (cachedV == v && cachedW == w)
            return cachedLength;
        cachedV = v;
        cachedW = w;
        BreadthFirstDirectedPaths vSearch = new BreadthFirstDirectedPaths(G, v);
        BreadthFirstDirectedPaths wSearch = new BreadthFirstDirectedPaths(G, w);
        int tmp;

        int length = Integer.MAX_VALUE;

        for (int i = 0; i < V; i++) {
            if (vSearch.hasPathTo(i) && wSearch.hasPathTo(i)) {
                tmp = vSearch.distTo(i) + wSearch.distTo(i);
                if (tmp < length) {
                    length = tmp;
                    cachedAncestor = i;
                }
            }
        }
        cachedLength = length == Integer.MAX_VALUE ? -1 : cachedAncestor;
        return length == Integer.MAX_VALUE ? -1 : length;
    }

    // a common ancestor of v and w that participates in a shortest ancestral path; -1 if no such path
    public int ancestor(int v, int w)
    {
        if (v < 0 || w < 0 || v >= V || w >= V)
            throw new IllegalArgumentException("Wrong vertices index");
        if (cachedV == v && cachedW == w)
            return cachedAncestor;
        length(v, w);
        return cachedAncestor;
//        BreadthFirstDirectedPaths vSearch = new BreadthFirstDirectedPaths(G, v);
//        BreadthFirstDirectedPaths wSearch = new BreadthFirstDirectedPaths(G, w);
//        int vertex = G.V();
//        int minLength = Integer.MAX_VALUE;
//        int result = -1;
//        for (int i = 0; i < vertex; i++) {
//            if (vSearch.hasPathTo(i) && wSearch.hasPathTo(i)) {
//                int tmp = vSearch.distTo(i) + wSearch.distTo(i);
//                if (tmp < minLength) {
//                    minLength = tmp;
//                    result = i;
//                }
//            }
//        }
//        if (minLength == Integer.MAX_VALUE) return -1;
//        return result;
    }

    private void validateInput(Iterable<Integer> v, Iterable<Integer> w)
    {
        if (v == null || w == null)
            throw new IllegalArgumentException("Given null argument");
        for (Integer k : v)
            if (k == null || k < 0 || k >= V)
                throw new IllegalArgumentException("Wrong vertices index");
        for (Integer k : w)
            if (k == null || k < 0 || k >= V)
                throw new IllegalArgumentException("Wrong vertices index");
    }

    // length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w)
    {
        validateInput(v, w);
        BreadthFirstDirectedPaths vSearch = new BreadthFirstDirectedPaths(G, v);
        BreadthFirstDirectedPaths wSearch = new BreadthFirstDirectedPaths(G, w);
        int minLength = Integer.MAX_VALUE;
        for (int i = 0; i < V; i++) {
            if (vSearch.hasPathTo(i) && wSearch.hasPathTo(i)) {
                minLength = Math.min(minLength,
                        vSearch.distTo(i) + wSearch.distTo(i));
            }
        }
        if (minLength == Integer.MAX_VALUE) return -1;
        return minLength;
    }

    // a common ancestor that participates in shortest ancestral path; -1 if no such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w)
    {
        validateInput(v, w);
        BreadthFirstDirectedPaths vSearch = new BreadthFirstDirectedPaths(G, v);
        BreadthFirstDirectedPaths wSearch = new BreadthFirstDirectedPaths(G, w);
        int minLength = Integer.MAX_VALUE;
        int result = -1;
        for (int i = 0; i < V; i++) {
            if (vSearch.hasPathTo(i) && wSearch.hasPathTo(i)) {
                int tmp = vSearch.distTo(i) + wSearch.distTo(i);
                if (tmp < minLength) {
                    minLength = tmp;
                    result = i;
                }
            }
        }
        if (minLength == Integer.MAX_VALUE) return -1;
        return result;
    }

    // do unit testing of this class
    public static void main(String[] args) {
//        Set<Integer> v = new HashSet<>();
//        Integer a = null;
//        System.out.println(a.equals(null));
//        SAP a = new SAP(new Digraph(4));
//        v.add(null);
//        System.out.println(v);
//        a.validateInput(v, v);
    }
}