#include "iostream"
#include "string"
#include "vector" //For the command handling function.
#include "cctype" //Will be used to eliminate case sensitivity problems.

void section_command(std::string Cmd, std::string &wd1, std::string &wd2);

int main()
{
	std::string command;
	std::string word_1;
	std::string word_2;

	while (word_1 != "QUIT")
	{
		command.clear();
		std::cout << "What shall I do?";
		std::getline(std::cin, command);
		std::cout << "Your raw command was: " << command << std::endl;
		word_1.clear();
		word_2.clear();

		section_command(command, word_1, word_2); //Calling the function that handles the command line format. Hasn't been created yet./
		std::cout << word_1 << " " << word_2 << std::endl;
	}

	system("pause");
	return 0;
}

void section_command(std::string Cmd, std::string &wd1, std::string &wd2)
{
	std::string sub_str;
	std::vector<std::string> words;
	char search = ' ';
	size_t i, j;

	for (i = 0; i <Cmd.size(); i++)
	{
		if (Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}

		if (i == Cmd.size() - 1)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}

		if (Cmd.at(i) == search)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
	}

	for (i = words.size() - 1; i > 0; i--)
	{
		if (words.at(i) == " ")
		{
			words.erase(words.begin() + i);
		}
	}

	for (i = 0; i < words.size(); i++)
	{
		for (j = 0; j < words.at(i).size(); j++)
		{
			if (islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}

	if (words.size() == 0)
	{
		std::cout << "No command given" << std::endl;
	}

	if (words.size() == 1)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
	}

	if (words.size() > 2)
	{
		std::cout << "Command too long. Only type one or two words (Direction or verb and noun)";
	}
}
