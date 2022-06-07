#include "saber.hpp"

std::string getBinaryString(int num)
{
	int sign = 1;
	std::string buf;

	if (num == 0)
		return std::string(BYTES_INT, '0');
	if (num < 0)
		sign = -1;
	while (num != 0)
	{
		if (sign == -1)
			buf += (num % 2) ? '0' : '1';
		else
			buf += (num % 2) ? '1' : '0';
		num /= 2;
	}
	reverse(buf.begin(), buf.end());
	if (sign == 1)
		buf = std::string(BYTES_INT - buf.size(), '0').append(buf);
	else
		buf = std::string(BYTES_INT - buf.size(), '1').append(buf);
	if (sign == -1)
		buf[0] = '1';
	return buf;
}

void printBinary(int num)
{
	std::cout << getBinaryString(num);
}