import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;
import javafx.scene.effect.Light;

import java.util.Iterator;
import java.util.LinkedList;

/**
 * An optimized version of PointSet to easily retrieve relations between 2D points
 */

public class KdTree {
    TwoDTree pointSet;

    /**
     * Class to represent a 2D Tree
     */
    private class TwoDTree
    {
        private Node root;
        private int size;

        private class Node implements Comparable
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
            public int compareTo(Object o) {
                if (o == this)
                    return 0;
                if (this.getClass() != o.getClass())
                    return -1;
                return point.compareTo(((Node)o).point);
            }
        }

        private void insert(Point2D p)
        {
            if (p == null)
                throw new IllegalArgumentException("Null argument");
            root = _insert(root, p, 0);
            ++size;
        }

        private Node _insert(Node node, Point2D val, int rank)
        {
            if (node == null)
                return new Node(val, rank);
            double cmp;
            if (node.rank % 2 == 0)
                cmp = (val.x() - node.point.x());
            else
                cmp = (val.y() - node.point.y());
            if (cmp < 0) { node.left = _insert(node.left, val, rank + 1); }
            if (cmp > 0) { node.right = _insert(node.right, val, rank + 1); }

            return node;
        }

        private String printTree()
        {
            String StringRep = "";
            _printTree(root, StringRep);
            return StringRep;
        }

        private void _printTree(Node x, String repr)
        {
            if (x == null)
                return;
            _printTree(x.left, repr);
            repr += x.point;
            System.out.println(x.point);
            _printTree(x.right, repr);
        }

        private boolean isEmpty(){
            return size == 0;
        }

        private int size()
        {
            return size;
        }

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


    }

    KdTree()
    {
        pointSet = new TwoDTree();
    }

    public boolean isEmpty(){
        return pointSet.isEmpty();
    }

    @Override
    public String toString() {
        return pointSet.printTree();
    }

    public int size(){
        return pointSet.size();
    }

    public void insert(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        pointSet.insert(p);
    }

//    public boolean contains(Point2D p){
//        if (p == null)
//            throw new IllegalArgumentException("Null argument provided");
//        return pointSet.contains(p);
//    }

    public void draw(){
        Iterable<TwoDTree.Node> it = pointSet.getNaturalOrder();
        for (TwoDTree.Node a : it)
        {
            StdDraw.setPenRadius(0.01);
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.point(a.point.x(), a.point.y());
            StdDraw.setPenRadius(0.005);
            if (a.rank % 2 == 0) {
                StdDraw.setPenColor(StdDraw.RED);
                StdDraw.line(a.point.x(), -1, a.point.x(), 1);
            }
            else {
                StdDraw.setPenColor(StdDraw.BLUE);
                StdDraw.line(-1, a.point.y(), 1, a.point.y());
            }
        }
    }
//
//    public Iterable<Point2D> range(RectHV rect){
//        if (rect == null)
//            throw new IllegalArgumentException("Null argument provided");
//        LinkedList<Point2D> list = new LinkedList<>();
//        for (Point2D p : pointSet)
//        {
//            if (p.x() <= rect.xmax() && p.x() >= rect.xmin() && p.y() <= rect.ymax() && p.y() >= rect.ymin())
//                list.add(p);
//        }
//        return list;
//    }
//
//    public Point2D nearest(Point2D p){
//        if (p == null)
//            throw new IllegalArgumentException("Null argument provided");
//        Point2D nearest = null;
//        for (Point2D tmp : pointSet)
//        {
//            if (nearest == null || tmp.distanceTo(p) < nearest.distanceTo(p))
//                nearest = tmp;
//        }
//        return nearest;
//    }

    public static void main(String[] args) {
            RectHV rect = new RectHV(0.0, 0.0, 1.0, 1.0);
            StdDraw.enableDoubleBuffering();
            KdTree kdtree = new KdTree();
            while (true) {
                if (StdDraw.isMousePressed()) {
                    double x = StdDraw.mouseX();
                    double y = StdDraw.mouseY();
//                    StdOut.printf("%8.6f %8.6f\n", x, y);
                    Point2D p = new Point2D(x, y);
                    if (rect.contains(p)) {
//                        StdOut.printf("%8.6f %8.6f\n", x, y);
                        kdtree.insert(p);
                        StdDraw.clear();
                        kdtree.draw();
//                        Iterable<TwoDTree.Node> it = kdtree.pointSet.getNaturalOrder();
//                        for (TwoDTree.Node i : it)
//                            System.out.println(i.point);
                        StdDraw.show();
                    }
                }
                StdDraw.pause(20);
            }

        }
//        KdTree tree = new KdTree();
//        tree.insert(new Point2D(0.5, 0.5));
//        tree.insert(new Point2D(0.1, 0.2));
//        tree.insert(new Point2D(0.7, 0.8));
//        tree.insert(new Point2D(0.9, 0.3));
//        Iterable<Point2D> it = tree.pointSet.getNaturalOrder();
//        for (Point2D i : it)
//            System.out.println(it);
//        System.out.println(tree.toString());
//    }

}
