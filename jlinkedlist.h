#pragma once
template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node()
	{
		next = nullptr;
		prev = nullptr;
	}

	Node(T data)
	{
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}

	~Node()
	{
	}
};

template <typename T>
class jlinkedlist
{
public:
	jlinkedlist();
	jlinkedlist(jlinkedlist<T>& other);
	~jlinkedlist();

	void push_back(T value);
	void erase(T& item);
	void erase(T* item);
	void clear();
	int size();
	bool empty();

	class iterator {
	public:
		Node<T>* current;

		iterator(Node<T>* node)
		{
			this->current = node;
		}

	public:
		iterator()
		{
			this->current = head;
		}

		iterator(const iterator& other)
		{
			this->current = other.current;
		}

		iterator& operator=(const iterator& other)
		{
			this->current = other.current;
			return *this;
		}

		iterator& operator++()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator temp = *this;
			this->current = this->current->next;
			return temp;
		}

		iterator& operator--()
		{
			this->current = this->current->prev;
			return *this;
		}

		iterator operator--(int)
		{
			iterator temp = *this;
			this->current = this->current->prev;
			return temp;
		}

		bool operator==(const iterator& other)
		{
			return this->current == other.current;
		}

		bool operator!=(const iterator& other)
		{
			if(this->current == nullptr)
				return false;
			return this->current != other.current;
		}

		T& operator*()
		{
			return this->current->data;
		}

		const T& operator*() const
		{
			return this->current->data;
		}

		T* operator->()
		{
			return &this->current->data;
		}
	};

	class reverse_iterator {
	public:
		Node<T>* current;

		reverse_iterator(Node<T>* node)
		{
			this->current = node;
		}

	public:
		reverse_iterator()
		{
			this->current = tail;
		}

		reverse_iterator(const reverse_iterator& other)
		{
			this->current = other.current;
		}

		reverse_iterator& operator=(const reverse_iterator& other)
		{
			this->current = other.current;
			return *this;
		}

		reverse_iterator& operator++()
		{
			this->current = this->current->prev;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			this->current = this->current->prev;
			return temp;
		}

		reverse_iterator& operator--()
		{
			this->current = this->current->next;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			this->current = this->current->next;
			return temp;
		}

		bool operator==(const reverse_iterator& other)
		{
			return this->current == other.current;
		}

		bool operator!=(const reverse_iterator& other)
		{
			return this->current != other.current;
		}

		T& operator*()
		{
			return this->current->data;
		}

		const T& operator*() const
		{
			return this->current->data;
		}

		T* operator->()
		{
			return &this->current->data;
		}
	};

	iterator begin()
	{
		return iterator(head);
	}

	iterator end()
	{
		return NULL;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(tail);
	}

	reverse_iterator rend()
	{
		return NULL;
	}

private:
	Node<T>* head;
	Node<T>* tail;
	int length;
};

template <typename T>
inline jlinkedlist<T>::jlinkedlist()
{
	length = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
inline jlinkedlist<T>::jlinkedlist(jlinkedlist<T>& other)
{
	this->clear();
	Node<T>* current = other.head;
	while (current != nullptr)
	{
		this->push_back(current->data);
		current = current->next;
	}
}

template <typename T>
inline jlinkedlist<T>::~jlinkedlist()
{
	this->clear();
}

template <typename T>
inline void jlinkedlist<T>::push_back(T value)
{
	Node<T>* node = new Node<T>(value);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	length++;
}

template <typename T>
inline void jlinkedlist<T>::erase(T& item)
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current->data == item)
		{
			if (current->prev != nullptr)
			{
				current->prev->next = current->next;
			}
			else
			{
				head = current->next;
			}
			if (current->next != nullptr)
			{
				current->next->prev = current->prev;
			}
			else
			{
				tail = current->prev;
			}
			delete current;
			length--;
			return;
		}
		current = current->next;
	}
}

template <typename T>
inline void jlinkedlist<T>::erase(T* it)
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current == it)
		{
			if (current->prev != nullptr)
			{
				current->prev->next = current->next;
			}
			else
			{
				head = current->next;
			}
			if (current->next != nullptr)
			{
				current->next->prev = current->prev;
			}
			else
			{
				tail = current->prev;
			}
			delete current;
			length--;
			return;
		}
		current = current->next;
	}
}

template <typename T>
inline void jlinkedlist<T>::clear()
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template <typename T>
inline int jlinkedlist<T>::size()
{
	return length;
}

template <typename T>
inline bool jlinkedlist<T>::empty()
{
	return length == 0;
}
