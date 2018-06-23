package me.termax.practice.lab08;

import com.sun.javafx.css.converters.CursorConverter;

import javax.swing.*;
import java.awt.*;

public class Display extends JFrame{
    private Canvas canvas;

    public Display(String title, int width, int height){
        super(title);
        setSize(width, height);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLocationRelativeTo(null);

        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setMaximumSize(new Dimension(width, height));
        canvas.setMinimumSize(new Dimension(width, height));
        canvas.setFocusable(false);
        canvas.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
        add(canvas);
        pack();
        setVisible(true);
    }

    public Canvas getCanvas(){
        return canvas;
    }


}
