#define _CRT_SECURE_NO_WARNINGS
#include "jstring.h"
#include <cstring>

jstring::jstring()
{
	this->len = 0;
	this->size = get_block_size(this->len);
	this->str = new char[this->size];
	this->str[this->len] = '\0';
}

jstring::jstring(const char* str)
{
	this->len = strlen(str);
	this->size = get_block_size(this->len);
	this->str = new char[this->size];
	strncpy(this->str, str, this->len);
	this->str[this->len] = '\0';
}

jstring::jstring(const jstring& str)
{
	this->len = str.len;
	this->size = str.size;
	this->str = new char[this->size];
	strncpy(this->str, str.str, this->len);
	this->str[this->len] = '\0';
}

jstring::jstring(jstring&& other)
{
	if (this != &other)
	{
		this->len = other.len;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
	}
}

jstring::~jstring()
{
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}
}

jstring& jstring::operator=(char str)
{
	this->len = 1;
	this->size = get_block_size(this->len);
	if (this->str != nullptr)
		delete[] this->str;
	this->str = new char[this->size];
	this->str[0] = str;
	this->str[this->len] = '\0';

	return *this;
}

jstring& jstring::operator=(const char* str)
{
	this->len = strlen(str);
	this->size = get_block_size(this->len);
	if (this->str != nullptr)
		delete[] this->str;
	this->str = new char[this->size];
	strncpy(this->str, str, this->len);
	this->str[this->len] = '\0';

	return *this;
}

jstring& jstring::operator=(jstring& other)
{
	this->len = other.len;
	this->size = other.size;
	if (this->str != nullptr)
		delete[] this->str;
	this->str = new char[this->size];
	strncpy(this->str, other.str, this->len);
	this->str[this->len] = '\0';

	return *this;
}

jstring& jstring::operator=(jstring&& other)
{
	this->len = other.len;
	this->size = other.size;
	if (this->str != nullptr)
		delete[] this->str;
	this->str = other.str;
	other.str = nullptr;

	return *this;
}

jstring& jstring::operator+=(char str)
{
	this->len += 1;
	if (this->size != get_block_size(this->len))
	{
		this->size = get_block_size(this->len);
		char* new_str = new char[this->size];
		strncpy(new_str, this->str, this->len - 1);
		delete[] this->str;
		this->str = new_str;
		this->str[this->len - 1] = str;
		this->str[this->len] = '\0';
	}
	else
	{
		this->str[this->len - 1] = str;
		this->str[this->len] = '\0';
	}

	return *this;
}

jstring& jstring::operator+=(const char* str)
{
	this->len += strlen(str);
	if (this->size != get_block_size(this->len))
	{
		this->size = get_block_size(this->len);
		char* new_str = new char[this->size];
		strncpy(new_str, this->str, this->len - strlen(str));
		delete[] this->str;
		this->str = new_str;
		strncat(this->str, str, strlen(str));
		this->str[this->len] = '\0';
	}
	else
	{
		strncat(this->str, str, strlen(str));
		this->str[this->len] = '\0';
	}

	return *this;
}

jstring& jstring::operator+=(jstring& other)
{
	this->len += other.len;
	if (this->size != get_block_size(this->len))
	{
		this->size = get_block_size(this->len);
		char* new_str = new char[this->size];
		strncpy(new_str, this->str, this->len - other.len);
		delete[] this->str;
		this->str = new_str;
		strncat(this->str, other.str, other.len);
		this->str[this->len] = '\0';
	}
	else
	{
		strncat(this->str, other.str, other.len);
		this->str[this->len] = '\0';
	}

	return *this;
}

jstring jstring::operator+(char str)
{
	jstring new_str(*this);
	new_str += str;
	return new_str;
}

jstring jstring::operator+(const char* str)
{
	jstring new_str(*this);
	new_str += str;
	return new_str;
}

jstring jstring::operator+(jstring& other)
{
	jstring new_str(*this);
	new_str += other;
	return new_str;
}

bool jstring::operator==(const char* str)
{
	if (this->len != strlen(str))
		return false;
	for (size_t i = 0; i < this->len; i++)
	{
		if (this->str[i] != str[i])
			return false;
	}
	return true;
}

bool jstring::operator==(jstring& other)
{
	if (this->len != other.len)
		return false;
	for (size_t i = 0; i < this->len; i++)
	{
		if (this->str[i] != other.str[i])
			return false;
	}
	return true;
}

bool jstring::operator!=(const char* str)
{
	return !(this->operator==(str));
}

bool jstring::operator!=(jstring& other)
{
	return !(this->operator==(other));
}

char& jstring::operator[](size_t index)
{
	if (index > this->len)
		throw std::out_of_range("Index out of range");
	return this->str[index];
}

const char& jstring::operator[](size_t index) const
{
	if (index > this->len)
		throw std::out_of_range("Index out of range");
	return this->str[index];
}

jstring& jstring::substring(size_t start, size_t count)
{
	jstring* new_string = new jstring();
	new_string->len = count;
	new_string->size = get_block_size(new_string->len);
	new_string->str = new char[new_string->size];
	strncpy(new_string->str, &(this->str[start]), new_string->len + 1);
	new_string->str[new_string->len] = '\0';

	return *new_string;
}

int jstring::find(char c)
{
	for (size_t i = 0; i < this->len; i++)
	{
		if (this->str[i] == c)
			return i;
	}
	return -1;
}

size_t jstring::get_length() const
{
	return this->len;
}

size_t jstring::get_size() const
{
	return this->size;
}

char* jstring::c_str() const
{
	return this->str;
}

typedef jiterator<char> iterator;
typedef jiterator<const char> const_iterator;

typedef reverse_jiterator<char> reverse_iterator;
typedef reverse_jiterator<const char> const_reverse_iterator;

iterator jstring::begin()
{
	return iterator(&(str[0]));
}

iterator jstring::end()
{
	return iterator(&(str[len]));
}

reverse_iterator jstring::rbegin()
{
	return reverse_iterator(&(str[len - 1]));
}

reverse_iterator jstring::rend()
{
	return reverse_iterator(&(str[-1]));
}

size_t get_block_size(size_t len)
{
	return ((len / STRING_BLOCK_SIZE + 1) * STRING_BLOCK_SIZE) + 1;
}

std::ostream& operator<<(std::ostream& os, const jstring& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, jstring& str)
{
	jstring new_str;
	char c;
	while (((c = is.get()) != EOF) && (c != '\n') && !(is.eof()))
	{
		new_str += c;
	}
	str = new_str;
	return is;
}
