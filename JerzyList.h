#pragma once
#define BLOCK_SIZE 8
#include <stdexcept>

template <typename T>
struct Node
{
	T* value;
	Node* next;
	Node* prev;
	int size;
};

template <typename T, int K>
class JerzyList
{
public:
	JerzyList();
	JerzyList(const JerzyList<T, K>& list);
	~JerzyList();
	JerzyList<T, K>& operator=(const JerzyList<T, K>& list);
	JerzyList<T, K>& operator=(const int other);
	void push_back(const T& value);
	void replace(int index, const T& value);
	void remove(int index);
	void clear();
	int find(const T& value);
	int getLength() const;
	T& operator[](int index);
	const T& operator[](int index) const;
	bool operator==(const int other) const;

private:
	Node<T>* head;
	Node<T>* tail;
	int length;
};

template<typename T, int K>
inline JerzyList<T, K>::JerzyList() : head(nullptr), tail(nullptr), length(0)
{
}

template<typename T, int K>
inline JerzyList<T, K>::JerzyList(const JerzyList<T, K>& list)
{
	this->head = list.head;
	this->tail = list.tail;
	this->length = list.length;
}

template<typename T, int K>
inline JerzyList<T, K>::~JerzyList()
{
	this->clear();
}

template<typename T, int K>
inline JerzyList<T, K>& JerzyList<T, K>::operator=(const JerzyList<T, K>& list)
{
	if (this != &list)
	{
		this->head = list.head;
		this->tail = list.tail;
		this->length = list.length;
	}
	return *this;
}

template<typename T, int K>
inline JerzyList<T, K>& JerzyList<T, K>::operator=(const int other)
{
	if (other == NULL)
	{
		this->clear();
	}
	return *this;
}

template<typename T, int K>
inline void JerzyList<T, K>::push_back(const T& value)
{
	if (head == nullptr) {
		head = new Node<T>;
		head->value = new T[K];
		head->value[0] = value;
		head->size = 1;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
	}
	else {
		if (tail->size == K) {
			Node<T>* temp = new Node<T>;
			temp->value = new T[K];
			temp->value[0] = value;
			temp->size = 1;
			temp->next = nullptr;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		else {
			Node<T>* temp = tail;
			int counter = 0;
			for (int i = 0; i < K; i++) {
				if ((counter == temp->size) && (i < K)) {
					temp->value[i] = value;
					temp->size++;
					this->length++;
					return;
				}
				if (temp != nullptr) counter++;
			}
			temp = new Node<T>;
			temp->value = new T[K];
			temp->value[0] = value;
			temp->size = 1;
			temp->next = nullptr;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}
	length++;
}

template<typename T, int K>
inline void JerzyList<T, K>::replace(int index, const T& value)
{
	delete this->operator[](index);
	this->operator[](index) = value;
}

template<typename T, int K>
inline void JerzyList<T, K>::remove(int index)
{
	if (index < 0 || index > length)
	{
		return;
	}

	int current_index = 0;
	Node<T>* temp = head;

	while (temp != nullptr && ((current_index + temp->size) < index))
	{
		current_index += temp->size;
		temp = temp->next;
	}

	if (temp != nullptr)
	{
		int nothing = NULL;

		for (int i = 0; i < temp->size; i++)
		{
			if (temp->value[i] == nothing) index++;
		}
		temp->value[index - current_index] = nothing;
		temp->size--;
		length--;
	}

	if (temp->size == 0) {
		if (temp->prev != nullptr && temp->next != nullptr)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
		else if (temp->prev == nullptr && temp->next != nullptr)
		{
			temp->next->prev = nullptr;
			head = temp->next;
			delete temp;
		}
		else if (temp->prev != nullptr && temp->next == nullptr)
		{
			temp->prev->next = nullptr;
			tail = temp->prev;
			delete temp;
		}
		else
		{
			head = nullptr;
			tail = nullptr;
			delete temp;
		}
	}
}

template<typename T, int K>
inline void JerzyList<T, K>::clear()
{
	Node<T>* temp = head;
	while (temp != nullptr)
	{
		Node<T>* temp2 = temp;
		temp = temp->next;
		delete[] temp2->value;
		delete temp2;
	}
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template<typename T, int K>
inline int JerzyList<T, K>::find(const T& value)
{
	Node<T>* temp = head;
	int counter = 0;
	while (temp != nullptr)
	{
		for (int i = 0; i < temp->size; i++)
		{
			if (temp->value[i] == value) return counter;
			int nothing = NULL;
			if (!(temp->value[i] == nothing)) counter++;
		}
		temp = temp->next;
	}
	return -1;
}

template<typename T, int K>
inline int JerzyList<T, K>::getLength() const
{
	return length;
}

template<typename T, int K>
inline T& JerzyList<T, K>::operator[](int index)
{
	if (index < 0 || index > length)
		throw std::out_of_range("Index out of range");

	int current_index = 0, i;
	Node<T>* temp = head;

	while (temp != nullptr && ((current_index + temp->size) <= index))
	{
		current_index += temp->size;
		temp = temp->next;
	}

	if (temp != nullptr)
	{
		int nothing = NULL;

		for (i = 0; i < temp->size; i++)
		{
			if (current_index == index)
			{
				break;
			}
			if (!(temp->value[i] == nothing))
			{
				current_index++;
			}
		}

		while (temp->value[i] == nothing)
		{
			i++;
		}

		return temp->value[i];
	}
}

template<typename T, int K>
inline const T& JerzyList<T, K>::operator[](int index) const
{
	if (index < 0 || index > length)
	{
		return;
	}

	int current_index = 0;
	Node<T>* temp = head;

	while (temp != nullptr && ((current_index + temp->size) < index))
	{
		current_index += temp->size;
		temp = temp->next;
	}

	if (temp != nullptr)
	{
		int nothing = NULL;

		for (int i = 0; i < temp->size; i++)
		{
			if (!(temp->value[i] == nothing)) current_index++;
		}
		return temp->value[index - current_index];
	}
}

template<typename T, int K>
inline bool JerzyList<T, K>::operator==(const int other) const
{
	if (this->length == 0 && other == NULL) {
		return true;
	}
	return false;
}
