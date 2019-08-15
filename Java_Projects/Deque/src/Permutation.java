import edu.princeton.cs.algs4.StdIn;

import java.util.NoSuchElementException;

public class Permutation {
    public static void main(String[] args) {
        String s;
        if (args.length != 1)
            return;
        int stop = Integer.parseInt(args[0]);
        RandomizedQueue<String> q = new RandomizedQueue<>();
        try
        {
            while ((s = StdIn.readString()) != null)
                q.enqueue(s);
        }
        catch (NoSuchElementException e)
        {

        }
//        System.out.println(s);
//        s = StdIn.readString();
//        System.out.println(s);
//        String[] split = s.split(" ", -1);
//        for (String t : split) {
//            q.enqueue(t);
//        }

        if (stop <= 0 || stop > q.size())
            return;
        for (String t : q) {
            if (stop == 0)
                break ;
            System.out.println(t);
            stop--;
        }
    }
}
