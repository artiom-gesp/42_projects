import edu.princeton.cs.algs4.Picture;

import javax.swing.*;
import java.awt.Color;

/**
 * A Simple yet elegant algorithm invented by Vidya Setlur, Saeko Takage, Ramesh Raskar,
 * Michael Gleicher and Bruce Gooch in 2005.
 * This class is a simple implementation of it using the dual-gradient energy function
 */

public class SeamCarver {

    private int width;
    private int height;
    private Picture picture;
    private double min = 0;
    private double max = 0;
    private JFrame lab;
    private static int gray = 15658734;

    /**
     * To find the least energy path, we build a map of pixels, each having a reference to his parent
     */
    private class Pixel
    {
        private double cumulatedEnergy;
        private int parentIndex;
        private int index;

        private Pixel(int index, double cumulatedEnergy, int parentIndex)
        {
            this.cumulatedEnergy = cumulatedEnergy;
            this.parentIndex = parentIndex;
            this.index = index;
        }
    }

    /**
     * Class constructor
     * @param picture Algs4 picture object (use new Picture(your-picture))
     */
    public SeamCarver(Picture picture)
    {
        if (picture == null)
            throw new IllegalArgumentException("Null argument");
        this.picture = new Picture(picture);
        this.height = picture.height();
        this.width = picture.width();
    }

    /**
     * Get a copy of the picture
     * @return a copy of the picture
     */
    public Picture picture()
    {
        return new Picture(this.picture);
    }
    
    public void save()
    {
        picture.save("resized_picture");
    }

    // width of current picture
    public int width()
    {
        return this.width;
    }

    // height of current picture
    public int height()
    {
        return this.height;
    }

    /**
     * Energy of a pixel, here measured using dual gradient energy function i.e. √((left - right)² + (top - bottom)²)
     * @param x x coordinate
     * @param y y coordinate
     * @return pixels energy
     */
    public double energy(int x, int y)
    {
        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
            throw new IllegalArgumentException("Index out of range : x " + x + " y : " + y);
        if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
        {
            return 1000;
        }
        Color left = picture.get(x - 1, y);
        Color right = picture.get(x + 1, y);
        Color top = picture.get(x, y - 1);
        Color bottom = picture.get(x, y + 1);

        double hSquareDif = Math.pow(left.getBlue() - right.getBlue(), 2)
                + Math.pow(left.getRed() - right.getRed(), 2)
                + Math.pow(left.getGreen() - right.getGreen(), 2);

        double vSquareDif = Math.pow(top.getBlue() - bottom.getBlue(), 2)
                + Math.pow(top.getRed() - bottom.getRed(), 2)
                + Math.pow(top.getGreen() - bottom.getGreen(), 2);

        return Math.sqrt(hSquareDif + vSquareDif);
    }

    /**
     * Visualize algorithm step by step
     * @param seam Current seam
     * @param vertical is the seam vertical ?
     */
    public void colorPath(int[] seam, boolean vertical)
    {
        int red = 16711680;

        if (this.lab == null)
            this.lab = new JFrame();
        int i = 0;
        Picture pic = new Picture(picture);
        if (vertical)
            for (int e : seam)
            {
                pic.setRGB(e, i++, red);
            }
        else
            for (int e : seam)
            {
                pic.setRGB(i++, e, red);
            }
        lab.setContentPane(pic.getJLabel());
        lab.setVisible(true);
        lab.pack();
        lab.repaint();
    }

    /**
     * Select the optimal parent 
     * @param p1 parent 1 (left or top)
     * @param p2 parent 2 (middle)
     * @param p3 parent 3 (right or bottom)
     * @return optimal parent
     */
    private Pixel selectParent(Pixel p1, Pixel p2, Pixel p3)
    {
        Pixel min = p2;
        if (p1 != null && p1.cumulatedEnergy < min.cumulatedEnergy)
            min = p1;
        if (p3 != null && p3.cumulatedEnergy < min.cumulatedEnergy)
            min = p3;
        return min;
    }

    /**
     * Rearrange pixels after vertical seam removal
     * @param col x index
     * @param row y index
     */
    private void shiftLeft(int col, int row)
    {
        if (col == width - 1)
            picture.setRGB(col, row, gray);
        else {
            for (int i = col; i < width - 1; i++) {
                picture.setRGB(i, row, picture.getRGB(i + 1, row));

            }
            picture.setRGB(width - 1, row, gray);
        }
    }

    /**
     * Sets pixel array for vertical seam carving
     * @return Array of image pixels linked to each other form bottom to top
     */
    private Pixel[] setVerticalPixelMap()
    {
        Pixel left;
        Pixel right;
        Pixel middle;
        Pixel parent;

        Pixel[] vPixelMap = new Pixel[width * height];
        double energy;

        for (int i = 0; i <= (width  - 1) + (height - 1) * width; i++)
        {
            if (i < width)
                vPixelMap[i] = new Pixel(i, 1000, -1);
            else {
                left = i % width == 0 ? null : vPixelMap[i - width - 1];
                right = i % width == width - 1 ? null : vPixelMap[i - width + 1];
                middle = vPixelMap[i - width];

                parent = selectParent(left, middle, right);
                energy = energy(i % width, i / width);
                vPixelMap[i] = new Pixel(i, energy + parent.cumulatedEnergy, parent.index);
            }
        }
        return vPixelMap;
    }

    /**
     * Find the most optimal vertical seam
     * @return a seam
     */
    public int[] findVerticalSeam()
    {
        Pixel end = null;
        int[] seam;

        Pixel[] map = setVerticalPixelMap();
        for (int i = (height - 1) * width; i <= (width  - 1) + (height - 1) * width; i++)
        {
            if (end == null || map[i].cumulatedEnergy < end.cumulatedEnergy)
                end = map[i];
        }

        if (end == null)
            return null;
        seam = new int[height];
        for (int i = 0; i < height; i++)
        {
            seam[height - 1 - i] = end.index % width;
            if (end.parentIndex == -1) {
                break;
            }
            end = map[end.parentIndex];
        }
        return seam;
    }

    /**
     * Remove a vertical seam from the piture
     * @param seam seam to remove
     */
    public void removeVerticalSeam(int[] seam)
    {
        if (seam == null || seam.length != height || width - 1 <= 0)
            throw new IllegalArgumentException("null argument");

        Picture tmp = new Picture(width - 1, height);

        for (int i = 0; i < height; i++)
        {
            shiftLeft(seam[i], i);
        }

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width - 1; j++)
                tmp.setRGB(j, i, picture.getRGB(j, i));
        picture = tmp;
        --width;
    }

    /**
     * Rearrange pixels after horizontal seam removal
     * @param col x index
     * @param row y index
     */
    private void shiftTop(int col, int row)
    {
        if (row == height - 1)
            picture.setRGB(col, row, gray);
        else {
            for (int i = row; i < height - 1; i++) {
                picture.setRGB(col, i, picture.getRGB(col, i + 1));
            }
            picture.setRGB(col, height - 1, gray);
        }
    }

    /**
     * Sets pixel array for horizontal seam carving
     * @return Array of image pixels linked to each other form right to left
     */
    private Pixel[] setHorizontalPixelMap()
    {
        Pixel top;
        Pixel bottom;
        Pixel middle;
        Pixel parent;

        Pixel[] hPixelMap = new Pixel[width * height];
        double energy;

        for (int j = 0; j < width; j++)
        {
            for (int i = 0; i <= (height - 1) * width; i += width) {
                if ((i + j) % width == 0)
                    hPixelMap[(i + j)] = new Pixel((i + j), 1000, -1);
                else {
                    top = i == 0 ? null : hPixelMap[(i + j) - width - 1];
                    bottom = i / width == height - 1 ? null : hPixelMap[(i + j) + width - 1];
                    middle = hPixelMap[(i + j) - 1];

                    parent = selectParent(top, middle, bottom);
                    energy = energy((i + j) % width, (i + j) / width);
                    hPixelMap[(i + j)] = new Pixel((i + j), energy + parent.cumulatedEnergy, parent.index);
                }
            }
        }
        return hPixelMap;
    }

    /**
     * Find the most optimal horizontal seam
     * @return a seam
     */
    public int[] findHorizontalSeam()
    {
        Pixel end = null;
        int[] seam;

        Pixel[] map = setHorizontalPixelMap();
        for (int i = width - 1; i <= (width  - 1) + (height - 1) * width; i += width)
        {
            if (end == null || map[i].cumulatedEnergy < end.cumulatedEnergy) {
                end = map[i];
            }
        }

        if (end == null)
            return null;

        seam = new int[width];

        for (int i = 0; i < width; i++)
        {
            seam[width - 1 - i] = end.index / width;
            if (end.parentIndex == -1)
                break;
            end = map[end.parentIndex];
        }
        return seam;
    }

    /**
     * Remove a horizontal seam from the piture
     * @param seam seam to remove
     */
    public void removeHorizontalSeam(int[] seam)
    {
        if (seam == null || seam.length != width || height - 1 <= 0)
            throw new IllegalArgumentException("null argument");;

        Picture tmp = new Picture(width, height - 1);

        for (int i = 0; i < width; i++)
        {
            shiftTop(i, seam[i]);
        }

        for (int i = 0; i < height - 1; i++)
            for (int j = 0; j < width; j++)
                tmp.setRGB(j, i, picture.getRGB(j, i));
        picture = tmp;
        --height;
    }

    private double map(double value, double minFrom, double maxFrom, double minTo, double maxTo)
    {
        return ((maxTo - minTo) / (maxFrom - minFrom)) * value + minTo;
    }

    private void setMinMax()
    {
        double energy;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                energy = energy(j, i);
                min = energy < min ? energy : min;
                max = energy > max ? energy : max;
            }
    }

    private Picture getEnergyMap()
    {
        int scaledEnergy;
        if (min == 0 && max == 0)
            setMinMax();
        Picture map = new Picture(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                scaledEnergy = (int)map(energy(j, i), min, max,0, 255);
//                scaledEnergy += scaledEnergy < 225 && scaledEnergy > 128 ? 30 : 0;
                map.setRGB(j, i, scaledEnergy << 16 | scaledEnergy << 8 | scaledEnergy);
            }
        return map;
    }

    //  unit testing (optional)
    public static void main(String[] args)
    {
        boolean showPaths = false;
        boolean showEnergy = false;
        Picture p = new Picture(args[0]);
        SeamCarver seam = new SeamCarver(p);

        for (String a : args)
        {
            if (a.contains("--show-paths"))
                showPaths = true;
            if (a.contains("--show-energy"))
                showEnergy = true;
        }

        if (showEnergy)
            seam.getEnergyMap().show();

        int[] s;
        if (args[1] != null) {
            for (int i = 0; i < Integer.parseInt(args[1]); i++) {
                s = seam.findVerticalSeam();
                if (showPaths)
                    seam.colorPath(s, true);
                seam.removeVerticalSeam(s);
            }
        }
        if (args[2] != null) {
            for (int i = 0; i < Integer.parseInt(args[2]); i++) {
                s = seam.findHorizontalSeam();
                if (showPaths)
                    seam.colorPath(s, false);
                seam.removeHorizontalSeam(s);
            }
        }
        seam.picture.show();
    }

}