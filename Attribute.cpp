
#include "Attribute.h"

Attribute::Attribute(void): name(""), value("")
{
}

Attribute::Attribute(JerzyString name, JerzyString value): name(name), value(value)
{
}

Attribute::Attribute(JerzyString attribute_string)
{
	int colon_position = attribute_string.find(':');
	int semicolon_position = attribute_string.find(';');
	name = attribute_string.substring(0, colon_position - 1);
	name.trim();
	value = attribute_string.substring(colon_position + 1, semicolon_position - 1);
	value.trim();
}

Attribute::~Attribute(void)
{
}
