#pragma once
template<typename T>
struct node
{
	T value;
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

	explicit linked_list()
	{
		head = nullptr;
		tail = nullptr;
	}
	void add(int i)
	{
		if(head == nullptr)
		{
			head = new node<int>(i);
			tail = head;

		}else
		{
			tail->next = new node<int>(i);
			tail = tail->next;
		}
	}

	void print() const
	{
		for (auto iter = head; iter != nullptr; iter = iter->next)
		{
			std::cout << iter->value;
		}
	};
};