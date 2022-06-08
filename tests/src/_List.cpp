#include "List.hpp"
#include <climits>
#include <bitset>

# define LIST_SIZE 5

ListNode *createSimpleList()
{
	int i;
	ListNode *it;
	ListNode *head;
	ListNode *prev;

	i = 0;
	head = new ListNode;
	it = head;
	it->prev = nullptr;
	prev = nullptr;
	while (i < LIST_SIZE)
	{
		it->data = std::string("test") + std::to_string(i);
		it->rand = it->prev;

		i++;
		if (i < LIST_SIZE)
		{
			it->next = new ListNode;
			prev = it;
			it = it->next;
			it->prev = prev;
		}
	}
	it->next = nullptr;
	head->prev = nullptr;
	std::cout << "[.] createSimpleList size (" << i << ")\n";
	return head;
}

// Success test
void testSerialize(FILE *file, List *list)
{
	list->serialize(file);
	std::cout << "[+] Success testSerialize\n";
}

// Success test
void testDeserialize(FILE *file, List *list)
{
	list->deserialize(file);
	assert(list->getCount() == LIST_SIZE);
	std::cout << "[+] Success testDeserialize\n";
}

// Success test
void testListComparison(const ListNode *oldLst, const ListNode *newLst)
{
	const ListNode *end;

	end = oldLst;
	while (1)
	{
		assert(oldLst);
		assert(newLst);
		assert(oldLst->data == newLst->data);
		if (oldLst->rand)
		{
			assert(newLst->rand);
			assert(oldLst->rand->data == newLst->rand->data);
		}
		oldLst = oldLst->next;
		newLst = newLst->next;
		if (oldLst == nullptr || oldLst == end)
			break;
	}
	std::cout << "[+] Success testListComparison\n";
}

void _List()
{
	List list;
	ListNode *oldLst;
	FILE *file;

	file = fopen("./tests/bin/testSerialize.txt", "wb");
	assert(file);
	oldLst = createSimpleList();
	list.setList(oldLst);
	testSerialize(file, &list);
	fclose(file);

	file = fopen("./tests/bin/testSerialize.txt", "rb");
	assert(file);
	testDeserialize(file, &list);
	fclose(file);
	testListComparison(oldLst, list.getList());
}