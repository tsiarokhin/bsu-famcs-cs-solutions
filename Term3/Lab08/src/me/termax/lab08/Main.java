package me.termax.lab08;

public class Main {

    private static final int[] PRESET1 = {10, 6, 14, 5, 7, 13, 17, 16, 18};
    private static final int[] PRESET2 = {5, 2, 3, 1, 6, 0, 10};
    private static final int[] PRESET3 = {8, 5, 17, 4, 6, 15, 20, 19, 24};


    public static void main(String[] args) {
        BinarySearchTree<Integer> tree = new BinarySearchTree<>();
        for (int val: PRESET1)
            tree.add(val);

        System.out.println("LeftRightRoot: " + tree.traverseLeftRightRoot());
        System.out.println("LeftRootRight: " + tree.traverseLeftRootRight());
        System.out.println("RootLeftRight: " + tree.traverseRootLeftRight());

    }
}