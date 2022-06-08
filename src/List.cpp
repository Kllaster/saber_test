#include "List.hpp"

int List::getCount() const
{
	return count;
}

const ListNode *List::getList() const
{
	return head;
}

void List::setList(ListNode *lst)
{
	ListNode *it;
	ListNode *tail;

	if (lst == nullptr)
		return;
	it = lst;
	count = 0;
	while (it)
	{
		count++;
		tail = it;
		it = it->next;
	}
	this->head = lst;
	this->tail = tail;
}

void List::serialize(FILE *file)
{
	size_t length;
	ListNode *it = head;
	ListNode *end;

	if (file == nullptr)
		return;

	fwrite(&head->prev, sizeof(void *), 1, file);
	fwrite(&tail->next, sizeof(void *), 1, file);

	if (head->prev == nullptr)
		end = nullptr;
	else
		end = head;
	while (it != end)
	{
		fwrite(&it, sizeof(void *), 1, file);
		fwrite(&it->rand, sizeof(void *), 1, file);

		length = it->data.length();
		fwrite(&length, sizeof(size_t), 1, file);

		fwrite(it->data.c_str(), sizeof(char), length, file);
		it = it->next;
	}
}

void List::deserialize(FILE *file)
{
	void *ptr;
	size_t length;
	ListNode *it, *prev, *tail_next;
	std::unordered_map<void *, ListNode *> oldPtrToNew;
	std::unordered_map<void *, ListNode *>::iterator iterPtr;

	if (file == nullptr)
		return;

	it = new ListNode;
	head = it;
	prev = nullptr;

	fread(&head->prev, 8, 1, file);
	fread(&tail_next, 8, 1, file);
	while (!feof(file))
	{
		if (fread(&ptr, sizeof(void *), 1, file) != 1)
			break;
		if (prev != nullptr)
		{
			it->next = new ListNode;
			it = it->next;
		}
		oldPtrToNew[ptr] = it;
		fread(&it->rand, sizeof(void *), 1, file);
		fread(&length, sizeof(size_t), 1, file);
		it->data = std::string(length, '\0');
		fread(&it->data[0], sizeof(char), length, file);

		it->prev = prev;
		if (prev)
			prev->next = it;
		prev = it;
	}

	tail = prev;

	// set ListNode *rand
	it = head;
	count = 1;
	while (it != tail)
	{
		iterPtr = oldPtrToNew.find(it->rand);
		it->rand = iterPtr == oldPtrToNew.end() ? nullptr : iterPtr->second;
		it = it->next;
		count++;
	}

	// set if looped list
	iterPtr = oldPtrToNew.find(head->prev);
	head->prev = iterPtr == oldPtrToNew.end() ? nullptr : iterPtr->second;
	iterPtr = oldPtrToNew.find(tail->next);
	tail->next = iterPtr == oldPtrToNew.end() ? nullptr : iterPtr->second;
}