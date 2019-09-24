import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

import edu.princeton.cs.algs4.Topological;

public class WordNet {

    private final HashMap<String, Set<Integer>> words;
    private final SAP sap;
    private String[] synsets;

    // constructor takes the name of the two input files
    public WordNet(String synsets, String hypernyms)
    {
        if (synsets == null || hypernyms == null)
            throw new IllegalArgumentException("Given null arguments");
        In inSyn = new In(synsets);
        In inHyp = new In(hypernyms);

        words = setHashMap(inSyn.readAll().split("\n"));
        Digraph net = setGraph(inHyp.readAll().split("\n"));
        Topological topo = new Topological(net);
        if (!topo.hasOrder())
            throw new IllegalArgumentException("Graph has cycles");

        System.out.println(net);
        sap = new SAP(net);
    }

    private HashMap<String, Set<Integer>> setHashMap(String[] synsetArray)
    {
        HashMap<String, Set<Integer>> words = new HashMap<>();
        String[] splitRow;
        String[] splitSynset;
        synsets = new String[synsetArray.length];
        Set<Integer> set;

        int index = 0;
        for (String s : synsetArray) {
            splitRow = s.split(",");

            if (splitRow[1] != null)
            {
                synsets[index++] = splitRow[1];
                splitSynset = splitRow[1].split(" ");
                for (String word : splitSynset) {
                    // if key is not found i.e. has not been added yet, create new key/value pair
                    if (!words.containsKey(word)) {
                        set = new HashSet<>();
                        set.add(Integer.parseInt(splitRow[0]));
                        words.put(word, set);
                    }
                    // add new index to already existing key (if a word has multiple definitions)
                    else
                        words.get(word).add(Integer.parseInt(splitRow[0]));
                }
            }
        }
        return words;
    }

    private Digraph setGraph(String[] hypernymArray)
    {
        String[] splitHyp;
        System.out.println(hypernymArray.length);
        Digraph net = new Digraph(hypernymArray.length);
        for (String pair : hypernymArray) {
            splitHyp = pair.split(",");
            for (int i = 1; i < splitHyp.length; i++)
                net.addEdge(Integer.parseInt(splitHyp[0]), Integer.parseInt(splitHyp[i]));
        }
        return net;
    }

    // returns all WordNet nouns
    public Iterable<String> nouns()
    {
        return words.keySet();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word)
    {
        if (word == null)
            throw new IllegalArgumentException("Given null arguments");
        return words.containsKey(word);
    }

    // distance between nounA and noun
    public int distance(String nounA, String nounB)
    {
        if (nounB == null || nounA == null)
            throw new IllegalArgumentException("Given null arguments");

        return sap.length(words.get(nounA), words.get(nounB));
    }

    // a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB
    // in a shortest ancestral path
    public String sap(String nounA, String nounB)
    {
        if (nounB == null || nounA == null)
            throw new IllegalArgumentException("Given null arguments");

        return synsets[sap.ancestor(words.get(nounA), words.get(nounB))];
    }

    public static void main(String[] args)
    {
        WordNet test  = new WordNet("synsets.txt", "hypernyms.txt");
        Iterable<String> it = test.nouns();
        System.out.println(test.isNoun("-1"));
        System.out.println(test.distance("tea", "coffee"));
        System.out.println(test.sap("coffee", "tea"));
        System.out.println(test.words.get("coffee"));
    }
}