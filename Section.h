#pragma once
#include "jlinkedlist.h"
#include "jstring.h"

class attribute {
public:
	jstring name;
	jstring value;

	attribute();
	attribute(jstring name, jstring value);
	~attribute();

	bool operator==(const char* str);
	bool operator==(attribute& attr);
};

class Section
{
private:
	jlinkedlist<jstring> selectors;
	jlinkedlist<attribute> attributes;

public:
	Section();
	Section(Section& other);
	~Section();

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

	bool operator==(Section& other);

	Section& operator=(Section& other);

	void print();
};

