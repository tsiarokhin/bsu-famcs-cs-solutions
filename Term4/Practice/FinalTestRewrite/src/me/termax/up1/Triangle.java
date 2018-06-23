package me.termax.up1;

public class Triangle extends Figure {

    private Point p3;

    public Triangle(Point p1, Point p2, Point p3) {
        super(p1, p2);
        this.p3 = p3;
    }

    public Point getP3() {
        return p3;
    }

    public double getSide1() {
        return p1.getDistanceTo(p2);
    }

    public double getSide2() {
        return p2.getDistanceTo(p3);
    }

    public double getSide3() {
        return p3.getDistanceTo(p1);
    }

    @Override
    public double getPerimeter() {
        return getSide1() + getSide2() + getSide3();
    }

    @Override
    public String toString() {
        return "Triangle {" + getP3() + ", " + super.toString() + "}";
    }
}
