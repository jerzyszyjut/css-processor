#pragma once
#include <list>
#include <string>


struct attribute
{
	std::string name;
	std::string value;
};

class Section
{
private:
	std::list<std::string> selectors;
	std::list<attribute> attributes;

public:
	Section();
	~Section();

	bool isEmpty();
	bool deleteAtribute(std::string* name);
	bool selectorExists(std::string* selector);
	int getAttributeCount();
	int getSelectorCount();
	int getAttributeOccurances(std::string* selector);
	int getSelectorOccurances(std::string* selector);
	std::string* getAttribute(std::string* name);
	std::string* getAttribute(int index);
	std::string* getSelector(int index);
	void addAttribute(std::string name, std::string value);
	void addSelector(std::string selector);

	void print();
};

