/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

ifstream fin("input.txt");

struct Flowerbed {
    int id;
    string shape;
    set<string> flowers;

    Flowerbed(int id, string shape, set<string> flowers)
        : id(id)
        , shape(shape)
        , flowers(flowers)
    {
    }

    void print()
    {
        cout << "{ " << id << " | " << shape << " |: ";
        for (auto it = flowers.begin(); it != flowers.end(); it++)
            cout << *it << ", ";
        cout << "}\n";
    }
};

set<string> comma_separated_string_to_set(const string& s)
{
    int prev_pos = 0, cur_pos = 0;
    set<string> res;
    while ((cur_pos = s.find(",", prev_pos)) >= 0) {
        res.insert(s.substr(prev_pos, cur_pos - prev_pos));
        prev_pos = cur_pos + 1;
    }
    res.insert(s.substr(prev_pos, s.size()));
    return res;
}

void sort_by_id(vector<Flowerbed>& flowerbeds)
{
    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.id < b.id;
    });
}

void sort_by_shape(vector<Flowerbed>& flowerbeds)
{
    sort(flowerbeds.begin(), flowerbeds.end(), [](const Flowerbed& a, const Flowerbed& b) {
        return a.shape < b.shape;
    });
}

int main()
{
    vector<Flowerbed> flowerbeds;
    int t_id;
    string t_shape;
    string t_flowers;

    // TASK 1
    while (fin >> t_id) {
        fin.ignore();
        getline(fin, t_shape, ',');
        getline(fin, t_flowers);
        flowerbeds.push_back(Flowerbed(t_id, t_shape, comma_separated_string_to_set(t_flowers)));
    }

    // TASK 2
    cout << "SORTED BY ID:\n";
    sort_by_id(flowerbeds);
    for (Flowerbed& x : flowerbeds)
        x.print();

    cout << "\nSORTED BY SHAPE:\n";
    sort_by_shape(flowerbeds);
    for (Flowerbed& x : flowerbeds)
        x.print();

    return 0;
}