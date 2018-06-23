package me.termax.practice.lab11;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class BookSAXHandler extends DefaultHandler {
    private int booksCount;
    private int totalPages;
    private boolean isParsingPages;

    public void startElement(String namespaceURI, String localName, String qName, Attributes atts) throws SAXException {
        super.startElement(namespaceURI, localName, qName, atts);
        if (qName.equals("books")) {
            booksCount = 0;
            totalPages = 0;
        }
        if (qName.equals("book")) {
            booksCount++;
        }
        if (qName.equals("pages")) {
            isParsingPages = true;
        }
    }

    @Override
    public void endElement(String s, String s1, String qName) throws SAXException {
        super.endElement(s, s1, qName);
        if (qName.equals("pages")) {
            isParsingPages = false;
        }
    }

    @Override
    public void characters(char[] chars, int i, int i1) throws SAXException {
        super.characters(chars, i, i1);
        if (isParsingPages)
            totalPages += Integer.parseInt(new String(chars, i, i1));
    }

    public int getBooksCount() {
        return booksCount;
    }

    public int getTotalPages() {
        return totalPages;
    }

    public double getAvgPages() {
        return ((double)totalPages)/booksCount;
    }
}
