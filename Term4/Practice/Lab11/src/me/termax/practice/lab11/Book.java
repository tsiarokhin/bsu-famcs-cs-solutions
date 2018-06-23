package me.termax.practice.lab11;

import java.io.Serializable;

public class Book implements Serializable {
    private String title;
    private String author;
    private String isbn;
    private int pages;
    private int year;

    public Book() {}

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getIsbn() {
        return isbn;
    }

    public void setIsbn(String isbn) {
        this.isbn = isbn;
    }

    public int getPages() {
        return pages;
    }

    public void setPages(int pages) {
        this.pages = pages;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public String toXML() {
        return "\t<book isbn=\""+isbn+"\" year=\""+year+"\">\n" +
                "\t\t<title>"+title+"</title>\n" +
                "\t\t<author>"+author+"</author>\n" +
                "\t\t<pages>"+pages+"</pages>\n" +
                "\t</book>";
    }
}
