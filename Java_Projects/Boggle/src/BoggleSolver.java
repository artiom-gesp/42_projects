import edu.princeton.cs.algs4.TST;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

public class BoggleSolver
{
    private TST<Integer>[] dictionary;
    private Set<String> words;

    // Initializes the data structure using the given array of strings as the dictionary.
    // (You can assume each word in the dictionary contains only the uppercase letters A through Z.)
    public BoggleSolver(String[] dictionary)
    {
        int val = 0;
        this.words = new HashSet<>();
        this.dictionary = new TST[26];
        for (int i = 0; i < 26; i++)
        {
            this.dictionary[i] = new TST<>();
        }
        for (String s : dictionary)
        {
            this.dictionary[s.charAt(0) - 'A'].put(s, val++);
        }
//        for (TST tmp : this.dictionary)
//            System.out.println(tmp.keys());
    }

    // Returns the set of all valid words in the given Boggle board, as an Iterable.
    public Iterable<String> getAllValidWords(BoggleBoard board)
    {
        words = new HashSet<>();
        if (board == null)
            throw new NullPointerException("Board cannot be null");

        int col = board.cols();
        int row = board.rows();

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                boolean[][] test = new boolean[row][col];
                test[i][j] = true;
                String toAdd = String.valueOf(board.getLetter(i, j));
                findValidSubset(i, j, board, toAdd.equals("Q") ? "QU" : toAdd, test);
            }
        }
        return words;
    }

    private void findValidSubset(int row, int col, BoggleBoard board, String word, boolean[][] visited)
    {
        if (word.length() > 2 && dictionary[word.charAt(0) - 'A'].contains(word)) {
            words.add(word);
        }

        Iterable<Integer> neighbors = neighbors(row, col, board.rows(), board.cols());
        for (Integer j : neighbors) {
            int tmpRow = board.rows() != 1 ? j / board.cols() : 0;
            int tmpCol = board.rows() != 1 ? j % board.cols() : j;

            if (tmpRow < 0 || tmpRow >= board.rows() || tmpCol < 0 || tmpCol >= board.cols())
                continue;
            String toAdd = String.valueOf(board.getLetter(tmpRow, tmpCol));
            String wordTmp = word + (toAdd.equals("Q") ? "QU" : toAdd);
            if (!visited[tmpRow][tmpCol] && hasPrefix(wordTmp)) {
                // Set this node as visited for all of his children
                visited[tmpRow][tmpCol] = true;
                findValidSubset(tmpRow, tmpCol, board, wordTmp, visited);
                // Free this node for next iterations
                visited[tmpRow][tmpCol] = false;
            }
        }
//        for (int i = Math.max(row - 1, 0); i <= Math.min(row + 1, board.rows() - 1); i++)
//            for (int j = Math.max(col - 1, 0); j <= Math.min(col + 1, board.cols() - 1); j++)
//            {
////                System.out.println(i + " " + j);
//                String toAdd = String.valueOf(board.getLetter(i, j));
//                String wordTmp = word + (toAdd.equals("Q") ? "QU" : toAdd);
//                if (!visited[i][j] && hasPrefix(wordTmp)) {
//
//                    visited[i][j] = true;
//
//                    findValidSubset(i, j, board, wordTmp, visited);
//                    // Free this node for next iterations
//                    visited[i][j] = false;
//                }
//            }
    }

    private boolean hasPrefix(String word)
    {
        int size = 0;
        Iterable<String> it = dictionary[word.charAt(0) - 'A'].keysWithPrefix(word);

        for (String s : it) {
            ++size;
            if (size == 1)
                break ;
        }
        return size != 0;
    }

    private Iterable<Integer> neighbors(int row, int col, int height, int width)
    {
        LinkedList<Integer> neighbors = new LinkedList<>();
        if (height == 1)
        {
            neighbors.add(col + 1);
            if (col > 0)
                neighbors.add(col - 1);
        }
        else if (width == 1)
        {
            neighbors.add(row + 1);
            neighbors.add(row - 1);
        }
        else if (row < height - 1 && row > 0)
        {
            if (col < width - 1 && col > 0)
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add(row * width + (col + 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row + 1) * width + col);
                neighbors.add((row - 1) * width + (col - 1));
                neighbors.add((row - 1) * width + (col + 1));
                neighbors.add((row + 1) * width + (col + 1));
                neighbors.add((row + 1) * width + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * width + (col + 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row + 1) * width + col);
                neighbors.add((row - 1) * width + (col + 1));
                neighbors.add((row + 1) * width + (col + 1));
            }
            else
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row + 1) * width + col);
                neighbors.add((row - 1) * width + (col - 1));
                neighbors.add((row + 1) * width + (col - 1));
            }
        }
        else if (row == 0)
        {
            if (col > 0 && col < width - 1)
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add(row * width + (col + 1));
                neighbors.add((row + 1) * width + col);
                neighbors.add((row + 1) * width + (col + 1));
                neighbors.add((row + 1) * width + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * width + (col + 1));
                neighbors.add((row + 1) * width + col);
                neighbors.add((row + 1) * width + (col + 1));
            }
            else
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add((row + 1) * width + col);
                neighbors.add((row + 1) * width + (col - 1));
            }
        }
        else
        {
            if (col > 0 && col < width - 1)
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add(row * width + (col + 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row - 1) * width + (col + 1));
                neighbors.add((row - 1) * width + (col - 1));
            }
            else if (col == 0)
            {
                neighbors.add(row * width + (col + 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row - 1) * width + (col + 1));
            }
            else
            {
                neighbors.add(row * width + (col - 1));
                neighbors.add((row - 1) * width + col);
                neighbors.add((row - 1) * width + (col - 1));
            }
        }
        return neighbors;
    }

    // Returns the score of the given word if it is in the dictionary, zero otherwise.
    // (You can assume the word contains only the uppercase letters A through Z.)
    public int scoreOf(String word)
    {
        int[] score = {1, 1, 1, 1, 2, 3, 5, 11};
        if (dictionary[word.charAt(0) - 'A'].contains(word) && word.length() > 2)
            return word.length() < 8 ? score[word.length() - 1] : 11;
        return 0;
    }

    public static void main(String[] args) {
//        In in = new In(args[0]);
//        BoggleSolver bog = new BoggleSolver(in.readAllLines());
//        BoggleBoard board = new BoggleBoard();
//        System.out.println(board);
//        bog.getAllValidWords(board);
            In in = new In(args[0]);
            String[] dictionary = in.readAllStrings();
            BoggleSolver solver = new BoggleSolver(dictionary);
            BoggleBoard board = new BoggleBoard(args[1]);
//            double end = 0;
//            for (int i = 0; i < 100; i++)
//            {
//                board = new BoggleBoard();
//                double start = System.currentTimeMillis();
//                solver.getAllValidWords(board);
//                end += (System.currentTimeMillis() - start);
//                System.out.println((System.currentTimeMillis() - start));
//            }
//        System.out.println(end / 100);
            int score = 0;
            for (String word : solver.getAllValidWords(board)) {
                StdOut.println(word);
                score += solver.scoreOf(word);
            }
//            StdOut.println("Score = " + score);
//        System.out.println(solver.scoreOf("AT"));

    }
}
