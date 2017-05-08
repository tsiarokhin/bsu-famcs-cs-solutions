#include<iostream>

using namespace std;

void subtask1(int* arr, int n, int k)
{
	__asm {
		xor		ecx, ecx
cycle:
		mov		eax, n
		imul	k
		add		eax, ecx
		mov		esi, eax
		
		mov		eax, n
		imul	ecx
		add		eax, k
		mov		edi, eax

		mov		edx, arr			; proper dynamic array loading in asm
		mov		eax, [edx][esi*4]
		mov		ebx, [edx][edi*4]
		mov		[edx][esi*4], ebx
		mov		[edx][edi*4], eax

		inc		ecx
		mov		eax, n
		cmp		ecx, eax
		jl		cycle
	}
}

bool subtask2(int* arr, int n)
{
	bool res = true;
		__asm {
		xor		ecx, ecx
		mov		edx, arr ; proper dynamic array loading in asm
cycle:
		mov		esi, n
		sub		esi, 1
		sub		esi, ecx
		mov		eax, [edx][ecx*4]
		mov		ebx, [edx][esi*4]
		
		cmp		eax, ebx
		jne		not_palindrome

		inc		ecx
		cmp		ecx, n
		jl		cycle
		jmp		the_end
not_palindrome:
		mov		res, 0
the_end:
	}
	return res;
}

void subtask3(int* arr, int n)
{
	int freq[1001] = {0};
	int diff_el = 0;
	int biggest_freq = 0;
	__asm {
		xor		ecx, ecx
		mov		esi, arr ; proper dynamic array loading in asm
		lea		edi, freq ; proper static array loading in asm
cycle:
		mov		eax, [esi][ecx*4]
		inc		[edi][eax*4]  
		mov		ebx, [edi][eax*4]  
		
		cmp		ebx, 1
		jne		same_el

		inc		diff_el
same_el:

		cmp		ebx, biggest_freq
		jle		lower_freq
		mov		biggest_freq, ebx
lower_freq:

		inc		ecx
		cmp		ecx, n
		jl		cycle
	}
	cout << diff_el << " different elements\n\nMost frequent elements (" << biggest_freq << " times): ";
	for (int i = 0; i < 1001; i++)
		if (freq[i] == biggest_freq)
			cout << "[" << i << "], ";
}

int main()
{
	int n, k;

	cout << "Enter matrix size: ";
	cin >> n;
	cout << "Enter row/column number to swap: ";
	cin >> k;
	int *arr = new int[n*n];
	cout << "Enter matrix:\n";
	for (int i = 0; i < n*n; i++)
		cin >> arr[i];
	subtask1(arr, n, k);
	
	cout << "Result:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << arr[i*n+j] << ' ';
		cout << endl;
	}

	cout << "\n=============================================\n";
	
	cout << "Enter sequence len: ";
	cin >> n;
	int *poly = new int[n];
	cout << "Enter sequence: ";
	for (int i = 0; i < n; i++)
		cin >> poly[i];
	cout << (subtask2(poly, n)?"Palindrome":"NOT palindrome");
	
	cout << "\n=============================================\n";
	
	cout << "Enter sequence len: ";
	cin >> n;
	int *arr2 = new int[n];
	cout << "Enter sequence: ";
	for (int i = 0; i < n; i++)
		cin >> arr2[i];
	subtask3(arr2, n);


	cout << endl;
	return 0;
}