#pragma once
#include "SpawnTerrain.h"
#include "Termocolor.h"

#pragma region Identifiers
void map(int& mapX, int& mapY);
void selectMapSize(int& mapX, int& mapY, int& waterAmount, int& mountainAmount, int& treeAmount, int& pointAmount, int& playerAmount, char water, char mountain, char tree, char point, int& mountainTreeAmount);
void declareMapSize(int& mapX, int& mapY, char empty, char border, vector<vector<char>>& map);
void mapBorder(int mapX, int mapY, vector<vector<char>>& map, char border);
void mapPrint(int mapX, int mapY, vector<vector<char>> map, char empty, char border, char water, char deepWater, char mountain, char tree, char point, char player, char mountainTree);
void mapReset(int mapX, int mapY, char empty, vector<vector<char>>& map);
char rngLettersConsonant();
char rngLettersVowel();
#pragma endregion

//-------------------------------------------------------------------------------------------------------------------------

void map(int& mapX, int& mapY) {
	mapX = 10000; //The game changes this later, but it MUST stay 10000 for now
	mapY = 10000; //The game changes this later, but it MUST stay 10000 for now
	vector<vector<char>> map(mapX, vector<char>(mapY));

	int waterAmount{50}; //Holds amount of water tiles by default
	int mountainAmount{40}; //Holds amount of mountain tiles by default
	int mountainTreeAmount{15}; //Holds amount of mountain tiles by default
	int treeAmount{30}; //Holds amount of trees by default
	int pointAmount{20}; //Holds amount of points by default
	int playerAmount{1}; //Holds the starting player

	char empty{' '}; //icon for empty space
	char border('#'); //icon for the game border (which you cannot cross)
	char water{'s'}; //icon for water
	char deepWater{ 'S' }; //icon for water
	char mountain{'A'}; //icon for mountain
	char tree{'T'}; //icon for trees
	char mountainTree{ 't' }; //icon for mountainTrees
	char point{'o'}; //icon for points
	char player{'@'}; //icon for the player

	bool firstGame{false};
	bool boardSpawn{true};

	//--------------------------------------------------------------------------------------------------------------------

	selectMapSize(mapX, mapY, waterAmount, mountainAmount, treeAmount, pointAmount, playerAmount, water, mountain, tree, point, mountainTreeAmount);

	while (boardSpawn == true)
	{
		declareMapSize(mapX, mapY, empty, border, map);
		mapBorder(mapX, mapY, map, border);
		mapTerrain(mapX, mapY, map, empty, water, mountain, tree, point, player, border, waterAmount, mountainAmount, treeAmount, pointAmount, playerAmount, deepWater, mountainTreeAmount, mountainTree);
		mapPrint(mapX, mapY, map, empty, border, water, deepWater, mountain, tree, point, player, mountainTree);
		mapReset(mapX, mapY, empty, map);

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 13:
			break;
		case 8:
			boardSpawn = false;
			break;
		default:
			break;
		}

		system("cls");
	}
}

void selectMapSize(int& mapX, int& mapY, int& waterAmount, int& mountainAmount, int& treeAmount, int& pointAmount, int& playerAmount, char water, char mountain, char tree, char point, int& mountainTreeAmount) {
	int select{};
	string selectIcon{"->"};
	bool modeCustom{};
	bool menu{};

	while (menu == false)
	{
		cout << "Map properties:" << endl;
		cout << "-------------------" << endl << endl;
		if (select == 0)
			cout << selectIcon << " | 200x200 (progress so far)" << endl;
		else
			cout << " | 200x200 (progress so far)" << endl;
		if (select == 1)
			cout << selectIcon << " | Default (30x30)" << endl;
		else
			cout << " | Default" << endl;
		if (select == 2)
			cout << selectIcon << " | Custom" << endl << endl;
		else
			cout << " | Custom" << endl << endl;

		cout << "-------------------" << endl;

		cout << "        W: Up" << endl;
		cout << "        S: Down" << endl;
		cout << "    Enter: Celect" << endl;
		cout << "Backspace: Quit" << endl;

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 'w':
			select -= 1;
			break;
		case 's':
			select += 1;
			break;
		case 13:
			if (select == 0) {
				mapX = 200;
				mapY = 200;
				waterAmount = 4500;
				mountainAmount = 2500;
				treeAmount = 800;
				mountainTreeAmount = treeAmount / 3;
				pointAmount = 300;
				menu = true;
			}
			
			else if (select == 1) {
				mapX = 30;
				mapY = 30;
				menu = true;
			}
				
			else if (select == 2) {
				menu = true;
				modeCustom = true;
			}
			break;
		case 8:
			exit(0);
			break;
		default:
			break;
		}

		if (select < 0)
			select = 2;
		if (select > 2)
			select = 0;
		
		system("cls");
	}

	if (modeCustom == true)
	{
		cout << "Menu size X: ";
		cin >> mapX;
		cout << "Menu size Y: ";
		cin >> mapY;
		cout << "Amounts of water tiles ( " << water << " ) : ";
		cin >> waterAmount;
		cout << "Amounts of mountain tiles ( " << mountain << " ) : ";
		cin >> mountainAmount;
		cout << "Amounts of trees ( " << tree << " ) : ";
		cin >> treeAmount;
		mountainTreeAmount = treeAmount / 3;
		cout << "Amounts of points ( " << point << " ) : ";
		cin >> pointAmount;

		system("cls");
	}
}

void declareMapSize(int& mapX, int& mapY, char empty, char border, vector<vector<char>>& map) {
	//Declare the map size
	/*cout << "Map size" << endl;
	cout << "--------" << endl;
	cout << "Map X: ";
	cin >> mapX;
	cout << "Map Y: ";
	cin >> mapY;
	system("cls");*/
	
	//Make the map size
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++)
			map[i][j] = empty;
	}
}

void mapBorder(int mapX, int mapY, vector<vector<char>>& map, char border) {
	//Make the border of the map
	for (size_t i = 0; i < mapY; i++)
		for (size_t j = 0; j < mapX; j++)
		{
			map[i][0] = border;
			map[0][j] = border;
			map[i][mapX - 1] = border;
			map[mapY - 1][j] = border;
		}
}

void mapPrint(int mapX, int mapY, vector<vector<char>> map, char empty, char border, char water, char deepWater, char mountain, char tree, char point, char player, char mountainTree) {
	//Print name
	/*
	#pragma region Print Map Name
	//Consonants
	char letterC_One = rngLettersConsonant();
	char letterC_Two = rngLettersConsonant();
	char letterC_Tree = rngLettersConsonant();
	char letterC_Four = rngLettersConsonant();
	char letterC_Five = rngLettersConsonant();
	char letterC_Six = rngLettersConsonant();
	char letterC_Seven = rngLettersConsonant();
	char letterC_Eight = rngLettersConsonant();
	char letterC_Nine = rngLettersConsonant();
	char letterC_Ten = rngLettersConsonant();

	//Vowels
	char letterV_One = rngLettersVowel();
	char letterV_Two = rngLettersVowel();
	char letterV_Tree = rngLettersVowel();
	char letterV_Four = rngLettersVowel();
	char letterV_Five = rngLettersVowel();
	char letterV_Six = rngLettersVowel();
	char letterV_Seven = rngLettersVowel();
	char letterV_Eight = rngLettersVowel();
	char letterV_Nine = rngLettersVowel();
	char letterV_Ten = rngLettersVowel();

	#pragma endregion
	


	cout << "   " << (letterC_One -= 32) << letterV_One << letterC_Two << letterV_Two << letterC_Tree << letterV_Tree << "topia" << endl;
	cout << "  -------------" << endl << endl;
	*/


	//Print out the map
	for (size_t i = 0; i < mapY; i++)
	{
		for (size_t j = 0; j < mapX; j++)
		{
			#pragma region Assign Colors
			if (map[i][j] == empty)
			{
				cout << termcolor::on_bright_green;
				cout << termcolor::bright_green;
			}
			else if (map[i][j] == border)
			{
				cout << termcolor::on_red;
				cout << termcolor::red;
			}
			else if (map[i][j] == water)
			{
				cout << termcolor::on_bright_blue;
				cout << termcolor::bright_blue;
			}
			else if (map[i][j] == deepWater)
			{
				cout << termcolor::on_blue;
				cout << termcolor::blue;
			}
			
			else if (map[i][j] == mountain)
			{
				cout << termcolor::on_white;
				cout << termcolor::white;
			}
			else if (map[i][j] == tree)
			{
				cout << termcolor::on_green;
				cout << termcolor::green;
			}
			else if (map[i][j] == mountainTree)
			{
				cout << termcolor::on_white;
				cout << termcolor::white;
			}
			else if (map[i][j] == point)
			{
				cout << termcolor::on_bright_yellow;
				cout << termcolor::bright_yellow;
			}
			else if (map[i][j] == player)
			{
				cout << termcolor::on_white;
				cout << termcolor::white;
			}
			#pragma endregion

			cout << setw(3) << map[i][j];
			cout << termcolor::reset;
		}
		if(i != mapY - 1)
			cout << endl;
	}
}

void mapReset(int mapX, int mapY, char empty, vector<vector<char>>& map) {
	//Make the map empty
	for (int i = 0; i < mapY; i++)
		for (int j = 0; j < mapX; j++)
			map[i][j] = empty;

	//map.clear();
}

char rngLettersConsonant() {
	int rn{};
	bool loop{true};

	while (loop)
	{
		random_device rdX;
		mt19937_64 genX(rdX());
		uniform_int_distribution<int> RNGX(97, 122);
		rn = RNGX(genX);

		if (rn != 97 && rn != 101 && rn != 105 && rn != 111 && rn != 117 && rn != 121)
			loop = false;
	}
	
	return rn;
}

char rngLettersVowel() {
	int rn{};
	bool loop{true};

	while (loop)
	{
		random_device rdX;
		mt19937_64 genX(rdX());
		uniform_int_distribution<int> RNGX(97, 122);
		rn = RNGX(genX);

		if (rn == 97 || rn == 101 || rn == 105 || rn == 111 || rn == 117 || rn == 121)
			loop = false;
	}

	return rn;
}