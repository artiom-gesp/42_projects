import java.util.LinkedList;

public class Board {

    private final int gridSize;
    private final int[][] grid;
    private final int printPadding;
    private int[] blankCoord;

    // create a grid from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles){
        checkInput(tiles);
        gridSize = tiles.length;

        grid = tiles.clone();
        // Get length of biggest element from grid to align items in toString();
        printPadding = String.valueOf((int)Math.pow(gridSize , 2) - 1).length();
        blankCoord = findBlank();
    }

    private Board(int[][] tiles, int[] blankCoord, int printPadding)
    {
        gridSize = tiles.length;
        grid = tiles.clone();
        this.blankCoord = blankCoord;
        this.printPadding = printPadding;
    }

    // string representation of this grid
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

    // grid dimension n
    public int dimension(){
        return gridSize;
    }

    // number of tiles out of place
    // each element final position is given by row_index[from 0 to n - 1] * nb_rows(= gridSize)
    // + (column_index + 1)
    public int hamming(){
        int outOfPlace = 0;
        for (int rowIndex = 0; rowIndex < gridSize; rowIndex++)
            for (int columnIndex = 0; columnIndex < gridSize; columnIndex++)
            {
                outOfPlace += grid[rowIndex][columnIndex] != rowIndex * gridSize + (columnIndex + 1) ? 1 : 0;
            }
        return outOfPlace - (grid[gridSize - 1][gridSize - 1] == 0 ? 1 : 0);
    }

    // sum of Manhattan distances between tiles and goal
    public int manhattan(){
        int distance = 0;
        int goalRow;
        int goalCol;
        for (int rowIndex = 0; rowIndex < gridSize; rowIndex++)
            for (int columnIndex = 0; columnIndex < gridSize; columnIndex++)
            {
                goalRow = (int)Math.ceil(grid[rowIndex][columnIndex] / (double)gridSize) - 1;
                goalCol = grid[rowIndex][columnIndex] - goalRow * gridSize - 1;
                if (grid[rowIndex][columnIndex] != 0)
                    distance += Math.abs(rowIndex - goalRow) + Math.abs(columnIndex - goalCol);
            }
        return distance;
    }

    // is this grid the goal grid?
    public boolean isGoal(){
        return hamming() == 0;
    }

    private boolean isSolvable()
    {
        int inv_count = 0;
        int len = (int)Math.pow(gridSize, 2);
        int baseRow;
        int tmpRow;
        int baseCol;
        int tmpCol;

        for (int i = 0; i < len - 1; i++)
        {
            baseRow = i / gridSize; // Iterating through the 2D array using a single variable, for simplicity
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
        // Checks whether grid size if odd or even, if even takes than it takes in account blank position
        return gridSize % 2 == 0 ? ((inv_count % 2 + blankCoord[0] + 1) % 2 == 0) : inv_count % 2 == 0;
    }

    // does this grid equal y?
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

    // all neighboring grids
    public Iterable<Board> neighbors() {
        LinkedList<Board> neighbors = new LinkedList<>();
        Board tmp;

        if ((tmp = swapUp()) != null) { neighbors.add(tmp); }
        if ((tmp = swapDown()) != null) { neighbors.add(tmp); }
        if ((tmp = swapLeft()) != null) { neighbors.add(tmp); }
        if ((tmp = swapRight()) != null) { neighbors.add(tmp); }

        return neighbors;
    }

    // a grid that is obtained by exchanging any pair of tiles
    public Board twin(){
        int[][] tmpGrid = cloneGrid();
        int tmpVal;
        if (grid[0][0] == 0)
        {
            tmpVal = grid[0][1];
            tmpGrid[0][1] = tmpGrid[1][1];
            tmpGrid[1][1] = tmpVal;
        }
        else if (grid[0][1] != 0)
        {
            tmpVal = grid[0][1];
            tmpGrid[0][1] = tmpGrid[0][0];
            tmpGrid[0][0] = tmpVal;
        }
        else
        {
            tmpVal = grid[1][0];
            tmpGrid[1][0] = tmpGrid[0][0];
            tmpGrid[0][0] = tmpVal;
        }
        return new Board(tmpGrid, blankCoord, printPadding);
    }

    private void checkInput(int[][] grid)
    {
        if (grid.length < 2 || grid.length > 127)
            throw new IllegalArgumentException("Board size must be : 2 <= n < 128");
        for (int i = 0; i < grid.length; i++)
            if (grid[i].length != grid.length)
                throw new IllegalArgumentException("Please submit a valid n-by-n grid of integers between 0 " +
                        "(missing value) and n^2 - 1");
    }

    private int[][] cloneGrid()
    {
        int[][] tmp = new int[gridSize][];
        for (int i = 0; i < gridSize; i++)
        {
            tmp[i] = grid[i].clone();
        }
        return tmp;
    }
    

    private Board swapUp()
    {
        if (blankCoord[0] - 1 >= 0)
        {
            int[][] tmp = cloneGrid();
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0] - 1][blankCoord[1]];
            tmp[blankCoord[0] - 1][blankCoord[1]] = 0;
            return new Board(tmp, new int[]{blankCoord[0] - 1, blankCoord[1]}, printPadding);
        }
        return null;
    }

    private Board swapDown()
    {
        if (blankCoord[0] + 1 < gridSize)
        {
            int[][] tmp = cloneGrid();
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0] + 1][blankCoord[1]];
            tmp[blankCoord[0] + 1][blankCoord[1]] = 0;
            return new Board(tmp, new int[]{blankCoord[0] + 1, blankCoord[1]}, printPadding);
        }
        return null;

    }

    private Board swapLeft()
    {
        if (blankCoord[1] - 1 >= 0)
        {
            int[][] tmp = cloneGrid();
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0]][blankCoord[1] - 1];
            tmp[blankCoord[0]][blankCoord[1] - 1] = 0;
            return new Board(tmp, new int[]{blankCoord[0], blankCoord[1] - 1}, printPadding);
        }
        return null;

    }

    private Board swapRight()
    {
        if (blankCoord[1] + 1 < gridSize)
        {
            int[][] tmp = cloneGrid();
            tmp[blankCoord[0]][blankCoord[1]] = tmp[blankCoord[0]][blankCoord[1] + 1];
            tmp[blankCoord[0]][blankCoord[1] + 1] = 0;
            return new Board(tmp, new int[]{blankCoord[0], blankCoord[1] + 1}, printPadding);
        }
        return null;

    }

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

    // unit testing (not graded)
    public static void main(String[] args){
//        ParseInput input = new ParseInput();
//        int [][] grid = input.readInput();
//        Board board = new Board(grid);
//        Board board2 = new Board(grid);
//        System.out.println(board.toString());
//        System.out.println("Out of place : " + board.hamming());
//        System.out.println("Is goal ? " + board.isGoal());
//        System.out.println("Manhattan " + board.manhattan());
//        System.out.println(board.equals(board2));
//        Iterable<Board> list = board.neighbors();
//        for (Board i : list)
//            System.out.println(i);
//        System.out.println(board.twin().toString());
//
//
//        System.out.println("Solvable " + board.isSolvable());
    }

}