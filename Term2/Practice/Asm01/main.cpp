#include <iostream>

using namespace std;

short swap_a, swap_b;

void Task1() // swaps swap_a and swap_b
{
	__asm {
		mov		ax, swap_a
		mov		bx, swap_b
		mov		swap_a, bx
		mov		swap_b, ax
	}
}

int Task2(int a, int b) // solves ax+b=0, a!=0
{
	int res;
	__asm {
		mov		eax, b
		neg		eax
		cdq
		idiv	a
		mov		res, eax
	}
	return res;
}

int Task3(int s, int x, int z) // computes s* (x-s*z)/(s+x*z)
{
	int divider;
	int res;
	__asm {
		mov		eax, x
		
		cdq
		imul	z
		add		eax, s
		mov		divider, eax

		mov		eax, s
		cdq
		imul	z
		neg		eax
		add		eax, x

		cdq
		idiv	divider
		imul	s
		mov		res, eax
	}
	return res;
}


int main()
{
	swap_a = 10;
	swap_b = 20;
	cout << "BEFORE SWAP: " << swap_a << ' ' << swap_b << endl;
	Task1();
	cout << "AFTER SWAP: " << swap_a << ' ' << swap_b << endl;
	
	cout << "TASK 2: " << Task2(2, -4) << endl;
	
	cout << "TASK 3: " << Task3(3, 1, -2);
	
	cout << endl;
	return 0;
}