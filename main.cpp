#include <iostream>
#include <string>
#include <list>
#include "Section.h"
#define ESCAPE_CSS_PARSING_SPECIAL_CHARACTER '?'
#define ESCAPE_COMMAND_PARSING_SPECIAL_CHARACTER '*'
#define ESCAPE_CHARACTER_COUNT 4

using namespace std;

bool is_a_number(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

bool load_input(list<string>* keywords) {
	bool in_section = false, in_attribute = false;
	int special_character_count = 0;
	string input = "";
	char c;
	while ((c = getchar()) != EOF) {
		if (c < ' ') {
			continue;
		}

		if (c == ESCAPE_CSS_PARSING_SPECIAL_CHARACTER) {
			special_character_count++;
			if (special_character_count == ESCAPE_CHARACTER_COUNT) {
				return true;
			}
		}
		else {
			special_character_count = 0;
		}

		if (c == '{') {
			in_section = true;
			if (input.length() > 0 && input[input.length() - 1] == ' ') {
				input = input.substr(0, input.length() - 1);
			}
			keywords->push_back(input);
			input = c;
			keywords->push_back(input);
			input = "";
		}
		else if (c == '}') {
			in_section = false;
			input = c;
			keywords->push_back(input);
			input = "";
		}
		else if (in_section && c == ':') {
			in_attribute = true;
			keywords->push_back(input);
			input = c;
			keywords->push_back(input);
			input = "";
		}
		else if (in_section && in_attribute && c == ';') {
			in_attribute = false;
			keywords->push_back(input);
			input = "";
		}
		else {
			if (!in_section && !in_attribute) {
				if (c == ',') {
					input += c;
					keywords->push_back(input);
					input = "";
					continue;
				}
			}

			if (in_section && !in_attribute) {
				if (c == ' ') {
					continue;
				}
			}

			input += c;
		}
	}
	return false;
}

void load_sections(list<Section>* sections, list<string>* keywords) {
	Section* section = new Section();
	bool in_section = false;
	string* previous_keyword = NULL;
	for (list<string>::iterator it = keywords->begin(); it != keywords->end(); it++) {
		if (*it == "{") {
			in_section = true;
		}
		else if (*it == "}") {
			in_section = false;
			sections->push_back(*section);
			section = new Section();
		}
		else {
			if (!in_section) {
				string trimmed_selector_value, value = *it;
				bool reached_proper_string = false;
				for (string::iterator it = value.begin(); it != value.end(); it++) {
					if (*it == ',') continue;
					if (*it == ' ') {
						if (reached_proper_string) {
							trimmed_selector_value += *it;
						}
					}
					else {
						reached_proper_string = true;
						trimmed_selector_value += *it;
					}
				}

				if (trimmed_selector_value.length() > 0) {
					section->addSelector(trimmed_selector_value);
				}
			}
			else if (in_section) {
				if (*it == ":") {
					string trimmed_attribute_value, value = *(++it);
					bool reached_proper_string = false;
					for (string::iterator it = value.begin(); it != value.end(); it++) {
						if (*it == ' ') {
							if (reached_proper_string) {
								trimmed_attribute_value += *it;
							}
						}
						else {
							reached_proper_string = true;
							trimmed_attribute_value += *it;
						}
					}
					
					section->addAttribute(*previous_keyword, trimmed_attribute_value);
				}
				previous_keyword = &(*it);
			}
		}
	}
	keywords->clear();
}

bool handle_commands(list<Section>* sections) {
	string command_line;
	while (cin >> command_line) {
		if (command_line[0] == ESCAPE_COMMAND_PARSING_SPECIAL_CHARACTER)
			return true;

		if (command_line[0] == '?') {
			cout << "? == " << sections->size() << endl;
			continue;
		}

		int first_comma_position = command_line.find(',');

		if (command_line[first_comma_position + 2] != ',') continue;

		char command = command_line[first_comma_position + 1];
		string selector = command_line.substr(0, first_comma_position);
		string value = command_line.substr(first_comma_position + 3, command_line.length() - first_comma_position - 3);

		if (command == 'S') {
			if (is_a_number(selector[0])) {
				int index = atoi(selector.c_str()) - 1;

				if (index < 0 || index >= sections->size()) {
					continue;
				}

				list<Section>::iterator it = sections->begin();
				for (int i = 0; i < index; i++) {
					it++;
				}

				if (value[0] == '?') {
					cout << selector << "," << command << "," << value << " == " << it->getSelectorCount() << endl;
				}
				else if (is_a_number(value[0])) {
					int selector_index = atoi(value.c_str()) - 1;
					string* selector_name = it->getSelector(selector_index);
					if (selector_name == NULL) continue;
					cout << selector << "," << command << "," << value << " == " << *selector_name << endl;
				}
			}
			else if (value[0] == '?') {
				int occurance_count = 0;
				for (list<Section>::iterator it = sections->begin(); it != sections->end(); it++) {
					occurance_count += it->getSelectorOccurances(&selector);
				}
				cout << selector << "," << command << "," << value << " == " << occurance_count << endl;
			}
		}
		else if (command == 'A') {
			if (is_a_number(selector[0])) {
				int index = atoi(selector.c_str()) - 1;

				if (index < 0 || index >= sections->size()) {
					continue;
				}

				list<Section>::iterator it = sections->begin();
				for (int i = 0; i < index; i++) {
					it++;
				}

				if (value[0] == '?') {
					cout << selector << "," << command << "," << value << " == " << it->getAttributeCount() << endl;
				}
				else {
					string* selector_name = it->getAttribute(&value);
					if (selector_name == NULL) continue;
					cout << selector << "," << command << "," << value << " == " << *selector_name << endl;
				}
			}
			else if (value[0] == '?') {
				int occurance_count = 0;
				for (list<Section>::iterator it = sections->begin(); it != sections->end(); it++) {
					occurance_count += it->getAttributeOccurances(&selector);
				}
				cout << selector << "," << command << "," << value << " == " << occurance_count << endl;
			}
		}
		else if (command == 'E') {
			Section* last_section = NULL;
			for (list<Section>::reverse_iterator it = sections->rbegin(); it != sections->rend(); it++) {
				if (it->selectorExists(&selector)) {
					last_section = &(*it);
					break;
				}
			}
			if (last_section == NULL) continue;
			string* attribute = last_section->getAttribute(&value);
			if (attribute == NULL) continue;
			cout << selector << "," << command << "," << value << " == " << *(attribute) << endl;
		}
		else if (command == 'D') {
			int index = atoi(selector.c_str()) - 1;

			if (index < 0 || index >= sections->size()) {
				continue;
			}

			list<Section>::iterator it = sections->begin();
			for (int i = 0; i < index; i++) {
				it++;
			}

			if (value[0] == '*') {
				sections->erase(it);
				cout << selector << "," << command << "," << value << " == deleted" << endl;
			}
			else {
				if (it->getAttribute(&value) != NULL) {
					it->deleteAtribute(&value);
					if (it->isEmpty()) {
						sections->erase(it);
					}
					cout << selector << "," << command << "," << value << " == deleted" << endl;
				}
			}
		}
	}
	return false;
}

int main() {
	list<string>* keywords = new list<string>();
	list<Section>* sections = new list<Section>();

	while (true)
	{
		if (!load_input(keywords)) break;
		load_sections(sections, keywords);
		if (!handle_commands(sections)) break;
	}

	return 0;
}
