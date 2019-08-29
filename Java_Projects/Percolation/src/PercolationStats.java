import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {

    private double[] save_trials;
    private static double CONFIDENCE_95 = 1.96;
    private double mean;
    private double std;

    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials){
        if (n <= 0 | trials <= 0)
        {
            throw new java.lang.IllegalArgumentException("n must be greater or equal to one");
        }

        Percolation percolation;
        int trial;
        int row;
        int col;

        trial = trials;
        save_trials = new double[trial];
        mean = -1;
        std = -1;

        for (int i = 0; i < trial; i++)
        {
            int j = 0;
            percolation = new Percolation(n);
            while (true) {
                row = Math.round(StdRandom.uniform(1, n + 1));
                col = Math.round(StdRandom.uniform(1, n + 1));
                if (!percolation.isOpen(row, col)) {
                    percolation.open(row, col);
                    if (percolation.percolates())
                        break;
                }
            }
            save_trials[i] = Double.valueOf(percolation.numberOfOpenSites()) / (n * n);
        }
    }
    // sample mean of percolation threshold
    public double mean(){
        mean = mean == -1 ? StdStats.mean(save_trials) : mean;
        return mean;
    }

    // sample standard deviation of percolation threshold
    public double stddev(){
        std = std == -1 ? StdStats.stddev(save_trials) : std;
        return std;
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo(){
        mean = mean == -1 ? StdStats.mean(save_trials) : mean;
        std = std == -1 ? StdStats.stddev(save_trials) : std;
        return mean - (CONFIDENCE_95 * std) / Math.sqrt(save_trials.length);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi(){
        mean = mean == -1 ? StdStats.mean(save_trials) : mean;
        std = std == -1 ? StdStats.stddev(save_trials) : std;
        return mean + (CONFIDENCE_95 * std) / Math.sqrt(save_trials.length);
    }

    // test client (see below)
    public static void main(String[] args){
        if (args.length != 2)
            return;
        PercolationStats stats = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        System.out.printf("mean                    = %f\n", stats.mean());
        System.out.printf("stddev                  = %f\n", stats.stddev());
        System.out.printf("95%% confidence interval = [%f, %f]\n", stats.confidenceLo(), stats.confidenceHi());
    }

}