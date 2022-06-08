#ifndef LIST_HPP
# define LIST_HPP

# include <string>
# include <iostream>
# include <unordered_map>

struct ListNode
{
	ListNode *prev;
	ListNode *next;
	ListNode *rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};

class List
{
 public:
	int getCount() const;
	const ListNode *getList() const;

	void setList(ListNode *lst);

	// сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void serialize(FILE *file);
	// загрузка из файла (файл открыт с помощью fopen(path, "rb"))
	void deserialize(FILE *file);

 private:
	ListNode *head;
	ListNode *tail;
	int count;
};

#endif