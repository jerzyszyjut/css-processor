#pragma once
template <typename T>
class JerzyLinkedList
{
	public:
	JerzyLinkedList();
	~JerzyLinkedList();
	void push_back(const T& value);
	void remove(const T& value);
	void insert(int index, const T& value);
	void clear();
	int find(const T& value);
	int getLength() const;
	T& operator[](int index);
	const T& operator[](int index) const;
	private:
	struct LinkedListNode
	{
		T value;
		LinkedListNode* next;
	};
	LinkedListNode* head;
	int length;
};

template<typename T>
inline JerzyLinkedList<T>::JerzyLinkedList(): head(nullptr), length(0)
{
}

template<typename T>
inline JerzyLinkedList<T>::~JerzyLinkedList()
{
}

template<typename T>
inline void JerzyLinkedList<T>::push_back(const T& value)
{
	if (head == nullptr)
	{
		head = new LinkedListNode;
		head->value = value;
		head->next = nullptr;
	}
	else
	{
		LinkedListNode* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = new LinkedListNode;
		temp->next->value = value;
		temp->next->next = nullptr;
	}
	length++;
}

template<typename T>
inline void JerzyLinkedList<T>::remove(const T& value)
{
	LinkedListNode* temp = head;
	while (temp->next != nullptr)
	{
		if (temp->next->value == value)
		{
			LinkedListNode* temp2 = temp->next;
			temp->next = temp->next->next;
			delete temp2;
			length--;
			return;
		}
		temp = temp->next;
	}
}

template<typename T>
inline void JerzyLinkedList<T>::insert(int index, const T& value)
{
	if (index < 0 || index > length)
	{
		return;
	}
	if (index == 0)
	{
		LinkedListNode* temp = head;
		head = new LinkedListNode;
		head->value = value;
		head->next = temp;
	}
	else
	{
		LinkedListNode* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		LinkedListNode* temp2 = temp->next;
		temp->next = new LinkedListNode;
		temp->next->value = value;
		temp->next->next = temp2;
	}
}

template<typename T>
inline void JerzyLinkedList<T>::clear()
{
	LinkedListNode* temp = head;
	while (temp != nullptr)
	{
		LinkedListNode* temp2 = temp;
		temp = temp->next;
		delete temp2;
	}
}

template<typename T>
inline int JerzyLinkedList<T>::find(const T& value)
{
	LinkedListNode* temp = head;
	for (int i = 0; i < length; i++)
	{
		if (temp->value == value)
		{
			return i;
		}
		temp = temp->next;
	}
	return -1;
}

template<typename T>
inline int JerzyLinkedList<T>::getLength() const
{
	return length;
}

template<typename T>
inline T& JerzyLinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= length)
	{
		return;
	}
	LinkedListNode* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp->value;
}

template<typename T>
inline const T& JerzyLinkedList<T>::operator[](int index) const
{
	if (index < 0 || index >= length)
	{
		return;
	}
	LinkedListNode* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp->value;
}
