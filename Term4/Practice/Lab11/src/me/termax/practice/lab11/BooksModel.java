package me.termax.practice.lab11;

import jdk.internal.org.xml.sax.SAXException;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableModel;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class BooksModel extends AbstractTableModel implements Serializable {
    private List<Book> books;
    private final String COL_NAMES[] = {"Title", "Author", "ISBN", "Year", "Pages"};


    public BooksModel(File file, boolean validate) throws IOException, SAXException, org.xml.sax.SAXException {
        books = new ArrayList<>();
        DocumentBuilderFactory f = DocumentBuilderFactory.newInstance();
        f.setValidating(false);

        if (validate) {
            SchemaFactory factory = SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");
            Schema schema = factory.newSchema(BooksModel.class.getClassLoader().getResource("schema.xsd"));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(file));
        }

        try {
            DocumentBuilder builder = f.newDocumentBuilder();
            Document doc = builder.parse(file);
            Node root = doc.getFirstChild();
            if (!root.getNodeName().equals("books"))
                throw new SAXException();
            NodeList items = root.getChildNodes();
            for (int i = 0; i < items.getLength(); ++i) {
                Node node = items.item(i);
                if (!node.getNodeName().equals("book"))
                    continue;
                Book curBook = new Book();
                curBook.setIsbn(node.getAttributes().getNamedItem("isbn").getTextContent());
                curBook.setYear(Integer.parseInt(node.getAttributes().getNamedItem("year").getTextContent()));

                NodeList fields = node.getChildNodes();
                for(int j = 0; j < fields.getLength(); ++j) {
                    switch (fields.item(j).getNodeName()) {
                        case "title":
                            curBook.setTitle(fields.item(j).getTextContent());
                            break;
                        case "author":
                            curBook.setAuthor(fields.item(j).getTextContent());
                            break;
                        case "pages":
                            curBook.setPages(Integer.parseInt(fields.item(j).getTextContent()));
                            break;
                    }
                }
                books.add(curBook);
            }
        } catch (ParserConfigurationException ignored) {}
    }

    public static BooksModel loadFromBinary(File file) throws IOException, ClassNotFoundException {
        ObjectInputStream stream = new ObjectInputStream(new FileInputStream(file));
        BooksModel model = new BooksModel();
        model.setItems((List<Book>) stream.readObject());
        stream.close();
        return model;
    }

    public BooksModel() {
        books = new ArrayList<>();
    }

    public List<Book> getItems() {
        return books;
    }

    public void setItems(List<Book> books) {
        this.books = books;
    }

    @Override
    public int getRowCount() {
        return books.size();
    }

    @Override
    public int getColumnCount() {
        return 5;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        switch (columnIndex) {
            case 0:
                return books.get(rowIndex).getTitle();
            case 1:
                return books.get(rowIndex).getAuthor();
            case 2:
                return books.get(rowIndex).getIsbn();
            case 3:
                return books.get(rowIndex).getYear();
            case 4:
                return books.get(rowIndex).getPages();
            default:
                return null;
        }
    }

    @Override
    public String getColumnName(int column) {
        return COL_NAMES[column];
    }

    @Override
    public Class<?> getColumnClass(int column) {
        if (column < 3)
            return String.class;
        else
            return Integer.class;
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return true;
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
        switch (columnIndex) {
            case 0:
                books.get(rowIndex).setTitle((String) aValue);
                break;
            case 1:
                books.get(rowIndex).setAuthor((String) aValue);
                break;
            case 2:
                books.get(rowIndex).setIsbn((String) aValue);
                break;
            case 3:
                books.get(rowIndex).setYear((Integer) aValue);
                break;
            case 4:
                books.get(rowIndex).setPages((Integer) aValue);
                break;
        }
    }

    public String toXML() {
        StringBuilder sb = new StringBuilder();
        sb.append("<books>\n");
        for (Book book : books){
            sb.append("\t<book isbn=\"").append(book.getIsbn()).append("\" year=\"").append(book.getYear()).append("\">\n");
            sb.append("\t\t<title>").append(book.getTitle()).append("</title>\n").append("\t\t<author>").append(book.getAuthor()).append("</author>\n").append("\t\t<pages>").append(book.getPages()).append("</pages>\n");
            sb.append("\t</book>\n");
        }
        sb.append("</books>\n");
        return sb.toString();
    }

    public void saveToXML(File file) throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(file);
        pw.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
        pw.println(toXML());
        pw.close();
    }

    public void saveToBinary(File file) throws IOException {
        ObjectOutputStream stream = new ObjectOutputStream(new FileOutputStream(file));
        stream.writeObject(books);
        stream.close();
    }

    public void deleteRows(int[] rows) {
        for (int i = rows.length - 1; i >= 0; --i)
            if (rows[i] < books.size())
                books.remove(rows[i]);
    }
}
