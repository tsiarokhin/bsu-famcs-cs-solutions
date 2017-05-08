#include <iostream>

extern "C"
{
	int _stdcall rootsCount(int a, int b, int c);
}

int main()
{
	int a,b,c,res;
	std::cin >> a >> b >> c; 

	__asm {
		push	c
		push	b
		push	a
		call	rootsCount
		mov		res, eax
	}

	std::cout << res << std::endl;

	return 0;
}