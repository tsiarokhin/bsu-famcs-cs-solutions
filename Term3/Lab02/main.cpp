/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

/** Task 1 **/

template<typename T>
T FSums(const T v) {
    return v;
}

template<typename T, typename... Args>
double FSums(const T first, Args... args) {
    return first + FSums(args...);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

/** Task 2 **/

template<typename T>
T minArg(T v) {
    return v;
}

template<typename T, typename... Args>
double minArg(T first, Args... args) {
    auto second = minArg(args...);
    return (first<second)?first:second;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

/** Task 3 **/
template<typename... Args> tuple<int, double> FSum2(const double arg, Args... args);

tuple<int, double> FSum2() {
    return tuple<int, double>(0, 0.0);
}

template<typename... Args>
tuple<int, double> FSum2(const int arg, Args... args) {
    auto t = FSum2(args...);
    return tuple<int, double>(arg+get<0>(t), get<1>(t));
}

template<typename... Args>
tuple<int, double> FSum2(const double arg, Args... args) {
    auto t = FSum2(args...);
    return tuple<int, double>(get<0>(t), arg+get<1>(t));
}
///////////////////////////////////////////////////////////////////////////////////////////////////

/** Task 4 **/

template<typename T>
string ToString(const string& sep, T elem) {
    return to_string(elem);
}

template<typename T, typename... Args>
string ToString(const string& sep, T elem, Args... args) {
    return to_string(elem) + sep + ToString(sep, args...);
}



int main()
{
    short m = -3;
	auto xSum = FSums(1, 4.7, m, 1.5, 10);
    cout << "xSum = " << xSum << endl;


	auto xMin = minArg(1, 4.7, m, 1.5, 10);
    cout << "xMin = " << xMin << endl;


    short sm = 33;
	auto sx2 = FSum2(10.6, 2, 4.7, sm);
	cout << "sx2 = ";
	cout << get<0>(sx2) << " " << get<1>(sx2) << endl;


    int n  = 17;
    double x = 6.75;
    string s = ToString(";", 25, 3.7, n, x);
    cout << "ToString = " << s << endl;


    return 0;
}
