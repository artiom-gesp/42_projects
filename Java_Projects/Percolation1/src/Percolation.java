import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {

    // creates n-by-n grid, with all sites initially blocked
    private final WeightedQuickUnionUF union;
    private final int[][] is_open;
    private final int size;
    private final int celling;
    private final int floor;


    public Percolation(int n)
    {
        if (n <= 0)
        {
            throw new java.lang.IllegalArgumentException("n must be greater or equal to one");
        }
        is_open = new int[n][n];
        union = new WeightedQuickUnionUF(n * n + 2);
        size = n;
        celling = n * n;
        floor = n * n + 1;
    }

    public void open(int row, int col){
        if (row < 1 || row > size || col < 1 || col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        this.is_open[row - 1][col - 1] = 1;
        if (row == 1)
            this.union.union((row - 1) * size + col - 1, celling);
        if (row == size)
            this.union.union((row - 1) * size + col - 1, floor);

        if (row - 1 >= 1 && isOpen(row - 1, col))
        {
            this.union.union(((row - 1) - 1) * size + col - 1, (row - 1) * size + col - 1);
        }
        if (row + 1 <= size && isOpen(row + 1, col))
        {
            this.union.union(((row + 1) - 1) * size + col - 1, (row - 1) * size + col - 1);
        }
        if (col - 1 >= 1 && isOpen(row, col - 1))
        {
            this.union.union((row - 1) * size + col - 1 - 1, (row - 1) * size + col - 1);
        }
        if (col + 1 <= size && isOpen(row, col + 1))
        {
            this.union.union((row - 1) * size + col + 1 - 1, (row - 1) * size + col - 1);
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col){
        if (row < 1 || row > size || col < 1 || col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        return is_open[row - 1][col - 1] == 1;
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col){
        if (row < 1 || row > size || col < 1 || col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        return (isOpen(row, col) && this.union.connected((row - 1) * size + (col - 1), celling));
    }

    // returns the number of open sites
    public int numberOfOpenSites(){
        int open = 0;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                open += is_open[i][j];
            }
        }
        return open;
    }

    // does the system percolate?
    public boolean percolates() {
        return (this.union.connected(floor, celling));
    }

    // test client (optional)
    public static void main(String[] args) {
        int n = 10;
        Percolation perc = new Percolation(n);

//        perc.open(1, 1);
//        perc.open(1, 10);
//        perc.open(2, 10);
//        perc.open(3, 2);
//        perc.open(4, 2);
//        perc.open(5, 2);

        System.out.println(perc.numberOfOpenSites());
//        System.out.println(perc.isOpen(1, 6));
//        System.out.println(perc.isOpen(5, 2));
//        System.out.println(perc.isFull(2, 10));
//        System.out.println(perc.isFull(2, 1));
//        System.out.println(perc.isFull(2, 2));
//        System.out.println(perc.isFull(5, 3));

        System.out.println(perc.percolates());
    }
}