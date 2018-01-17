package me.termax.lab11;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;
import java.util.List;

public class Canvas extends JPanel {
    private CanvasLine currentLine;
    private List<CanvasLine> lines;

    private int maxX;
    private int maxY;

    public Canvas() {
        super(null);
        this.setBackground(Color.white);
        maxX = this.getPreferredSize().width;
        maxY = this.getPreferredSize().height;
        lines = new ArrayList<CanvasLine>();

        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                currentLine = new CanvasLine(getCurrentColor());
                lines.add(currentLine);
                currentLine.add(e.getX(), e.getY());
            }
        });

        this.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                currentLine.add(e.getX(), e.getY());
                maxX = Math.max(maxX, e.getX());
                maxY = Math.max(maxY, e.getY());
                repaint();
            }
        });

    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Image bgImage = getBackgroundImage();
        if (bgImage != null) {
            g.drawImage(bgImage, 0,0,null);
            maxX = Math.max(maxX, bgImage.getWidth(null));
            maxY = Math.max(maxY, bgImage.getHeight(null));
        }

        for (CanvasLine line: lines) {
            line.paint(g);
        }
        this.setPreferredSize(new Dimension(this.maxX, this.maxY));
        this.revalidate();
    }

    private Color getCurrentColor() {
        return ((Paint)SwingUtilities.getRoot(this)).getCurrentColor();
    }

    private Image getBackgroundImage() {
        return ((Paint)SwingUtilities.getRoot(this)).getBackgroundImage();
    }

    public void clear() {
        lines.clear();
        repaint();
    }

    public List<CanvasLine> getLines() {
        return lines;
    }
}
