#include "saber.hpp"

// пример использования
// char data[] = “AAA BBB AAA”;
// RemoveDups(data);
// printf(“%s\n”, data); // “A B A”

void removeDups(char* str)
{
	int i, a;
	char c = '\0';

	if (str == nullptr)
		return;
	i = 0;
	a = 0;
	while (str[i])
	{
		if (c != str[i])
		{
			c = str[i];
			str[a] = c;
			a++;
		}
		i++;
	}
	str[a] = '\0';
}