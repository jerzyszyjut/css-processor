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
	JerzyString temp;
	for (int i = start; i < end; i++)
	{
		temp += section_string[i];
		if (section_string[i] == ';')
		{
			attributes.push_back(Attribute(temp));
			temp.clear();
		}
	}
	if (temp.find(':') > 0)
	{
		temp += ';';
		attributes.push_back(Attribute(temp));
	}
	temp.clear();
}

Section::Section()
{
}

Section::Section(JerzyString &section)
{
	int open_bracket_position = section.find('{');
	if (open_bracket_position == -1)
	{
		selectors.push_back("global");
		attributes.push_back(Attribute(section));
	}
	else
	{
		int close_bracket_position = section.find('}');

		this->parseSelectors(section, 0, open_bracket_position);
		this->parseAttributes(section, open_bracket_position + 1, close_bracket_position - 1);
	}
}

Section::Section(const Section &section)
{
	this->selectors = section.selectors;
	this->attributes = section.attributes;
}

Section::Section(const Section &&section)
{
	this->selectors = section.selectors;
	this->attributes = section.attributes;
}

Section &Section::operator=(const Section &section)
{
	this->selectors = section.selectors;
	this->attributes = section.attributes;
	return *this;
}

Section::~Section()
{
}
