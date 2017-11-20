package me.termax.lab09;

public class ExponentialSeries extends Series {
    public ExponentialSeries(double first, double delta, int n) {
        super(first, delta, n);
    }

    public ExponentialSeries(Series other) {
        super(other);
    }

    @Override
    public double get(int i) {
        return this.first * Math.pow(this.delta, i);
    }
}
