#pragma once
#include <cstring>
#include <iostream>
#include "jiterators.h"
#define STRING_BLOCK_SIZE 64

size_t get_block_size(size_t len);

class jstring
{
private:
	char* str;
	size_t len, size;
public:
	jstring();
	jstring(const char* str);
	jstring(const jstring& str);
	jstring(jstring&& other);
	jstring(int other);
	~jstring();

	jstring& operator=(char str);
	jstring& operator=(const char* str);
	jstring& operator=(jstring& other);
	jstring& operator=(jstring&& other);
	jstring& operator=(int other);

	jstring& operator+=(char str);
	jstring& operator+=(const char* str);
	jstring& operator+=(jstring& other);

	jstring operator+(char str);
	jstring operator+(const char* str);
	jstring operator+(jstring& other);

	bool operator==(const char* str);
	bool operator==(jstring& other);
	bool operator==(int other);

	bool operator!=(const char* str);
	bool operator!=(jstring& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;


	friend std::ostream& operator<<(std::ostream& os, const jstring& str);
	friend std::istream& operator>>(std::istream& is, jstring& str);

	jstring& substring(size_t start, size_t count);
	int find(char c);

	size_t get_length() const;
	size_t get_size() const;
	char* c_str() const;

	typedef jiterator<char> iterator;
	typedef jiterator<const char> const_iterator;

	typedef reverse_jiterator<char> reverse_iterator;
	typedef reverse_jiterator<const char> const_reverse_iterator;

	iterator begin();
	iterator end();

	reverse_iterator rbegin();
	reverse_iterator rend();

	char* m_ptr;
};

