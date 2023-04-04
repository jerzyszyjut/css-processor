#pragma once
#define DEFAULT_BLOCK_LIST_BLOCK_SIZE 8

template <typename T>
struct BlockNode
{
	T** data;
	BlockNode<T>* next;
	BlockNode<T>* prev;
	int size;

	BlockNode(int block_size);
	BlockNode(int block_size, T& data);
	~BlockNode();
};

template <typename T>
class jblocklist
{
public:
	jblocklist();
	jblocklist(T* data);
	~jblocklist();

	void push_back(T* data);
	void erase(T* data);
	void erase(T& data);
	void clear();

	size_t size();

	class iterator
	{
	public:
		iterator(BlockNode<T>* node, int index) : node(node), index(index) {}
		iterator& operator++() { index++; if (index >= node->size) { node = node->next; index = 0; } return *this; }
		iterator& operator++(int) { iterator it = *this; ++(*this); return it; }
		iterator& operator--() { index--; if (index < 0) { node = node->prev; index = node->size - 1; } return *this; }
		bool operator!=(const iterator& other) {
			return node != other.node;
		}
		T& operator*() { return *node->data[index]; }
		T& operator->() { return *node->data[index]; }
		T* operator&() { return node->data[index]; }
	private:
		BlockNode<T>* node;
		int index;
	};

	class reverse_iterator
	{
	public:
		reverse_iterator(BlockNode<T>* node, int index) : node(node), index(index) {}
		reverse_iterator& operator++() { index--; if (index < 0) { node = node->prev; index = node->size - 1; } return *this; }
		reverse_iterator& operator++(int) { reverse_iterator it = *this; ++(*this); return it; }
		reverse_iterator& operator--() { index++; if (index >= node->size) { node = node->next; index = 0; } return *this; }
		bool operator!=(const reverse_iterator& other) 
		{ 
			if (node->prev == NULL && index == 0) return false;
			return node != other.node; 
		}
		T& operator*() { return *node->data[index]; }
		T& operator->() { return *node->data[index]; }
		T* operator&() { return node->data[index]; }
	private:
		BlockNode<T>* node;
		int index;
	};

	iterator begin() { return iterator(head, 0); }
	iterator end() { return iterator(nullptr, 0); }
	reverse_iterator rbegin() { return reverse_iterator(tail, tail->size - 1); }
	reverse_iterator rend() { return reverse_iterator(nullptr, 0); }

private:
	BlockNode<T>* head;
	BlockNode<T>* tail;
	size_t length, block_size;
};

template<typename T>
inline BlockNode<T>::BlockNode(int block_size)
{
	this->data = new T * [block_size];
	this->next = nullptr;
	this->prev = nullptr;
	this->size = 0;
}

template<typename T>
inline BlockNode<T>::BlockNode(int block_size, T& data)
{
	this->data = new T * [block_size];
	this->data[0] = new T(data);
	this->next = nullptr;
	this->prev = nullptr;
	this->size = 1;
}

template<typename T>
inline BlockNode<T>::~BlockNode()
{
	if(this->data != nullptr)
		delete[] this->data;
}

template<typename T>
inline jblocklist<T>::jblocklist() : head(nullptr), tail(nullptr), length(0), block_size(DEFAULT_BLOCK_LIST_BLOCK_SIZE)
{
}

template<typename T>
inline jblocklist<T>::jblocklist(T* data)
{
	head = new BlockNode<T>(*data);
	tail = head;
	length = 1;
	block_size = DEFAULT_BLOCK_LIST_BLOCK_SIZE;
}

template<typename T>
inline jblocklist<T>::~jblocklist()
{
	this->clear();
}

template<typename T>
inline void jblocklist<T>::push_back(T* data)
{
	if (this->head == nullptr) {
		head = new BlockNode<T>(block_size, *data);
		tail = head;
	}
	else {
		if (length % block_size == 0) {
			BlockNode<T>* temp = new BlockNode<T>(block_size, *data);
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		else {
			tail->data[tail->size] = new T(data);
			tail->size++;
		}
	}
	length++;
}

template<typename T>
inline void jblocklist<T>::erase(T* data)
{
	BlockNode<T>* temp = head;
	int index = 0;
	while (temp->data[index] != data && temp != nullptr)
	{
		index++;
		if (index == temp->size) {
			temp = temp->next;
			index = 0;
		}
	}

	if (temp != nullptr)
	{
		delete temp->data[index];
		for (int i = index; i < temp->size; i++)
		{
			temp->data[i] = temp->data[i + 1];
		}
		temp->size--;
		length--;
	}

	if (temp->size == 0)
	{
		temp->data = nullptr;
		if (temp->next != nullptr)
		{
			temp->next->prev = temp->prev;
		}
		else
		{
			tail = temp->prev;
		}

		if (temp->prev != nullptr)
		{
			temp->prev->next = temp->next;
		}
		else
		{
			head = temp->next;
		}

		delete temp;
	}
}

template<typename T>
inline void jblocklist<T>::erase(T& data)
{
	BlockNode<T>* temp = head;
	int index = 0;
	while (*(temp->data[index]) != data && temp != nullptr)
	{
		index++;
		if (index == temp->size) {
			temp = temp->next;
			index = 0;
		}
	}

	if (temp != nullptr)
	{
		delete temp->data[index];
		for (int i = index; i < temp->size; i++)
		{
			temp->data[i] = temp->data[i + 1];
		}
		temp->size--;
		length--;
	}

	if (temp->size == 0)
	{
		if (temp->next != nullptr)
		{
			temp->next->prev = temp->prev;
		}
		else
		{
			tail = temp->prev;
		}

		if (temp->prev != nullptr)
		{
			temp->prev->next = temp->next;
		}
		else
		{
			head = temp->next;
		}

		delete temp;
	}
}

template<typename T>
inline void jblocklist<T>::clear()
{
	BlockNode<T>* temp = this->head;
	while (temp != nullptr)
	{
		BlockNode<T>* next = temp->next;
		delete temp;
		temp = next;
	}
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template<typename T>
inline size_t jblocklist<T>::size()
{
	return length;
}
