package me.termax.practice.lab01;


import javax.management.Notification;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;


public class ProgrammingTest {

    public static void main(String[] args) {

        Set<Student> students = new HashSet<>();

        Academic tutor = new Academic("tutor1");
        Academic supervisor1 = new Academic("super1");
        Academic supervisor2 = new Academic("super2");

        students.add(new Undergraduate("Alex","alex", "alex@uni.edu", tutor));
        students.add(new Undergraduate("Max","max", "max@uni.edu", supervisor1));

        students.add(new Postgraduate("Rich","rich", "rich@uni.edu", supervisor1));
        students.add(new Postgraduate("Mathias","matt", "matt@uni.edu", supervisor1));
        students.add(new Postgraduate("Chris","chris", "chris@uni.edu", supervisor2));

        Course course = new Course("Very Important Course", students);


        Scanner input = new Scanner(System.in);
        System.out.print("Enter supervisor name: ");
        String supervisorName = input.nextLine();
        System.out.print("Enter message: ");
        String msg = input.nextLine();


        Set<Postgraduate>  postgraduateStidents = course.getPostgraduates(supervisorName);

        (new Notifier<Postgraduate>(postgraduateStidents)).doNotifyAll(msg);

    }
}
