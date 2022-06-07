#include "saber.hpp"
#include <climits>
#include <bitset>

// Success test
void testZero()
{
	std::string result = getBinaryString(0);
	std::string correctResult = std::string(BYTES_INT, '0');

	assert(result == correctResult);
	std::cout << "[+] Success testZero\n";
}

// Success test
void testOne()
{
	std::string result = getBinaryString(1);
	std::string correctResult = std::string(BYTES_INT - 1, '0').append("1");

	assert(result == correctResult);
	std::cout << "[+] Success testOne\n";
}

// Success test
void testTwentyOne()
{
	std::string result = getBinaryString(21);
	std::string correctResult = std::bitset<BYTES_INT>(21).to_string();

	assert(result == correctResult);
	std::cout << "[+] Success testTwentyOne\n";
}

// Success test
void testBigNum()
{
	std::string result = getBinaryString(123456789);
	std::string correctResult = std::bitset<BYTES_INT>(123456789).to_string();

	assert(result == correctResult);
	std::cout << "[+] Success testBigNum\n";
}

// Success test
void testNegativeOne()
{
	std::string result = getBinaryString(-1);
	std::string correctResult = std::string(BYTES_INT - 1, '1').append("0");

	assert(result == correctResult);
	std::cout << "[+] Success testNegativeOne\n";
}

// Success test
void testNegativeTwo()
{
	std::string result = getBinaryString(-2);
	std::string correctResult = std::string(BYTES_INT, '1');
	correctResult[32 - 2] = '0';

	assert(result == correctResult);
	std::cout << "[+] Success testNegativeTwo\n";
}

int main(void)
{
	testZero();
	testOne();
	testTwentyOne();
	testBigNum();
	testNegativeOne();
	testNegativeTwo();

	return (0);
}
