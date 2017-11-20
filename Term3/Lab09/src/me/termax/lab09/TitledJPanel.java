package me.termax.lab09;

import javax.swing.*;

public class TitledJPanel extends JPanel {
    public TitledJPanel(String title) {
        super();
        this.setBorder(BorderFactory.createTitledBorder(title));
    }
}
