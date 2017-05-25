#include <iostream>
#include <cstring>

extern "C"
{
	int __stdcall shortest_word(char* s);
	bool __stdcall find(char* s, char* word, int n, int m);
}

int main()
{
	char s[] = "Some random line of words";
	std::cout << "\"" << s << "\"\n";

	std::cout << "The shortest word is " << shortest_word(s)+1 << "th\n\n";
	
	char word[] = "random";

	std::cout << "Searching \"" << word << "\" in line \"" << s << "\".\n";
	std::cout << (find(s, word, strlen(s), strlen(word))?"FOUND":"NOT FOUND") << std::endl;

	return 0;
}