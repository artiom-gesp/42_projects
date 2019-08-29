import edu.princeton.cs.algs4.Insertion;

import java.util.Iterator;
import java.lang.IllegalArgumentException;

public class Deque<Item> implements Iterable<Item>, Comparable<Deque> {

    private Node first = null;
    private Node last = null;
    private int size = 0;

    // construct an empty deque
    public Deque() {
        first = new Node();
        last = first;
        assert false;
    }

    // unit testing (required)
    public static void main(String[] args) {
        Deque<Character> dk = new Deque<>();
        Deque<Integer> dq = new Deque<>();
        Deque[] q = new Deque[2];

        System.out.println("Current size : " + dk.size);

        dk.addFirst('C');

        System.out.println("Current size : " + dk.size);

        dk.printDeque();

        dk.addFirst('Z');
        dk.addFirst('V');
        dk.addFirst('V');
        dk.addFirst('V');
        dq.addFirst(1);
        dq.addFirst(2);
        dq.addFirst(3);
        q[1] = dk;
        q[0] = dq;
        System.out.println(q[0] + " " + q[1]);
        Insertion.sort(q);
        System.out.println(q[0] + " " + q[1]);
    }

    // is the deque empty?
    public boolean isEmpty() {
        return first == null || first.item == null;
    }

    // return the number of items on the deque
    public int size() {
        return size;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null)
            throw new IllegalArgumentException("item must not be null");
        if (first != null && first.item == null) {
            first.item = item;
        } else {
            Node new_first = new Node();

            new_first.item = item;
            new_first.next = first;
            first = new_first;
            if (first.next != null)
                first.next.prev = first;
            if (last == null)
                last = first;
        }
        ++size;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null)
            throw new IllegalArgumentException("item must not be null");
        Node new_last = new Node();
        new_last.item = item;

        if (first != null && first.item == null)
        {
            first.item = item;
        }
        else if (last == null) {
            first = new_last;
            last = new_last;
        }
        else
        {
            last.next = new_last;
            last.next.prev = last;
            last = last.next;
            last.next = null;
        }

        ++size;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        Item tmp;

        if (first == null || first.item == null) {
            throw new java.util.NoSuchElementException("Deque already empty");
        }
        tmp = first.item;
        --size;
        first = first.next;
        if (first != null)
            first.prev = null;
        return tmp;
    }

    // remove and return the item from the back
    public Item removeLast() {
        Item tmp;

        if (first == null) {
            throw new java.util.NoSuchElementException("Deque already empty");
        }
        tmp = last.item;
        if (last.prev != null) {
            last = last.prev;
            last.next = null;
        } else {
            last = null;
            first = null;
        }
        --size;
        return tmp;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    private void printDeque() {
        System.out.println("Printing Deque");
        for (Item item : this) {
            System.out.println(item);
        }
    }

    private class Node {
        Item item;
        Node next;
        Node prev;
    }

    private class ListIterator implements Iterator<Item> {
        private Node current = first;

        public boolean hasNext() {
            return current != null && current.item != null;
        }

        public Item next() {
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public int compareTo(Deque a)
    {
        return a.size() - this.size();
    }
}
