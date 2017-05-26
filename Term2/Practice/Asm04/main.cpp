#include <iostream>

using namespace std;

extern "C" int _stdcall power(int x, int n);
extern "C" int _stdcall longest_seq(char* s, char* seq_len); // returns index of the longest sequence of chars, writes it length in seq_len


int main()
{
	int a, n;
	cout << "Enter x and n: ";
	cin >> a >> n;
	cout << "x^n = " << power(a, n) << endl;

	char s[] = "prooooooogrammmmming";
	char seq_len = 0;
	int index = longest_seq(s, &seq_len);
	cout << "String: "<< s << "\nLongest subsequence start at index " << index << ".\nIt length is " << (int)seq_len; 

	cout << endl;

}
