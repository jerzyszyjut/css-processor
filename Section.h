#pragma once
#include "jlist.h"
#include "jstring.h"


struct attribute
{
	jstring name;
	jstring value;

	bool operator==(attribute& other)
	{
		if (this->name == other.name)
			return true;
		return false;
	}

	bool operator==(int other)
	{
		if (this->name.get_length() == other)
			return true;
		return false;
	}
};

class Section
{
private:
	jlist<jstring> selectors;
	jlist<attribute> attributes;

public:
	Section();
	Section(Section& other);
	~Section();

	Section& operator=(Section& other);
	bool operator==(Section& other);
	bool operator==(int other);

	bool isEmpty();
	bool deleteAtribute(jstring* name);
	bool selectorExists(jstring* selector);
	int getAttributeCount();
	int getSelectorCount();
	int getAttributeOccurances(jstring* selector);
	int getSelectorOccurances(jstring* selector);
	jstring* getAttribute(jstring* name);
	jstring* getAttribute(int index);
	jstring* getSelector(int index);
	void addAttribute(jstring name, jstring value);
	void addSelector(jstring selector);

	void print();
};

