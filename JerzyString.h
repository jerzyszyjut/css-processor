#pragma once
#define BASE_STRING_BLOCK_SIZE 64

int get_initial_size(int length);

class JerzyString
{
public:
	JerzyString();
	JerzyString(const char *str);
	JerzyString(const JerzyString &str);
	~JerzyString();
	JerzyString &operator=(const JerzyString &str);
	JerzyString &operator=(const char *str);
	JerzyString &operator+=(const JerzyString &str);
	JerzyString &operator+=(const char *str);
	JerzyString &operator+=(char c);
	char &operator[](int index);
	const char &operator[](int index) const;
	bool operator==(const JerzyString &str) const;
	bool operator==(const char *str) const;
	int find(char c) const;
	int find(char c, int start) const;
	int toInt() const;
	void clear();
	int getLength() const;
	int getSize() const;
	const char *c_str() const;

private:
	char *str;
	int length, size;
};
