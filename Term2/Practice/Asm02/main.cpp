#include<iostream>

using namespace std;

int subtask1(int a, int b)
{
	int res;
	__asm {
		mov		eax, a
		mov		ebx, b
		cmp		eax, ebx

		je		a_equal_b
		jg		a_greater_b
		
		mov		eax, b
		mov		ebx, a
		add		ebx, 1
		cdq
		idiv	ebx
		mov		res, eax
		jmp		the_end
a_equal_b:
		mov		res, 4
		jmp		the_end
a_greater_b:
		mov		eax, a
		imul	a
		imul	a
		sub		eax, 5
		cdq
		idiv	b
		mov		res, eax
the_end:
	}
	return res;
}

int subtask2(int n)
{
	int res;
	__asm {
		mov		eax, n
		mov		ebx, 10
		xor		ecx, ecx
cycle:
		inc		ecx
		cdq
		idiv	ebx
		cmp		eax, 0
		jne cycle

		mov		res, ecx
	}
	return res;
}

int subtask3(int n)
{
	int res;
	__asm {
		mov		eax, n
		xor		ebx, ebx
cycle:
		shr		eax, 1
		jnc		cycle
		inc		ecx
		cmp		eax, 0
		jne cycle

		and		ecx, 1
		mov		res, ecx
	}
	return res;
}

int main()
{
	int a,b;
	cin >> a >> b;
	cout << "Result: " << subtask1(a, b) << endl;
	
	int n;
	cin >> n;
	cout << "Number of digits: " << subtask2(n) << endl;

	int n2;
	cin >> n2;
	cout << (subtask3(n2)?"ODD number of ones":"EVEN number of ones") << endl;


	cout << endl;
	return 0;
}