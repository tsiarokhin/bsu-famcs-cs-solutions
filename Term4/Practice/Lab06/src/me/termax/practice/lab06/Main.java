package me.termax.practice.lab06;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main extends JFrame {
    private final int NUMBER_OF_TILES = 4;
    private final String IMAGE_PATH = "test.jpg";


    private JPanel tilePanel;
    private JPanel controlPanel;

    private JButton[][] tileMatrix;

    private int swapTileX = -1;
    private int swapTileY = -1;

    public Main() {
        super("Lab 6.1");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        controlPanel = new JPanel();
        JLabel exampleImage = new JLabel();
        exampleImage.setIcon(new ImageIcon(new ImageIcon(IMAGE_PATH).getImage().getScaledInstance(200, 200, Image.SCALE_DEFAULT)));
        controlPanel.add(exampleImage);

        GridLayout gridLayout = new GridLayout(NUMBER_OF_TILES, NUMBER_OF_TILES);
        gridLayout.setHgap(5);
        gridLayout.setVgap(5);
        tilePanel = new JPanel(gridLayout);
        tileMatrix = generateTiles(IMAGE_PATH);

        for (int i = 0; i < NUMBER_OF_TILES*NUMBER_OF_TILES; i++)
            swapTiles((int)(Math.random() * 4),
                      (int)(Math.random() * 4),
                      (int)(Math.random() * 4),
                      (int)(Math.random() * 4),
                      false);

        for (int i = 0; i < NUMBER_OF_TILES; i++)
            for (int j = 0; j < NUMBER_OF_TILES; j++)
                tilePanel.add(tileMatrix[i][j]);

        add(controlPanel, BorderLayout.WEST);
        add(tilePanel, BorderLayout.CENTER);
    }

    private  JButton[][] generateTiles(String imagePath) {
        try {
            BufferedImage wholeImage = ImageIO.read(new File(imagePath));
            int tileWidth = wholeImage.getWidth()/NUMBER_OF_TILES, tileHeight = wholeImage.getHeight()/NUMBER_OF_TILES;
            JButton[][] tiles = new JButton[NUMBER_OF_TILES][NUMBER_OF_TILES];
            for (int i = 0; i < NUMBER_OF_TILES; i++)
                for (int j = 0; j < NUMBER_OF_TILES; j++) {
                    tiles[i][j] = new JButton();
                    tiles[i][j].setIcon(new ImageIcon(wholeImage.getSubimage(j*tileWidth, i*tileHeight, tileWidth, tileHeight)));
                    tiles[i][j].setName(""+(i*NUMBER_OF_TILES+j));
                    tiles[i][j].putClientProperty(0, i);
                    tiles[i][j].putClientProperty(1, j);
                    tiles[i][j].addActionListener(e -> {
                        JButton b = ((JButton) e.getSource());
                        if (swapTileX == -1) {
                            b.setEnabled(false);
                            swapTileX = (int)b.getClientProperty(0);
                            swapTileY = (int)b.getClientProperty(1);
                        }
                        else {
                            swapTiles((int)b.getClientProperty(0), (int)b.getClientProperty(1), swapTileX, swapTileY, true);
                            checkCorrectness();
                            swapTileX = -1;
                        }
                    });
                }
            return tiles;

        } catch (IOException e) {
            return null;
        }
    }

    private void swapTiles(int tile1X, int tile1Y, int tile2X, int tile2Y, boolean repaint) {

        JButton tile1 =  tileMatrix[tile1X][tile1Y];
        JButton tile2 =  tileMatrix[tile2X][tile2Y];
        tile1.setEnabled(true);
        tile1.putClientProperty(0, tile2X);
        tile1.putClientProperty(1, tile2Y);
        tile2.setEnabled(true);
        tile2.putClientProperty(0, tile1X);
        tile2.putClientProperty(1, tile1Y);

        JButton temp = tileMatrix[tile1X][tile1Y];
        tileMatrix[tile1X][tile1Y] = tileMatrix[tile2X][tile2Y];
        tileMatrix[tile2X][tile2Y] = temp;

        if (repaint) {
            tilePanel.removeAll();
            for (int i = 0; i < NUMBER_OF_TILES; i++)
                for (int j = 0; j < NUMBER_OF_TILES; j++)
                    tilePanel.add(tileMatrix[i][j]);
            tilePanel.revalidate();
            tilePanel.repaint();
        }
    }

    void checkCorrectness() {
        for (int i = 0; i < NUMBER_OF_TILES; i++)
            for (int j = 0; j < NUMBER_OF_TILES; j++)
                if(Integer.parseInt(tileMatrix[i][j].getName()) != i*NUMBER_OF_TILES+j)
                    return;
        JOptionPane.showMessageDialog(null, "You've solved the puzzle!", "CONGRATULATIONS!", JOptionPane.INFORMATION_MESSAGE );
    }

    public static void main(String[] args) {
        Main app = new Main();
        app.setVisible(true);
    }
}
