/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Flowerbed {
    int id;
    string shape;
    set<string> flowers;
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
    ostream_iterator<Flowerbed> FB_out(cout, "\n\t");
    ostream_iterator<string> str_out(cout, "\n\t");
    vector<Flowerbed> flowerbeds;

    // FLOWERBEDS INPUT
    copy(FB_in, end_in, back_inserter(flowerbeds));

    // FLOWERBEDS SORED BY ID
    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.id < b.id;
    });
    cout << "SORTED BY ID:\n\t";
    copy(flowerbeds.begin(), flowerbeds.end(), FB_out);

    // FLOWERBEDS SORED BY SHAPE
    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.shape < b.shape;
    });
    cout << "\nSORTED BY SHAPE:\n\t";
    copy(flowerbeds.begin(), flowerbeds.end(), FB_out);

    //DIFFERENT SHAPES
    set<string> different_forms;
    for_each(flowerbeds.begin(), flowerbeds.end(), [&different_forms](const Flowerbed& a) {
        different_forms.insert(a.shape);
    });
    cout << "\nDIFFERENT SHAPES (" << different_forms.size() << "):\n\t";
    copy(different_forms.begin(), different_forms.end(), str_out);

    //FLOWERS FROM FLOWERBED ID, FLOWERBED BY FLOWER NAME
    map<int, Flowerbed> flowerbeds_map;
    multimap<string, int> FB_id_by_flower;

    for_each(flowerbeds.begin(), flowerbeds.end(), [&FB_id_by_flower, &flowerbeds_map](const Flowerbed& a) {
        flowerbeds_map.insert(make_pair(a.id, a));
        for_each(a.flowers.begin(), a.flowers.end(), [&FB_id_by_flower, &a](const string& s) {
            FB_id_by_flower.insert(make_pair(s, a.id));
        });
    });

    int id;
    cout << "\nEnter flowerbed id: ";
    cin >> id;
    cout << "Flowers from flowerbed #" << id << ":\n\t";
    copy(flowerbeds_map[id].flowers.begin(), flowerbeds_map[id].flowers.end(), str_out);

    string fl_name;
    cout << "\nEnter flower name: ";
    cin >> fl_name;
    auto found = FB_id_by_flower.find(fl_name);
    cout << "Flower \"" << fl_name << "\" found in flowerbed #" << found->second << ":\n\t";
    cout << flowerbeds_map[found->second] << endl;

    //LIST OF ALL DIFFERENT FLOWERS, FLOWERBED WITH MAXIMUM NUMBER OF FLOWERS
    int max_flowers = 0, max_flowers_FB_id;
    set<string> different_flowers;
    for_each(flowerbeds.begin(), flowerbeds.end(), [&different_flowers, &max_flowers, &max_flowers_FB_id](const Flowerbed& a) {
        if (a.flowers.size() > max_flowers) {
            max_flowers = a.flowers.size();
            max_flowers_FB_id = a.id;
        }
        different_flowers.insert(a.flowers.begin(), a.flowers.end());
    });
    cout << "\nLIST OF ALL DIFFERENT FLOWERS (" << different_flowers.size() << "):\n\t";
    copy(different_flowers.begin(), different_flowers.end(), str_out);

    cout << "\nFOLWERBED WITH MAXIMUM NUMBER OF FLOWERS (" << max_flowers << "):\n\t";
    cout << flowerbeds_map[max_flowers_FB_id];

    cout << endl
         << endl;
    return 0;
}
