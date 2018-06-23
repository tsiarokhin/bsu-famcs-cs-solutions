package me.termax.practice.lab02;

import javax.swing.*;
import java.util.*;

public class Country{
    private String name;
    private String capital;
    private ImageIcon  flag;

    @Override
    public String toString() {
        return name;
    }

    public Country(String name, String capital, ImageIcon  flag) {
        this.name = name;
        this.capital = capital;
        this.flag = flag;
    }

    public String getName() {
        return name;
    }

    public String getCapital() {
        return capital;
    }

    public ImageIcon getFlag() {
        return flag;
    }
}
