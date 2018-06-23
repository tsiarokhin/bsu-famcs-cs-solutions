package me.termax.up1;

public abstract class Figure {
    protected Point p1;
    protected Point p2;

    public Figure()  {
        this.p1 = new Point(0,0);
        this.p2 = new Point(0,0);
    }

    public Figure(Point p1, Point p2)  {
        this.p1 = p1;
        this.p2 = p2;
    }

    public Point getP1() {
        return p1;
    }

    public Point getP2() {
        return p2;
    }

    public abstract double getPerimeter();

    @Override
    public String toString() {
        return p1.toString() + ", " + p2.toString() + ", Perimeter=" + this.getPerimeter();
    }
}
