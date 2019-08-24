import edu.princeton.cs.algs4.MinPQ;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class Solver {

    private final int dimension;
    private final SearchNode initialNode;
    private final MinPQ<SearchNode> minPQ;
    private int nbMoves;
    private boolean isSolvable = true;
//    private LinkedList<Board> visited;
//    private final Set<Board> visited;

    private class SearchNode
    {
        private final Board curr;
        private SearchNode prevNode;
        private int priority = 0;
        private int moves = 0;

        private SearchNode(Board inital)
        {
            this.curr = inital;
        }

        private SearchNode(Board curr, SearchNode prev)
        {
            this.curr = curr;
            this.prevNode = prev;
            this.priority = prev.priority;
            this.moves = prev.moves + 1;
        }

        private Comparator<SearchNode> priority()
        {
            return new Priority();
        }

        private class Priority implements Comparator<SearchNode>
        {
            public int compare(SearchNode a, SearchNode b)
            {
                if (a.priority + a.moves == b.priority + b.moves) {
//                    if (a.moves == b.moves)
                        return 0;
//                    return a.moves > b.moves ? 1 : -1;
                }
                return a.priority + a.moves > b.priority + b.moves ? 1 : -1;
            }
        }
    }

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial){
        if (initial == null)
            throw new IllegalArgumentException("Null argument");
        dimension = initial.dimension();
        this.initialNode = new SearchNode(initial, initial.manhattan(), null, 0);
        minPQ = new MinPQ<>(5, this.initialNode.priority());
        minPQ.insert(this.initialNode);
//        visited = new HashSet<Board>();
//        visited = new LinkedList<>();
        solve();
    }

    // is the initial board solvable?
    public boolean isSolvable(){
        // to change later
//        return initial.grid[0][0] == 0;
        return isSolvable;
    }

    // min number of moves to solve initial board
    public int moves(){
        return this.nbMoves;
    }

    // sequence of boards in a shortest solution
    public Iterable<Board> solution(){
        if (!isSolvable)
            return null;
        LinkedList<Board> solution = new LinkedList<>();
        SearchNode finalNode = minPQ.min();
        while (finalNode.prevNode != null)
        {
            solution.addFirst(finalNode.curr);
            finalNode = finalNode.prevNode;
        }
        solution.addFirst(finalNode.curr);
        return solution;
    }

    private void solve() {
        try {
            while (!minPQ.min().curr.isGoal()) {
                SearchNode minNode = minPQ.delMin();
                if (minNode.moves > 80) {
                    isSolvable = false;
                    break;
                }
                for (Board tmp : minNode.curr.neighbors()) {
                    if (minNode.prevNode == null || !tmp.equals(minNode.prevNode.curr)) {
                        minPQ.insert(new SearchNode(tmp, minNode));
                    }
                }
            }
            this.nbMoves = minPQ.min().moves;
        }
        catch (NoSuchElementException e) {
            isSolvable = false;
        }
    }

//    private boolean isVisited(Board toCheck)
//    {
//        for (Board tmp : visited)
//        {
//            if (toCheck.equals(tmp))
//                return true;
//        }
//        return false;
//    }

    // test client
    public static void main(String[] args){
////        long before = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
//
//        ParseInput input = new ParseInput();
//        final double startTime = System.currentTimeMillis() / Math.pow(10, 3);
//        int[][] grid = input.readInput();
//        Board board = new Board(grid);
////        Board board2 = new Board(grid);
//        Solver solve = new Solver(board);
////        solve.solve();
//        System.out.println("solved in " + solve.moves());
////        long after = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
////        System.out.println("memory usage : " + (after - before));
//        Iterable<Board> sol = solve.solution();
//        if (sol == null)
//            return;
//        for (Board tmp : sol)
//        {
//            System.out.println(tmp.toString());
//        }
//        final double endTime = System.currentTimeMillis() / Math.pow(10, 3);
//        System.out.println("Total execution time: " + (endTime - startTime) + " seconds");
    }

}