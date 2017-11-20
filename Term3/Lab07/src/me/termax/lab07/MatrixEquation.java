package me.termax.lab07;

import java.util.Scanner;

public class MatrixEquation {
    private Matrix a;
    private Matrix b;
    private boolean solved;

    public MatrixEquation(Matrix a, Matrix b) {
        a = a;
        b = b;
        solved = false;
    }

    public MatrixEquation(int n, Scanner input) {
        //System.out.println("Enter matrix A:");
        a = new Matrix(n, n, input);

        //System.out.println("Enter vector b:");
        b = new Matrix(n, 1, input);

        solved = false;
    }

    private void gaussianSolve() {
        double c;
        int n = a.getN();

        for (int i = 0; i < n; i++) {

            double currentMax = Math.abs(a.get(i, i));
            int maxIdx = i;
            for (int k = i + 1; k < n; k++) {
                if (Math.abs(a.get(k, i)) > currentMax) {
                    currentMax = Math.abs(a.get(k, i));
                    maxIdx = k;
                }
            }
            a.swapRows(i, maxIdx);
            b.swapRows(i, maxIdx);

            for (int j = i + 1; j < n; j++) {
                c = a.get(j, i) / a.get(i, i);
                b.set(j, b.get(j) - (b.get(i)*c));
                for (int l = i; l < n; l++) {
                    a.set(j, l, a.get(j, l) - (a.get(i, l)*c));
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            b.set(i, b.get(i)/a.get(i,i));
            a.set(i, i, 1);
            for (int j = i - 1; j >= 0; j--) {
                b.set(j, b.get(j) - (a.get(j, i)*b.get(i)));
                a.set(j, i, 0);
            }
        }
        solved = true;
    }

    public Matrix getSolution(){
        if (solved)
            return b;
        else {
            gaussianSolve();
            return b;
        }
    }

    @Override
    public String toString() {
        return "MatrixEquation:\nMatrix A:\n" + a + "\nVector b:" + b;
    }
}
