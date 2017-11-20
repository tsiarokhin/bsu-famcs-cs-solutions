package me.termax.lab08;

public class BinarySearchTree<T extends Comparable<T>> {
    private class Node {
        private T value;
        private Node leftNode;
        private Node rightNode;

        public Node(T value) {
            this.value = value;
            this.leftNode = this.rightNode = null;
        }

        public T getValue() {
            return value;
        }

        public void setValue(T value) {
            this.value = value;
        }

        public Node getLeftNode() {
            return leftNode;
        }

        public void setLeftNode(Node leftNode) {
            this.leftNode = leftNode;
        }

        public Node getRightNode() {
            return rightNode;
        }

        public void setRightNode(Node rightNode) {
            this.rightNode = rightNode;
        }
    }
    private Node root;

    public BinarySearchTree() {
        this.root = null;
    }

    public boolean find(Node node, T value) {
        if (node == null)
            return false;
        int comp = value.compareTo(node.getValue());
        if (comp < 0)
            return find(node.getLeftNode(), value);
        if (comp > 0)
            return find(node.getRightNode(), value);
        return true;
    }

    public boolean find(T value) {
        return find(root, value);
    }

    public void add(Node node, T value) {
        int comp = value.compareTo(node.getValue());
        if (comp < 0)
            if (node.getLeftNode() == null)
                node.setLeftNode(new Node(value));
            else
                add(node.getLeftNode(), value);
        if (comp > 0)
            if (node.getRightNode() == null)
                node.setRightNode(new Node(value));
            else
                add(node.getRightNode(), value);
    }

    public void add(T value) {
        if (root == null)
            root = new Node(value);
        else
            add(root, value);
    }

    private final class Traverse {
        static final int LEFT = 0;
        static final int ROOT = 1;
        static final int RIGHT = 2;
    }
    private String traverse(Node node, int order1, int order2, int order3) {
        if (node == null) return "";
        String[] subTreeTraverse = {
                traverse(node.getLeftNode(), order1, order2, order3),
                node.getValue().toString() + ", ",
                traverse(node.getRightNode(), order1, order2, order3)
        };
        return subTreeTraverse[order1] + subTreeTraverse[order2] + subTreeTraverse[order3];
    }
    public String traverseRootLeftRight() {
        return traverse(root, Traverse.ROOT, Traverse.LEFT, Traverse.RIGHT);
    }
    public String traverseLeftRightRoot() {
        return traverse(root, Traverse.LEFT, Traverse.RIGHT, Traverse.ROOT);
    }
    public String traverseLeftRootRight() {
        return traverse(root, Traverse.LEFT, Traverse.ROOT, Traverse.RIGHT);
    }
}
