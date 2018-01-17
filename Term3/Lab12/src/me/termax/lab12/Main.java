package me.termax.lab12;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class Main extends JFrame {
    private JTabbedPane tabbedPane;
    private JPanel listTab, gridTab, radioTab;

    private final int GRID_N = 5;

    private JList leftList, rightList;
    private DefaultListModel<Integer> leftListModel, rightListModel;
    private JButton moveToRight, moveToLeft;

    public static void main(String[] args) {
        Main app = new Main();
        app.setVisible(true);
    }

    private void initListTab() {
        listTab.setLayout(new BorderLayout());
        leftListModel = new DefaultListModel<Integer>();
        rightListModel = new DefaultListModel<Integer>();

        Random random = new Random();
        for (int i = 0; i < 10; i++)
            leftListModel.addElement(random.nextInt(1000));

        leftList = new JList<Integer>(leftListModel);
        rightList = new JList<Integer>(rightListModel);

        leftList.setVisibleRowCount(-1);
        rightList.setVisibleRowCount(-1);

        JScrollPane leftListScroller = new JScrollPane(leftList);
        leftListScroller.setPreferredSize(new Dimension(150, 400));

        JScrollPane rightListScroller = new JScrollPane(rightList);
        rightListScroller.setPreferredSize(new Dimension(150, 400));

        listTab.add(leftListScroller, BorderLayout.WEST);
        listTab.add(rightListScroller, BorderLayout.EAST);

        JPanel center = new JPanel(new BorderLayout());
        moveToRight = new JButton(">>");
        moveToRight.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int indices[] = leftList.getSelectedIndices();
                moveElements(indices, leftListModel, rightListModel);
            }
        });

        moveToLeft = new JButton("<<");
        moveToLeft.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int indices[] = rightList.getSelectedIndices();
                moveElements(indices, rightListModel, leftListModel);
            }
        });

        center.add(moveToRight, BorderLayout.NORTH);
        center.add(moveToLeft, BorderLayout.SOUTH);
        listTab.add(center, BorderLayout.CENTER);

    }

    private void initGridTab() {
        gridTab.setLayout(new GridLayout(GRID_N, GRID_N));

        MouseListener mListener = new MouseAdapter() {
            private String oldText;

            @Override
            public void mousePressed(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON1) {
                    JButton b = (JButton)e.getSource();
                    oldText = b.getText();
                    b.setText("PRESSED!");
                }
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON1) {
                    ((JButton)e.getSource()).setText(oldText);
                }
            }

            @Override
            public void mouseEntered(MouseEvent e) {
                ((JButton)e.getSource()).setBackground(Color.GREEN);
            }

            @Override
            public void mouseExited(MouseEvent e) {
                ((JButton)e.getSource()).setBackground(null);
            }
        };

        for (int i = 0; i < GRID_N * GRID_N; i++) {
            JButton b = new JButton(Integer.toString(i+1));
            b.addMouseListener(mListener);
            gridTab.add(b);
        }


    }

    private void initRadioTab() {
        radioTab.setLayout(new BoxLayout(radioTab, BoxLayout.Y_AXIS));
        ButtonGroup bg = new ButtonGroup();
        final String[] cities = {"Минск", "Гомель", "Брест", "Гродно", "Витебск", "Могилев"};
        for (String city: cities) {
            JRadioButton b = new JRadioButton(city, new ImageIcon(city+".png"));
            b.setSelectedIcon(new ImageIcon(city+"_s.png"));
            b.setRolloverIcon(new ImageIcon(city+"_r.png"));
            bg.add(b);
            radioTab.add(b);
        }
    }

    private void moveElements(int[] indices, DefaultListModel<Integer> from,  DefaultListModel<Integer> to) {
        for (int index : indices)
            to.addElement(from.get(index));
        for (int i = indices.length-1; i >= 0; i--)
            from.remove(indices[i]);
    }


    public Main() {
        setTitle("Lab 12: Tabbed Pane");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 500);
        setLocationRelativeTo(null);

        tabbedPane = new JTabbedPane();
        this.add(tabbedPane);

        listTab = new JPanel(); initListTab();
        gridTab = new JPanel(); initGridTab();
        radioTab = new JPanel(); initRadioTab();

        tabbedPane.addTab("Lists", listTab);
        tabbedPane.addTab("Buttons", gridTab);
        tabbedPane.addTab("Radio Buttons", radioTab);
    }

}
