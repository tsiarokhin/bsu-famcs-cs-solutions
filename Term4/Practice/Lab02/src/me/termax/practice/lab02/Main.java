package me.termax.practice.lab02;


import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.text.NumberFormatter;
import javax.swing.tree.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.text.NumberFormat;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Main extends JFrame {

    private JTabbedPane tabbedPane;

    private JPanel countriesTab, countriesInfo;
    private JList<Country> countryList;
    private DefaultListModel<Country> countryListModel;
    private JLabel countryFlag, countryName, countryCapital;


    private JMenu tourMenu;
    private JPanel toursTab;
    private JTable tourTable, tourSummary;
    private DefaultTableModel tourTableModel;

    private JPanel studentsTab;
    private JMenu studentMenu;
    private JTree studentTree;
    private DefaultMutableTreeNode[] studentCourses;
    private DefaultMutableTreeNode[][] studentGroups;

    public static void main(String[] args) {
        Main app = new Main();
        app.setVisible(true);
    }


    public Main() {
        super("Practice 2");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 400);
        setLocationRelativeTo(null);

        tabbedPane = new JTabbedPane();
        add(tabbedPane, BorderLayout.CENTER);

        countriesTab = new JPanel(new BorderLayout());
        tabbedPane.add(countriesTab, "2.1: Countries");
        initCountriesTab(countriesTab);

        toursTab = new JPanel(new BorderLayout());
        tabbedPane.add(toursTab, "2.2: Tours");
        initToursTab(toursTab);

        studentsTab = new JPanel(new BorderLayout());
        tabbedPane.add(studentsTab, "2.3: Students");
        initStudentsTab(studentsTab);



        JMenuBar menuBar = new JMenuBar();
        add(menuBar, BorderLayout.NORTH);

        tourMenu = new JMenu("Tours");
        JMenuItem addTour = new JMenuItem("Add tour");
        addTour.addActionListener(e -> tourTableModel.setRowCount(tourTableModel.getRowCount()+1));
        tourMenu.add(addTour);

        studentMenu = new JMenu("Students");
        JMenuItem addStudent = new JMenuItem("Add student");
        addStudent.addActionListener(new AddStudent());
        studentMenu.add(addStudent);
        JMenuItem editStudent = new JMenuItem("Edit selected student");
        editStudent.addActionListener(new EditStudent());
        studentMenu.add(editStudent);
        JMenuItem removeStudent = new JMenuItem("Remove selected student");
        removeStudent.addActionListener(new RemoveStudent());
        studentMenu.add(removeStudent);


        menuBar.add(new JMenu("Countries"));
        menuBar.add(tourMenu);
        menuBar.add(studentMenu);

    }

    private void initCountriesTab(JPanel tab) {
        countryListModel = new DefaultListModel<>();
        countryList = new JList<>(countryListModel);
        countryList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        tab.add(new JScrollPane(countryList), BorderLayout.CENTER);
        Map<String, String> capitals = new TreeMap<String, String>() {{
            put("afghanistan", "Kabul");
            put("albania", "Tirana");
            put("algeria", "Algiers");
            put("american samoa", "Pago Pago");
            put("andorra", "Andorra la Vella");
            put("angola", "Luanda");
            put("anguilla", "The Valley");
            put("antigua and barbuda", "Saint John's");
            put("argentina", "Buenos Aires");
            put("armenia", "Yerevan");
            put("aruba", "Oranjestad");
            put("australia", "Canberra");
            put("austria", "Vienna");
            put("azerbaijan", "Baku");
            put("bahamas", "Nassau");
            put("bahrain", "Manama");
            put("bangladesh", "Dhaka");
            put("barbados", "Bridgetown");
            put("belarus", "Minsk");
            put("belgium", "Brussels");
            put("belize", "Belmopan");
            put("benin", "Porto-Novo");
            put("bermuda", "Hamilton");
            put("bhutan", "Thimphu");
            put("bolivia", "La Paz");
            put("bosnia and herzegovina", "Sarajevo");
            put("botswana", "Gaborone");
            put("brazil", "Brasilia");
            put("british indian ocean territory", "Diego Garcia");
            put("british virgin islands", "Road Town");
            put("brunei", "Bandar Seri Begawan");
            put("bulgaria", "Sofia");
            put("burkina faso", "Ouagadougou");
            put("burma", "Naypyidaw");
            put("burundi", "Bujumbura");
            put("cambodia", "Phnom Penh");
            put("cameroon", "Yaounde");
            put("canada", "Ottawa");
            put("cape verde", "Praia");
            put("cayman islands", "George Town");
            put("central african republic", "Bangui");
            put("chad", "N'Djamena");
            put("chile", "Santiago");
            put("china", "Beijing");
            put("colombia", "Bogota");
            put("comoros", "Moroni");
            put("congo democratic republic", "Kinshasa");
            put("congo republic", "Brazzaville");
            put("cook islands", "Avarua");
            put("costa rica", "San Jose");
            put("cote divoire", "Yamoussoukro");
            put("croatia", "Zagreb");
            put("cuba", "Havana");
            put("cyprus", "Nicosia");
            put("czech republic", "Prague");
            put("denmark", "Copenhagen");
            put("djibouti", "Djibouti");
            put("dominica", "Roseau");
            put("dominican republic", "Santo Domingo");
            put("east timor", "Dili");
            put("egypt", "Cairo");
            put("el salvador", "San Salvador");
            put("england", "London");
            put("equador", "Quito");
            put("equatorial guinea", "Malabo");
            put("eritrea", "Asmara");
            put("estonia", "Tallinn");
            put("ethiopia", "Addis Ababa");
            put("falkland islands", "Stanley");
            put("faroe islands", "Torshavn");
            put("fiji", "Suva");
            put("finland", "Helsinki");
            put("france", "Paris");
            put("french polynesia", "Papeete");
            put("gabon", "Libreville");
            put("gambia", "Banjul");
            put("georgia", "Tbilisi");
            put("germany", "Berlin");
            put("ghana", "Accra");
            put("gibraltar", "Gibraltar");
            put("great britain", "Athens");
            put("greece", "Nuuk");
            put("greenland", "Saint George's");
            put("grenada", "Hagatna");
            put("guam", "Guatemala City");
            put("guatemala", "Saint Peter Port");
            put("guernsey", "Conakry");
            put("guinea", "Bissau");
            put("guinea bissau", "Georgetown");
            put("guyana", "Port-au-Prince");
            put("haiti", "Port-au-Prince");
            put("honduras", "Tegucigalpa");
            put("hong kong", "Hong Kong");
            put("hungary", "Budapest");
            put("iceland", "Reykjavik");
            put("india", "New Delhi");
            put("indonesia", "Jakarta");
            put("iran", "Tehran");
            put("iraq", "Baghdad");
            put("ireland", "Dublin");
            put("isle of man", "Douglas");
            put("israel", "Jerusalem");
            put("italy", "Rome");
            put("jamaica", "Kingston");
            put("japan", "Tokyo");
            put("jersey", "Saint Helier");
            put("jordan", "Amman");
            put("kazakhstan", "Astana");
            put("kenya", "Nairobi");
            put("kiribati", "Tarawa");
            put("kuwait", "Kuwait City");
            put("kyrgyzstan", "Bishkek");
            put("laos", "Vientiane");
            put("latvia", "Riga");
            put("lebanon", "Beirut");
            put("lesotho", "Maseru");
            put("liberia", "Monrovia");
            put("libya", "Tripoli");
            put("liechtenstein", "Vaduz");
            put("lithuania", "Vilnius");
            put("luxembourg", "Luxembourg");
            put("macau", "N/A");
            put("macedonia", "Skopje");
            put("madagascar", "Antananarivo");
            put("malawi", "Lilongwe");
            put("malaysia", "Kuala Lumpur");
            put("maledives", "Male");
            put("mali", "Bamako");
            put("malta", "Valletta");
            put("marshall islands", "Majuro");
            put("martinique", "Fort-de-France");
            put("mauretania", "Nouakchott");
            put("mauritius", "Port Louis");
            put("mexico", "Mexico City");
            put("micronesia", "Palikir");
            put("moldova", "Chisinau");
            put("monaco", "Monaco");
            put("mongolia", "Ulaanbaatar");
            put("montserrat", "Plymouth");
            put("morocco", "Rabat");
            put("mozambique", "Maputo");
            put("namibia", "Windhoek");
            put("nauru", "Yaren");
            put("nepal", "Kathmandu");
            put("netherlands", "Amsterdam");
            put("netherlands antilles", "Willemstad");
            put("new zealand", "Wellington");
            put("nicaragua", "Managua");
            put("niger", "Niamey");
            put("nigeria", "Abuja");
            put("niue", "Alofi");
            put("norfolk island", "Kingston");
            put("northern mariana islands", "Saipan");
            put("north korea", "Pyongyang");
            put("norway", "Oslo");
            put("oman", "Muscat");
            put("pakistan", "Islamabad");
            put("palau", "Melekeok");
            put("panama", "Panama City");
            put("papua new guinea", "Port Moresby");
            put("paraquay", "Asuncion");
            put("peru", "Lima");
            put("philippines", "Manila");
            put("pitcairn islands", "Adamstown");
            put("poland", "Warsaw");
            put("portugal", "Lisbon");
            put("puerto rico", "San Juan");
            put("qatar", "Doha");
            put("romania", "Bucharest");
            put("russia", "Moscow");
            put("rwanda", "Kigali");
            put("saint helena", "Jamestown");
            put("saint kitts and nevis", "Basseterre");
            put("saint lucia", "Castries");
            put("saint pierre and miquelon", "Saint-Pierre");
            put("saint vincent and the grenadines", "Kingstown");
            put("samoa", "Apia");
            put("san marino", "San Marino");
            put("sao tome and principe", "Sao Tome");
            put("saudi arabia", "Riyadh");
            put("scotland", "Edinburgh");
            put("senegal", "Dakar");
            put("serbia montenegro", "Belgrade");
            put("seychelles", "Victoria");
            put("sierra leone", "Freetown");
            put("singapore", "Singapore");
            put("slovakia", "Bratislava");
            put("slovenia", "Ljubljana");
            put("solomon islands", "Honiara");
            put("somalia", "Mogadishu");
            put("south africa", "Pretoria");
            put("south georgia", "King Edward Point");
            put("south korea", "Seoul");
            put("spain", "Madrid");
            put("sri lanka", "Colombo");
            put("sudan", "Khartoum");
            put("suriname", "Paramaribo");
            put("swaziland", "Mbabane");
            put("sweden", "Stockholm");
            put("switzerland", "Bern");
            put("syria", "Damascus");
            put("taiwan", "Taipei");
            put("tajikistan", "Dushanbe");
            put("tanzania", "Dar es Salaam");
            put("thailand", "Bangkok");
            put("tibet", "Lhasa");
            put("togo", "Lome");
            put("tonga", "Nuku'alofa");
            put("trinidad and tobago", "Port of Spain");
            put("tunisia", "Tunis");
            put("turkey", "Ankara");
            put("turkmenistan", "Ashgabat");
            put("turks and caicos islands", "Grand Turk");
            put("tuvalu", "Funafuti");
            put("uganda", "Kampala");
            put("ukraine", "Kyiv");
            put("united arab emirates", "Abu Dhabi");
            put("uruquay", "Montevideo");
            put("usa", "Washington");
            put("uzbekistan", "Tashkent");
            put("vanuatu", "Port-Vila");
            put("vatican city", "Vatican City");
            put("venezuela", "Caracas");
            put("vietnam", "Hanoi");
            put("virgin islands", "Charlotte Amalie");
            put("wales", "Cardiff");
            put("wallis and futuna", "Mata-Utu");
            put("yemen", "Sanaa");
            put("zambia", "Lusaka");
            put("zimbabwe", "Harare");
        }};

        capitals.forEach(
                (country, capital) -> countryListModel.addElement(
                        new Country(
                                country,
                                capital,
                                new ImageIcon("flags/flag_"+country.replace(' ', '_')+".png")
                        )
                )
        );

        countriesInfo = new JPanel();
        countriesInfo.setLayout(new BoxLayout(countriesInfo, BoxLayout.Y_AXIS));
        tab.add(countriesInfo, BorderLayout.EAST);

        countryFlag = new JLabel();
        countryName = new JLabel();
        countryCapital = new JLabel();

        countriesInfo.add(countryFlag);
        countriesInfo.add(countryName);
        countriesInfo.add(countryCapital);

        countryList.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                Country c = countryList.getSelectedValue();
                countryFlag.setIcon(c.getFlag());
                countryName.setText(c.getName().toUpperCase());
                countryCapital.setText("Capital: " + c.getCapital());
            }
        });

        countryList.setSelectedIndex(0);
    }

    private void initToursTab(JPanel tab) {
        String colNames[] = {"Flag", "Description", "Price", "Selected"};
        Object[][] data = {
                {new ImageIcon("flags/flag_belarus.png"), "Minsk City Tour", 100, false},
                {new ImageIcon("flags/flag_egypt.png"), "Weekend in Hurgada ", 1299, false},
                {new ImageIcon("flags/flag_great_britain.png"), "London sights", 3999, false},
                {new ImageIcon("flags/flag_usa.png"), "New York in One Day", 5500, false},
        };
        tourTableModel = new DefaultTableModel(data, colNames);
        tourTable = new JTable(tourTableModel) {
            @Override
            public Class<?> getColumnClass(int column) {
                switch (column) {
                    case 0:
                        return ImageIcon.class;
                    case 1:
                        return String.class;
                    case 2:
                        return Integer.class;
                    case 3:
                        return Boolean.class;
                    default:
                        return super.getColumnClass(column);
                }
            }

        };
        tab.add(new JScrollPane(tourTable), BorderLayout.CENTER);
        tourTable.setRowHeight(40);
        tourTable.getTableHeader().setReorderingAllowed(false);
        tourTable.getModel().addTableModelListener(e -> {
            if (e.getColumn() == 3) {
                int row = e.getFirstRow();
                boolean check = (Boolean)tourTable.getValueAt(row, 3);
                if (check)
                    tourSummary.setValueAt(
                            (Integer)tourSummary.getValueAt(0,3)+
                                    (Integer)tourTable.getValueAt(row, 2), 0, 3
                    );
                else
                    tourSummary.setValueAt(
                            (Integer)tourSummary.getValueAt(0,3)-
                                    (Integer)tourTable.getValueAt(row, 2), 0, 3
                    );
            }
        });

        tourSummary = new JTable(1,4) {
            DefaultTableCellRenderer renderRight = new DefaultTableCellRenderer();

            {
                renderRight.setHorizontalAlignment(SwingConstants.RIGHT);
            }

            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }

            @Override
            public TableCellRenderer getCellRenderer(int row, int column) {
                return renderRight;
            }
        };
        tourSummary.setValueAt("<html><b>Total:</b></html>", 0, 2);
        tourSummary.setValueAt(0, 0, 3);
        tab.add(tourSummary, BorderLayout.SOUTH);


    }

    private void initStudentsTab(JPanel tab) {
        try {
            DefaultMutableTreeNode root = new DefaultMutableTreeNode("Students");
            DefaultTreeModel treeModel = new DefaultTreeModel(root);
            studentTree = new JTree(treeModel);
            //studentTree.setEditable(true);
            studentTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

            ImageIcon studentIcon = new ImageIcon("student.png");
            ImageIcon courseIcon = new ImageIcon("course.jpg");
            DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
            renderer.setLeafIcon(studentIcon);
            renderer.setOpenIcon(courseIcon);
            renderer.setClosedIcon(courseIcon);
            studentTree.setCellRenderer(renderer);

            tab.add(new JScrollPane(studentTree), BorderLayout.CENTER);

            studentCourses = new DefaultMutableTreeNode[5];
            studentGroups = new DefaultMutableTreeNode[5][13];

            Scanner in = new Scanner(new File("students.txt"));
            while (in.hasNext()) {
                int course = in.nextInt();
                int group = in.nextInt();
                String studentName = in.nextLine();
                addStudent(course-1, group-1, studentName);
            }

        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    private void insertNode(JTree tree, DefaultMutableTreeNode parent, DefaultMutableTreeNode node){
        ((DefaultTreeModel)tree.getModel()).insertNodeInto(node, parent, parent.getChildCount());
    }

    private void addStudent(int course, int group, Object student) {
        DefaultMutableTreeNode root = (DefaultMutableTreeNode)studentTree.getModel().getRoot();
        if (studentCourses[course] == null){
            studentCourses[course] = new DefaultMutableTreeNode("" + (course+1) + " course"){
                @Override
                public boolean isLeaf() {
                    return false;
                }
            };
            insertNode(studentTree, root, studentCourses[course]);
        }
        if (studentGroups[course][group] == null) {
            studentGroups[course][group] = new DefaultMutableTreeNode("" + (group+1) + " group"){
                @Override
                public boolean isLeaf() {
                    return false;
                }
            };
            insertNode(studentTree, studentCourses[course], studentGroups[course][group]);
        }
        DefaultMutableTreeNode toInsert;
        if (student instanceof DefaultMutableTreeNode) {
            toInsert = (DefaultMutableTreeNode)student;
        }
        else {
            toInsert = new DefaultMutableTreeNode(student);
        }
        insertNode(studentTree, studentGroups[course][group], toInsert);
        studentTree.setSelectionPath(new TreePath(toInsert.getPath()));
    }

    private class StudentInfo {
        public StudentInfo(String name, int course, int group) {
            this.name = name;
            this.course = course;
            this.group = group;
        }

        public String name;
        public int course;
        public int group;
    }

    private StudentInfo showStudentEditDialog(String defaultName) {
        NumberFormat intFormat = NumberFormat.getIntegerInstance();

        NumberFormatter numberFormatter = new NumberFormatter(intFormat);
        numberFormatter.setValueClass(Integer.class);
        numberFormatter.setAllowsInvalid(false);
        numberFormatter.setMinimum(1);

        JTextField name = new JTextField(defaultName, 15);
        JFormattedTextField course = new JFormattedTextField(numberFormatter);
        JFormattedTextField group = new JFormattedTextField(numberFormatter);
        course.setColumns(3);
        group.setColumns(3);


        JPanel dialogPanel = new JPanel();
        dialogPanel.add(new JLabel("Name:"));
        dialogPanel.add(name);
        dialogPanel.add(Box.createHorizontalStrut(10));
        dialogPanel.add(new JLabel("Course"));
        dialogPanel.add(course);
        dialogPanel.add(Box.createHorizontalStrut(10));
        dialogPanel.add(new JLabel("Group:"));
        dialogPanel.add(group);

        int result = JOptionPane.showConfirmDialog(null, dialogPanel,
                "Edit student", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            return new StudentInfo(name.getText(), (Integer)course.getValue(), (Integer)group.getValue());
        }
        else return null;
    }

    private class AddStudent implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            StudentInfo st = showStudentEditDialog("");
            if (st != null)
                addStudent(st.course-1, st.group-1, st.name);
        }
    }

    private class RemoveStudent implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            TreePath currentSelection = studentTree.getSelectionPath();
            if (currentSelection != null) {
                DefaultMutableTreeNode currentNode = (DefaultMutableTreeNode)
                        (currentSelection.getLastPathComponent());
                if (currentNode.isLeaf()) {
                    MutableTreeNode parent = (MutableTreeNode)(currentNode.getParent());
                    if (parent != null)
                        ((DefaultTreeModel)studentTree.getModel()).removeNodeFromParent(currentNode);
                }
            }
        }
    }
    private class EditStudent implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            TreePath currentSelection = studentTree.getSelectionPath();
            if (currentSelection != null) {
                DefaultMutableTreeNode currentNode = (DefaultMutableTreeNode)
                        (currentSelection.getLastPathComponent());
                if (currentNode.isLeaf()) {
                    StudentInfo st = showStudentEditDialog((String) currentNode.getUserObject());
                    if (st != null) {
                        MutableTreeNode parent = (MutableTreeNode) (currentNode.getParent());
                        if (parent != null)
                            ((DefaultTreeModel) studentTree.getModel()).removeNodeFromParent(currentNode);
                        addStudent(st.course - 1, st.group - 1, st.name);
                    }
                }
            }
        }
    }

}
