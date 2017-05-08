#include <iostream>

using namespace std;

void subtask1() // compares b^2 - 4*A*C with 0
{
	int a, b, c, res;
	cout << "Enter A, B, C: ";
	cin >> a >> b >> c;
	cout << "D = " << b*b - 4*a*c << "\nASM RES = ";
	__asm {
		mov		ebx, 4
		imul	ebx, a
		imul	ebx, c
		neg		ebx
		mov		eax, b
		imul	eax, b
		add		eax, ebx
		cmp		eax, 0
		jg		greater
		jz		zero
		jl		less
greater:
		mov		res, 2
		jmp		the_end
zero:
		mov		res, 1
		jmp		the_end
less:
		mov		res, 0
		jmp		the_end
the_end:
	}
	cout << res << endl;
}

void subtask2() // counts number of digits
{
	int a, res;
	cout << "Enter number: "; 
	cin >> a;
	__asm {
		mov		eax, a
		mov		ecx, 10
		xor		ebx, ebx  
cycle:	
		cdq
		idiv	ecx
		inc		ebx
		test	eax, eax
		jnz		cycle
		mov		res, ebx
	}
	cout << "The number has " << res << " digits\n";
}

int main()
{
	
	//subtask1();
	subtask2();

	cout << endl;
	return 0;
}