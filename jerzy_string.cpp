#define _CRT_SECURE_NO_WARNINGS
#include "jerzy_string.h"
#include <string>
#include <stdexcept>

jerzy_string::jerzy_string() : str(nullptr), length(0)
{
}

jerzy_string::jerzy_string(const char* str)
{
	this->length = strlen(str);
	this->str = new char[length + 1];
	strcpy(this->str, str);
}

jerzy_string::jerzy_string(const jerzy_string& str)
{
	this->length = str.length;
	this->str = new char[length + 1];
	strcpy(this->str, str.str);
}

jerzy_string::~jerzy_string()
{
	if (str != nullptr)
		delete[] str;
}

jerzy_string& jerzy_string::operator=(const jerzy_string& str)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->length = str.length;
	this->str = new char[length + 1];
	strcpy(this->str, str.str);

	return *this;
}

jerzy_string& jerzy_string::operator=(const char* str)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->length = strlen(str);
	this->str = new char[length + 1];
	strcpy(this->str, str);

	return *this;
}

jerzy_string& jerzy_string::operator+=(const jerzy_string& str)
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

jerzy_string& jerzy_string::operator+=(const char* str)
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

char& jerzy_string::operator[](int index)
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index out of range");
	return str[index];
}

const char& jerzy_string::operator[](int index) const
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index out of range");
	return str[index];
}

bool jerzy_string::operator==(const jerzy_string& str) const
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

bool jerzy_string::operator==(const char* str) const
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

int jerzy_string::getLength() const
{
	return length;
}

const char* jerzy_string::c_str() const
{
	return str;
}
