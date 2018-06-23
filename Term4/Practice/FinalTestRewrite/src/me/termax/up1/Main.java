package me.termax.up1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        try {
            File inputFile = new File("input.txt");
            Scanner input = new Scanner(inputFile);

            List<Triangle> triangleList = new ArrayList<>();

            while (input.hasNext()) {
                Point p1 = new Point(input.nextInt(), input.nextInt());
                Point p2 = new Point(input.nextInt(), input.nextInt());
                Point p3 = new Point(input.nextInt(), input.nextInt());
                Triangle t = new Triangle(p1, p2, p3);
                triangleList.add(t);
            }
            System.out.println("\n[TASK 1] Number of triangles read: " + triangleList.size());

            triangleList.sort(new Comparator<Triangle>() {
                @Override
                public int compare(Triangle o1, Triangle o2) {
                    double maxSide1 = Math.max(o1.getSide1(), Math.max(o1.getSide2(), o1.getSide3()));
                    double maxSide2 = Math.max(o2.getSide1(), Math.max(o2.getSide2(), o2.getSide3()));
                    return Double.compare(maxSide1, maxSide2);
                }
            });
            System.out.println("\n[TASK 2] Triangles sorted by max side length:");
            for (Triangle t: triangleList)
                System.out.println(t);

            triangleList.sort(new Comparator<Triangle>() {
                @Override
                public int compare(Triangle o1, Triangle o2) {
                    return Double.compare(o2.getPerimeter(), o1.getPerimeter());
                }
            });
            System.out.println("\n[TASK 3] Triangles sorted by perimeter:");
            for (Triangle t: triangleList)
                System.out.println(t);

            List<Double> perimetersOnly = new ArrayList<>();
            for (Triangle t: triangleList)
                perimetersOnly.add(t.getPerimeter());
            int idx = Collections.binarySearch(perimetersOnly, perimetersOnly.get(0)/2, Collections.reverseOrder());
            if (idx > 0) {
                System.out.println("\n[TASK 4] Triangle, with the perimeter=maximum/2 (which is " + perimetersOnly.get(0) + ") FOUND.");
                System.out.println("[TASK 4] It's: " + triangleList.get(idx));
            } else {
                System.out.println("\n[TASK 4] Triangle, with the perimeter=maximum/2 NOT FOUND.");
            }

            Map<Point, Integer> pointsMap = new HashMap<>();
            Set<Point> pointsSet = new HashSet<>();

            for (Triangle t: triangleList){
                for (Point p: Arrays.asList(t.getP1(), t.getP2(), t.getP3())) {
                    pointsMap.merge(p, 1, Integer::sum);
                    pointsSet.add(p);
                }

            }
            System.out.println("\n[TASK 5] Number of (10, 20) points: " + pointsMap.get(new Point(10, 20)));
            System.out.println("[TASK 5] Number of (20, 10) points: " + pointsMap.get(new Point(20, 10)));

            System.out.println("\n[TASK 6] List of unique points:");
            for (Point p: pointsSet)
                System.out.println(p);
        } catch (FileNotFoundException e) {
            System.out.println("[ERROR] Input file not found!");
        }
    }
}
