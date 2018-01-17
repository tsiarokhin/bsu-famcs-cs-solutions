package me.termax.lab10;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.awt.event.*;

public class Main extends JFrame {

    private JPanel dragArea, statusPanel;
    private JLabel status;
    private JButton button;


    public static void main(String[] args) {
	    Main app = new Main();
	    app.setVisible(true);
    }

    public Main() {
        setTitle("Lab 10: Mouse and Key Events");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600,600);
        setLocationRelativeTo(null);

        statusPanel = new JPanel();
        statusPanel.setBorder(new BevelBorder(BevelBorder.RAISED));
        this.add(statusPanel, BorderLayout.SOUTH);
        status = new JLabel("X: 123, Y: 321");
        statusPanel.add(status);


        dragArea = new JPanel(null);
        this.add(dragArea, BorderLayout.CENTER);
        button = new JButton("Button");
        dragArea.add(button);
        button.setBounds(250,250, button.getPreferredSize().width, button.getPreferredSize().height);


        MouseMotionAdapter statusBarUpdater = new MouseMotionAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                updateStatusBar(e.getComponent(), e.getX(), e.getY());
            }
            @Override
            public void mouseDragged(MouseEvent e) {
                updateStatusBar(e.getComponent(), e.getX(), e.getY());
            }
        };
        dragArea.addMouseMotionListener(statusBarUpdater);
        button.addMouseMotionListener(statusBarUpdater);
        statusPanel.addMouseMotionListener(statusBarUpdater);
        button.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (e.getKeyChar() == KeyEvent.VK_BACK_SPACE) {
                    String buttonText = button.getText();
                    if (buttonText.length() > 0)
                        button.setText(buttonText.substring(0, buttonText.length()-1));
                }
                else
                    button.setText(button.getText() + e.getKeyChar());
                button.setSize(button.getPreferredSize());
            }
        });

        button.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                updateStatusBar(e.getComponent(), e.getX(), e.getY());
                if (e.isControlDown())
                    button.setLocation(e.getX()+button.getX()-button.getWidth()/2, e.getY()+button.getY()-button.getHeight()/2);
            }
        });

        dragArea.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                button.setLocation(e.getX()-button.getWidth()/2, e.getY()-button.getHeight()/2);
            }
        });
    }


    private void updateStatusBar(Component c, int x, int y) {
        x += c.getX();
        y += c.getY();
        status.setText("X: " + x + ", Y: " + y);
    }


}
