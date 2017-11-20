package me.termax.lab07;

import java.util.Arrays;
import java.util.Scanner;

public class Matrix {
    private int n;
    private int m;
    private double[][] matrix;

    public Matrix(int n, int m) {
        this.n = n;
        this.m = m;

        matrix = new double[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    public Matrix(int n, int m, double[][] matrix) {
        this.n = n;
        this.m = m;
        this.matrix = matrix;
    }


    public Matrix(int n, int m, Scanner input) {
        this.n = n;
        this.m = m;
        this.matrix = new double[n][m];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                //System.out.print("\tMatrix[" + i + "]" + "[" + j + "]: ");
                this.matrix[i][j] = input.nextDouble();
            }
        }
    }


    public int getN() {
        return n;
    }

    public int getM() {
        return m;
    }

    public double get(int i, int j) {
        return matrix[i][j];
    }

    public double get(int i) throws IllegalArgumentException {
        if (getN() == 1)
            return matrix[0][i];
        else if (getM() == 1)
            return matrix[i][0];
        else
            throw new IllegalArgumentException("Not a vector");
    }

    public void set(int i, int j, double value) {
        this.matrix[i][j] = value;
    }

    public void set(int i, double value) throws IllegalArgumentException {
        if (getN() == 1)
            matrix[0][i] = value;
        else if (getM() == 1)
            matrix[i][0] = value;
        else
            throw new IllegalArgumentException("Not a vector");
    }

    public void swapRows(int row1, int row2) {
        if (row1 == row2) return;
        double temp;
        for (int i = 0; i < getM(); ++i) {
            temp = get(row1, i);
            set(row1, i, get(row2, i));
            set(row2, i, temp);
        }
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < n; ++i) {
            res.append("\t").append(Arrays.toString(matrix[i])).append("\n");
        }
        return res.toString();
    }
}
