import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;

import java.util.LinkedList;

/**
 * An optimized version of PointSet to easily retrieve relations between 2D points
 */

public class KdTree {
    private Node root;
    private int size;

    /**
     * Tree representation of geometric data in a 2D plane.
     */
//    private class TwoDTree
//    {
//        private Node root;
//        private int size;

    private class Node implements Comparable<Node>
    {
        Point2D point;
        int rank;
        private Node left;
        private Node right;

        private Node(Point2D point, int rank)
        {
            this.point = point;
            this.rank = rank;
        }

        @Override
        public int compareTo(Node o) {
            if (o == this)
                return 0;
            return point.compareTo(o.point);
        }
    }

    /**
     * Insert point in 2D-Tree
     * @param p Point2D point
     */
    public void insert(Point2D p)
    {
        if (p == null)
            throw new IllegalArgumentException("Null argument");
        root = _insert(root, p, 0);
    }

    private Node _insert(Node node, Point2D val, int rank)
    {
        if (node == null) {
            ++size;
            return new Node(val, rank);
        }
        double cmp;
        if (node.rank % 2 == 0)
            cmp = (val.x() - node.point.x());
        else
            cmp = (val.y() - node.point.y());
        if (cmp == 0)
            cmp = val.compareTo(node.point);
        if (cmp < 0) { node.left = _insert(node.left, val, rank + 1); }
        if (cmp > 0) { node.right = _insert(node.right, val, rank + 1); }

        return node;
    }

    /**
     * String representation of 2D-Tree
     */
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        Iterable<Node> it = getNaturalOrder();
        for (Node x : it)
            s.append(x.point.toString());
        return s.toString();
    }

    /**
     * Is tree empty ?
     * @return true if empty, false otherwise
     */
    public boolean isEmpty(){
        return size == 0;
    }

    public int size()
    {
        return size;
    }

    /**
     * Returns tree elements in natural order i.e. in ascending order.
     * @return
     */
    private Iterable<Node> getNaturalOrder()
    {
        LinkedList<Node> list = new LinkedList<>();
        _getNaturalOrder(root, list);
        return list;
    }

    private void _getNaturalOrder(Node x, LinkedList<Node> list)
    {
        if (x == null)
            return;
        _getNaturalOrder(x.left, list);
        list.add(x);
        _getNaturalOrder(x.right, list);
    }

    public boolean contains(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        return _contains(root, p);
    }

    private boolean _contains(Node node, Point2D p)
    {
        if (node == null) {
            return false;
        }
        double cmp;
        if (node.rank % 2 == 0)
            cmp = (p.x() - node.point.x());
        else
            cmp = (p.y() - node.point.y());
        if (cmp == 0)
            cmp = p.compareTo(node.point);
        if (cmp < 0) { return _contains(node.left, p); }
        else if (cmp > 0) { return _contains(node.right, p); }
        else
            return true;
    }

    public void draw(){
        Iterable<Node> nodeList = getNaturalOrder();
        for (Node a : nodeList)
        {
            StdDraw.setPenRadius(0.01);
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.point(a.point.x(), a.point.y());
        }
    }

    public Iterable<Point2D> range(RectHV rect){
        if (rect == null)
            throw new IllegalArgumentException("Null argument provided");
        LinkedList<Point2D> list = new LinkedList<>();
        _range(root, rect, list);
        return list;
    }

    private void _range(Node node, RectHV rect, LinkedList<Point2D> list)
    {
        if (node == null)
            return;
        if (rect.contains(node.point)) {
            list.add(node.point);
        }
        if (node.rank % 2 == 0) {
            if (node.left != null && rect.xmin() <= node.point.x()) {
                _range(node.left, rect, list);
            }
            if (node.right != null && node.point.x() <= rect.xmax()) {
                _range(node.right, rect, list);
            }
        }
        else
        {
            if (node.left != null && rect.ymin() <= node.point.y()) {
                _range(node.left, rect, list);
            }
            if (node.right != null && node.point.y() <= rect.ymax()) {
                _range(node.right, rect, list);
            }
        }
    }

    public Point2D nearest(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        return _nearest(root, p, null);
    }


    private Point2D _nearest(Node node, Point2D p, Point2D nearest)
    {
        if (node == null)
            return nearest;
        if (node.point.compareTo(p) == 0)
            return node.point;
        if (nearest == null || node.point.distanceSquaredTo(p) < nearest.distanceSquaredTo(p))
            nearest = node.point;
        double cmp;
        if (node.rank % 2 == 0)
            cmp = (p.x() - node.point.x());
        else
            cmp = (p.y() - node.point.y());
        if (cmp == 0)
            cmp = p.compareTo(node.point);
        if (cmp < 0) { nearest = _nearest(node.left, p, nearest); }
        if (cmp > 0) { nearest = _nearest(node.right, p, nearest); }

        // distance from target to the hyperplane associated with the node.
        double distToPlane = node.rank % 2 == 0 ?
                Math.pow(p.x() - node.point.x(), 2) : Math.pow(p.y() - node.point.y(), 2);
        if (cmp < 0 && distToPlane < nearest.distanceSquaredTo(p))
            nearest = _nearest(node.right, p, nearest);
        else if (cmp > 0  && distToPlane < nearest.distanceSquaredTo(p))
            nearest = _nearest(node.left, p, nearest);

        return nearest;
    }

    public static void main(String[] args) {
        KdTree kdtree = new KdTree();
        In in = new In(args[0]);

        while (!in.isEmpty()) {
            double x = in.readDouble();
            double y = in.readDouble();
            Point2D p = new Point2D(x, y);
            kdtree.insert(p);
        }
        System.out.println(kdtree);
        System.out.println(kdtree.size());
        System.out.println(kdtree.nearest(new Point2D(0.307, 0.442)));
//        System.out.println(kdtree.contains(new Point2D(0.32, 0.85)));
    }
}
