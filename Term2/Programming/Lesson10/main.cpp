#include <iostream>
#include <cstring>

int strfindchar(char* s, char c)
{
	int res = 0;
	int len = strlen(s);
	__asm {
		cld
		mov		al, c
		mov		edi, s
		mov		ecx, len
		repne	scasb
		jecxz	not_found
		mov		res, 1
not_found:
	}
	return res;
}


int main()
{
	char ch = 'k';
	char s[] = "Programming";

	std::cout << (strfindchar(s, ch)?"Found":"Not found") << std::endl;

	return 0;
}