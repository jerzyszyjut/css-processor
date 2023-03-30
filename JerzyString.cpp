#define _CRT_SECURE_NO_WARNINGS
#include "JerzyString.h"
#include <string.h>
#include <stdexcept>

JerzyString::JerzyString() : str(nullptr), length(0), size(0)
{
}

JerzyString::JerzyString(const char* str)
{
	this->length = strlen(str);
	this->size = get_initial_size(length) + 1;
	this->str = new char[size];
	strcpy(this->str, str);
}

JerzyString::JerzyString(const JerzyString& str)
{
	this->length = str.length;
	this->size = str.size;
	this->str = new char[size];
	strcpy(this->str, str.c_str());
}

JerzyString::~JerzyString()
{
	if (str != nullptr)
		delete[] str;
}

JerzyString& JerzyString::operator=(const JerzyString& str)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->length = str.length;
	this->size = str.size;
	this->str = new char[size];
	strcpy(this->str, str.str);
	return *this;
}

JerzyString& JerzyString::operator=(const char* str)
{
	if (str == nullptr) {
		this->length = 0;
		this->size = 1;
		delete[] this->str;
		this->str = new char[1];
		this->str[0] = '\0';
		return *this;
	}

	if (this->str != nullptr)
		delete[] this->str;

	this->length = strlen(str);
	this->size = get_initial_size(length) + 1;

	char* temp = new char[size];
	strncpy(temp, str, size - 1);
	temp[size - 1] = '\0';

	this->str = temp;
	return *this;
}

JerzyString& JerzyString::operator+=(const JerzyString& str)
{
	if (this->str == nullptr)
	{
		this->length = str.length;
		this->size = get_initial_size(length) + 1;
		this->str = new char[size];
		strcpy(this->str, str.str);
	}
	else
	{
		this->length += str.length;
		if (this->length < this->size) {
			strcat(this->str, str.str);
		}
		else
		{
			char* temp = new char[size];
			this->size = get_initial_size(length) + 1;
			strcpy(temp, this->str);
			delete[] this->str;
			this->str = new char[size];
			strcpy(this->str, temp);
			strcat(this->str, str.str);
			delete[] temp;
		}
	}
	this->str[length] = '\0';
	return *this;
}

JerzyString& JerzyString::operator+=(const char* str)
{
	if (this->str == nullptr)
	{
		this->length = strlen(str);
		this->size = get_initial_size(length) + 1;
		this->str = new char[size];
		strcpy(this->str, str);
	}
	else
	{
		this->length += strlen(str);
		if (this->length < this->size) {
			strcat(this->str, str);
		}
		else
		{
			char* temp = new char[size];
			this->size = get_initial_size(length) + 1;
			strcpy(temp, this->str);
			delete[] this->str;
			this->str = new char[size];
			strcpy(this->str, temp);
			strcat(this->str, str);
			delete[] temp;
		}
	}
	this->str[length] = '\0';
	return *this;
}

JerzyString& JerzyString::operator+=(char c)
{
	if (this->str == nullptr)
	{
		this->length = 1;
		this->size = get_initial_size(length) + 1;
		this->str = new char[size];
		this->str[0] = c;
	}
	else {
		this->length += 1;
		if (this->length < this->size) {
			this->str[length - 1] = c;
		}
		else {
			char* temp = new char[size];
			this->size = get_initial_size(length) + 1;
			strcpy(temp, this->str);
			delete[] this->str;
			this->str = new char[size];
			strcpy(this->str, temp);
			this->str[length - 1] = c;
			delete[] temp;
		}
	}
	this->str[length] = '\0';
	return *this;
}

char& JerzyString::operator[](int index)
{
	if (index < 0 || index > length)
		throw std::out_of_range("Index out of range");
	return str[index];
}

const char& JerzyString::operator[](int index) const
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index out of range");
	return str[index];
}

bool JerzyString::operator==(const JerzyString& str) const
{
	if (this->length != str.length)
		return false;
	for (int i = 0; i < length; i++)
	{
		if (this->str[i] != str.str[i])
			return false;
	}
	return true;
}

bool JerzyString::operator==(const char* str) const
{
	if (this->length != strlen(str))
		return false;
	for (int i = 0; i < length; i++)
	{

		if (this->str[i] != str[i])
			return false;
	}
	return true;
}

int JerzyString::find(char c) const
{
	for (int i = 0; i < length; i++)
	{
		if (this->str[i] == c)
			return i;
	}
	return -1;
}

int JerzyString::find(char c, int start) const
{
	if (start < 0 || start >= length)
		throw std::out_of_range("Index out of range");
	for (int i = start; i < length; i++)
	{
		if (this->str[i] == c)
			return i;
	}
	return -1;
}

int JerzyString::toInt() const
{
	int result = 0;
	for (int i = 0; i < length; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			throw std::invalid_argument("String is not a number");
	}
	return result;
}

void JerzyString::clear()
{
	if (str != nullptr)
	{
		delete[] str;
		str = nullptr;
	}
	length = 0;
}

int JerzyString::getLength() const
{
	return length;
}

int JerzyString::getSize() const
{
	return size;
}

const char* JerzyString::c_str() const
{
	return str;
}

int get_initial_size(int length)
{
	int initial_size = BASE_STRING_BLOCK_SIZE;
	while (initial_size < length)
		initial_size += initial_size;
	return initial_size;
}
