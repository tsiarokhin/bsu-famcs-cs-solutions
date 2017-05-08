#include <iostream>

using namespace std;

int __stdcall getRealRootsCount(int a, int b, int c)
{
	int res;
	__asm {
		mov		ebx, 4
		imul	ebx, a
		imul	ebx, c
		neg		ebx
		mov		eax, b
		imul	eax, b
		add		eax, ebx
		cmp		eax, 0
		jz		zero
		jl		less
		mov		res, 2
		jmp		the_end
zero:
		mov		res, 1
		jmp		the_end
less:
		mov		res, 0
the_end:
	}
	return res;
}

int __stdcall sumArray(int* a, int n)
{
	int res;
	__asm {
		xor		eax,eax
		mov		esi, a
		mov		ecx, n
cycle:
		add		eax, [esi]
		add		esi, 4
		loop cycle
		mov res, eax
	}
	return res;
}

int main()
{
	int a, b, c, res;
	cout << "Enter A, B, C: ";
	cin >> a >> b >> c;
	__asm {
		push	c
		push	b
		push	a
		call	getRealRootsCount
		mov		res, eax
	}
	cout << res << endl;

	int n;
	cout << "Enter elements count: ";
	cin >> n;
	int* arr = new int[n];
	//int arr[3] = {1,2,3};
	cout << "Enter elements: ";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	
	__asm {
		push	n
		push	arr
		call	sumArray
		mov		res, eax
	}
	cout << res << endl;
	cout << endl;
	return 0;
}