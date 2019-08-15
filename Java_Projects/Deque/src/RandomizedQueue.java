import java.lang.Iterable;
import java.util.Iterator;
import java.util.NoSuchElementException;

import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private Item[] queue;
    private int[] is_full;
    private int pos = 0;

    // construct an empty randomized queue
    public RandomizedQueue(){
        queue = (Item[]) new Object[1];
        is_full = new int[1];
    }

    // is the randomized queue empty?
    public boolean isEmpty(){
        return pos == 0;
    }

    // return the number of items on the randomized queue
    public int size(){
        return pos;
    }

    // add the item
    public void enqueue(Item item){
        if (item == null)
            throw new IllegalArgumentException("item must not be null");
        if (pos == queue.length) {
            Item[] tmp = (Item[]) new Object[queue.length * 2];
            pos = 0;
            for ( ; pos < queue.length; pos++){
                tmp[pos] = queue[pos];
            }
            queue = tmp;
            queue[pos++] = item;
        }
        else {
            queue[pos++] = item;
        }
    }

    // remove and return a random item
    public Item dequeue(){
        if (pos == 0)
        {
            throw new NoSuchElementException("Queue already empty");
        }
        int rand = StdRandom.uniform(0, pos);
        if (pos < queue.length / 4)
        {
            Item[] tmp = (Item[]) new Object[queue.length / 2];

            for (int i = 0 ; i < pos; i++){
                tmp[i] = queue[i];
            }
            queue = tmp;
        }
        Item rand_item = queue[rand];
        queue[rand] = queue[pos - 1];
        queue[pos - 1] = null;
        pos--;
        return rand_item;
    }

    private Item dequeue(Item[] s, int pos)
    {
        if (pos == 0)
        {
            throw new NoSuchElementException("Queue already empty");
        }
        int rand = StdRandom.uniform(0, pos);
        Item rand_item = queue[rand];
        queue[rand] = queue[pos - 1];
        return rand_item;
    }

    // return a random item (but do not remove it)
    public Item sample(){
        if (pos == 0)
        {
            throw new NoSuchElementException("Queue already empty");
        }
        int rand = StdRandom.uniform(0, pos);
        return queue[rand];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator(){
        return new  QueueIterator();
    }

    private class QueueIterator implements Iterator<Item>
    {
        private Item[] current;
        private int n = pos;

        public QueueIterator()
        {
            current = (Item[]) new Object[queue.length];
            for (int i = 0 ; i < queue.length ; i++) {
                current[i] = queue[i];
            }
        }
        public boolean hasNext()
        {
            return n > 0;
        }
        public Item next()
        {
            return dequeue(current, n--);
        }
    }

    private void printQueue()
    {
        System.out.println("Here comes the queue !");
        for (int i = 0; i < pos; i++)
            System.out.println(queue[i]);
    }

    // unit testing (required)
    public static void main(String[] args){
        RandomizedQueue<Integer> q = new RandomizedQueue<>();

        q.enqueue(12);
        q.enqueue(13);
        q.enqueue(14);
        q.enqueue(15);
        q.enqueue(16);
        q.enqueue(17);
        q.enqueue(18);
        q.enqueue(19);
        for (int s : q)
        {
            System.out.println(s);
        }
        q.dequeue();
        System.out.println(q.size());
        System.out.println(q.isEmpty());
//        q.printQueue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.dequeue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.printQueue();
//        q.dequeue();
//        q.dequeue();




    }

}