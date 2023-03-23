#include "JerzyString.h"

#pragma once
class Attribute
{
public:
	Attribute(void);
	Attribute(JerzyString name, JerzyString value);
	Attribute(JerzyString attribute_string);
	~Attribute(void);
	JerzyString name;
	JerzyString value;
};

