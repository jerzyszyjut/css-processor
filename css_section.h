#pragma once
#include "jlinkedlist.h"
#include "jstring.h"


struct attribute
{
	jstring name;
	jstring value;
};

class css_section
{
private:
	jlinkedlist<jstring> selectors;
	jlinkedlist<attribute> attributes;

public:
	css_section();
	~css_section();

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

