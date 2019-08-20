import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.In;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;

public class FastCollinearPoints {

    private final int nb_points;
    private final Point[] new_points;
    private final Point[] cp_points;
    private int nb_segments;
    private final LineSegment[] line_seg;
    private final LinkedList<Point[]> extremums;
    private final LinkedList<LineSegment> segments;

    public FastCollinearPoints(Point[] points){
        checkEntry(points);
        nb_points = points.length;

        this.new_points = Arrays.copyOf(points, nb_points);
        this.cp_points = Arrays.copyOf(points, nb_points);

        nb_segments = 0;
        extremums = new LinkedList<>();
        segments = new LinkedList<>();

        findSegments();
        line_seg = segments.toArray(new LineSegment[0]);
    }

    public           int numberOfSegments(){
        return nb_segments;
    }

    public LineSegment[] segments(){
        return Arrays.copyOf(line_seg, nb_segments);
    }

    private void checkEntry(Point[] points)
    {
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
    }

    private void findSegments()
    {
        for (int i = 0; i < nb_points; i++)
        {
            Arrays.sort(new_points, cp_points[i].slopeOrder().thenComparing(Point::compareTo));
            int l;
            double base_slope;
            for (int k = 1; k < nb_points - 2; k++)
            {
                base_slope = new_points[0].slopeTo(new_points[k]);
                l = k + 1;
                for ( ; l < nb_points && new_points[0].slopeTo(new_points[l]) == base_slope; ) {
                    ++l;
                }
                if (new_points[0].slopeTo(new_points[l - 1]) == base_slope && l > k + 2) {
                    addToArray(k, l - 1);
                    k = l - 2;
                }
            }
        }
    }

    private void addToArray(int start, int end) {
        Point low = new_points[start].compareTo(new_points[0]) < 0 ? new_points[start] : new_points[0];
        Point high = new_points[end].compareTo(new_points[0]) > 0 ? new_points[end] : new_points[0];
        Point[] tmp;
        Iterator<Point[]> iterator = this.extremums.iterator();

        while (iterator.hasNext()) {
            tmp = iterator.next();
            if (tmp[0] == low && tmp[1] == high) {
                return;
            }
        }
        LineSegment newSeg = new LineSegment(low, high);
        this.extremums.add(new Point[]{low, high});
        this.segments.add(newSeg);
        ++nb_segments;
    }

    public static void main(String[] args) {

        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x;
            x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }
//
//         draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            System.out.println(segment);
//            segment.draw();
        }
//        StdDraw.show();
    }
}