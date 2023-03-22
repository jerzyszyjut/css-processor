#include "JerzyList.h"

template<typename T>
JerzyList<T>::JerzyList(): head(nullptr), tail(nullptr), length(0)
{
}

template<typename T>
JerzyList<T>::JerzyList(const JerzyList<T>& list)
{
	this->head = list.head;
	this->tail = list.tail;
	this->length = list.length;
}

template<typename T>
JerzyList<T>::~JerzyList()
{
	this->clear();
}

template<typename T>
JerzyList<T>& JerzyList<T>::operator=(const JerzyList<T>& list)
{
	if (this != &list)
	{
		this->head = list.head;
		this->tail = list.tail;
		this->length = list.length;
	}
	return *this;
}

template<typename T>
void JerzyList<T>::push_back(const T& value)
{
	Node* newNode = new Node(value);
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	length++;
}

template<typename T>
void JerzyList<T>::insert(int index, const T& value)
{
	if (index == 0)
	{
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
		length++;
	}
	else if (index == length)
	{
		push_back(value);
	}
	else if (index > 0 && index < length)
	{
		Node* newNode = new Node(value);
		Node* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
		length++;
	}
}

template<typename T>
void JerzyList<T>::remove(int index)
{
	if (index == 0)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
		length--;
	}
	else if (index == length - 1)
	{
		Node* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		delete tail;
		tail = temp;
		tail->next = nullptr;
		length--;
	}
	else if (index > 0 && index < length - 1)
	{
		Node* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		Node* temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;
		length--;
	}
}

template<typename T>
void JerzyList<T>::clear()
{
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	length = 0;
}

template<typename T>
T& JerzyList<T>::find(const T& value)
{
	Node* temp = head;
	for (int i = 0; i < length; i++)
	{
		if (temp->value == value)
		{
			return temp->value;
		}
		temp = temp->next;
	}
}

template<typename T>
int JerzyList<T>::getLength() const
{
	return length;
}

template<typename T>
T& JerzyList<T>::operator[](int index)
{
	if (this->length == 0)
	{
		return nullptr;
	}
	else if (index == 0)
	{
		return head->value;
	}
	else if (index == length - 1)
	{
		return tail->value;
	}
	else if (index > 0 && index < length - 1)
	{
		Node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->value;
	}
}

template<typename T>
const T& JerzyList<T>::operator[](int index) const
{
	if (this->length == 0)
	{
		return nullptr;
	}
	else if (index == 0)
	{
		return head->value;
	}
	else if (index == length - 1)
	{
		return tail->value;
	}
	else if (index > 0 && index < length - 1)
	{
		Node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->value;
	}
}

