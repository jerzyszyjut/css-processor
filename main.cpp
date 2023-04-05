#include <iostream>
#include "css_section.h"
#include "jstring.h"
#include "jblocklist.h"
#define ESCAPE_CSS_PARSING_SPECIAL_CHARACTER '?'
#define ESCAPE_COMMAND_PARSING_SPECIAL_CHARACTER '*'
#define ESCAPE_CHARACTER_COUNT 4

using namespace std;

bool is_a_number(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	return false;
}

void load_sections(jblocklist<css_section> *sections, jblocklist<jstring> *keywords)
{
	css_section section = css_section();
	bool in_section = false;
	jstring *previous_keyword = NULL;
	for (jblocklist<jstring>::iterator it = keywords->begin(); it != keywords->end(); it++)
	{
		if (*it == "{")
		{
			in_section = true;
		}
		else if (*it == "}")
		{
			in_section = false;
			sections->push_back(&section);
			section = css_section();
		}
		else
		{
			if (!in_section)
			{
				jstring trimmed_selector_value, value = *it;
				bool reached_proper_string = false;
				for (jstring::iterator it_2 = value.begin(); it_2 != value.end(); it_2++)
				{
					if (*it_2 == ',')
						continue;
					if (*it_2 == ' ')
					{
						if (reached_proper_string)
						{
							trimmed_selector_value += *it_2;
						}
					}
					else
					{
						reached_proper_string = true;
						trimmed_selector_value += *it_2;
					}
				}

				if (trimmed_selector_value.get_length() > 0)
				{
					section.addSelector(trimmed_selector_value);
				}
			}
			else if (in_section)
			{
				if (*it == ":")
				{
					jstring trimmed_attribute_value, value = *(++it);
					bool reached_proper_string = false;
					for (jstring::iterator it_2 = value.begin(); it_2 != value.end(); it_2++)
					{
						if (*it_2 == ' ')
						{
							if (reached_proper_string)
							{
								trimmed_attribute_value += *it_2;
							}
						}
						else
						{
							reached_proper_string = true;
							trimmed_attribute_value += *it_2;
						}
					}

					section.addAttribute(*previous_keyword, trimmed_attribute_value);
				}
				previous_keyword = &it;
			}
		}
	}
	keywords->clear();
}

bool load_input(jblocklist<css_section> *sections, jblocklist<jstring> *keywords)
{
	bool in_section = false, in_attribute = false;
	int special_character_count = 0;
	jstring input = "";
	char c;
	while ((c = getchar()) != EOF)
	{
		if (c < ' ')
		{
			continue;
		}

		if (c == ESCAPE_CSS_PARSING_SPECIAL_CHARACTER)
		{
			special_character_count++;
			if (special_character_count == ESCAPE_CHARACTER_COUNT)
			{
				return true;
			}
		}
		else
		{
			special_character_count = 0;
		}

		if (c == '{')
		{
			in_section = true;
			if (input.get_length() > 0 && input[input.get_length() - 1] == ' ')
			{
				input = input.substring(0, input.get_length() - 1);
			}
			keywords->push_back(&input);
			input = c;
			keywords->push_back(&input);
			input = "";
		}
		else if (c == '}')
		{
			in_section = false;
			input = c;
			keywords->push_back(&input);
			input = "";
			load_sections(sections, keywords);
		}
		else if (in_section && c == ':')
		{
			in_attribute = true;
			keywords->push_back(&input);
			input = c;
			keywords->push_back(&input);
			input = "";
		}
		else if (in_section && in_attribute && c == ';')
		{
			in_attribute = false;
			keywords->push_back(&input);
			input = "";
		}
		else
		{
			if (!in_section && !in_attribute)
			{
				if (c == ',')
				{
					input += c;
					keywords->push_back(&input);
					input = "";
					continue;
				}
			}

			if (in_section && !in_attribute)
			{
				if (c == ' ')
				{
					continue;
				}
			}

			input += c;
		}
	}
	return false;
}

bool handle_commands(jblocklist<css_section> *sections)
{
	jstring command_line;
	while (cin >> command_line || (!cin.eof() || command_line.get_length() > 0))
	{
		if (command_line.get_length() == 0)
			continue;

		if (command_line[0] == ESCAPE_COMMAND_PARSING_SPECIAL_CHARACTER)
			return true;

		if (command_line[0] == '?')
		{
			cout << "? == " << sections->size() << endl;
			continue;
		}

		int first_comma_position = command_line.find(',');

		if (command_line[first_comma_position + 2] != ',')
			continue;

		char command = command_line[first_comma_position + 1];
		jstring selector = command_line.substring(0, first_comma_position);
		jstring value = command_line.substring(first_comma_position + 3, command_line.get_length() - first_comma_position - 3);

		if (command == 'S')
		{
			if (is_a_number(selector[0]))
			{
				int index = atoi(selector.c_str()) - 1;

				if (index < 0 || index >= sections->size())
				{
					continue;
				}

				jblocklist<css_section>::iterator it = sections->begin();
				for (int i = 0; i < index; i++)
				{
					it++;
				}

				if (value[0] == '?')
				{
					cout << selector << "," << command << "," << value << " == " << (&it)->getSelectorCount() << endl;
				}
				else if (is_a_number(value[0]))
				{
					int selector_index = atoi(value.c_str()) - 1;
					jstring *selector_name = (&it)->getSelector(selector_index);
					if (selector_name == NULL)
						continue;
					cout << selector << "," << command << "," << value << " == " << *selector_name << endl;
				}
			}
			else if (value[0] == '?')
			{
				int occurance_count = 0;
				for (jblocklist<css_section>::iterator it = sections->begin(); it != sections->end(); it++)
				{
					occurance_count += (&it)->getSelectorOccurances(&selector);
				}
				cout << selector << "," << command << "," << value << " == " << occurance_count << endl;
			}
		}
		else if (command == 'A')
		{
			if (is_a_number(selector[0]))
			{
				int index = atoi(selector.c_str()) - 1;

				if (index < 0 || index >= sections->size())
				{
					continue;
				}

				jblocklist<css_section>::iterator it = sections->begin();
				for (int i = 0; i < index; i++)
				{
					it++;
				}

				if (value[0] == '?')
				{
					cout << selector << "," << command << "," << value << " == " << (&it)->getAttributeCount() << endl;
				}
				else
				{
					jstring *selector_name = (&it)->getAttribute(&value);
					if (selector_name == NULL)
						continue;
					cout << selector << "," << command << "," << value << " == " << *selector_name << endl;
				}
			}
			else if (value[0] == '?')
			{
				int occurance_count = 0;
				for (jblocklist<css_section>::iterator it = sections->begin(); it != sections->end(); it++)
				{
					occurance_count += (&it)->getAttributeOccurances(&selector);
				}
				cout << selector << "," << command << "," << value << " == " << occurance_count << endl;
			}
		}
		else if (command == 'E')
		{
			css_section *last_section = NULL;
			for (jblocklist<css_section>::reverse_iterator it = sections->rbegin(); it != sections->rend(); it++)
			{
				if ((&it)->selectorExists(&selector))
				{
					last_section = &(*it);
					break;
				}
			}
			if (last_section == NULL)
				continue;
			jstring *attribute = last_section->getAttribute(&value);
			if (attribute == NULL)
				continue;
			cout << selector << "," << command << "," << value << " == " << *(attribute) << endl;
		}
		else if (command == 'D')
		{
			int index = atoi(selector.c_str()) - 1;

			if (index < 0 || index >= sections->size())
			{
				continue;
			}

			jblocklist<css_section>::iterator it = sections->begin();
			for (int i = 0; i < index; i++)
			{
				it++;
			}

			if (value[0] == '*')
			{
				sections->erase(&it);
				cout << selector << "," << command << "," << value << " == deleted" << endl;
			}
			else
			{
				if ((&it)->getAttribute(&value) != NULL)
				{
					(&it)->deleteAtribute(&value);
					if ((&it)->isEmpty())
					{
						sections->erase(&it);
					}
					cout << selector << "," << command << "," << value << " == deleted" << endl;
				}
			}
		}
	}
	return false;
}

int main()
{
	jblocklist<jstring> *keywords = new jblocklist<jstring>();
	jblocklist<css_section> *sections = new jblocklist<css_section>();

	while (true)
	{
		if (!load_input(sections, keywords))
			break;
		load_sections(sections, keywords);
		if (!handle_commands(sections))
			break;
	}

	delete sections;
	delete keywords;

	return 0;
}
