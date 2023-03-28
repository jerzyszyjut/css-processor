#pragma once
#define BLOCK_SIZE 3

template <typename T>
struct Node
{
	T *value;
	Node *next;
	Node *prev;
};

template <typename T>
class JerzyList
{
public:
	JerzyList();
	JerzyList(const JerzyList<T> &list);
	JerzyList(int block_size);
	~JerzyList();
	JerzyList<T> &operator=(const JerzyList<T> &list);
	void push_back(const T &value);
	void insert(int index, const T &value);
	void remove(int index);
	void clear();
	int find(const T &value);
	int getLength() const;
	int getBlockSize() const;
	T &operator[](int index);
	const T &operator[](int index) const;

private:
	Node<T> *head;
	Node<T> *tail;
	int length, block_size;
};

template <typename T>
inline JerzyList<T>::JerzyList() : head(nullptr), tail(nullptr), length(0), block_size(BLOCK_SIZE)
{
}

template <typename T>
inline JerzyList<T>::JerzyList(const JerzyList<T> &list) : block_size(BLOCK_SIZE)
{
	this->head = list.head;
	this->tail = list.tail;
	this->length = list.length;
	this->block_size = list.block_size;
}

template <typename T>
inline JerzyList<T>::JerzyList(int block_size) : head(nullptr), tail(nullptr), length(0), block_size(block_size)
{
}

template <typename T>
inline JerzyList<T>::~JerzyList()
{
	this->clear();
}

template <typename T>
inline JerzyList<T> &JerzyList<T>::operator=(const JerzyList<T> &list)
{
	if (this != &list)
	{
		this->head = list.head;
		this->tail = list.tail;
		this->length = list.length;
		this->block_size = list.block_size;
	}
	return *this;
}

template <typename T>
inline void JerzyList<T>::push_back(const T &value)
{
	if (length % block_size == 0)
	{
		Node<T> *temp = new Node<T>;
		temp->value = new T[block_size];
		temp->value[0] = value;
		temp->next = nullptr;
		temp->prev = tail;
		if (tail != nullptr)
			tail->next = temp;
		tail = temp;
		if (head == nullptr)
			head = temp;
	}
	else
	{
		tail->value[length % block_size] = value;
	}
	length++;
}

template <typename T>
inline void JerzyList<T>::insert(int index, const T &value)
{
	if (index >= 0 && index < length)
	{
		Node<T> *temp = head;
		for (int i = 0; i < length; i += block_size)
		{
			if (i == index)
			{
				break;
			}
			temp = temp->next;
		}
		for (int i = index; i < length; i += block_size)
		{
			if (i == index)
			{
				temp->value[i % block_size] = value;
			}
			else
			{
				temp->value[i % block_size] = temp->next->value[(i + 1) % block_size];
			}
			temp = temp->next;
		}
	}
}

template <typename T>
inline void JerzyList<T>::remove(int index)
{
	if (this->length == 0)
	{
		return;
	}
}

template <typename T>
inline void JerzyList<T>::clear()
{
	while (head != nullptr)
	{
		Node<T> *temp = head;
		head = head->next;
		delete[] temp->value;
		delete temp;
	}
	length = 0;
}

template <typename T>
inline int JerzyList<T>::find(const T &value)
{
	for (int i = 0; i < length; i++)
	{
		if (this->operator[](i) == value)
		{
			return i;
		}
	}
}

template <typename T>
inline int JerzyList<T>::getLength() const
{
	return length;
}

template <typename T>
inline int JerzyList<T>::getBlockSize() const
{
	return 0;
}

template <typename T>
inline T &JerzyList<T>::operator[](int index)
{
	if (index >= 0 && index < length)
	{
		Node<T> *temp = head;
		for (int i = 0; i < length; i += block_size)
		{
			for (int j = 0; j < block_size; j++)
			{
				if ((j + i) == index)
				{
					return temp->value[j];
				}
			}
			temp = temp->next;
		}
	}
}

template <typename T>
inline const T &JerzyList<T>::operator[](int index) const
{
	if (index >= 0 && index < length)
	{
		Node<T> *temp = head;
		for (int i = 0; i < length; i += block_size)
		{
			for (int j = 0; j < block_size; j++)
			{
				if ((j + i) == index)
				{
					return temp->value[j];
				}
			}
			temp = temp->next;
		}
	}
}
