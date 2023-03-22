#pragma once

template <typename T>
struct Node
{
	T value;
	Node* next;
	Node* prev;
};

template <typename T>
class JerzyList
{
public:
	JerzyList();
	JerzyList(const JerzyList<T>& list);
	~JerzyList();
	JerzyList<T>& operator=(const JerzyList<T>& list);
	void push_back(const T& value);
	void insert(int index, const T& value);
	void remove(int index);
	void clear();
	T& find(const T& value);
	int getLength() const;
	T& operator[](int index);
	const T& operator[](int index) const;
private:
	Node<T>* head;
	Node<T>* tail;
	int length;
};
