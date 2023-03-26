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
	void parseSection(JerzyString& section);
	void parseSelectors(JerzyString& selectors_string);
	void parseAttributes(JerzyString& attributes_string);
	Section();
	~Section();
};

