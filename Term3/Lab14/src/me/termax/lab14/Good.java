package me.termax.lab14;

public class Good implements Comparable<Good> {
    protected String name;
    protected int count;

    public Good() {
    }

    public Good(String name,  int count) {
        this.name = name;
        this.count = count;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    @Override
    public int compareTo(Good o) {
        int f = o.count - this.count;
        if (f!=0)
            return f;
        else return name.compareTo(o.name);
    }

    @Override
    public String toString() {
        return name;
    }

}
