/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

struct Student
{
    Student(int id, string surname, string name): ID(id), Surname(surname), Name(name) {}
    int ID;
    string Surname;
    string Name;
};


int main()
{
    multimap<string, Student> students_db {
        {"Иванов", Student(1623089, "Иванов", "Иван")},
        {"Петров", Student(1623135, "Петров", "Арнольд")},
        {"Петров", Student(1623325, "Петров", "Джеймс")}
    };

    string s;
    cout << "Поиск студентов по фамилии. Для выхода нажмите Ctrl+C" << endl;

    do {
        cout << "Введите фамилию: ";
        cin >> s;
        auto low = students_db.lower_bound(s); 
        auto up =  students_db.upper_bound(s);

        if (low != students_db.end()){
            cout << "Студенты с фамилией \"" << s << "\":\n";
            for (auto it = low; it != up; it++) {
                auto t = it->second;
                cout << '\t' << t.ID << ": " << t.Surname << " " << t.Name << endl;
            }
        }
        else
            cout << "Студентов с такой фамилией нет";
        cout << endl;
    } while (true);

    return 0;
}