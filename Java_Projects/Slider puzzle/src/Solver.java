import edu.princeton.cs.algs4.MinPQ;

import java.util.Comparator;

public class Solver {

    private final int dimension;
    private final Board initial;
    private final MinPQ<Board> minPQ;

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial){
        if (initial == null)
            throw new IllegalArgumentException("Null argument");
        dimension = initial.dimension();
        this.initial = initial;
        minPQ = new MinPQ<>(5, )

    }

    // is the initial board solvable? (see below)
    public boolean isSolvable(){
        // to change later
//        return initial.grid[0][0] == 0;
        return true;
    }

    // min number of moves to solve initial board
    public int moves(){
        return initial.manhattan();

    }

    // sequence of boards in a shortest solution
    public Iterable<Board> solution(){
        return null;

    }

    private void solve()
    {

    }

    // test client (see below)
    public static void main(String[] args){

    }

    private Comparator<Board> priority()
    {
        return new Priority();
    }

    private class Priority implements Comparator<Board>
    {
        public int compare(Board a, Board b)
        {
            if (a.equals(b))
                return 0;
            return a.manhattan() > b.manhattan() ? 1 : -1;
        }
    }

}