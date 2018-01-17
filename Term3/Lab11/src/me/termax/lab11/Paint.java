package me.termax.lab11;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Paint extends JFrame {

    private static Paint app;
    private Canvas canvas;
    private JPanel configPanel;
    private JButton openButton, openTxtButton;
    private JButton saveButton, saveTxtButton;
    private JButton chooseColor;
    private Color currentColor;
    private Image img;


    public Paint() {
        super("Lab 11: Paint");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        img = null;

        Container c = this.getContentPane();

        canvas = new Canvas();
        JScrollPane scrollPane = new JScrollPane(canvas);
        configPanel = new JPanel();


        chooseColor = new JButton("Color...");
        chooseColor.setIcon(new ImageIcon("color.png"));
        currentColor = Color.black;
        chooseColor.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color chosenColor = JColorChooser.showDialog(app, "Choose color", currentColor);
                if (chosenColor != null)
                    currentColor = chosenColor;
            }
        });
        configPanel.add(chooseColor);

        openButton = new JButton("Open");
        openButton.setIcon(new ImageIcon("open.png"));
        openButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(app) == JFileChooser.APPROVE_OPTION) {
                    File inputFile = fileChooser.getSelectedFile();
                    try {
                        img = ImageIO.read(inputFile);
                        canvas.clear();
                    } catch (IOException e1) {
                        JOptionPane.showMessageDialog(app, "File cannot be opened");
                    }
                }
            }
        });
        configPanel.add(openButton);

        saveButton = new JButton("Save");
        saveButton.setIcon(new ImageIcon("save.png"));
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setSelectedFile(new File("image.png"));
                if (fileChooser.showSaveDialog(app) == JFileChooser.APPROVE_OPTION) {
                    File outputFile = fileChooser.getSelectedFile();
                    try {
                        BufferedImage im = new BufferedImage(c.getWidth(), c.getHeight(), BufferedImage.TYPE_INT_ARGB);
                        canvas.paint(im.getGraphics());
                        ImageIO.write(im, "PNG", outputFile);
                    } catch (IOException e1) {
                        JOptionPane.showMessageDialog(app, "File cannot be saved to this location");
                    }
                }
            }
        });
        configPanel.add(saveButton);

        saveTxtButton = new JButton("Save to txt");
        saveTxtButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setSelectedFile(new File("image.txt"));
                if (fileChooser.showSaveDialog(app) == JFileChooser.APPROVE_OPTION) {
                    File outputFile = fileChooser.getSelectedFile();
                    try {
                        PrintWriter out = new PrintWriter(outputFile);
                        for (CanvasLine line: canvas.getLines()) {
                            out.println(line.toTxt());
                        }
                        out.close();
                    } catch (IOException e1) {
                        JOptionPane.showMessageDialog(app, "File cannot be saved to this location");
                    }
                }
            }
        });
        configPanel.add(saveTxtButton);

        openTxtButton = new JButton("Open from txt");
        openTxtButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(app) == JFileChooser.APPROVE_OPTION) {
                    File inputFile = fileChooser.getSelectedFile();
                    try {
                        canvas.clear();
                        Scanner in = new Scanner(inputFile);
                        while (in.hasNextLine()){
                            canvas.getLines().add(new CanvasLine(in.nextLine()));
                        }
                        canvas.repaint();
                    } catch (IOException err) {
                        JOptionPane.showMessageDialog(app, "File cannot be opened");
                    } catch (InputMismatchException err) {
                        JOptionPane.showMessageDialog(app, "Illegal input file format");
                    }
                }
            }
        });
        configPanel.add(openTxtButton);

        c.add(scrollPane, BorderLayout.CENTER);
        c.add(configPanel, BorderLayout.SOUTH);
    }

    public static void main(String[] args) {
	    app = new Paint();
	    app.setSize(600,600);
	    app.setLocationRelativeTo(null);
	    app.setVisible(true);
    }

    public Color getCurrentColor() {
        return currentColor;
    }

    public Image getBackgroundImage() {
        return img;
    }
}
