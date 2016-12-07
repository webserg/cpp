#pragma once
template<typename T>
class node
{
	T value;

public:
	node* next;
	explicit node(const T& value)
		: value(value)
	{
		next = nullptr;
	}

};
class linked_list
{
	node<int>* head;
	node<int>* tail;

public:
	explicit linked_list(node<int>* head)
		: head(head)
	{
		tail = head;
	}
	explicit linked_list(int i)
	{
		auto curr = node<int>(i);
		head = &curr;
		head->next = tail;
	}
	void add(int i)
	{
		auto cur = node<int>(i);
		tail = &cur;
		tail = &cur;
	}
};