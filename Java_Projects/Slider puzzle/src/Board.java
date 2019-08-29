import java.util.LinkedList;

class Board {

    private final int gridSize;
    private final int[][] grid;
    private final int printPadding;
    private int[] blankCoord;
    private int manhattan = 0;

    /**
     * Base constructor of class Board
     * @param tiles A n * n of grid of integers representing a (n^2 - 1)-puzzle.
     */
    public Board(int[][] tiles){
        checkInput(tiles);
        gridSize = tiles.length;

        grid = cloneGrid(tiles);
        // Get the length of the biggest element from grid to align items in toString();
        printPadding = String.valueOf((int)Math.pow(gridSize , 2) - 1).length();
        blankCoord = findBlank();
    }

    /**
     * Constructor overload for class wise operations e.g. avoiding recalculating blank position for neighbor grids
     * @param tiles A n * n of grid integers representing a (n - 1)-puzzle.
     * @param blankCoord The coordinates of the missing tile.
     * @param printPadding Padding for toString method.
     * @param manhattan Manhattan distance of board.
     */
    private Board(int[][] tiles, int[] blankCoord, int printPadding, int manhattan)
    {
        gridSize = tiles.length;
        grid = tiles;
        this.blankCoord = blankCoord;
        this.printPadding = printPadding;
        this.manhattan = manhattan;
    }

    /**
     * String representation of the grid
     * @return String representation of the grid preceded by its size (see this.dimension()).
     */
    public String toString(){
        String ret = "";
        ret = ret.concat(String.format("%d\n", gridSize));
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                String format = "%" + printPadding + "d";
                ret = ret.concat(String.format(format, grid[i][j]));
                if (j + 1 < gridSize)
                    ret = ret.concat(" ");
            }
            ret = ret.concat("\n");
        }
        return ret;
    }

    /**
     * Get grid side length (3 for a 8 puzzle)
     * @return grid side length
     */
    public int dimension(){
        return gridSize;
    }

    /**
     * Hamming binary encoding of grid element position, a element in correct position has an hamming distance of 0,
     * 1 otherwise.
     * @return Sum of hamming distance for each grid element.
     */
    public int hamming(){
        int outOfPlace = 0;
        for (int rowIndex = 0; rowIndex < gridSize; rowIndex++)
            for (int columnIndex = 0; columnIndex < gridSize; columnIndex++)
            {
                // each element final position is given by row_index[from 0 to n - 1] * nb_rows(= gridSize)
                // + (column_index + 1)
                if (grid[rowIndex][columnIndex] != 0)
                    outOfPlace += grid[rowIndex][columnIndex] != rowIndex * gridSize + (columnIndex + 1) ? 1 : 0;
            }
        return outOfPlace;
    }

    /**
     * Get the manhattan distance of a grid element to this expected position.
     * @param grid either the original grid or a neighbor)
     * @param rowIndex row index from 0 to n - 1
     * @param columnIndex column index from 0 to n - 1
     * @return 0 if element is in right position, otherwise returns the manhattan distance to elements correct position.
     */
    private int getElemDiff(int[][] grid, int rowIndex, int columnIndex)
    {
        int goalRow = (int)Math.ceil(grid[rowIndex][columnIndex] / (double)gridSize) - 1;
        int goalCol = grid[rowIndex][columnIndex] - goalRow * gridSize - 1;
        if (grid[rowIndex][columnIndex] != 0)
            return Math.abs(rowIndex - goalRow) + Math.abs(columnIndex - goalCol);
        return 0;
    }

    /**
     * Get the sum of all manhattan distances, if sum is not cached, calculate it.
     * @return Sum of all manhattan distances.
     */
    public int manhattan(){
        if (this.manhattan != 0)
            return this.manhattan;
        int distance = 0;
        for (int rowIndex = 0; rowIndex < gridSize; rowIndex++)
            for (int columnIndex = 0; columnIndex < gridSize; columnIndex++)
            {
                distance += getElemDiff(this.grid, rowIndex, columnIndex);
            }
//        System.out.println("calc " + distance);
        this.manhattan = distance;
        return distance;
    }

    /**
     * Are all the tiles in correct position ?
     * @return true if all tiles are in correct position, false otherwise.
     */
    public boolean isGoal(){
        return hamming() == 0;
    }

    /**
     * Verify whether number of permutation in grid is even i.e. if it is solvable.
     * @return true if solvable, false otherwise.
     */
    public boolean isSolvable()
    {
        int inv_count = 0;
        int len = (int)Math.pow(gridSize, 2);
        int baseRow;
        int tmpRow;
        int baseCol;
        int tmpCol;

        for (int i = 0; i < len - 1; i++)
        {
            baseRow = i / gridSize; // Iterating through the 2D array using a single variable, for simplicity.
            baseCol = i % gridSize;
            for (int j = i + 1; j < len; j++){
                tmpRow = j / gridSize;
                tmpCol = j % gridSize;
                if (grid[baseRow][baseCol] != 0 && grid[tmpRow][tmpCol] != 0
                        && grid[baseRow][baseCol] > grid[tmpRow][tmpCol]) {
                    inv_count++;
                }
            }
        }
        // Sorry :)
        // Checks whether grid size is odd or even, if even than takes in account the blank position.
        return gridSize % 2 == 0 ? ((inv_count % 2 + blankCoord[0] + 1) % 2 == 0) : inv_count % 2 == 0;
    }

    /**
     * Are both grids equal (element wise)
     * @param y The grid to compare with.
     * @return true if grids are equal, false otherwise
     */
    public boolean equals(Object y){
        if (y != null && y.getClass() == Board.class)
        {
            return _equals((Board)y);
        }
        return false;
    }

    private boolean _equals(Board y)
    {
        if (this.dimension() != y.dimension())
            return false;
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++)
                if (grid[i][j] != y.grid[i][j])
                    return false;
        return true;
    }

    /**
     * Get all grid neighbors, i.e. those obtained by swapping the blank with any neighboring tile.
     * @return An Iterable (Linked list) of neighbors.
     */
    public Iterable<Board> neighbors() {
        LinkedList<Board> neighbors = new LinkedList<>();
        Board tmp;

        if ((tmp = swapUp()) != null) { neighbors.add(tmp); }
        if ((tmp = swapDown()) != null) { neighbors.add(tmp); }
        if ((tmp = swapLeft()) != null) { neighbors.add(tmp); }
        if ((tmp = swapRight()) != null) { neighbors.add(tmp); }

        return neighbors;
    }

    /**
     * Does the provided grid has correct format ?
     * @param grid grid to check
     */
    private void checkInput(int[][] grid)
    {
        if (grid.length < 2 || grid.length > 127)
            throw new IllegalArgumentException("Board size must be : 2 <= n < 128");
        for (int i = 0; i < grid.length; i++)
            if (grid[i].length != grid.length)
                throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                        "(missing value) and n^2 - 1");
    }

    /**
     * Get a fresh copy of the grid
     * @param toCopy the grid to clone
     * @return A fresh grid identical to the provided one.
     */
    private int[][] cloneGrid(int[][] toCopy)
    {
        int[][] tmp = new int[gridSize][];
        for (int i = 0; i < gridSize; i++)
        {
            tmp[i] = toCopy[i].clone();
        }
        return tmp;
    }

    /**
     * Swap blank with upper tile if possible
     * @return null if there is no upper tile, an new board instance otherwise
     */
    private Board swapUp()
    {
        if (blankCoord[0] - 1 >= 0)
        {
            if (this.manhattan == 0)
                this.manhattan = manhattan();
            // Caching of manhattan heuristic, calculating only changed elements instead of entire grid.
            int newMan = this.manhattan - getElemDiff(this.grid, blankCoord[0] - 1, blankCoord[1]);
            int[][] tmp = cloneGrid(grid);
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0] - 1][blankCoord[1]];
            tmp[blankCoord[0] - 1][blankCoord[1]] = 0;
            newMan += getElemDiff(tmp, blankCoord[0], blankCoord[1]);
            return new Board(tmp, new int[]{blankCoord[0] - 1, blankCoord[1]}, printPadding, newMan);
        }
        return null;
    }

    /**
     * Swap blank with lower tile if possible
     * @return null if there is no lower tile, an new board instance otherwise
     */
    private Board swapDown()
    {
        if (blankCoord[0] + 1 < gridSize)
        {
            if (this.manhattan == 0)
                this.manhattan = manhattan();
            // Caching of manhattan heuristic, calculating only changed elements instead of entire grid.
            int newMan = this.manhattan - getElemDiff(this.grid, blankCoord[0] + 1, blankCoord[1]) ;
            int[][] tmp = cloneGrid(grid);
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0] + 1][blankCoord[1]];
            tmp[blankCoord[0] + 1][blankCoord[1]] = 0;
            newMan += getElemDiff(tmp, blankCoord[0], blankCoord[1]);
            return new Board(tmp, new int[]{blankCoord[0] + 1, blankCoord[1]}, printPadding, newMan);
        }
        return null;

    }

    /**
     * Swap blank with left tile if possible
     * @return null if there is no left tile, an new board instance otherwise
     */
    private Board swapLeft()
    {
        if (blankCoord[1] - 1 >= 0)
        {
            if (this.manhattan == 0)
                this.manhattan = manhattan();
            // Caching of manhattan heuristic, calculating only changed elements instead of entire grid.
            int newMan = this.manhattan - getElemDiff(this.grid, blankCoord[0], blankCoord[1] - 1) ;
            int[][] tmp = cloneGrid(grid);
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0]][blankCoord[1] - 1];
            tmp[blankCoord[0]][blankCoord[1] - 1] = 0;
            newMan += getElemDiff(tmp, blankCoord[0], blankCoord[1]);
            return new Board(tmp, new int[]{blankCoord[0], blankCoord[1] - 1}, printPadding, newMan);
        }
        return null;

    }

    /**
     * Swap blank with right tile if possible
     * @return null if there is no right tile, an new board instance otherwise
     */
    private Board swapRight()
    {
        if (blankCoord[1] + 1 < gridSize)
        {
            if (this.manhattan == 0)
                this.manhattan = manhattan();
            // Caching of manhattan heuristic, calculating only changed elements instead of entire grid.
            int newMan = this.manhattan - getElemDiff(this.grid, blankCoord[0], blankCoord[1] + 1) ;
            int[][] tmp = cloneGrid(grid);
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0]][blankCoord[1] + 1];
            tmp[blankCoord[0]][blankCoord[1] + 1] = 0;
            newMan += getElemDiff(tmp, blankCoord[0], blankCoord[1]);
            return new Board(tmp, new int[]{blankCoord[0], blankCoord[1] + 1}, printPadding, newMan);
        }
        return null;

    }

    /**
     * Finds the position of the missing tile
     * @return Array of blank coordinates
     */
    private int[] findBlank()
    {
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++)
            {
                if (grid[i][j] == 0)
                    return new int[]{i, j};
            }
        return null;
    }

    // Unit testing
    public static void main(String[] args){
        ParseInput input = new ParseInput();
        int [][] grid = input.readInput();
        Board board = new Board(grid);
        Board board2 = new Board(grid);
        System.out.println(board.toString());
        System.out.println("Out of place : " + board.hamming());
        System.out.println("Is goal ? " + board.isGoal());
        System.out.println("Manhattan " + board.manhattan());
        System.out.println(board.equals(board2));
        Iterable<Board> list = board.neighbors();
        for (Board i : list)
            System.out.println(i);


        System.out.println("Solvable " + board.isSolvable());

    }

}