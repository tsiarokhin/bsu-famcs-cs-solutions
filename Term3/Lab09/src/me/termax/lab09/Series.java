package me.termax.lab09;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public abstract class Series {
    protected double first;
    protected double delta;
    protected int n;

    public Series(double first, double delta, int n) {
        this.first = first;
        this.delta = delta;
        this.n = n;
    }

    public Series(Series other) {
        this.first = other.first;
        this.delta = other.delta;
        this.n = other.n;
    }

    public abstract double get(int i);

    public double sum() {
        double sum = first;
        for (int i = 1; i < n; i++)
            sum += get(i);
        return sum;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < n; i++)
            result.append(get(i)).append(", ");
        return result.toString();
    }

    public void toFile(File outputFile) throws IOException {
        PrintWriter out = new PrintWriter(outputFile);
        out.println(this);
        out.close();
    }

    public double getFirst() {
        return first;
    }

    public void setFirst(double first) {
        this.first = first;
    }

    public double getDelta() {
        return delta;
    }

    public void setDelta(double delta) {
        this.delta = delta;
    }

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }
}
