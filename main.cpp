#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string.h>
#include "JerzyString.h"
#include "JerzyList.h"
#include "Section.h"

#define INPUT_BUFFER_SIZE 64
#define ESCPAE_CHARACTERS_COUNT 4

void parse_sections(JerzyString &input, JerzyList<Section, BLOCK_SIZE> &sections, int &sections_count)
{
	int cursor = 0;
	while (true)
	{
		int next_semicolon = input.find(';', cursor), next_open_brackets = input.find('{', cursor), section_end;
		if (next_semicolon == -1 || next_open_brackets == -1)
			break;

		if (next_semicolon < next_open_brackets)
		{
			section_end = next_semicolon;
		}
		else
		{
			int next_closing_brackets = input.find('}', cursor);
			if (next_closing_brackets == -1)
				break;

			section_end = next_closing_brackets + 1;
		}
		Section new_section = Section(input, cursor, section_end);
		sections.push_back(new_section);
		cursor = section_end + 1;
		sections_count++;
	}
	input.clear();
}

int main()
{
	int sections_count = 0, special_character_count = 0;
	char c;
	JerzyString input;
	JerzyList<Section, BLOCK_SIZE> sections;

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

