package me.termax.lab09;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class SeriesGUI extends JFrame{
    private SeriesGUI app;

    private JPanel panelNorth, panelCenter, panelEast;

    private JPanel seriesPanel;
    private JPanel seriesStringPanel, seriesSumPanel;
    private JLabel seriesString, seriesSum;

    private JPanel paramPanel;
    private JLabel firstLabel, deltaLabel, nLabel;
    private JTextField firstText, deltaText, nText;

    private JPanel seriesTypePanel, buttonsPanel;
    private JRadioButton linearButton, exponentialButton;
    private JButton updateButton, saveButton;

    private Series series;

    public static void main(String[] args) {
        SeriesGUI app = new SeriesGUI();
        app.setVisible(true);
    }

    public SeriesGUI(){
        app = this;
        setTitle("Lab 9: Series");
        setSize(500, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        series = new LinearSeries(1, 2, 10);
        initComponents(getContentPane());
    }

    private void initComponents(Container c) {
        panelNorth = new JPanel(new BorderLayout());
        c.add(panelNorth, BorderLayout.NORTH);

        seriesPanel = new JPanel(new BorderLayout());
        panelNorth.add(seriesPanel, BorderLayout.CENTER);

        seriesStringPanel = new TitledJPanel("Series");
        seriesString = new JLabel(series.toString());
        seriesStringPanel.add(seriesString);
        seriesPanel.add(seriesStringPanel, BorderLayout.CENTER);

        seriesSumPanel = new TitledJPanel("Sum");
        seriesSumPanel.setPreferredSize(new Dimension(70, 0));
        seriesSum = new JLabel(String.valueOf(series.sum()));
        seriesSumPanel.add(seriesSum);
        seriesPanel.add(seriesSumPanel, BorderLayout.EAST);


        panelCenter = new JPanel(new BorderLayout());
        c.add(panelCenter, BorderLayout.CENTER);

        paramPanel = new TitledJPanel("Parameters");
        paramPanel.setLayout(new GridLayout(3, 2));
        panelCenter.add(paramPanel, BorderLayout.CENTER);

        paramPanel.add(firstLabel = new JLabel("First: "));
        paramPanel.add(firstText = new JTextField(String.valueOf(series.getFirst())));
        paramPanel.add(deltaLabel = new JLabel("Delta: "));
        paramPanel.add(deltaText = new JTextField(String.valueOf(series.getDelta())));
        paramPanel.add(nLabel = new JLabel("# of elements: "));
        paramPanel.add(nText = new JTextField(String.valueOf(series.getN())));

        panelEast = new JPanel(new BorderLayout());
        c.add(panelEast, BorderLayout.EAST);

        seriesTypePanel = new TitledJPanel("Series type");
        panelEast.add(seriesTypePanel, BorderLayout.CENTER);

        ButtonGroup bg = new ButtonGroup();
        bg.add(linearButton = new JRadioButton("Linear", true));
        linearButton.addActionListener(new LinearButtonClicked());
        bg.add(exponentialButton = new JRadioButton("Exponential", false));
        exponentialButton.addActionListener(new ExponentialButtonClicked());

        seriesTypePanel.add(linearButton);
        seriesTypePanel.add(exponentialButton);

        buttonsPanel = new JPanel(new BorderLayout());
        buttonsPanel.add(saveButton = new JButton("Save as..."), BorderLayout.NORTH);
        saveButton.addActionListener(new SaveButtonClicked());
        buttonsPanel.add(updateButton = new JButton("Update"), BorderLayout.SOUTH);
        updateButton.addActionListener(new UpdateButtonClicked());


        panelEast.add(buttonsPanel, BorderLayout.SOUTH);

    }

    private void syncGUIwithSeriesObject() {
        seriesString.setText(series.toString());
        seriesSum.setText(String.valueOf(series.sum()));

        firstText.setText(String.valueOf(series.getFirst()));
        deltaText.setText(String.valueOf(series.getDelta()));
        nText.setText(String.valueOf(series.getN()));
        if (series instanceof LinearSeries)
            linearButton.setSelected(true);
        if (series instanceof  ExponentialSeries)
            exponentialButton.setSelected(true);
    }



    private class LinearButtonClicked implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            series = new LinearSeries(series);
            syncGUIwithSeriesObject();
        }
    }

    private class ExponentialButtonClicked implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            series = new ExponentialSeries(series);
            syncGUIwithSeriesObject();
        }
    }

    private class UpdateButtonClicked implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                double first = Double.parseDouble(firstText.getText());
                double delta = Double.parseDouble(deltaText.getText());
                int n = Integer.parseInt(nText.getText());

                series.setFirst(first);
                series.setDelta(delta);
                series.setN(n);

                syncGUIwithSeriesObject();
            } catch (NumberFormatException err) {
                JOptionPane.showMessageDialog(app, "Incorrect format of parameters");
            }

        }
    }

    private class SaveButtonClicked implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showSaveDialog(app) == JFileChooser.APPROVE_OPTION) {
                File outputFile = fileChooser.getSelectedFile();
                try {
                    series.toFile(outputFile);
                } catch (IOException e1) {
                    JOptionPane.showMessageDialog(app, "File cannot be saved to this location");
                }
            }
        }
    }
}
