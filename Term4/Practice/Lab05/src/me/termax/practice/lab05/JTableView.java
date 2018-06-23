package me.termax.practice.lab05;

import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import java.awt.Component;
import java.util.HashSet;

import static javax.swing.ListSelectionModel.SINGLE_SELECTION;

public class JTableView extends JFrame {
    private JTable table;

    private JScrollPane tablePanel;

    public JTableView(DateTableModel model) {
        super("Lab 5");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(900, 562);
        setLocationRelativeTo(null);

        table = new JTable(model);
        table.setDefaultRenderer(String.class, new DefaultTableCellRenderer(){
            @Override
            public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
                if (column == 0)
                    setText("<html><b><i>"+(row+1)+"</b></i></html>");
                else
                    setText((value == null) ? "" : model.calculateCell((String)value, row, column, new HashSet<Integer>()));
                return this;
            }
        });
        table.getModel().addTableModelListener(e -> tablePanel.updateUI());
        table.setSelectionMode(SINGLE_SELECTION);
        table.getColumnModel().getColumn(0).setMaxWidth(20);
        table.setRowHeight(25);
        tablePanel = new JScrollPane(table);
        add(tablePanel);
        this.setVisible(true);
    }


}

