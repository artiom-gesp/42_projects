import edu.princeton.cs.algs4.MinPQ;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;

public class Solver {

    private final SearchNode initialNode;
    private int nbMoves;
    private Iterable<Board> solution;

    /**
     * SearchNode class to link together related Boards and easily retrieve the path to solution.
     * Each node has a board, a previous node (null for the initial node), a priority (manhattan distance)
     * and the number of moves made to reach this node.
     */

    private class SearchNode implements Comparable
    {
        private final Board board;
        private SearchNode prevNode;
        private int priority = 0;
        private int moves = 0;
        Method heuristic;

        private SearchNode(Board initial, String heuristic)
        {
            this.board = initial;
            try {
                this.heuristic = Board.class.getMethod(heuristic);
            }
            catch (NoSuchMethodException e)
            {
                throw new IllegalArgumentException("Please provide a correct heuristics name");
            }
        }

        private SearchNode(Board board, SearchNode prev)
        {
            this.board = board;
            this.prevNode = prev;
            this.heuristic = prev.heuristic;
            this.moves = prev.moves + 1;
            try {
                this.priority = (int)this.heuristic.invoke(board);
            }
            catch (IllegalAccessException | InvocationTargetException e)
            {
                throw new UnsupportedOperationException("Something went wrong :( Please try again");
            }
        }

        /**
         * Compares two search node by depth in solution graph
         * @param o The Search node to compare to
         * @return A negative integer if o is farther from the origin, a positive one if closer and 0 if same depth
         */
        public int compareTo(Object o) {
            if (o != null && o.getClass() == SearchNode.class)
                return this.compareTo((SearchNode)o);
            return -1;
        }

        private int compareTo(SearchNode a)
        {
            return (this.priority ) - (a.priority);
        }
    }

    /**
     * Find a solution to the initial board (using the A* algorithm)
     * @param initial Board object representing the initial grid
     */
    private Solver(Board initial, String heuristic){
        if (initial == null)
            throw new IllegalArgumentException("Null argument");
        if (!isSolvable(initial))
            throw new IllegalArgumentException("Given grid is not solvable");
        this.initialNode = new SearchNode(initial, heuristic);
        solve();
    }

    // is the board solvable?
    private boolean isSolvable(Board toCheck){
        return toCheck.isSolvable();
    }
    // number of moves to solve initial board
    private int moves(){
        return this.nbMoves;
    }

    // sequence of boards in a shortest solution
    private Iterable<Board> computeSolution(SearchNode node){
        LinkedList<Board> solution = new LinkedList<>();
        while (node.prevNode != null)
        {
            solution.addFirst(node.board);
            node = node.prevNode;
        }
        solution.addFirst(node.board);
        return solution;
    }

    private Iterable<Board> getSolution()
    {
        return this.solution;
    }

    private void solve() {
        MinPQ<SearchNode> minPQ = new MinPQ<>(5);
        minPQ.insert(this.initialNode);
        while (!minPQ.min().board.isGoal()) {
            SearchNode minNode = minPQ.delMin();
            for (Board tmp : minNode.board.neighbors()) {
                // Do not add parent node to queue
                if (minNode.prevNode == null || !tmp.equals(minNode.prevNode.board)) {
                    minPQ.insert(new SearchNode(tmp, minNode));
                }
            }
        }
        this.nbMoves = minPQ.min().moves;
        this.solution = computeSolution(minPQ.min());
    }

    static private int[][] generator(int size)
    {
        ArrayList<Integer> list  = new ArrayList<>();
        int[][] grid = new int[size][size];
        for (int i = 0; i < Math.pow(size, 2); i++)
        {
            list.add(i);
        }
        Collections.shuffle(list);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                grid[i][j] = list.get(size * i + j);
        return grid;
    }

    // test client
    public static void main(String[] args){
        ParseInput input = new ParseInput();
        final double startTime = System.currentTimeMillis() / Math.pow(10, 3);
        int[][] grid = input.readInput();
//        int[][] grid = Solver.generator(3);
        Board board = new Board(grid);
        Board board2 = new Board(grid);
        Solver solve = new Solver(board, "manhattan");
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