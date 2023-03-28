#pragma once
#include "Attribute.h"
#include "JerzyString.h"
#include "JerzyList.h"

class Section
{
private:
public:
	JerzyList<JerzyString> selectors;
	JerzyList<Attribute> attributes;
	void parseSelectors(JerzyString &section_string, int start, int end);
	void parseAttributes(JerzyString &section_string, int start, int end);
	Section();
	Section(JerzyString &section);
	Section(const Section &section);
	Section(const Section &&section);
	Section &operator=(const Section &section);
	~Section();
};
