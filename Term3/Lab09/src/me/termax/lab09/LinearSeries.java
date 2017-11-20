package me.termax.lab09;

public class LinearSeries extends Series {
    public LinearSeries(double first, double delta, int n) {
        super(first, delta, n);
    }

    public LinearSeries(Series other) {
        super(other);
    }

    @Override
    public double get(int i) {
        return this.first + i*this.delta;
    }
}
