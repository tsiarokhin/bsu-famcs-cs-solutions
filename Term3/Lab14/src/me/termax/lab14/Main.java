package me.termax.lab14;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.swing.*;
import javax.swing.text.NumberFormatter;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.NumberFormat;
import java.util.*;
import java.util.List;

public class Main extends JFrame {
    private JMenuItem openXML, openTXT, save, add, generateGoodList;
    private JList<Product> productList;
    private JList<String> goodList;
    private DefaultListModel<Product> productListModel;
    private DefaultListModel<String> goodListModel;
    private SortedSet<Product> products;;


    public static void main(String[] args) {
        Main app = new Main();
        app.setVisible(true);
    }

    public Main() {
        super("Lab 14");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 400);
        setLocationRelativeTo(null);

        products = new TreeSet<>();

        productListModel = new DefaultListModel<>();
        productList = new JList<>(productListModel);
        productList.setPreferredSize(new Dimension(190, 0));
        add(productList, BorderLayout.WEST);
        goodListModel = new DefaultListModel<>();
        goodList = new JList<>(goodListModel);
        goodList.setPreferredSize(new Dimension(190, 0));
        add(goodList, BorderLayout.EAST);


        JMenuBar menuBar = new JMenuBar();
        add(menuBar, BorderLayout.NORTH);
        JMenu fileMenu = new JMenu("File");
        JMenu dataMenu = new JMenu("Data");

        menuBar.add(fileMenu);
        menuBar.add(dataMenu);


        openXML = new JMenuItem("Open XML...");
        openXML.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
                if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                    File inputFile = fileChooser.getSelectedFile();
                    try {
                        SAXParserFactory factory = SAXParserFactory.newInstance();
                        SAXParser saxParser = factory.newSAXParser();

                        ProductXMLHandler handler = new ProductXMLHandler();
                        saxParser.parse(inputFile, handler);

                        products = handler.getProductList();

                        syncGUIWithList();

                    } catch (ParserConfigurationException err) {
                        JOptionPane.showMessageDialog(null, "XML parser error", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (NumberFormatException|SAXException err) {
                        JOptionPane.showMessageDialog(null, "XML format error", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (IOException err) {
                        JOptionPane.showMessageDialog(null, "File cannot be opened","Error",  JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });
        fileMenu.add(openXML);

        openTXT = new JMenuItem("Open TXT...");
        openTXT.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
                if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                    File inputFile = fileChooser.getSelectedFile();
                    try {
                        Scanner input = new Scanner(inputFile);
                        products.clear();
                        while (input.hasNext()) {
                            products.add(new Product(input.next(), input.next(), input.nextInt()));
                        }
                        syncGUIWithList();

                    } catch (NoSuchElementException|NumberFormatException err) {
                        JOptionPane.showMessageDialog(null, "File format error", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (IOException err) {
                        JOptionPane.showMessageDialog(null, "File cannot be opened","Error",  JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });
        fileMenu.add(openTXT);

        save = new JMenuItem("Save XML...");
        save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
                fileChooser.setSelectedFile(new File("products.xml"));
                if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                    File outputFile = fileChooser.getSelectedFile();
                    try {
                        PrintWriter out = new PrintWriter(outputFile);
                        out.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<products>");
                        Iterator<Product> it = products.iterator();
                        while (it.hasNext())
                            out.println(it.next().toXML());
                        out.println("</products>");
                        out.close();
                    } catch (IOException e1) {
                        JOptionPane.showMessageDialog(null, "File cannot be saved to this location");
                    }
                }
            }
        });
        fileMenu.add(save);

        add = new JMenuItem("Add Item");
        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                NumberFormat intFormat = NumberFormat.getIntegerInstance();

                NumberFormatter numberFormatter = new NumberFormatter(intFormat);
                numberFormatter.setValueClass(Integer.class);
                numberFormatter.setAllowsInvalid(false);
                numberFormatter.setMinimum(1);

                JTextField name = new JTextField(7);
                JTextField origin = new JTextField(7);
                JFormattedTextField count = new JFormattedTextField(numberFormatter);
                count.setColumns(7);


                JPanel dialogPanel = new JPanel();
                dialogPanel.add(new JLabel("Name:"));
                dialogPanel.add(name);
                dialogPanel.add(Box.createHorizontalStrut(10));
                dialogPanel.add(new JLabel("Origin:"));
                dialogPanel.add(origin);
                dialogPanel.add(Box.createHorizontalStrut(10));
                dialogPanel.add(new JLabel("Count:"));
                dialogPanel.add(count);

                int result = JOptionPane.showConfirmDialog(null, dialogPanel,
                        "Add product", JOptionPane.OK_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION) {
                    Product res = new Product(name.getText(), origin.getText(), (Integer)count.getValue());
                    products.add(res);
                    syncGUIWithList();
                }
            }
        });
        dataMenu.add(add);

        generateGoodList = new JMenuItem("Generate goods list");
        generateGoodList.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                SortedSet<String> goods = new TreeSet<>();
                Iterator<Product> it = products.iterator();
                while (it.hasNext()){
                    goods.add(it.next().getName());
                }
                goodListModel.clear();
                for (String good: goods) {
                    goodListModel.addElement(good);
                }
            }
        });
        dataMenu.add(generateGoodList);

    }

    private void syncGUIWithList() {
        goodListModel.clear();
        productListModel.clear();
        for (Product product: products)
            productListModel.addElement(product);
    }

    private class ProductXMLHandler extends DefaultHandler {
        boolean name = false;
        boolean origin = false;
        boolean count = false;

        private Product product;
        private SortedSet<Product> productList;

        public SortedSet<Product> getProductList() {
            return productList;
        }

        @Override
        public void startDocument() throws SAXException {
            productList = new TreeSet<>();
        }

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            if (qName.equalsIgnoreCase("product")) {
                product = new Product();
            } else if (qName.equalsIgnoreCase("name"))
                name = true;
            else if (qName.equalsIgnoreCase("origin"))
                origin = true;
            else if (qName.equalsIgnoreCase("count"))
                count = true;
        }

        @Override
        public void characters(char ch[], int start, int length) throws SAXException {
            if (name) {
                product.setName(new String(ch, start, length));
                name = false;
            }
            else if (origin) {
                product.setOrigin(new String(ch, start, length));
                origin = false;
            }
            else if (count) {
                product.setCount(Integer.parseInt(new String(ch, start, length)));
                count = false;
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            if (product == null)
                throw new SAXException();
            if (qName.equalsIgnoreCase("product")) {
                productList.add(product);
            }

        }
    }

}
