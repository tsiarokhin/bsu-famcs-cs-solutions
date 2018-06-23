package me.termax.practice.lab03;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.labels.PieSectionLabelGenerator;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import org.jfree.chart.plot.PiePlot;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;


public class Main extends JFrame {
    private JTabbedPane tabbedPane;

    private ClockTab clockTab;

    private JPanel imageSpinTab;
    private ImageSpin imageSpin;
    private JSlider spinSpeed;
    private JComboBox<String> spinDirection;

    private JPanel diagramTab;

    public Main() {
        super("Practice 3");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(530, 550);
        setLocationRelativeTo(null);
        tabbedPane = new JTabbedPane();
        add(tabbedPane, BorderLayout.CENTER);

        clockTab = new ClockTab();
        tabbedPane.add(clockTab, "2.1: Clock");

        imageSpinTab = new JPanel(new BorderLayout());
        spinSpeed = new JSlider(JSlider.HORIZONTAL, 1, 100, 10);
        imageSpinTab.add(spinSpeed, BorderLayout.NORTH);
        String directions[] = {"Clockwise", "Anticlockwise"};
        spinDirection = new JComboBox<String>(directions);
        spinDirection.addActionListener(e -> {
            if (spinDirection.getSelectedIndex() == 0)
                imageSpin.setDirection(1);
            else
                imageSpin.setDirection(-1);
        });
        imageSpinTab.add(spinDirection, BorderLayout.SOUTH);
        imageSpin = new ImageSpin();
        imageSpinTab.add(imageSpin);
        tabbedPane.add(imageSpinTab, "2.2: Image Spin");

        diagramTab = new JPanel(new BorderLayout());
        tabbedPane.add(diagramTab, "2.3: Diagram");
        initDiagramTab(diagramTab);

    }

    public static void main(String[] args) {
        Main app = new Main();
        app.setVisible(true);
    }

    private class ClockTab extends JPanel {
        private int sec;
        private Timer clockTimer;

        public ClockTab() {
            super();
            sec = 0;
            clockTimer = new Timer(1000, e -> {
                sec = (sec+1)%60;
                clockTab.repaint();
            });
            clockTimer.start();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setStroke(new BasicStroke(2));
            int maxX = this.getSize().width;
            int maxY = this.getSize().height;

            g2d.draw(new Ellipse2D.Double(0,0,maxX,maxY));
            g2d.draw(
                    new Line2D.Double(
                            maxX/2,
                            maxY/2,
                            maxX/2+maxX/2*Math.sin((double)sec/60*2*Math.PI),
                            maxY/2-maxY/2*Math.cos((double)sec/60*2*Math.PI)
                    )
            );
        }
    }


    private class ImageSpin extends JPanel {
        private Image img;
        private Timer spinTimer;
        private double rotation;
        private int direction;
        private final int IMG_SIZE = 80;

        public ImageSpin() {
            super(null);
            rotation = 0;
            direction = 1;
            img = new ImageIcon("spinner.gif").getImage().getScaledInstance(IMG_SIZE, IMG_SIZE, Image.SCALE_DEFAULT);
            spinTimer = new Timer(10, e -> {
                double dRotation = spinSpeed.getValue()/10;
                rotation = (rotation+direction*dRotation)%360;
                repaint();
            });
            spinTimer.start();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            rh.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);

            g2d.setRenderingHints(rh);
            g2d.setStroke(new BasicStroke(2));
            int maxX = this.getSize().width-IMG_SIZE;
            int maxY = this.getSize().height-IMG_SIZE;
            double x = maxX/2+maxX/2*Math.sin(rotation/180*Math.PI);
            double y = maxY/2-maxY/2*Math.cos(rotation/180*Math.PI);

            g2d.draw(new Ellipse2D.Double(IMG_SIZE/2,IMG_SIZE/2,maxX,maxY));
            g2d.drawImage(img, (int)x, (int)y, null);
        }

        public int getDirection() {
            return direction;
        }

        public void setDirection(int direction) {
            this.direction = direction;
        }
    }

    private void initDiagramTab(JPanel tab) {
        try {
            Scanner in = new Scanner(new File("data.txt"));
            int n = in.nextInt();
            if (n <= 0)
                throw new IllegalArgumentException("non positive number of categories");
            DefaultPieDataset dataset = new DefaultPieDataset();
            String categoryName;
            int value;
            for (int i = 0; i < n; i++){
                categoryName = in.next();
                value = in.nextInt();
                if (value < 0)
                    throw new IllegalArgumentException("negative category value");
                dataset.setValue(categoryName, value);
            }
            JFreeChart chart = ChartFactory.createPieChart(
                    "Very important data",
                     dataset,
                    true,
                    true,
                    false);

            //Format Label
            PieSectionLabelGenerator labelGenerator = new StandardPieSectionLabelGenerator(
                    "{0}: {1}", new DecimalFormat("0"), new DecimalFormat("0%"));
            ((PiePlot) chart.getPlot()).setLabelGenerator(labelGenerator);

            // Create Panel
            ChartPanel panel = new ChartPanel(chart);
            tab.add(panel, BorderLayout.CENTER);

        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(null, "Dataset not found" );
        } catch (IllegalArgumentException | NoSuchElementException  e) {
            JOptionPane.showMessageDialog(null, "Illegal input format: " + e.getMessage());
        }





    }

}
