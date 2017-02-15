/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <map>

using namespace std;

template<class T>
void print_vector(vector<T>& v)
{
    for (T& x: v)
        cout << x << ' ';
    cout << endl;
}

class greater_than
{
private:
    int n;
public:
    greater_than(int n): n(n) {}
    bool operator()(int a)
    {
        return a > n;
    }
};

void Task_1(vector<int>& v)
{
    cout << "\nTask 1:\nEven-first sorted: ";
    sort(v.begin(), v.end(), [](int& a, int& b){
        if (a % 2 == b % 2)
            return a < b;
        else
            return (a % 2 == 0);
    });
    print_vector(v);
}

void Tasks_2_and_4(vector<int>& v)
{
    cout << "\nTasks 2 and 4:\nElements, greater than 5: ";
    ostream_iterator<int> out_it (cout," ");
    copy_if(v.begin(), v.end(), out_it, greater_than(5));
}

void Task_5()
{
    cout << "\n\nЗадание 5:";
    ostream_iterator<string> out_it (cout," ");
    set<string> river_bank{"пескарь", "мидия", "рак"};
    set<string> at_the_depth{"бычок", "окунь", "мидия"};

    cout << "\nВсе обитатели реки:\n";
    set_union(river_bank.begin(), river_bank.end(), at_the_depth.begin(), at_the_depth.end(), out_it);
    cout << "\nВодятся по всей реке:\n";
    set_intersection(river_bank.begin(), river_bank.end(), at_the_depth.begin(), at_the_depth.end(), out_it);
    cout << "\nВодятся у дерева, но не на глубине:\n";
    set_difference(river_bank.begin(), river_bank.end(), at_the_depth.begin(), at_the_depth.end(), out_it);
    
}

void Task_6()
{
    multimap<int, string> numbers = {
        { 1, "адзін" },
        { 1, "один" },
        { 1, "one" },
        { 2, "два" },
        { 2, "two" },
        { 3, "тры" },
        { 3, "три" },
        { 3, "three" },
        { 4, "чатыры" },
        { 4, "четыре" },
        { 4, "four" }
    };
    cout << "\n\nЗадание 6:\nВведите число N: ";
    int n;
    cin >> n;
    auto low = numbers.lower_bound(n); 
    auto up =  numbers.upper_bound(n);
    if (low != numbers.end()){
        cout << "Варианты написания числа \"" << n << "\": ";
        for (auto it = low; it != up; it++)
            cout << it->second << ", ";
    }
    else
        cout << "Вариантов написания числа \"" << n << "\" нет";
    cout << endl;

}

int main()
{
    vector<int> v{ 1, 8, 7, 4, 3, 6, 2, 5 };
    cout << "Initial vector:\n";
    print_vector(v);
    Task_1(v);
    Tasks_2_and_4(v);
    Task_5();
    Task_6();

    return 0;
}
