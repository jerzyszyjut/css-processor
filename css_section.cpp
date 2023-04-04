#include <iostream>
#include "css_section.h"
#include "jstring.h"

css_section::css_section()
{
	this->selectors = jlinkedlist<jstring>();
	this->attributes = jlinkedlist<attribute>();
}

css_section::css_section(css_section* other)
{
	this->selectors = other->selectors;
	this->attributes = other->attributes;
}

css_section::~css_section()
{
	selectors.clear();
	attributes.clear();
}

bool css_section::isEmpty()
{
	if(this->attributes.size() == 0)
		return true;
	return false;
}

bool css_section::deleteAtribute(jstring* name)
{
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if ((&it)->name == *name)
		{
			this->attributes.erase((&it));
			return true;
		}
	}
	return false;
}

jstring* css_section::getAttribute(jstring* name)
{
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if ((&it)->name == *name)
		{
			return &(&it)->value;
		}
	}
	return NULL;
}

jstring* css_section::getAttribute(int index)
{
	if(index < 0 || index >= this->attributes.size())
		return NULL;
	int i = 0;
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		attribute* attr = &it;
		if (i == index)
		{
			return &attr->value;
		}
		i++;
	}
	return NULL;
}

int css_section::getAttributeCount()
{
	return this->attributes.size();
}

int css_section::getSelectorCount()
{
	return this->selectors.size();
}

int css_section::getAttributeOccurances(jstring* selector)
{
	int count = 0;
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		if ((&it)->name == *selector)
		{
			count++;
		}
	}
	return count;
}

int css_section::getSelectorOccurances(jstring* selector)
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

jstring* css_section::getSelector(int index)
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

bool css_section::selectorExists(jstring* selector)
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

void css_section::addAttribute(jstring name, jstring value)
{
	jstring* existing_attribute = this->getAttribute(&name);
	if (existing_attribute != NULL)
	{
		*existing_attribute = value;
		return;
	}
	attribute* attr = new attribute;
	attr->name = name;
	attr->value = value;
	this->attributes.push_back(attr);
}

void css_section::addSelector(jstring selector)
{
	if(this->selectorExists(&selector))
		return;
	this->selectors.push_back(new jstring(selector));
}

void css_section::print()
{
	for (jlinkedlist<jstring>::iterator it = this->selectors.begin(); it != this->selectors.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "{" << std::endl;
	for (jlinkedlist<attribute>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++)
	{
		std::cout << "\t" << (&it)->name << ":" << (&it)->value << ";" << std::endl;
	}
	std::cout << "}" << std::endl;
}
