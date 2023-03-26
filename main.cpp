#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "JerzyString.h"
#include "JerzyList.h"
#include "Section.h"

enum Mode {
	PARSE,
	QUERY
};

void parse_sections(JerzyString& input, JerzyList<Section>& sections, int& sections_count) {
	while (true) {
		int next_semicolon = input.find(';'), next_open_brackets = input.find('{');
		if(next_semicolon == -1 || next_open_brackets == -1)
			break;

		JerzyString section_str;

		if (next_semicolon < next_open_brackets) {
			section_str = input.substring(0, next_semicolon);
			input = input.substring(next_semicolon + 1);
		}
		else {
			int next_closing_brackets = input.find('}');
			section_str = input.substring(0, next_closing_brackets);
			input = input.substring(next_closing_brackets + 1);
		}

		Section* section = new Section();
		section->parseSection(section_str);
		sections.push_back(*section);
		sections_count++;
	}
}

int main() {
	int sections_count = 0, special_character_count = 0;
	Mode current_mode = PARSE;
	char c;
	JerzyString input;
	JerzyList<Section> sections;

	while ((c = getchar()) != EOF) {
		input += c;

		if (current_mode == PARSE) {
			if (c == '?') special_character_count++;
			else special_character_count = 0;
		}
		else if (current_mode == QUERY) {
			if (c == '*') special_character_count++;
			else special_character_count = 0;
		}

		if (special_character_count == 4) {
			if (current_mode == PARSE) {
				input = input.substring(0, input.getLength() - 4);
				parse_sections(input, sections, sections_count);
				current_mode = QUERY;
			}
			else {
				current_mode = PARSE;
			}
		}

		if (current_mode == QUERY) {
			c = getchar();
			if (c == '?') {
				printf("%d\n", sections_count);
			}
		}
	}

	parse_sections(input, sections, sections_count);

	return 0;
}
