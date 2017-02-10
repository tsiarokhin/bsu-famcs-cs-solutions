/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

#include <Man.h>
#include <Student.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cout << "Week #12, Task #1" << endl;

    char type;
    string name;
    int age;
    bool sex;
    float weight;
    int edYear;
    int n;

    fin >> n;
    Man** arr = new Man*[n];
    for (int i = 0; i < n; i++){
        fin >> type >> name >> age >> sex >> weight;
        if (type == 'm')
            arr[i] = new Man(name, age, sex, weight);
        else if (type == 's'){
            fin >> edYear;
            arr[i] = new Student(name, age, sex, weight, edYear);
        }
    }
    cout << "\nRead this list from file:\n";
    for (int i = 0; i < n; i++){
        cout << '\t'; arr[i]->print(); cout << '\n';
    }

    cout << "\Men with the same age:\n";
    for (int i = 0; i < n; i++){
        if (dynamic_cast<Student*>(arr[i]) == NULL)
            for (int j = i+1; j < n; j++)
                if (dynamic_cast<Student*>(arr[j]) == NULL && *arr[i] == *arr[j])
                    cout << '\t' << arr[i]->getName() << " and " << arr[j]->getName() << endl;
    }

    cout << "\nStudents with the same ed. year:\n";
    for (int i = 0; i < n; i++){
        if (dynamic_cast<Student*>(arr[i]) != NULL)
            for (int j = i+1; j < n; j++)
                if (dynamic_cast<Student*>(arr[j]) != NULL)
                    if( *dynamic_cast<Student*>(arr[i]) == *dynamic_cast<Student*>(arr[j]))
                        cout << '\t' << arr[i]->getName() << " and " << arr[j]->getName() << endl;
    }

    for (int i = 0; i < n; i++)
        delete arr[i];
    delete[] arr;

    return 0;
}
