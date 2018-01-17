package me.termax.lab14;

public class Product extends Good {
    protected String origin;

    public Product() {
    }

    public Product(String name, String origin, int count) {
        super(name, count);
        this.origin = origin;
    }

    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }



    public String toXML() {
        StringBuilder xml = new StringBuilder();
        xml.append("\t<product>\n");
        xml.append("\t\t<name>").append(name).append("</name>\n");
        xml.append("\t\t<origin>").append(origin).append("</origin>\n");
        xml.append("\t\t<count>").append(count).append("</count>\n");
        xml.append("\t</product>");
        return xml.toString();
    }

    @Override
    public String toString() {
        return name + " to " + origin + ", " + count + " pcs";
    }
}
