import edu.princeton.cs.algs4.Heap;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.TST;
import edu.princeton.cs.algs4.In;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class BoggleSolver
{
    private TST<Integer>[] dictionary;
    private int[] arr;

    // Initializes the data structure using the given array of strings as the dictionary.
    // (You can assume each word in the dictionary contains only the uppercase letters A through Z.)
    public BoggleSolver(String[] dictionary)
    {
        int val = 0;
        this.dictionary = new TST[26];
        for (int i = 0; i < 26; i++)
        {
            this.dictionary[i] = new TST<>();
        }
        for (String s : dictionary)
        {
            this.dictionary[s.charAt(0) - 'A'].put(s, val++);
        }
        for (TST tmp : this.dictionary)
            System.out.println(tmp.keys());
    }

    // Returns the set of all valid words in the given Boggle board, as an Iterable.
    public Iterable<String> getAllValidWords(BoggleBoard board)
    {
        if (board == null)
            throw new NullPointerException("Board cannot be null");

        int col = board.cols();
        int row = board.rows();

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                findValidSubset(i, j, board);
            }
        }
        return null;
    }

    private class Node{
        int subset;
        int row;
        int column;

        private Node(int subset, int row, int column){
            this.subset = subset;
            this.row = row;
            this.column = column;
        }
    }

    private int findValidSubset(int row, int col, BoggleBoard board)
    {
        boolean[][] visited;
        LinkedList<String>[] words;
        Queue<Node> toVisit;

        int size = 0;
        for (Integer i : neighbors(row, col, board.rows(), board.cols())) {
            ++size;
        }
        words = new LinkedList[size];
        for (int i = 0; i < size; i++)
        {
            words[i] = new LinkedList<>();
        }
        visited = new boolean[size][board.rows() * board.cols()];
        for (int i = 0; i < size; i++)
        {
            toVisit = new LinkedList<Node>();
            toVisit.add(new Node(i, row, col));
//            System.out.println("here " + (board.rows() * row + col) + " " + i + " size " + size);
//            System.out.println(visited[0][0]);
            visited[i][row * board.rows() + col] = true;
            words[i].add(String.valueOf(board.getLetter(row, col)));
            while (!toVisit.isEmpty())
            {
                Node tmp = toVisit.remove();

                Iterable<Integer> neighbors = neighbors(tmp.row, tmp.column, board.rows(), board.cols());
                for (Integer j : neighbors) {

//                    System.out.println("in for loop " + i + " " + j);
//                    System.out.println("rows cols " + tmp.row + " " + tmp.column);
//                    System.out.println(neighbors(tmp.row, tmp.column, board.rows(), board.cols()));
                    if (!visited[i][j]) {
                        toVisit.add(new Node(i, j / board.rows(), j % board.rows()));
                        visited[i][j] = true;
                        words[i].add(words[i].peekLast() + board.getLetter(j / board.rows(), j % board.rows()));
                    }
                }

        }

        }
        for (int i = 0; i < size; i++)
        {
            System.out.println(words[i]);
        }
        return 0;
    }

    private Iterable<Integer> neighbors(int row, int col, int rowLength, int colLength)
    {
        LinkedList<Integer> neighbors = new LinkedList<>();
        if (row < rowLength - 1 && row > 0)
        {
            if (col < colLength - 1 && col > 0)
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col - 1));
                neighbors.add((row - 1) * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + (col + 1));
            }
            else
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col - 1));
                neighbors.add((row + 1) * rowLength + (col - 1));
            }
        }
        else if (row == 0)
        {
            if (col > 0 && col < colLength - 1)
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + (col + 1));
            }
            else
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add((row + 1) * rowLength + col);
                neighbors.add((row + 1) * rowLength + (col - 1));
            }
        }
        else
        {
            if (col > 0 && col < colLength - 1)
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col + 1));
                neighbors.add((row - 1) * rowLength + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * rowLength + (col + 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col + 1));
            }
            else
            {
                neighbors.add(row * rowLength + (col - 1));
                neighbors.add((row - 1) * rowLength + col);
                neighbors.add((row - 1) * rowLength + (col - 1));
            }
        }
        return neighbors;
    }

    // Returns the score of the given word if it is in the dictionary, zero otherwise.
    // (You can assume the word contains only the uppercase letters A through Z.)
    public int scoreOf(String word)
    {
        return 0;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        BoggleSolver bog = new BoggleSolver(in.readAllLines());
        BoggleBoard board = new BoggleBoard();
        bog.getAllValidWords(board);
    }
}
