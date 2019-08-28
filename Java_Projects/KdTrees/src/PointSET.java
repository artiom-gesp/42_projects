import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;

import java.util.LinkedList;
import java.util.TreeSet;

/**
 * A class to represent a set of 2D points between 0 and 1
 * Points are stored in a Red/Black Tree
 * range and nearest function use simple brute force search method and thus are O(n) in time complexity.
 * Refer to KdTree.java for a more optimized version.
 */

public class PointSET {
    private TreeSet<Point2D> pointSet;

    public PointSET()
    {
        pointSet = new TreeSet<>();
    }

    public boolean isEmpty(){
        return pointSet.isEmpty();
    }

    public int size(){
        return pointSet.size();
    }

    public void insert(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        pointSet.add(p);
    }

    public boolean contains(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        return pointSet.contains(p);
    }

    public void draw(){
        for (Point2D tmp : pointSet)
        {
            StdDraw.setPenRadius(0.005);
            StdDraw.setXscale(-1, 2);
            StdDraw.setYscale(-1, 2);
            StdDraw.setPenColor(StdDraw.MAGENTA);
            StdDraw.point(tmp.x(), tmp.y());
        }
    }

    public Iterable<Point2D> range(RectHV rect){
        if (rect == null)
            throw new IllegalArgumentException("Null argument provided");
        LinkedList<Point2D> list = new LinkedList<>();
        for (Point2D p : pointSet)
        {
            if (p.x() <= rect.xmax() && p.x() >= rect.xmin() && p.y() <= rect.ymax() && p.y() >= rect.ymin())
                list.add(p);
        }
        return list;
    }

    public Point2D nearest(Point2D p){
        if (p == null)
            throw new IllegalArgumentException("Null argument provided");
        Point2D nearest = null;
        for (Point2D tmp : pointSet)
        {
            if (nearest == null || tmp.distanceTo(p) < nearest.distanceTo(p))
                nearest = tmp;
        }
        return nearest;
    }

    public static void main(String[] args) {
//        PointSET a = new PointSET();
//        a.insert(new Point2D(0.5, 0.5));
//        a.insert(new Point2D(0.7, 0.1));
//        a.draw();
//        int xmin, ymin, xmax, ymax;
//        xmin = 0;
//        ymin = 0;
//        xmax = 1;
//        ymax  = 1;
////        RectHV t = new RectHV()
//        StdDraw.rectangle(xmin, ymin, xmax, ymax);
//        for (Point2D p : a.range(new RectHV(xmin, ymin, xmax, ymax)))
//            System.out.println(p);
//        System.out.println(a.nearest(new Point2D(0.5, 0.1)));
    }

}
