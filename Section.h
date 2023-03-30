#pragma once
#include "Attribute.h"
#include "JerzyString.h"
#include "JerzyList.h"
#include "JerzyLinkedList.h"

class Section
{
private:
public:
	JerzyLinkedList<JerzyString> selectors;
	JerzyLinkedList<Attribute> attributes;
	void parseSelectors(JerzyString &section_string, int start, int end);
	void parseAttributes(JerzyString &section_string, int start, int end);
	Section();
	Section(JerzyString &section, int start, int end);
	Section(const Section &section);
	Section(const int something);
	Section &operator=(const Section &section);
	bool operator==(const int other) const;
	void clear();
	~Section();
};
