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
	~jlist();

	void push_back(T value);
	void erase(T& item);
	void clear();
	int size();
	bool empty();

	class iterator {
	public:
		BlockNode<T>* current;
		int index;

		iterator(BlockNode<T>* node, int index)
		{
			this->current = node;
			this->index = index;
		}

	public:
		iterator()
		{
			this->current = head;
			this->index = 0;
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

		reverse_iterator(BlockNode<T>* current, int index)
		{
			this->current = current;
			this->index = index;
		}

	public:
		reverse_iterator()
		{
			this->current = tail;
			this->index = tail->size;
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

	reverse_iterator rbegin()
	{
		return reverse_iterator(tail, tail->size - 1);
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
inline jlist<T>::~jlist()
{
	this->clear();
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
		tail->size++;
	}
}

template<typename T>
inline void jlist<T>::erase(T& item)
{
	BlockNode<T>* current = head;
	bool found = false;
}

template<typename T>
inline void jlist<T>::clear()
{
	BlockNode<T>* current = head;
	while (current != nullptr)
	{
		BlockNode<T>* next = current->next;
		current = next;
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
