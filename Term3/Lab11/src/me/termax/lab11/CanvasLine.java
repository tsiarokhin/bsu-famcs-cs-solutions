package me.termax.lab11;

import java.awt.*;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

class Coordinates {
    private int x;
    private int y;

    public Coordinates(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
}

public class CanvasLine {
    private List<Coordinates> coordinatesList;
    private Color color;

    public CanvasLine() {
        this.coordinatesList = new ArrayList<Coordinates>();
        this.color = Color.black;
    }

    public CanvasLine(Color color) {
        super();
        this.coordinatesList = new ArrayList<Coordinates>();
        this.color = color;
    }

    public void add(int x, int y) {
        this.coordinatesList.add(new Coordinates(x, y));
    }

    public void paint(Graphics g) {
        g.setColor(color);
        ((Graphics2D)g).setStroke(new BasicStroke(3));
        for (int i = 1; i < coordinatesList.size(); i++) {
            g.drawLine(coordinatesList.get(i-1).getX(), coordinatesList.get(i-1).getY(),
                        coordinatesList.get(i).getX(), coordinatesList.get(i).getY());
        }
    }

    public String toTxt() {
        StringBuilder result = new StringBuilder();
        result.append(color.getRed()).append(" ");
        result.append(color.getGreen()).append(" ");
        result.append(color.getBlue()).append(" ");
        for (Coordinates point: coordinatesList) {
            result.append(point.getX()).append(" ").append(point.getY()).append(" ");
        }
        return result.toString();
    }

    public CanvasLine (String source) throws InputMismatchException {
        Scanner in = new Scanner(source);
        this.coordinatesList = new ArrayList<Coordinates>();
        this.color = new Color(in.nextInt(), in.nextInt(), in.nextInt());
        while (in.hasNextInt()) {
            add(in.nextInt(), in.nextInt());
        }
    }
}
