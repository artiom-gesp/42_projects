import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FlowNetwork;


import java.util.Arrays;
import java.util.LinkedList;

public class BaseballElimination {
    private int numberOfTeams;
    private String[] teamNames;
    private int[] wins;
    private int[] losses;
    private int[] remaining;
    private int[][] against;
    private int[] isEliminated; // 1 if eliminated -1 otherwise.
    private LinkedList<String>[] certificateOfElimination;


    public BaseballElimination(String filename) {
        readInput(filename);
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
//        System.out.println(division.against("Atlanta", "New_York"));
//        System.out.println(division.isEliminated("New"));
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            } else {
                StdOut.println(team + " is not eliminated");
            }
        }
//        System.out.println(division.isEliminated("Team0") + " " + division.certificateOfElimination("Team0"));
    }

    private void readInput(String input)
    {
        int lineCount = 0;
        In in = new In(input);
        String tmp;
        String[] split;

        while (in.hasNextLine())
        {
            tmp = in.readLine();
            if (lineCount == 0) {
                numberOfTeams = Integer.parseInt(tmp);
                wins = new int[numberOfTeams];
                losses = new int[numberOfTeams];
                remaining = new int[numberOfTeams];
                against = new int[numberOfTeams][numberOfTeams];
                teamNames = new String[numberOfTeams];
                certificateOfElimination = new LinkedList[numberOfTeams];
                isEliminated = new int[numberOfTeams];
            }
            else
            {
                if (tmp.isEmpty())
                    break;
                split = tmp.trim().split("\\s+");
                try {
                    teamNames[lineCount - 1] = split[0];
                    wins[lineCount - 1] = Integer.parseInt(split[1]);
                    losses[lineCount - 1] = Integer.parseInt(split[2]);
                    remaining[lineCount - 1] = Integer.parseInt(split[3]);
                    for (int i = 4; i < split.length; i++)
                    {
                        against[lineCount - 1][i - 4] = Integer.parseInt(split[i]);
                    }
                }
                catch (ArrayIndexOutOfBoundsException e)
                {
                    throw new IllegalArgumentException("Wrong input format : " + e);
                }
//                catch (NumberFormatException e)
//                {
//                    throw new IllegalArgumentException("Wrong input format : " + e);
//                }
            }
            ++lineCount;
        }
    }

    private boolean buildNetwork(int team)
    {
        int secondLayerSize = (numberOfTeams - 2) * (numberOfTeams - 1) / 2;
        int nbVertices = 1 + secondLayerSize + (numberOfTeams - 1) + 1;
        FlowNetwork network = new FlowNetwork(nbVertices);
        FlowEdge tmp;
        int clusterSize = numberOfTeams - 2;
        int start = 1;
        int dest;
        int maxFlow = 0;
        int flow;

        // Set last layer
        int j = 0;
        for (int i = secondLayerSize + 1; i < numberOfTeams + secondLayerSize; i++)
        {
            if (j == team)
                ++j;
            if (j == numberOfTeams)
                break;
            flow = wins[team] + remaining[team] - wins[j];
            if (flow < 0)
                return true;
            tmp = new FlowEdge(i, nbVertices - 1, flow);
            maxFlow += wins[team] + remaining[team] - wins[j];
            network.addEdge(tmp);
            ++j;
        }

        // Set mid layer 1
        for (int i = 0; i < numberOfTeams - 1; i++)
        {
            j = start;
            for (; j < clusterSize + start; j++)
            {
                tmp = new FlowEdge(j, i + secondLayerSize + 1, Integer.MAX_VALUE);
                network.addEdge(tmp);
            }
            start = j;
            --clusterSize;
        }

        start = 0;
        clusterSize = numberOfTeams - 2;
        dest = 0;
        // Set mid Layer 2
        for (int i = 1; i < secondLayerSize + 1; i++)
        {
            if (dest == clusterSize)
            {
                ++start;
                dest = 0;
                --clusterSize;
            }
            tmp = new FlowEdge(i, secondLayerSize + 1 + dest + start + 1, Integer.MAX_VALUE);
            network.addEdge(tmp);
            ++dest;
        }

        // Set first layer
        int r1;
        int pos;
        clusterSize = numberOfTeams - 2;
        j = 0;
        for (int i = 1; i < secondLayerSize + 1; )
        {
            if (j == team)
                ++j;
            r1 = j + 1;
            pos = 0;
            for (; pos < clusterSize; )
            {
                if (r1 == team)
                    ++r1;
                if (r1 == numberOfTeams)
                    r1 = 0;
                tmp = new FlowEdge(0, i++, against[j][r1]);
                network.addEdge(tmp);
                ++r1;
                ++pos;
            }
            --clusterSize;
            ++j;
        }

        FordFulkerson ff = new FordFulkerson(network, 0, nbVertices - 1);
        for (FlowEdge e : network.adj(0))
        {
            if (e.capacity() != e.flow()) {
                return true;
            }

        }
        return false;
    }

    public int numberOfTeams() {
        return numberOfTeams;
    }

    public Iterable<String> teams() {
        return Arrays.asList(teamNames);
    }

    public int wins(String team) {
        int winsIndex = Arrays.asList(teamNames).indexOf(team);
        if (winsIndex == -1)
            throw new IllegalArgumentException("No such team : " + team);
        return wins[winsIndex];
    }

    public int losses(String team) {
        int lossesIndex = Arrays.asList(teamNames).indexOf(team);
        if (lossesIndex == -1)
            throw new IllegalArgumentException("No such team : " + team);
        return losses[lossesIndex];
    }

    public int remaining(String team) {
        int remainingIndex = Arrays.asList(teamNames).indexOf(team);
        if (remainingIndex == -1)
            throw new IllegalArgumentException("No such team : " + team);
        return remaining[remainingIndex];
    }

    public int against(String team1, String team2) {
        int team1Index = Arrays.asList(teamNames).indexOf(team1);
        int team2Index = Arrays.asList(teamNames).indexOf(team2);

        if (team1Index == -1 || team2Index == -1)
            throw new IllegalArgumentException("No such team : " + team1 + " and/or " + team2);

        return against[team1Index][team2Index];
    }

    public boolean isEliminated(String team) {
        FordFulkerson network;
        int teamIndex = Arrays.asList(teamNames).indexOf(team);
        if (teamIndex == -1)
            throw new IllegalArgumentException("No such team : " + team);
        if (isEliminated[teamIndex] == 0)
        {
            if (buildNetwork(teamIndex))
                isEliminated[teamIndex] = 1;
            else
                isEliminated[teamIndex] = -1;
        }
        return isEliminated[teamIndex] == 1;
    }

    public Iterable<String> certificateOfElimination(String team) {
        int index = Arrays.asList(teamNames).indexOf(team);
        if (index == -1)
            throw new IllegalArgumentException("No such team : " + team);
        if (isEliminated[index] == 0)
            isEliminated(team);
        if (isEliminated[index] == -1) {
            return null;
        }
        if (certificateOfElimination[index] == null) {
            certificateOfElimination[index] = new LinkedList<>();
            for (int i = 0; i < numberOfTeams; i++) {
                if (isEliminated[i] == 0)
                    isEliminated[i] = buildNetwork(i) ? 1 : -1;
                if (i != index && isEliminated[i] == -1) {
                    certificateOfElimination[index].add(teamNames[i]);
                }
            }
        }
        return certificateOfElimination[index];
    }
}