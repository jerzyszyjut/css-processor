#pragma once
class JerzyString
{
public:
	JerzyString();
	JerzyString(const char* str);
	JerzyString(const JerzyString& str);
	~JerzyString();
	JerzyString& operator=(const JerzyString& str);
	JerzyString& operator=(const char* str);
	JerzyString& operator+=(const JerzyString& str);
	JerzyString& operator+=(const char* str);
	char& operator[](int index);
	const char& operator[](int index) const;
	bool operator==(const JerzyString& str) const;
	bool operator==(const char* str) const;
	int find(char c) const;
	JerzyString substring(int start, int end) const;
	JerzyString substring(int start) const;
	void trim();
	int getLength() const;
	const char* c_str() const;
private:
	char* str;
	int length;
};

