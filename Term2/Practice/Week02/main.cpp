/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Flowerbed {
    int id;
    string shape;
    set<string> flowers;

    Flowerbed()
        : flowers()
    {
    }
    Flowerbed(int id, string shape, set<string> flowers)
        : id(id)
        , shape(shape)
        , flowers(flowers)
    {
    }

    friend istream& operator>>(istream& in, Flowerbed& a);
    friend ostream& operator<<(ostream& out, const Flowerbed& a);
};

istream& operator>>(istream& in, Flowerbed& a)
{
    a = Flowerbed();
    string s;
    in >> a.id;
    in.ignore();
    getline(in, a.shape, ',');
    getline(in, s);

    int prev_pos = 0, cur_pos = 0;
    while ((cur_pos = s.find(",", prev_pos)) >= 0) {
        a.flowers.insert(s.substr(prev_pos, cur_pos - prev_pos));
        prev_pos = cur_pos + 1;
    }
    a.flowers.insert(s.substr(prev_pos, s.size()));

    return in;
}

ostream& operator<<(ostream& out, const Flowerbed& a)
{
    out << "{ " << a.id << " | " << a.shape << " |: ";
    for (auto it = a.flowers.begin(); it != a.flowers.end(); it++)
        out << *it << ", ";
    out << "}";
    return out;
}

int main()
{
    ifstream fin("input.txt");
    istream_iterator<Flowerbed> FB_in(fin);
    istream_iterator<Flowerbed> end_in;
    ostream_iterator<Flowerbed> FB_out(cout, "\n");
    ostream_iterator<string> str_out(cout, "\n");
    vector<Flowerbed> flowerbeds;
    // TASK 1
    copy(FB_in, end_in, back_inserter(flowerbeds));

    // TASK 2
    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.id < b.id;
    });
    cout << "SORTED BY ID:\n";
    copy(flowerbeds.begin(), flowerbeds.end(), FB_out);

    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.shape < b.shape;
    });
    cout << "\nSORTED BY SHAPE:\n";
    copy(flowerbeds.begin(), flowerbeds.end(), FB_out);

    //TASK 4
    
    set<string> different_forms;
    for_each(flowerbeds.begin(), flowerbeds.end(), [&different_forms](const Flowerbed& a) {
        different_forms.insert(a.shape);
    });
    cout << "\nDIFFERENT SHAPES:\n";
    copy(different_forms.begin(), different_forms.end(), str_out);

    
    map<int,Flowerbed> flowerbeds_map;
    for_each(flowerbeds.begin(), flowerbeds.end(), [&flowerbeds_map](const Flowerbed& a) {
        flowerbeds_map.insert(make_pair(a.id, a));
    });
    int id;
    cout << "\nEnter flowerbed id: ";
    cin >> id;
    cout << "Flowers from flowerbed #" << id << ":\n";
    copy(flowerbeds_map[id].flowers.begin(), flowerbeds_map[id].flowers.end(), str_out);

    set<string> different_flowers;
    for_each(flowerbeds.begin(), flowerbeds.end(), [&different_flowers](const Flowerbed& a) {
        different_flowers.insert(a.flowers.begin(), a.flowers.end());
    });
    cout << "\nLIST OF ALL DIFFERENT FLOWERS:\n";
    copy(different_flowers.begin(), different_flowers.end(), str_out);

    return 0;
}
