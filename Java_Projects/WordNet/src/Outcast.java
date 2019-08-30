import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Outcast {
    private WordNet net;
    public Outcast(WordNet wordnet)
    {
        this.net = wordnet;
    }

    public String outcast(String[] nouns)
    {
        int distance = -1;
        String tmpA = null;
        int tmp;
        for (String a: nouns)
        {
            tmp = 0;
            for (String b : nouns)
            {
                tmp += net.distance(a, b);
            }
            if (tmp < Integer.MAX_VALUE && tmp > distance) {
                tmpA = a;
                distance = tmp;
            }
        }
        return tmpA;
    }

    public static void main(String[] args) {
        WordNet wordnet = new WordNet(args[0], args[1]);
        Outcast outcast = new Outcast(wordnet);
        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
        }
    }
}