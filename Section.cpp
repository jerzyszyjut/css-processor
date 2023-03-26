#include "Section.h"

void Section::parseSection(JerzyString& section)
{
	int open_bracket_position = section.find('{');
	if (open_bracket_position == -1) {
		selectors.push_back("global");
		attributes.push_back(Attribute(section));
	}
	else {
		JerzyString selectors_string = section.substring(0, open_bracket_position - 1);
		this->parseSelectors(selectors_string);
		int close_bracket_position = section.find('}');
		JerzyString attributes_string = section.substring(open_bracket_position + 1, close_bracket_position - 1);
		this->parseAttributes(attributes_string);
	}
}

void Section::parseSelectors(JerzyString& selectors_string)
{
	JerzyString temp;
	for (int i = 0; selectors_string[i] != '\0'; i++) {
		if (selectors_string[i] == ',') {
			temp.trim();
			selectors.push_back(temp);
			temp.clear();
		}
		else {
			temp += selectors_string[i];
		}
	}
	temp.trim();
	selectors.push_back(temp);
	temp.clear();
}

void Section::parseAttributes(JerzyString& attributes_string)
{
	JerzyString temp;
	for (int i = 0; attributes_string[i] != '\0'; i++) {
		temp += attributes_string[i];
		if (attributes_string[i] == ';') {
			attributes.push_back(Attribute(temp));
			temp.clear();
		}
	}
	temp.trim();
	if (temp.getLength() > 0) {
		temp += ';';
		attributes.push_back(Attribute(temp));
		temp.clear();
	}
	temp.clear();
}



Section::Section() : selectors(), attributes()
{
}

Section::~Section()
{
}
