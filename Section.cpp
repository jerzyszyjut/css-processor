#include <iostream>
#include "Section.h"
#include "jstring.h"

Section::Section()
{
	this->selectors = jlinkedlist<jstring>();
	this->attributes = jlinkedlist<attribute>();
}

Section::Section(Section& other)
{
	this->selectors = *(new jlinkedlist<jstring>(other.selectors));
	this->attributes = *(new jlinkedlist<attribute>(other.attributes));
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
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if (it->name == *name)
		{
			this->attributes.erase(*it);
			return true;
		}
	}
	return false;
}

jstring* Section::getAttribute(jstring* name)
{
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
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
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
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
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
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
	for (jlinkedlist<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
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
	for (jlinkedlist<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
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
	for (jlinkedlist<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
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
	attribute attr(name, value);
	this->attributes.push_back(attr);
}

void Section::addSelector(jstring selector)
{
	if(this->selectorExists(&selector))
		return;
	this->selectors.push_back(selector);
}

bool Section::operator==(Section& other)
{
	if (&(this->selectors) == &(other.selectors) && &(this->attributes) != &(other.attributes))
			return true;
	return false;
}

Section& Section::operator=(Section& other)
{
	this->selectors = *(new jlinkedlist<jstring>(other.selectors));
	this->attributes = *(new jlinkedlist<attribute>(other.attributes));
	return *this;
}

void Section::print()
{
	for (jlinkedlist<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "{" << std::endl;
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		std::cout << "\t" << it->name << ":" << it->value << ";" << std::endl;
	}
	std::cout << "}" << std::endl;
}

attribute::attribute()
{
	name = "";
	value = "";
}

attribute::attribute(jstring name, jstring value)
{
	this->name = name;
	this->value = value;
}

attribute::~attribute()
{
}

bool attribute::operator==(const char* str)
{
	if (this->name == str)
		return true;

	return false;
}

bool attribute::operator==(attribute& attr)
{
	if (this->name == attr.name)
		return true;

	return false;
}
