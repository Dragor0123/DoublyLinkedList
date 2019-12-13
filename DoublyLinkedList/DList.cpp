#include "DList.h"

//DList::Iterator 구현

DList::Iterator::Iterator()
{
	this->m_ptr = nullptr;
}

DList::Iterator::Iterator(Node* ptr)
{
	this->m_ptr = ptr;
}

DList::Iterator::Iterator(const Iterator& Other)
{
	this->m_ptr = Other.m_ptr;
}

DList::Iterator&
DList::Iterator::operator=(const Iterator& Other)
{
	if (this != &Other) {
		this->m_ptr = Other.m_ptr;
	}
	return *this;
}

bool DList::Iterator::operator==(const Iterator& Other)
{
	return this->m_ptr == Other.m_ptr;
}

bool DList::Iterator::operator!=(const Iterator& Other)
{
	return !(this->m_ptr == Other.m_ptr);
}

element& DList::Iterator::operator* ()
{
	return m_ptr->data;
}

element* DList::Iterator::operator-> ()
{
	return &m_ptr->data;
}

DList::Iterator&
DList::Iterator::operator++()
{
	if (m_ptr->post == nullptr)
		throw(std::out_of_range("Cannot increment end list Iterator"));

	m_ptr = m_ptr->post;
	return *this;
}

const DList::Iterator
DList::Iterator::operator++(int)
{
	DList::Iterator it = *this;
	++(*this);
	return it;
}


DList::Iterator&
DList::Iterator::operator--()
{
	if (m_ptr->prev == nullptr)
		throw(std::out_of_range("Cannot decrement begin list Iterator"));

	m_ptr = m_ptr->prev;
	return *this;
}

const DList::Iterator
DList::Iterator::operator--(int)
{
	DList::Iterator it = *this;
	--(*this);
	return it;
}
////////////////////// DList::Iterator 완료

DList::Iterator
DList::insert(Iterator position, const element& val)
{
	Node* newNode = new Node(val);
	Node*& r_pos = position.m_ptr;
	newNode->prev = r_pos->prev;
	newNode->post = r_pos;
	r_pos->prev->post = newNode;
	r_pos->prev = newNode;

	Iterator it(newNode);
	++m_size;
	return it;
}

DList::Iterator
DList::insert(Iterator position, size_t n, const element& val)
{
	Iterator it = position;
	for (int i = 0; i < n; ++i) {
		it = this->insert(it, val);
	}
	return it;
}

DList::Iterator
DList::insert(Iterator position, Iterator const first, Iterator const last)
{
	Node*& r_pos = position.m_ptr;
	int cnt = 0;
	Iterator tempIt = first;
	for (; tempIt != last; ++tempIt) {
		++cnt;
	}

	r_pos->prev->post = first.m_ptr;
	first.m_ptr->prev = r_pos->prev;
	r_pos->prev = last.m_ptr->prev;
	last.m_ptr->prev->post = r_pos;
	
	m_size += cnt;
	return first;
}

DList::Iterator
DList::erase(Iterator position)
{
	Node*& r_pos = position.m_ptr;

	r_pos->prev->post = r_pos->post;
	r_pos->post->prev = r_pos->prev;
	
	Iterator it(r_pos->post);
	r_pos->prev = nullptr;
	r_pos->post = nullptr;
	delete r_pos;

	--m_size;
	return it;
}

DList::Iterator
DList::erase(Iterator first, Iterator last)
{
	Iterator it = first;
	while (it != last) {
		it = this->erase(it);
	}
	return it;
}

// Constructor
DList::DList()
{
	// dummy node를 만든다.
	Node* pDummy = new Node(INT_MIN);
	m_pHead = pDummy;
	m_pTail = pDummy;
	m_size = 0;
}

// Copy constructor
DList::DList(const DList& Other)
{
	DList::Iterator it;
	for (it = Other.begin(); it != Other.end(); ++it)
		this->push_back(*it);
}

// Assignment operator
DList& DList::operator=(const DList& Other)
{
	if (this != &Other) {
		if (!this->empty())
			this->clear();

		DList::Iterator it;
		for (it = Other.begin(); it != Other.end(); ++it)
			this->push_back(*it);
	}
	return *this;
}

// Destructor
DList::~DList()
{
	if (!this->empty())
		this->clear();

	delete m_pHead;
	m_pHead = m_pTail = nullptr;
}

DList::Iterator DList::begin()
{
	DList::Iterator it(this->m_pHead);
	return it;
}

DList::Iterator DList::end()
{
	DList::Iterator it(this->m_pTail);
	return it;
}

const DList::Iterator DList::begin() const
{
	DList::Iterator it(this->m_pHead);
	return it;
}

const DList::Iterator DList::end()const
{
	DList::Iterator it(this->m_pTail);
	return it;
}

element& DList::back()
{
	if (this->empty())
		throw (std::logic_error("back() called on empty list"));
	else
		return m_pTail->prev->data;
}

element& DList::front()
{
	if (this->empty())
		throw (std::logic_error("front() called on empty list"));
	else
		return m_pHead->data;
}

bool DList::empty()
{
	return (0 == m_size);
}

void DList::pop_back()
{
	if (this->empty()) {
		throw (std::logic_error("pop_back() called on empty list"));
	}
	else {
		Node* toRemove = m_pTail->prev;
		toRemove->prev->post = m_pTail;
		m_pTail->prev = toRemove->prev;
		delete toRemove;
		--m_size;
	}
}

void DList::pop_front()
{
	if (this->empty()) {
		throw (std::logic_error("pop_front() called on empty list"));
	}
	else {
		Node* toRemove = m_pHead;
		m_pHead = m_pHead->post;
		m_pHead->prev = nullptr;
		delete toRemove;
		--m_size;
	}
}

void DList::push_back(const element& val)
{
	Node* newNode = new Node(val);
	newNode->post = m_pTail;
	newNode->prev = m_pTail->prev;

	if (this->empty())
		m_pHead = newNode;
	else
		m_pTail->prev->post = newNode;
	
	m_pTail->prev = newNode;
	
	++m_size;
}

void DList::push_front(const element& val)
{
	Node* newNode = new Node(val);
	newNode->post = m_pHead;
	newNode->prev = nullptr;

	m_pHead->prev = newNode;
	m_pHead = newNode;

	++m_size;
}

void DList::reverse()
{
	if (!this->empty()) {
		Node* current = m_pHead;
		Node* before = nullptr;
		while (current != m_pTail) {
			before = current;
			current = current->post;

			// before->prev 와 before->post를 바꿔준다.
			Node* temp = before->prev;
			before->prev = before->post;
			before->post = temp;
		}
		m_pHead->post = m_pTail;
		current = m_pHead;
		m_pHead = m_pTail->prev;
		m_pHead->prev = nullptr;
		m_pTail->prev = current;
	}
}

void DList::clear()
{
	while (!this->empty())
		this->pop_front();
}

size_t DList::size()
{
	return m_size;
}