package me.termax.practice.lab08;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;

public class Menu extends JFrame {

    private JSlider bulletSpeed;
    private JSlider duckSpawnRate;
    private JButton confirmButton;

    public Menu() {
        super("Duck Hunt Settings");
        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 1));

        bulletSpeed = new JSlider(JSlider.HORIZONTAL, 10, 100, 20);
        bulletSpeed.setBorder(BorderFactory.createTitledBorder("Bullet Speed"));
        bulletSpeed.setMajorTickSpacing(10);
        bulletSpeed.setMinorTickSpacing(5);
        bulletSpeed.setPaintTicks(true);
        bulletSpeed.setPaintLabels(true);
        add(bulletSpeed);

        duckSpawnRate = new JSlider(JSlider.HORIZONTAL, 100, 2000, 1500);
        duckSpawnRate.setBorder(BorderFactory.createTitledBorder("Delay between ducks spawn"));
        duckSpawnRate.setMajorTickSpacing(200);
        duckSpawnRate.setMinorTickSpacing(50);
        duckSpawnRate.setPaintTicks(true);
        duckSpawnRate.setPaintLabels(true);
        add(duckSpawnRate);

        confirmButton = new JButton("Confirm");
        confirmButton.addActionListener(e -> {
            Settings.BULLET_SPEED = bulletSpeed.getValue();
            Settings.DUCK_SPAWN_RATE = duckSpawnRate.getValue();
            setVisible(false);
            Game game = new Game("Duck Hunt", 800, 500);
            game.start();
        });
        add(confirmButton);
        setVisible(true);
    }
}
