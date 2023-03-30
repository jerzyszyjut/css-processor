#include "Section.h"

void Section::parseSelectors(JerzyString &section_string, int start, int end)
{
	JerzyString temp;
	for (int i = start; i < end; i++)
	{
		if (section_string[i] == ',')
		{
			selectors.push_back(temp);
			temp.clear();
		}
		else
		{
			temp += section_string[i];
		}
	}
	selectors.push_back(temp);
	temp.clear();
}

void Section::parseAttributes(JerzyString &section_string, int start, int end)
{
	int cursor = start, next_semicolon_position = section_string.find(';', start);
	while (next_semicolon_position != -1 && next_semicolon_position < end) {
		attributes.push_back(Attribute(section_string, cursor, next_semicolon_position));
		cursor = next_semicolon_position + 1;
		next_semicolon_position = section_string.find(';', cursor);
	}
	if (section_string.find(':', cursor) > 0)
	{
		attributes.push_back(Attribute(section_string, cursor, section_string.getLength() + 1));
	}
}

Section::Section()
{
}

Section::Section(JerzyString &section, int start, int end)
{
	int open_bracket_position = section.find('{', start);
	if (open_bracket_position == -1)
	{
		selectors.push_back("global");
		attributes.push_back(Attribute(section, start, end));
	}
	else
	{
		int close_bracket_position = section.find('}', start);

		this->parseSelectors(section, start, open_bracket_position);
		this->parseAttributes(section, open_bracket_position + 1, close_bracket_position - 1);
	}
}

Section::Section(const Section &section)
{
	this->selectors = section.selectors;
	this->attributes = section.attributes;
}

Section::Section(const int something)
{
	if (something == NULL) {

	}
}

Section &Section::operator=(const Section &section)
{
	this->selectors = section.selectors;
	this->attributes = section.attributes;
	return *this;
}

bool Section::operator==(const int other) const
{
	if (this->selectors.getLength() == 0 && this->attributes.getLength() == 0 && other == NULL) {
		return true;
	}
	return false;
}

void Section::clear()
{
	this->attributes.clear();
	this->selectors.clear();
}

Section::~Section()
{
	this->clear();
}
