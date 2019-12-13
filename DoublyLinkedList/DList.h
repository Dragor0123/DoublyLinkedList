#pragma once
#include <iostream>

typedef int element;
class DList
{
public:

	class Node;
	class Iterator;

	Iterator insert(Iterator position, const element& val);
	Iterator insert(Iterator position, size_t n, const element& val);
	Iterator insert(Iterator position, Iterator const first, Iterator const last);
	Iterator erase(Iterator position);
	Iterator erase(Iterator first, Iterator last);

	class Iterator
	{
		friend Iterator DList::insert(Iterator position, const element& val);
		friend Iterator DList::insert(Iterator position, size_t n, const element& val);
		friend Iterator DList::insert(Iterator position, Iterator const first, Iterator const last);
		friend Iterator DList::erase(Iterator position);
		friend Iterator DList::erase(Iterator first, Iterator last);

	public:
		Iterator();
		explicit Iterator(Node* ptr);
		Iterator(const Iterator& Other);
		Iterator& operator=(const Iterator& Other);
		virtual ~Iterator() {};
		bool operator==(const Iterator& Other);
		bool operator!=(const Iterator& Other);
		element& operator* ();
		element* operator-> ();
		Iterator& operator++();
		const Iterator operator++(int);
		Iterator& operator--();
		const Iterator operator--(int);
	private:
		Node* m_ptr;
	};

	DList();
	DList(const DList& Other);
	DList& operator=(const DList& Other);
	virtual ~DList();

	Iterator begin();
	Iterator end();
	const Iterator begin() const;
	const Iterator end() const;
	element& back();
	element& front();
	bool empty();

	void pop_back();
	void pop_front();
	void push_back(const element& val);
	void push_front(const element& val);

	void reverse();

	void clear();
	size_t size();

private:
	class Node
	{
	public:
		Node(const element& _data, Node* _prev = nullptr, Node* _post = nullptr)
			: data(_data), prev(_prev), post(_post) {}

		Node(const Node& Other)
			: data(Other.data), prev(Other.prev), post(Other.post) {}

		element data;
		Node* prev;
		Node* post;
	};

	Node* m_pHead;
	Node* m_pTail;
	size_t m_size;
};
