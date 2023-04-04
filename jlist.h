#pragma once
#define BLOCK_LIST_BLOCK_SIZE 8

template <typename T>
struct BlockNode
{
	T* data;
	int size;
	BlockNode<T>* next;
	BlockNode<T>* prev;

	BlockNode(int block_size)
	{
		size = 0;
		data = new T[block_size];
		next = nullptr;
		prev = nullptr;
	}

	~BlockNode()
	{
		delete[] data;
	}
};

template <typename T>
class jlist
{
public:
	jlist();
	jlist(const jlist& other);
	~jlist();

	jlist& operator=(const jlist& other);
	bool operator==(const jlist& other);

	void push_back(T value);
	void erase(T& item);
	void clear();
	int size();
	bool empty();

	class iterator {
	public:
		BlockNode<T>* current;
		int index;

		iterator()
		{
			this->current = head;
			this->index = 0;
		}

		iterator(int other)
		{
			this->current = nullptr;
			this->index = other;
		}

		iterator(BlockNode<T>* node, int index)
		{
			this->current = node;
			this->index = index;
		}

		iterator(const iterator& other)
		{
			this->current = other.current;
			this->index = other.index;
		}

		iterator& operator=(const iterator& other) 
		{
			this->current = other.current;
			this->index = other.index;
			return *this;
		}
		iterator& operator++() 
		{
			if (index == current->size - 1)
			{
				current = current->next;
				index = 0;
			}
			else
			{
				index++;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			if (index == current->size - 1)
			{
				current = current->next;
				index = 0;
			}
			else
			{
				index++;
			}
			return temp;
		}
		iterator& operator--()
		{
			if (index == 0)
			{
				current = current->prev;
				index = current->size - 1;
			}
			else
			{
				index--;
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;
			if (index == 0)
			{
				current = current->prev;
				index = current->size - 1;
			}
			else
			{
				index--;
			}
			return temp;
		}

		bool operator==(const iterator& other)
		{
			return (this->current == other.current && this->index == other.index);
		}
		bool operator!=(const iterator& other)
		{
			if (this->current == nullptr)
				return false;
			if (this->current->data[index] == NULL)
				return false;
			return (this->current != other.current || this->index != other.index);
		}

		T& operator*()
		{
			return current->data[index];
		}
		const T& operator*() const
		{
			return current->data[index];
		}

		T* operator->()
		{
			return &current->data[index];
		}
	};

	class reverse_iterator {
	public:
		BlockNode<T>* current;
		int index;

		reverse_iterator()
		{
			this->current = tail;
			this->index = tail->size;
		}

		reverse_iterator(int other)
		{
			this->current = nullptr;
			this->index = other;
		}

		reverse_iterator(BlockNode<T>* current, int index)
		{
			this->current = current;
			this->index = index;
		}
		
		reverse_iterator(const reverse_iterator& other)
		{
			this->current = other.current;
			this->index = other.index;
		}

		reverse_iterator& operator=(const reverse_iterator& other)
		{
			this->current = other.current;
			this->index = other.index;
			return *this;
		}
		reverse_iterator& operator++()
		{
			if (index == 0)
			{
				current = current->prev;
				if (current != nullptr) index = current->size - 1;
			}
			else
			{
				index--;
			}
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			if (index == 0)
			{
				current = current->prev;
				if(current != nullptr) index = current->size - 1;
			}
			else
			{
				index--;
			}
			return temp;
		}
		reverse_iterator& operator--()
		{
			if (index == current->size - 1)
			{
				current = current->next;
				index = 0;
			}
			else
			{
				index++;
			}
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			if (index == current->size - 1)
			{
				current = current->next;
				index = 0;
			}
			else
			{
				index++;
			}
			return temp;
		}

		bool operator==(const reverse_iterator& other)
		{
			return (this->current == other.current && this->index == other.index);
		}
		bool operator!=(const reverse_iterator& other)
		{
			if (this->current == nullptr)
				return false;
			if (this->current->data[index] == NULL)
				return false;
			return (this->current != other.current || this->index != other.index);
		}

		T& operator*()
		{
			return current->data[index];
		}
		const T& operator*() const
		{
			return current->data[index];
		}
		T* operator->()
		{
			return &current->data[index];
		}
	};

	iterator begin()
	{
		return iterator(head, 0);
	}

	iterator end()
	{
		return NULL;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(tail, tail->size - 1);
	}

	reverse_iterator rend()
	{
		return NULL;
	}

private:
	BlockNode<T>* head;
	BlockNode<T>* tail;
	int length, block_size;
};

template<typename T>
inline jlist<T>::jlist()
{
	block_size = BLOCK_LIST_BLOCK_SIZE;
	length = 0;
	BlockNode<T>* temp = new BlockNode<T>(block_size);
	head = temp;
	tail = temp;
}

template<typename T>
inline jlist<T>::jlist(const jlist& other)
{
	this->block_size = other.block_size;
	this->length = 0;
	BlockNode<T>* current = other.head;
	while (current != nullptr)
	{
		for (int i = 0; i < current->size; i++)
		{
			this->push_back(current->data[i]);
		}
		current = current->next;
	}
}

template<typename T>
inline jlist<T>::~jlist()
{
	this->clear();
}

template<typename T>
inline jlist<T>& jlist<T>::operator=(const jlist& other)
{
	this->block_size = other.block_size;
	this->length = 0;
	BlockNode<T>* current = other.head;
	while (current != nullptr)
	{
		for (int i = 0; i < current->size; i++)
		{
			this->push_back(current->data[i]);
		}
		current = current->next;
	}
	return *this;
}

template<typename T>
inline bool jlist<T>::operator==(const jlist& other)
{
	if (this->length != other.length)
		return false;
	return true;
}

template<typename T>
inline void jlist<T>::push_back(T value)
{
	if (tail->size == block_size)
	{
		BlockNode<T>* new_tail = new BlockNode<T>(block_size);
		tail->next = new_tail;
		new_tail->prev = tail;
		tail = new_tail;
		new_tail->data[0] = value;
	}
	else
	{
		tail->data[tail->size] = value;
	}
	tail->size++;
	length++;
}

template<typename T>
inline void jlist<T>::erase(T& item)
{
	BlockNode<T>* current = head;
	while (current != nullptr)
	{
		for (int i = 0; i < current->size; i++)
		{
			if (&(current->data[i]) == &(item))
			{
				for (int j = i; j < current->size - 1; j++)
				{
					current->data[j] = current->data[j + 1];
				}
				current->size--;
				return;
			}
		}
		current = current->next;
	}
}

template<typename T>
inline void jlist<T>::clear()
{
	BlockNode<T>* current = head;
	while (current != nullptr)
	{
		BlockNode<T>* temp = current;
		current = current->next;
		delete temp;
	}

	block_size = BLOCK_LIST_BLOCK_SIZE;
	length = 0;
	BlockNode<T>* temp = new BlockNode<T>(block_size);
	head = temp;
	tail = head;
}

template<typename T>
inline int jlist<T>::size()
{
	return length;
}

template<typename T>
inline bool jlist<T>::empty()
{
	return length == 0;
}
