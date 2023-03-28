
#include "Attribute.h"
#include <string.h>

Attribute::Attribute(void) : name(""), value("")
{
}

Attribute::Attribute(JerzyString name, JerzyString value) : name(name), value(value)
{
}

Attribute::Attribute(JerzyString attribute_string)
{
	int colon_position = attribute_string.find(':');
	int semicolon_position = attribute_string.find(';');
	char *temp = new char[colon_position + 1];
	strncpy(temp, attribute_string.c_str(), colon_position);
	temp[colon_position] = '\0';
	name = temp;
	delete[] temp;

	char *temp2 = new char[semicolon_position - colon_position];
	strncpy(temp2, attribute_string.c_str() + colon_position + 1, semicolon_position - colon_position - 1);
	temp2[semicolon_position - colon_position - 1] = '\0';
	value = temp2;
	delete[] temp2;
}

Attribute::~Attribute(void)
{
}
