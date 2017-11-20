package me.termax.lab07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            File inputFile = new File("input1.txt");
            Scanner input = new Scanner(inputFile);

            int n;
            n = input.nextInt();
            if (n <= 0) throw new InputMismatchException();

            MatrixEquation eq = new MatrixEquation(n, input);

            System.out.println("X =\n" + eq.getSolution());
        }
        catch (InputMismatchException e) {
            System.out.println("Wrong file format");
        }
        catch (FileNotFoundException e) {
            System.out.println("No input file");
        }
        catch (NoSuchElementException e) {
            System.out.println("Not enough numbers in file");
        }

    }
}
