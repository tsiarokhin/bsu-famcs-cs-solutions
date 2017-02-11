#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

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
    cout << "Even-first sorted:" << endl;
    sort(v.begin(), v.end(), [](int& a, int& b){
        if (a % 2 == b % 2)
            return a < b;
        else
            return (a % 2 == 0);
    });
    print_vector(v);
}

void Task_2_and_4(vector<int>& v)
{
    cout << "Elements, greater than 5:" << endl;
    ostream_iterator<int> out_it (cout," ");
    copy_if(v.begin(), v.end(), out_it, greater_than(5));
}

int main()
{
    vector<int> v{ 1, 8, 7, 4, 3, 6, 2, 5 };
    print_vector(v);
    Task_1(v);
    Task_2_and_4(v);

    return 0;
}
