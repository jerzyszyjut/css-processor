#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string.h>
#include "JerzyString.h"
#include "JerzyList.h"
#include "Section.h"

#define INPUT_BUFFER_SIZE 64
#define ESCPAE_CHARACTERS_COUNT 4

bool is_a_number(JerzyString &str)
{
	for (int i = 0; i < str.getLength(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

void parse_sections(JerzyString &input, JerzyList<Section> &sections, int &sections_count)
{
	int cursor = 0;
	while (true)
	{
		int next_semicolon = input.find(';'), next_open_brackets = input.find('{');
		if (next_semicolon == -1 || next_open_brackets == -1)
			break;

		JerzyString section_str;

		if (next_semicolon < next_open_brackets)
		{
			char *temp = new char[next_semicolon + 1];
			for (int i = cursor; i < next_semicolon; i++)
				temp[i] = input[i];
			temp[next_semicolon] = '\0';
			section_str = temp;
			delete[] temp;
		}
		else
		{
			int next_closing_brackets = input.find('}');
			if (next_closing_brackets == -1)
				break;

			char *temp = new char[next_closing_brackets + 1];
			for (int i = cursor; i < next_closing_brackets; i++)
				temp[i] = input[i];
			temp[next_closing_brackets] = '\0';
			section_str = temp;
			delete[] temp;
		}

		sections.push_back(Section(section_str));
		sections_count++;
	}
	input.clear();
}

int main()
{
	int sections_count = 0, special_character_count = 0;
	char c;
	JerzyString input;
	JerzyList<Section> sections;

	while ((c = getchar()) != EOF)
	{
		input += c;

		if (c == '?')
			special_character_count++;
		else
			special_character_count = 0;

		if (special_character_count == ESCPAE_CHARACTERS_COUNT)
		{
			parse_sections(input, sections, sections_count);
			return 1;
		}
	}

	return 0;
}
