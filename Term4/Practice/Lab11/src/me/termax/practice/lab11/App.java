package me.termax.practice.lab11;

import javax.swing.*;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;


public class App extends JFrame {
    private JTable booksTable;
    private BooksModel booksTableModel;
    private JCheckBoxMenuItem validateXML;


    private final int COL_COUNT = 5;
    private enum BookField {
        TITLE, AUTHOR, ISBN, YEAR, PAGES;
    }

    public App() {
        super("Lab 11");

        setSize(800, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        JMenuBar menuBar = new JMenuBar();
        JMenu file = new JMenu("File");
        JMenuItem loadFromXML = new JMenuItem("[DOM] Load XML...");
        loadFromXML.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    booksTableModel = new BooksModel(chooser.getSelectedFile(), validateXML.getState());
                    booksTable.setModel(booksTableModel);
                    if (validateXML.getState())
                        JOptionPane.showMessageDialog(this,
                                "XML is valid and matches XSD schema",
                                "Info", JOptionPane.INFORMATION_MESSAGE);
                } catch (Exception err) {
                    JOptionPane.showMessageDialog(this, "Invalid XML file", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        file.add(loadFromXML);

        validateXML = new JCheckBoxMenuItem("Validate XML");
        validateXML.setState(true);
        file.add(validateXML);
        file.addSeparator();

        JMenuItem saveToXML = new JMenuItem("Save to XML");
        saveToXML.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showSaveDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    booksTableModel.saveToXML(chooser.getSelectedFile());
                } catch (FileNotFoundException err) {
                    JOptionPane.showMessageDialog(this, "Invalid file path", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

        });
        file.add(saveToXML);

        JMenuItem calcXml = new JMenuItem("[SAX] Do calculations");
        calcXml.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    SAXParserFactory factory = SAXParserFactory.newInstance();
                    SAXParser parser = factory.newSAXParser();
                    BookSAXHandler bookHandler = new BookSAXHandler();
                    parser.parse(chooser.getSelectedFile(), bookHandler);
                    JOptionPane.showMessageDialog(this,
                            "Books count: " + bookHandler.getBooksCount() +
                                    "\nTotal pages: " + bookHandler.getTotalPages() +
                                    "\nAverage page count: " + bookHandler.getAvgPages(),
                            "Info", JOptionPane.INFORMATION_MESSAGE);
                } catch (Exception err) {
                    JOptionPane.showMessageDialog(this, "Invalid XML file", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        file.add(calcXml);

        file.addSeparator();

        JMenuItem saveToBinary = new JMenuItem("Save to binary");
        saveToBinary.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showSaveDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    booksTableModel.saveToBinary(chooser.getSelectedFile());
                } catch (IOException err) {
                    JOptionPane.showMessageDialog(this, "Invalid file path", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

        });
        file.add(saveToBinary);

        JMenuItem loadFromBinary = new JMenuItem("Load from binary");
        loadFromBinary.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    booksTableModel = BooksModel.loadFromBinary(chooser.getSelectedFile());
                    booksTable.setModel(booksTableModel);
                } catch (Exception err) {
                    JOptionPane.showMessageDialog(this, "Invalid binary file", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

        });
        file.add(loadFromBinary);

        file.addSeparator();

        JMenuItem convertToHTML = new JMenuItem("Convert to HTML");
        convertToHTML.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    TransformerFactory factory = TransformerFactory.newInstance();
                    Transformer transformer = factory.newTransformer(new StreamSource(BooksModel.class.getClassLoader().getResourceAsStream("html.xsl")));

                    transformer.transform(new StreamSource(chooser.getSelectedFile()), new StreamResult(new File("output.html")));
                } catch (Exception err) {
                    JOptionPane.showMessageDialog(this, "Invalid XML file", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

        });
        file.add(convertToHTML);

        JMenuItem convertToTXT = new JMenuItem("Convert to TXT");
        convertToTXT.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            chooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int option = chooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                try {
                    TransformerFactory factory = TransformerFactory.newInstance();
                    Transformer transformer = factory.newTransformer(new StreamSource(BooksModel.class.getClassLoader().getResourceAsStream("txt.xsl")));

                    transformer.transform(new StreamSource(chooser.getSelectedFile()), new StreamResult(new File("output.txt")));
                } catch (Exception err) {
                    JOptionPane.showMessageDialog(this, "Invalid XML file", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

        });
        file.add(convertToTXT);



        JMenu booksMunu = new JMenu("Books");
        JMenuItem addBook = new JMenuItem("Add book");
        addBook.addActionListener(e -> {
            booksTableModel.getItems().add(new Book());
            booksTable.updateUI();
        });
        booksMunu.add(addBook);

        JMenuItem deleteBook = new JMenuItem("Delete selected book");
        deleteBook.addActionListener(e -> {
            booksTableModel.deleteRows(booksTable.getSelectedRows());
            booksTable.updateUI();
        });
        booksMunu.add(deleteBook);

        menuBar.add(file);
        menuBar.add(booksMunu);
        add(menuBar, BorderLayout.NORTH);


        booksTableModel = new BooksModel();
        booksTable = new JTable(booksTableModel);
        add(new JScrollPane(booksTable), BorderLayout.CENTER);
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    public static void main(String[] args) {
        App app = new App();
        app.setVisible(true);
    }
}
