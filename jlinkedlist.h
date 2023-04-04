#pragma once
#include "jstring.h"
#include "css_section.h"

template <typename T>
struct Node
{
	T* data;
	Node<T>* next;
	Node<T>* prev;

	Node(T& data);
	~Node();
};

template <typename T>
class jlinkedlist
{
public:
	jlinkedlist();
	jlinkedlist(T* data);
	~jlinkedlist();

	void push_back(T* data);
	void erase(T* data);
	void erase(T& data);
	void clear();

	size_t size();

	class iterator
	{
	public:
		iterator(Node<T>* node) : node(node) {}
		iterator& operator++() { node = node->next; return *this; }
		iterator& operator++(int) { iterator it = *this; ++(*this); return it; }
		iterator& operator--() { node = node->prev; return *this; }
		bool operator!=(const iterator& other) { return node != other.node; }
		T& operator*() { return *node->data; }
		T& operator->() { return *node->data; }
		T* operator&() { return node->data; }

	private:
		Node<T>* node;
	};

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(nullptr); }

private:
	Node<T>* head;
	Node<T>* tail;
	size_t length;
};

#include "jlinkedlist.h"

template<typename T>
inline Node<T>::Node(T& data)
{
	this->next = nullptr;
	this->prev = nullptr;
	this->data = new T(data);
}

template<typename T>
inline Node<T>::~Node()
{
}

template<typename T>
inline jlinkedlist<T>::jlinkedlist() : head(nullptr), tail(nullptr), length(0)
{
}

template<typename T>
inline jlinkedlist<T>::jlinkedlist(T* data)
{
	head = new Node<T>(*data);
	tail = head;
	length = 1;
}

template<typename T>
inline jlinkedlist<T>::~jlinkedlist()
{
	this->clear();
}

template<typename T>
inline void jlinkedlist<T>::push_back(T* data)
{
	Node<T>* temp = new Node<T>(*data);
	if (this->head == nullptr)
	{
		this->head = temp;
		this->tail = temp;
	}
	else
	{
		this->tail->next = temp;
		temp->prev = this->tail;
		this->tail = temp;
	}
	length++;
}

template<typename T>
inline void jlinkedlist<T>::erase(T* data)
{
	Node<T>* temp = this->head;
	while (temp->data != data)
	{
		temp = temp->next;
	}
	if (temp == this->head)
	{
		this->head = temp->next;
	}
	else if (temp == this->tail)
	{
		this->tail = temp->prev;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	delete temp;
	length--;
}

template<typename T>
inline void jlinkedlist<T>::erase(T& data)
{
	Node<T>* temp = this->head;
	while (temp->data != &data)
	{
		temp = temp->next;
	}
	if (temp == this->head)
	{
		this->head = temp->next;
	}
	else if (temp == this->tail)
	{
		this->tail = temp->prev;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	delete temp;
	length--;
}

template<typename T>
inline void jlinkedlist<T>::clear()
{
	Node<T>* temp = this->head;
	while (temp != nullptr)
	{
		Node<T>* next = temp->next;
		temp = next;
	}
	length = 0;
}

template<typename T>
inline size_t jlinkedlist<T>::size()
{
	return length;
}

