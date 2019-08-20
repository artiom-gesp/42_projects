import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.In;

import java.util.Arrays;

public class BruteCollinearPoints {

    private final Point[][] segments;
    private final int nb_points;
    private final Point[] points;
    private int nb_segments;
    private final LineSegment[] line_seg;

    public BruteCollinearPoints(Point[] points){
        int count = 0;
        if (points == null) { throw new IllegalArgumentException("Null array given"); }
        for (Point i : points) {
            if (i == null) { throw new IllegalArgumentException("Array contains null values"); }
            for (Point j : points) {
                if (j == null) { throw new IllegalArgumentException("Array contains null values"); }
                if (j.compareTo(i) == 0) {
                    ++count;
                    if (count == 2)
                        throw new IllegalArgumentException("Duplicate element");
                }
            }
            count = 0;
        }
        nb_points = points.length;
        segments = new Point[nb_points][2];
        this.points = Arrays.copyOf(points, nb_points);
        nb_segments = 0;
        bruteForce();
        line_seg = new LineSegment[nb_segments];
        for (int i = 0; i < nb_segments; i++)
            line_seg[i] = new LineSegment(this.segments[i][0], this.segments[i][1]);
    }

    public           int numberOfSegments(){
        return nb_segments;
    }

    public LineSegment[] segments(){
        return Arrays.copyOf(line_seg, nb_segments);
    }

    private void bruteForce()
    {
        Point[] tmp;
        double s1;
        double s2;
        double s3;

        for (int i = 0; i < nb_points; i++) {
            for (int j = 0; j < nb_points; j++) {
                s1 = points[i].slopeTo(points[j]);
                for (int k = 0; k < nb_points; k++) {
                    s2 = points[i].slopeTo(points[k]);
                    for (int l = 0; l < nb_points; l++) {
                        s3 = points[i].slopeTo(points[l]);

                        if (s1 == s2 && s1 == s3 && !is_duplicate(i, j, k, l)) {

                            boolean isInArray = false;
                            tmp = new Point[] {points[i], points[j], points[k], points[l]};
                            Arrays.sort(tmp);
                            for (int m = 0; m < nb_segments; m++)
                            {
                                if (segments[m][0] == tmp[0] && segments[m][1] == tmp[3]) {
                                    isInArray = true;
                                }
                            }

                            if (!isInArray) {
                                segments[nb_segments][0] = tmp[0];
                                segments[nb_segments][1] = tmp[3];
                                nb_segments++;
                            }
//                            addToArray(tmp);
                        }
                    }
                }
            }
        }
    }

//    private void addToArray(Point[] tmp) {
//        boolean is_in_array = false;
//        double slope;
//        for (int i = 0; i < nb_segments; i++) {
//            slope = segments[i][0].slopeTo(segments[i][1]);
//            if (slope == segments[i][0].slopeTo(tmp[0])
//                    && slope == segments[i][0].slopeTo(tmp[3])){
//                is_in_array = true;
//                if (tmp[3].compareTo(segments[i][1]) > 0 && segments[i][0].compareTo(tmp[0]) == 0) {
//                    segments[i][1] = tmp[3];
//                }
//                if (tmp[0].compareTo(segments[i][0]) < 0) {
//                    segments[i][0] = tmp[0];
//                }
//            }
//        }
//        if (!is_in_array) {
//            segments[nb_segments][0] = tmp[0];
//            segments[nb_segments++][1] = tmp[3];
//        }
//    }

//    private int get_min(int a, int b, int c, int d, Point[] point)
//    {
//        int min = point[a].compareTo(point[b]) < 0 ? a : b;
//        min = point[c].compareTo(point[min]) < 0 ? c : min;
//        min = point[d].compareTo(point[min]) < 0 ? d : min;
//        return min;
//    }
//
//    private int get_max(int a, int b, int c, int d, Point[] point)
//    {
//        int max = point[a].compareTo(point[b]) < 0 ? b : a;
//        max = point[c].compareTo(point[max]) < 0 ? max : c;
//        max = (point[d].compareTo(point[max]) < 0) ? max : d;
//        return max;
//    }

    private boolean is_duplicate(int a, int b, int c, int d)
    {
        return (a == b || a == c || a == d || b == c || b == d || c == d);
    }
    public static void main(String[] args) {


        Point h = new Point(212, 22);
//         read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

//        // draw the points
//        StdDraw.enableDoubleBuffering();
//        StdDraw.setXscale(0, 32768);
//        StdDraw.setYscale(0, 32768);
//        for (Point p : points) {
//            p.draw();
//        }
//        StdDraw.show();

        // print and draw the line segments
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            System.out.println(segment);
//            segment.draw();
        }
//        StdDraw.show();
    }
}