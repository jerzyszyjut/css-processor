#include "JerzyString.h"

#pragma once
class Attribute
{
public:
	Attribute(void);
	Attribute(Attribute& attr);
	Attribute(JerzyString name, JerzyString value);
	Attribute(JerzyString attribute_string, int start, int stop);
	~Attribute(void);
	JerzyString name;
	JerzyString value;
};

