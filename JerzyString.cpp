#define _CRT_SECURE_NO_WARNINGS
#include "JerzyString.h"
#include <string>
#include <stdexcept>

JerzyString::JerzyString() : str(nullptr), length(0)
{
}

JerzyString::JerzyString(const char* str)
{
	this->length = strlen(str);
	this->str = new char[length + 1];
	strcpy(this->str, str);
}

JerzyString::JerzyString(const JerzyString& str)
{
	this->length = str.length;
	this->str = new char[length + 1];
	strcpy(this->str, str.str);
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
	this->str = new char[length + 1];
	strcpy(this->str, str.str);

	return *this;
}

JerzyString& JerzyString::operator=(const char* str)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->length = strlen(str);
	this->str = new char[length + 1];
	strcpy(this->str, str);

	return *this;
}

JerzyString& JerzyString::operator+=(const JerzyString& str)
{
	if (this->str == nullptr)
	{
		this->length = str.length;
		this->str = new char[length + 1];
		strcpy(this->str, str.str);
	}
	else
	{
		char* temp = new char[length + 1];
		strcpy(temp, this->str);
		delete[] this->str;
		this->length += str.length;
		this->str = new char[length + 1];
		strcpy(this->str, temp);
		strcat(this->str, str.str);
		delete[] temp;
	}
	return *this;
}

JerzyString& JerzyString::operator+=(const char* str)
{
	if (this->str == nullptr)
	{
		this->length = strlen(str);
		this->str = new char[length + 1];
		strcpy(this->str, str);
	}
	else
	{
		char* temp = new char[length + 1];
		strcpy(temp, this->str);
		delete[] this->str;
		this->length += strlen(str);
		this->str = new char[length + 1];
		strcpy(this->str, temp);
		strcat(this->str, str);
		delete[] temp;
	}
	return *this;
}

char& JerzyString::operator[](int index)
{
	if (index < 0 || index >= length)
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

int JerzyString::getLength() const
{
	return length;
}

const char* JerzyString::c_str() const
{
	return str;
}
