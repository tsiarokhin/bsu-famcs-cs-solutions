package me.termax.practice.lab01;


import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class Course {
    protected String  name;
    protected Set<Student> students;

    public Course(String name, Set<Student> students) {
        this.students = students;
        this.name = name;
    }

    public Set<Postgraduate> getPostgraduates(String nameOfSupervisor) {
        Set<Postgraduate> newPostgraduates = new HashSet<>();
        for (Student st : students) {
            if (st instanceof Postgraduate) {
                Postgraduate pg = (Postgraduate) st;
                if (pg.getSupervisor().getName().equals(nameOfSupervisor)) {
                    newPostgraduates.add(pg);
                }
            }
        }
        return newPostgraduates;
    }

}