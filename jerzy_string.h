#pragma once
class jerzy_string
{
public:
	jerzy_string();
	jerzy_string(const char* str);
	jerzy_string(const jerzy_string& str);
	~jerzy_string();
	jerzy_string& operator=(const jerzy_string& str);
	jerzy_string& operator=(const char* str);
	jerzy_string& operator+=(const jerzy_string& str);
	jerzy_string& operator+=(const char* str);
	char& operator[](int index);
	const char& operator[](int index) const;
	bool operator==(const jerzy_string& str) const;
	bool operator==(const char* str) const;
	int getLength() const;
	const char* c_str() const;
private:
	char* str;
	int length;
};

