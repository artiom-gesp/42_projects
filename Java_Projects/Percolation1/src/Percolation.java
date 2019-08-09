import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {

    // creates n-by-n grid, with all sites initially blocked
    public int[][] arr;
    private WeightedQuickUnionUF union;
    public int[][] is_open;
    private int size;

    public Percolation(int n)
    {
        if (n <= 0)
        {
            throw new java.lang.IllegalArgumentException("n must be greater or equal to one");
        }
        arr = new int[n][n];
        is_open = new int[n][n];
        union = new WeightedQuickUnionUF(n * n);
        size = n;

        int k = 0;
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                arr[i][j] = k++;
            }
        }
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col){
        if (row < 1 | row > size | col < 1 | col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        this.is_open[row - 1][col - 1] = 1;

        if (row - 1 >= 1 && isOpen(row - 1, col))
        {
            this.union.union((row - 1) * size + col, row * size + col);
        }
        if (row + 1 <= size && isOpen(row + 1, col))
        {
            this.union.union((row + 1) * size + col, row * size + col);
        }
        if (col - 1 >= 1 && isOpen(row, col - 1))
        {
            this.union.union(row * size + col - 1, row * size + col);
        }
        if (col + 1 <= size && isOpen(row, col + 1))
        {
            this.union.union(row * size + col + 1, row * size + col);
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col){
        if (row < 1 | row > size | col < 1 | col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        return is_open[row - 1][col - 1] == 1;
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col){
        if (row < 1 | row > size | col < 1 | col > size)
        {
            throw new java.lang.IllegalArgumentException("wrong values");
        }
        for (int i = 1; i <= size; i++) {
            if (this.union.connected(row * size + col, size + i))
                return true;
        }
        return false;
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
//        for (int i = 0; i < size; i++) {
//            for (int j = 0; j < size; j++) {
//                if (this.union.connected(size * size + col))
//            }
            return true;
//        }
    }

    // test client (optional)
    public static void main(String[] args) {
        Percolation perc = new Percolation(10);
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                System.out.printf("%2d ", perc.arr[i][j]);
            }
            System.out.println("\n");
        }
        perc.open(1, 1);
        perc.open(2, 1);
        perc.open(2, 2);
        perc.open(10, 10);
        System.out.println(perc.numberOfOpenSites());
        System.out.println(perc.isOpen(1, 1));
        System.out.println(perc.isFull(2, 1));
        System.out.println(perc.isFull(2, 2));

        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                System.out.printf("%2d ", perc.is_open[i][j]);
            }
            System.out.println("\n");
        }

    }
}