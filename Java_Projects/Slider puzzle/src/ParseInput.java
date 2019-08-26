import java.util.Scanner;
import java.util.regex.*;
import java.util.Set;
import java.util.HashSet;

class ParseInput {
    private int gridSize = 0;
    private boolean init = true;
    private int[][] grid;

    /**
     * Read users input from command line or from file (using redirection)
     * @return a n * n grid of integers representing a (n^2 - 1)-puzzle
     */
    int[][] readInput()
    {
        int height = 0;
        String line;

        try (Scanner in = new Scanner(System.in)) {
            while (in.hasNextLine()) {
                line = in.nextLine();
                if (line.isEmpty())
                    throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                            "(missing value) and n^2 - 1");
                parseString(line, height);
                ++height;
                if (!init && height > gridSize)
                    throw new IllegalArgumentException("Width greater than length");
            }
        }
        if (height != gridSize)
            throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                    "(missing value) and n^2 - 1");

        findDuplicates();
        return grid;
    }

    /**
     * Retrieve integers values from string, throw error if anything else than integers of white spaces is found.
     * @param s String representing a line in the grid (e.g. 1 2 3)
     * @return a regex matcher containing the matched values.
     */
    private Matcher extractIntegers(String s)
    {
        Pattern findIinvalid = Pattern.compile("[^0-9\\s]");
        Matcher invalid = findIinvalid.matcher(s);

        if (invalid.find())
            throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                    "(missing value) and n^2 - 1");

        Pattern pattern = Pattern.compile("[0-9]+");
        return pattern.matcher(s);
    }

    /**
     * Check whether provided input contains duplicate values.
     */
    private void findDuplicates()
    {
        Set<Integer> set =  new HashSet<>();
        int sum = 0;

        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++)
            {
                if (!set.add(grid[i][j]))
                    throw new IllegalArgumentException("Grid must not contain duplicate values");
                sum += grid[i][j];
            }
        // Grid must contain every integer from 0 to n^2 - 1 => Sum(1, n^2 - 1)
        if (sum != (Math.pow(gridSize, 2) - 1) * Math.pow(gridSize, 2) / 2)
            throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                    "(missing value) and n^2 - 1");
    }

    /**
     * Copy matcher (n integer values) to int[n][n] grid
     * @param values Matcher values
     * @param height current line index (0 for upper side of grid, n - 1 for lower)
     */
    private void copyToGrid(Matcher values, int height)
    {
        int len = 0;

        while(len < gridSize && values.find()) {
            this.grid[height][len] = Integer.valueOf(values.group());
            ++len;
        }
        if (values.find() || len != gridSize)
            throw new IllegalArgumentException("Invalid width at line " + (height + 1));

    }

    /**
     * Create a grid from information contained in the first line of input
     * @param values Matcher of the first line of input
     */
    private void initGrid(Matcher values)
    {
        int len = 0;

        while(values.find() && len < 128) {
            ++len;
        }
        if (len == 128 || len < 2)
            throw new IllegalArgumentException("Grid size must 2 <= n < 128");
        this.gridSize = len;
        this.grid = new int[gridSize][gridSize];
        values.reset();
        len = 0;
        while(values.find())
        {
            this.grid[0][len] = Integer.valueOf(values.group());
            ++len;
        }
        this.init = false;
    }

    /**
     * initGrid if first input, else copyToGrid
     * @param s line as string
     * @param height current line index (0 for upper side of grid, n - 1 for lower)
     */
    private void parseString(String s, int height)
    {
        Matcher values = extractIntegers(s);
        if (init)
            initGrid(values);
        else
            copyToGrid(values, height);
    }
}
