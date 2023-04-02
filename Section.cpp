#include <iostream>
#include "Section.h"
#include "jstring.h"

Section::Section()
{
	this->selectors = std::list<jstring>();
	this->attributes = std::list<attribute>();
}

Section::~Section()
{
	selectors.clear();
	attributes.clear();
}

bool Section::isEmpty()
{
	if(this->attributes.size() == 0)
		return true;
	return false;
}

bool Section::deleteAtribute(jstring* name)
{
	for (std::list<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if (it->name == *name)
		{
			this->attributes.erase(it);
			return true;
		}
	}
	return false;
}

jstring* Section::getAttribute(jstring* name)
{
	for (std::list<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if (it->name == *name)
		{
			return &it->value;
		}
	}
	return NULL;
}

jstring* Section::getAttribute(int index)
{
	if(index < 0 || index >= this->attributes.size())
		return NULL;
	int i = 0;
	for (std::list<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if (i == index)
		{
			return &it->value;
		}
		i++;
	}
	return NULL;
}

int Section::getAttributeCount()
{
	return this->attributes.size();
}

int Section::getSelectorCount()
{
	return this->selectors.size();
}

int Section::getAttributeOccurances(jstring* selector)
{
	int count = 0;
	for (std::list<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if (it->name == *selector)
		{
			count++;
		}
	}
	return count;
}

int Section::getSelectorOccurances(jstring* selector)
{
	int count = 0;
	for (std::list<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		if (*it == *selector)
		{
			count++;
		}
	}
	return count;
}

jstring* Section::getSelector(int index)
{
	if(index < 0 || index >= this->selectors.size())
		return NULL;
	int i = 0;
	for (std::list<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		if (i == index)
		{
			return &(*it);
		}
		i++;
	}
	return NULL;
}

bool Section::selectorExists(jstring* selector)
{
	for (std::list<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		if (*it == *selector)
		{
			return true;
		}
	}
	return false;
}

void Section::addAttribute(jstring name, jstring value)
{
	jstring* existing_attribute = this->getAttribute(&name);
	if (existing_attribute != NULL)
	{
		*existing_attribute = value;
		return;
	}
	attribute attr;
	attr.name = name;
	attr.value = value;
	this->attributes.push_back(attr);
}

void Section::addSelector(jstring selector)
{
	if(this->selectorExists(&selector))
		return;
	this->selectors.push_back(selector);
}

void Section::print()
{
	for (std::list<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "{" << std::endl;
	for (std::list<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		std::cout << "\t" << it->name << ":" << it->value << ";" << std::endl;
	}
	std::cout << "}" << std::endl;
}
