#define _CRT_SECURE_NO_WARNINGS
#include "Attribute.h"
#include <string.h>

Attribute::Attribute(void) : name(""), value("")
{
}

Attribute::Attribute(Attribute& attr)
{
	name = attr.name;
	value = attr.value;
}

Attribute::Attribute(JerzyString name, JerzyString value) : name(name), value(value)
{
}

Attribute::Attribute(JerzyString attribute_string, int start, int stop)
{
	int colon_position = attribute_string.find(':', start);
	int semicolon_position = stop;
	char *temp = new char[colon_position - start + 2];
	strncpy(temp, attribute_string.c_str() + start, colon_position - start);
	temp[colon_position - start] = '\0';
	name = temp;
	delete[] temp;

	char *temp2 = new char[semicolon_position - colon_position + 1];
	strncpy(temp2, attribute_string.c_str() + colon_position + 1, semicolon_position - colon_position - 1);
	temp2[semicolon_position - colon_position - 1] = '\0';
	value = temp2;
	delete[] temp2;
}

Attribute::~Attribute(void)
{
}
