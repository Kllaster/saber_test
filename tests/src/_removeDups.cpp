#include "saber.hpp"
#include <climits>
#include <bitset>

// Success test
void testABC()
{
	char data[] = "AAA BBB AAA";

	removeDups(data);
	assert(std::string(data) == "A B A");
	std::cout << "[+] Success testABC\n";
}

// Success test
void testNumbers()
{
	char data[] = "   1111   223  456    ";

	removeDups(data);
	assert(std::string(data) == " 1 23 456 ");
	std::cout << "[+] Success testNumbers\n";
}

void _removeDups()
{
	testABC();
	testNumbers();
}