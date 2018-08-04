#include "iostream"
#include "string"
#include "vector" //For the command handling function.
#include "cctype" //Will be used to eliminate case sensitivity problems.

int main();

void section_command(std::string Cmd, std::string &wd1, std::string &wd2);
void set_rooms(room *rms);

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM, POOL, GARDEN, POND, PUMPROOM};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 11;

struct word
{
	std::string word;
	int code;
};

struct room
{
	std::string description;
	int exits_to_room[DIRS];
};

int main()
{
	room rooms[ROOMS];
	set_rooms(rooms);

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

void set_rooms(room *rms) 
{
	rms[SPORTSHOP].description.assign("sports shop");
	rms[SPORTSHOP].exits_to_room[NORTH] = NONE;
	rms[SPORTSHOP].exits_to_room[EAST] = NONE;
	rms[SPORTSHOP].exits_to_room[SOUTH] = CARPARK;
	rms[SPORTSHOP].exits_to_room[WEST] = NONE;

	rms[CASINO].description.assign("bustling casino");
	rms[CASINO].exits_to_room[NORTH] = NONE;
	rms[CASINO].exits_to_room[EAST] = NONE;
	rms[CASINO].exits_to_room[SOUTH] = LOBBY;
	rms[CASINO].exits_to_room[WEST] = NONE;

	rms[CARPARK].description.assign("parking lot");
	rms[CARPARK].exits_to_room[NORTH] = SPORTSHOP;
	rms[CARPARK].exits_to_room[EAST] = LOBBY;
	rms[CARPARK].exits_to_room[SOUTH] = NONE;
	rms[CARPARK].exits_to_room[WEST] = NONE;

	rms[LOBBY].description.assign("hotel lobby");
	rms[LOBBY].exits_to_room[NORTH] = CASINO;
	rms[LOBBY].exits_to_room[EAST] = RESTAURANT;
	rms[LOBBY].exits_to_room[SOUTH] = CORRIDOR;
	rms[LOBBY].exits_to_room[WEST] = CARPARK;

	rms[RESTAURANT].description.assign("high-class restaurant");
	rms[RESTAURANT].exits_to_room[NORTH] = NONE ;
	rms[RESTAURANT].exits_to_room[EAST] = NONE;
	rms[RESTAURANT].exits_to_room[SOUTH] = NONE;
	rms[RESTAURANT].exits_to_room[WEST] = LOBBY;

	rms[CORRIDOR].description.assign("long corridor");
	rms[CORRIDOR].exits_to_room[NORTH] = LOBBY;
	rms[CORRIDOR].exits_to_room[EAST] = STOREROOM;
	rms[CORRIDOR].exits_to_room[SOUTH] = GARDEN;
	rms[CORRIDOR].exits_to_room[WEST] = NONE;

	rms[STOREROOM].description.assign("empty storeroom");
	rms[STOREROOM].exits_to_room[NORTH] = NONE;
	rms[STOREROOM].exits_to_room[EAST] = NONE;
	rms[STOREROOM].exits_to_room[SOUTH] = NONE;
	rms[STOREROOM].exits_to_room[WEST] = CORRIDOR;

	rms[POOL].description.assign("pool");
	rms[POOL].exits_to_room[NORTH] = NONE;
	rms[POOL].exits_to_room[EAST] = GARDEN;
	rms[POOL].exits_to_room[SOUTH] = PUMPROOM;
	rms[POOL].exits_to_room[WEST] = NONE;

	rms[GARDEN].description.assign("hanging gardens");
	rms[GARDEN].exits_to_room[NORTH] = CORRIDOR;
	rms[GARDEN].exits_to_room[EAST] = POND;
	rms[GARDEN].exits_to_room[SOUTH] = NONE;
	rms[GARDEN].exits_to_room[WEST] = POOL;

	rms[POND].description.assign("relaxing pond");
	rms[POND].exits_to_room[NORTH] = NONE;
	rms[POND].exits_to_room[EAST] = NONE;
	rms[POND].exits_to_room[SOUTH] = NONE;
	rms[POND].exits_to_room[WEST] = GARDEN;

	rms[PUMPROOM].description.assign("pump room");
	rms[PUMPROOM].exits_to_room[NORTH] = POOL;
	rms[PUMPROOM].exits_to_room[EAST] = NONE;
	rms[PUMPROOM].exits_to_room[SOUTH] = NONE;
	rms[PUMPROOM].exits_to_room[WEST] = NONE;
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
