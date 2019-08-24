import edu.princeton.cs.algs4.MinPQ;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class Solver {

    private final int dimension;
    private final SearchNode initialNode;
    private final MinPQ<SearchNode> minPQ;
    private int nbMoves;
    private Iterable<Board> solution;

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
            this.priority = curr.manhattan();
            this.moves = prev.moves + 1;
        }

        private void getNewPriority()
        {

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
        if (!isSolvable(initial))
            throw new IllegalArgumentException("Given grid is not solvable");
        dimension = initial.dimension();
        this.initialNode = new SearchNode(initial);
        minPQ = new MinPQ<>(5, this.initialNode.priority());
        minPQ.insert(this.initialNode);
        solve();
    }

    // is the board solvable?
    private boolean isSolvable(Board toCheck){
        return toCheck.isSolvable();
    }
    // number of moves to solve initial board
    public int moves(){
        return this.nbMoves;
    }

    // sequence of boards in a shortest solution
    private Iterable<Board> computeSolution(SearchNode node){
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

    public Iterable<Board> getSolution()
    {
        return this.solution;
    }

    private void solve() {
        while (!minPQ.min().curr.isGoal()) {
            SearchNode minNode = minPQ.delMin();
            for (Board tmp : minNode.curr.neighbors()) {
                if (minNode.prevNode == null || !tmp.equals(minNode.prevNode.curr)) {
                    minPQ.insert(new SearchNode(tmp, minNode));
                }
            }
        }
        this.nbMoves = minPQ.min().moves;
        this.solution = computeSolution(minPQ.min());
    }

    // test client
    public static void main(String[] args){
        ParseInput input = new ParseInput();
        final double startTime = System.currentTimeMillis() / Math.pow(10, 3);
        int[][] grid = input.readInput();
        Board board = new Board(grid);
        Solver solve = new Solver(board);
        System.out.println("solved in " + solve.moves());
        Iterable<Board> sol = solve.getSolution();
        if (sol == null)
            return;
        for (Board tmp : sol)
        {
            System.out.println(tmp.toString());
        }
        final double endTime = System.currentTimeMillis() / Math.pow(10, 3);
        System.out.println("Total execution time: " + (endTime - startTime) + " seconds");
    }

}