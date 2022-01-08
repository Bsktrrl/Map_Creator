#pragma once
#include "Includes.h"

#pragma region Identifiers
void mapTerrain(int mapX, int mapY, vector<vector<char>>& map, char empty, char water, char mountain, char tree, char point, char player, char border, int waterAmount, int mountainAmount, int treeAmount, int pointAmount, int playerAmount, char deepWater, int mountainTreeAmount, char mountainTree);
void spawnDeepWater(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, int waterAmount, char border, int chance, char deepWater);
void spawnMountain(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char mountain, int mountainAmount, char border, int chance);
void spawnTrees(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char tree, int treeAmount, char border, int chance, int mountainTreeAmount, char mountain, char mountainTree);
void spawnSand(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char point, int pointAmount, char border, int chance, char deepWater, char water);
void spawnPlayer(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char player, int playerAmount, char border, int chance);
void spawnShallowWater(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char water, char deepWater, char empty);

void rngPlacement(int& rngX, int& rngY, int mapX, int mapY);
int rngDirections();

void corrections(int mapX, int mapY, vector<vector<char>>& map, char empty, char border, char tree, char mountain, char water, char deepWater);
#pragma endregion

//--------------------------------------------------------------------------------------------------------------------

void mapTerrain(int mapX, int mapY, vector<vector<char>>& map, char empty, char water, char mountain, char tree, char point, char player, char border, int waterAmount, int mountainAmount, int treeAmount, int pointAmount, int playerAmount, char deepWater, int mountainTreeAmount, char mountainTree) {
	int rngX{};
	int rngY{};
	int chance{4};

	//Spawns all the fundementals (areas) in the world
	for (size_t i = 0; i < 4; i++) //Reset to 4
		spawnDeepWater(rngX, rngY, mapX, mapY, map, empty, waterAmount, border, chance, deepWater);
	
	spawnShallowWater(rngX, rngY, mapX, mapY, map, water, deepWater, empty);

	for (size_t i = 0; i < 3; i++) //Reset to 3
		spawnMountain(rngX, rngY, mapX, mapY, map, empty, mountain, mountainAmount, border, chance);
	
	//corrects the areas so it looks cleaner
	for (size_t i = 0; i < 2; i++)
		corrections(mapX, mapY, map, empty, border, tree, mountain, water, deepWater);
	
	//Spawn in whatever that lays "on top" of the areas
	spawnShallowWater(rngX, rngY, mapX, mapY, map, water, deepWater, empty);
	spawnTrees(rngX, rngY, mapX, mapY, map, empty, tree, treeAmount, border, chance, mountainTreeAmount, mountain, mountainTree);
	spawnSand(rngX, rngY, mapX, mapY, map, empty, point, pointAmount, border, chance, deepWater, water);
	spawnPlayer(rngX, rngY, mapX, mapY, map, empty, player, playerAmount, border, chance);

}

void spawnDeepWater(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, int waterAmount, char border, int chance, char deepWater) {

	if (waterAmount > 0)
	{
		//Set the first water tile
		for (size_t i = 0; i < 1;)
		{
			rngPlacement(rngX, rngY, mapX, mapY);

			if (map[rngX][rngY] == empty) {
				map[rngX][rngY] = deepWater;
				i++;
			}
		}

		//Set the rest of the water tiles
		for (size_t i = 0; i < waterAmount - 1; i++)
		{
			for (size_t i = 0; i < 1;)
			{
				chance = rngDirections();

				if (chance == 1) //adjacent to the right
				{
					if (map[rngX += 1][rngY] != border)
					{
						rngX -= 1;
						if (map[rngX += 1][rngY] == empty)
						{
							rngX -= 1;
							map[rngX += 1][rngY] = deepWater;
							rngX -= 1;
							rngX += 1;
							i++;
						}
					}
					else
						rngX -= 1;
				}
				else if (chance == 2) //adjacent to the left
				{
					if (map[rngX -= 1][rngY] != border)
					{
						rngX += 1;
						if (map[rngX -= 1][rngY] == empty)
						{
							rngX += 1;
							map[rngX -= 1][rngY] = deepWater;
							rngX += 1;
							rngX -= 1;
							i++;
						}
					}
					else
						rngX += 1;
				}
				else if (chance == 3) //adjacent to the down
				{
					if (map[rngX][rngY += 1] != border)
					{
						rngY -= 1;
						if (map[rngX][rngY += 1] == empty)
						{
							rngY -= 1;
							map[rngX][rngY += 1] = deepWater;
							rngY -= 1;
							rngY += 1;
							i++;
						}
					}
					else
						rngY -= 1;
				}
				else if (chance == 4) //adjacent to the up
				{
					if (map[rngX][rngY -= 1] != border)
					{
						rngY += 1;
						if (map[rngX][rngY -= 1] == empty)
						{
							rngY += 1;
							map[rngX][rngY -= 1] = deepWater;
							rngY += 1;
							rngY -= 1;
							i++;
						}
					}
					else
						rngY += 1;
				}
			}
		}
	}

}

void spawnShallowWater(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char water, char deepWater, char empty) {

	for (size_t x = 1; x < mapX - 1; x++)
	{
		for (size_t y = 1; y < mapY - 1; y++)
		{
			if (map[x][y] == deepWater && map[x + 1][y] == empty)
			{
				map[x + 1][y] = water;
				map[x][y] = water;
			}
			if (map[x][y] == deepWater && map[x - 1][y] == empty)
			{
				map[x - 1][y] = water;
				map[x][y] = water;
			}
			if (map[x][y] == deepWater && map[x][y + 1] == empty)
			{
				map[x][y + 1] = water;
				map[x][y] = water;
			}
			if (map[x][y] == deepWater && map[x][y - 1] == empty)
			{
				map[x][y - 1] = water;
				map[x][y] = water;
			}
		}
	}

	
}

void spawnMountain(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char mountain, int mountainAmount, char border, int chance) {

	if (mountainAmount > 0)
	{
		//Set the first mountain tile
		for (size_t i = 0; i < 1;)
		{
			rngPlacement(rngX, rngY, mapX, mapY);

			if (map[rngX][rngY] == empty) {
				map[rngX][rngY] = mountain;
				i++;
			}
		}

		//Set the rest of the mountain tiles
		for (size_t i = 0; i < mountainAmount - 1; i++)
		{
			for (size_t i = 0; i < 1;)
			{
				chance = rngDirections();

				if (chance == 1)
				{
					if (map[rngX += 1][rngY] != border)
					{
						rngX -= 1;
						if (map[rngX += 1][rngY] == empty)
						{
							rngX -= 1;
							map[rngX += 1][rngY] = mountain;
							rngX -= 1;
							rngX += 1;
							i++;
						}
					}
					else
						rngX -= 1;
				}
				else if (chance == 2)
				{
					if (map[rngX -= 1][rngY] != border)
					{
						rngX += 1;
						if (map[rngX -= 1][rngY] == empty)
						{
							rngX += 1;
							map[rngX -= 1][rngY] = mountain;
							rngX += 1;
							rngX -= 1;
							i++;
						}
					}
					else
						rngX += 1;
				}
				else if (chance == 3)
				{
					if (map[rngX][rngY += 1] != border)
					{
						rngY -= 1;
						if (map[rngX][rngY += 1] == empty)
						{
							rngY -= 1;
							map[rngX][rngY += 1] = mountain;
							rngY -= 1;
							rngY += 1;
							i++;
						}
					}
					else
						rngY -= 1;
				}
				else if (chance == 4)
				{
					if (map[rngX][rngY -= 1] != border)
					{
						rngY += 1;
						if (map[rngX][rngY -= 1] == empty)
						{
							rngY += 1;
							map[rngX][rngY -= 1] = mountain;
							rngY += 1;
							rngY -= 1;
							i++;
						}
					}
					else
						rngY += 1;
				}
			}
		}
	}
}

void spawnTrees(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char tree, int treeAmount, char border, int chance, int mountainTreeAmount, char mountain, char mountainTree) {
	
	//Trees on empty
	if (treeAmount > 0)
	{
		//Trees on empty
		for (size_t i = 0; i < treeAmount; i++)
		{
			for (size_t j = 0; j < 1;)
			{
				rngPlacement(rngX, rngY, mapX, mapY);

				if (map[rngX][rngY] == empty && map[rngX + 1][rngY] != tree && map[rngX - 1][rngY] != tree && map[rngX][rngY + 1] != tree && map[rngX][rngY - 1] != tree) {
					map[rngX][rngY] = tree;
					j++;
				}
			}
		}
	}

	//Trees on mountain
	if (mountainTreeAmount > 0)
	{
		//Set the first mountain tile
		for (size_t i = 0; i < mountainTreeAmount; i++)
		{
			for (size_t j = 0; j < 1;)
			{
				rngPlacement(rngX, rngY, mapX, mapY);

				if (map[rngX][rngY] == mountain && map[rngX + 1][rngY] != mountainTree && map[rngX - 1][rngY] != mountainTree && map[rngX][rngY + 1] != mountainTree && map[rngX][rngY - 1] != mountainTree) {
					map[rngX][rngY] = mountainTree;
					j++;
				}
			}
		}
	}
}

void spawnSand(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char point, int pointAmount, char border, int chance, char deepWater, char water) {

	/*
	for (size_t y = 0; y < mapY; y++)
	{
		for (size_t x = 0; x < mapX; x++)
		{
			if (map[x][y] == water)
			{
				if (map[x + 1][y] != deepWater)
					map[x][y] = point;
				else if (map[x - 1][y] != deepWater)
					map[x][y] = point;
				else if (map[x][y + 1] != deepWater)
					map[x][y] = point;
				else if (map[x][y - 1] != deepWater)
					map[x][y] = point;
			}
		}
	}
	*/
	
}

void spawnPlayer(int& rngX, int& rngY, int mapX, int mapY, vector<vector<char>>& map, char empty, char player, int playerAmount, char border, int chance) {

	//Set the first mountain tile
	for (size_t i = 0; i < playerAmount; i++)
	{
		for (size_t i = 0; i < 1;)
		{
			rngPlacement(rngX, rngY, mapX, mapY);

			if (map[rngX][rngY] == empty) {
				map[rngX][rngY] = player;
				i++;
			}
		}
	}
}

void corrections(int mapX, int mapY, vector<vector<char>>& map, char empty, char border, char tree, char mountain, char water, char deepWater) {

	//Water
	#pragma region Water
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t x = 1; x < mapX - 1; x++)
			for (size_t y = 1; y < mapY - 1; y++)
			{
				//Clear out 1-islands in the ocean
				if (map[x][y] == water && map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
					map[x][y] = deepWater;

				//Clear out water dots in the ocean
				if (map[x][y] == water && map[x + 1][y] == water || map[x + 1][y] == deepWater)
					if (map[x][y] == water && map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater)
						if (map[x][y] == water && map[x][y + 1] == water || map[x][y + 1] == deepWater)
							if (map[x][y] == water && map[x - 1][y + 1] == water || map[x - 1][y + 1] == deepWater)
								if (map[x][y] == water && map[x - 1][y] == water || map[x - 1][y] == deepWater)
									if (map[x][y] == water && map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater)
										if (map[x][y] == water && map[x][y - 1] == water || map[x][y - 1] == deepWater)
											if (map[x][y] == water && map[x + 1][y - 1] == water || map[x + 1][y - 1] == deepWater)
												map[x][y] = deepWater;

				//Clear out water at the border
				if (map[x][y] == water && map[x + 1][y] == border)
				{
					if ((map[x - 1][y] == deepWater || map[x - 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
						map[x][y] = deepWater;
				}
				else if (map[x][y] == water && map[x - 1][y] == border)
				{
					if ((map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
						map[x][y] = deepWater;
				}
				else if (map[x][y] == water && map[x][y + 1] == border)
				{
					if ((map[x][y - 1] == deepWater || map[x][y - 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
						map[x][y] = deepWater;
				}
				else if (map[x][y] == water && map[x][y - 1] == border)
				{
					if ((map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
						map[x][y] = deepWater;
				}

				//Clear out 2x1-islands on the deepWater
				if ((map[x][y] == empty || map[x][y] == mountain) && (map[x + 1][y] == empty || map[x + 1][y] == mountain))
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							map[x][y] = deepWater;
							map[x + 1][y] = deepWater;
						}
					}
				}
				if (map[x][y] == empty && map[x + 1][y] == empty)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							map[x][y] = deepWater;
							map[x + 1][y] = deepWater;
						}
					}
				}
				if (map[x][y] == mountain && map[x + 1][y] == mountain)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							map[x][y] = deepWater;
							map[x + 1][y] = deepWater;
						}
					}
				}
				if (map[x][y] == empty && map[x + 1][y] == mountain)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							map[x][y] = deepWater;
							map[x + 1][y] = deepWater;
						}
					}
				}
				if (map[x][y] == mountain && map[x + 1][y] == empty)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							map[x][y] = deepWater;
							map[x + 1][y] = deepWater;
						}
					}
				}

				//Clear out 3x1-islands on the deepWater
				if ((map[x][y] == empty || map[x][y] == mountain) && (map[x + 1][y] == empty || map[x + 1][y] == mountain) && (map[x + 2][y] == empty || map[x + 2][y] == mountain))
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							if ((map[x + 2][y + 1] == water || map[x + 2][y + 1] == deepWater) && (map[x - 2][y - 1] == water || map[x - 2][y - 1] == deepWater))
							{
								map[x][y] = deepWater;
								map[x + 1][y] = deepWater;
								map[x + 2][y] = deepWater;
							}
						}
					}
				}
				if (map[x][y] == empty && map[x + 1][y] == empty)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							if ((map[x + 2][y + 1] == water || map[x + 2][y + 1] == deepWater) && (map[x - 2][y - 1] == water || map[x - 2][y - 1] == deepWater))
							{
								map[x][y] = deepWater;
								map[x + 1][y] = deepWater;
								map[x + 2][y] = deepWater;
							}
						}
					}
				}
				if (map[x][y] == mountain && map[x + 1][y] == mountain)
				{
					if ((map[x][y + 1] == water || map[x][y + 1] == deepWater) && (map[x][y - 1] == water || map[x][y - 1] == deepWater))
					{
						if ((map[x + 1][y + 1] == water || map[x + 1][y + 1] == deepWater) && (map[x - 1][y - 1] == water || map[x - 1][y - 1] == deepWater))
						{
							if ((map[x + 2][y + 1] == water || map[x + 2][y + 1] == deepWater) && (map[x - 2][y - 1] == water || map[x - 2][y - 1] == deepWater))
							{
								map[x][y] = deepWater;
								map[x + 1][y] = deepWater;
								map[x + 2][y] = deepWater;
							}
						}
					}
				}

				//Clear out single empty
				if (map[x][y] == empty)
				{
					if ((map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
						map[x][y] = deepWater;
				}

				//Clear out single mountain
				if (map[x][y] == mountain)
				{
					if ((map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
						map[x][y] = deepWater;
				}

				//Remove water from the deepWater ocean
				if (map[x][y] == water)
				{
					if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;

					else if (map[x + 1][y] == water && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == water && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == water && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == water)
						map[x][y] = deepWater;

					else if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == water)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == water && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == water && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == water && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;

					else if (map[x + 1][y] == water && map[x - 1][y] == water && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == water && map[x][y + 1] == water && map[x][y - 1] == deepWater)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == water && map[x][y - 1] == water)
						map[x][y] = deepWater;
					else if (map[x + 1][y] == water && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == water)
						map[x][y] = deepWater;
				}
			}
	}
	
	
	#pragma endregion
	
	//Empty
	#pragma region Empty
	//Clear out empty in ocean
	for (size_t x = 1; x < mapX - 1; x++)
		for (size_t y = 1; y < mapY - 1; y++)
		{
			if (map[x][y] == empty && map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
				map[x][y] = deepWater;
			if (map[x][y] == empty && map[x + 1][y] == water && map[x - 1][y] == water && map[x][y + 1] == water && map[x][y - 1] == water)
				map[x][y] = deepWater;

			//Clear out empty at the border
			if (map[x][y] == empty && map[x + 1][y] == border)
			{
				if ((map[x - 1][y] == deepWater || map[x - 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == empty && map[x - 1][y] == border)
			{
				if ((map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == empty && map[x][y + 1] == border)
			{
				if ((map[x][y - 1] == deepWater || map[x][y - 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == empty && map[x][y - 1] == border)
			{
				if ((map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
					map[x][y] = deepWater;
			}

			//Clear out single mountain on empty
			if (map[x][y] == mountain && map[x + 1][y] == empty && map[x - 1][y] == empty && map[x][y + 1] == empty && map[x][y - 1] == empty)
				map[x][y] = empty;
		}
	#pragma endregion

	//Mountains
	#pragma region Mountains
	//Clear out 1-mountains in ocean
	for (size_t x = 1; x < mapX - 1; x++)
		for (size_t y = 1; y < mapY - 1; y++)
		{
			if (map[x][y] == mountain && map[x + 1][y] == deepWater && map[x - 1][y] == deepWater && map[x][y + 1] == deepWater && map[x][y - 1] == deepWater)
				map[x][y] = deepWater;
			if (map[x][y] == mountain && map[x + 1][y] == water && map[x - 1][y] == water && map[x][y + 1] == water && map[x][y - 1] == water)
				map[x][y] = deepWater;
		
			//clear out 1-empties in mountinas
			if (map[x][y] == empty && map[x + 1][y] == mountain && map[x - 1][y] == mountain && map[x][y + 1] == mountain && map[x][y - 1] == mountain)
				map[x][y] = mountain;
	
			//Clear out mountinas at the border
			if (map[x][y] == mountain && map[x + 1][y] == border)
			{
				if ((map[x - 1][y] == deepWater || map[x - 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == mountain && map[x - 1][y] == border)
			{
				if ((map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x][y - 1] == deepWater || map[x][y - 1] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == mountain && map[x][y + 1] == border)
			{
				if ((map[x][y - 1] == deepWater || map[x][y - 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
					map[x][y] = deepWater;
			}
			else if (map[x][y] == mountain && map[x][y - 1] == border)
			{
				if ((map[x][y + 1] == deepWater || map[x][y + 1] == water) && (map[x + 1][y] == deepWater || map[x + 1][y] == water) && (map[x - 1][y] == deepWater || map[x - 1][y] == water))
					map[x][y] = deepWater;
			}

			//Clear out single empty on mountain
			if (map[x][y] == empty && map[x + 1][y] == mountain && map[x - 1][y] == mountain && map[x][y + 1] == mountain && map[x][y - 1] == mountain)
				map[x][y] = mountain;

			//Clear out 2x1 empty on mountain
			if (map[x][y] == empty && map[x + 1][y] == mountain && map[x - 1][y] == mountain && map[x][y + 1] == mountain)
				map[x][y] = mountain;
			else if (map[x][y] == empty && map[x + 1][y] == mountain && map[x - 1][y] == mountain && map[x][y - 1] == mountain)
				map[x][y] = mountain;
			else if (map[x][y] == empty && map[x + 1][y] == mountain && map[x][y - 1] == mountain && map[x][y + 1] == mountain)
				map[x][y] = mountain;
			else if (map[x][y] == empty && map[x - 1][y] == mountain && map[x][y - 1] == mountain && map[x][y + 1] == mountain)
				map[x][y] = mountain;
		}
	
	#pragma endregion
}



//-------------------------------------------------------------------------------------------------------------------------

void rngPlacement(int& rngX, int& rngY, int mapX, int mapY) {

	//Random X
	random_device rdX;
	mt19937_64 genX(rdX());
	uniform_int_distribution<int> RNGX(0, mapX - 1);
	rngX = RNGX(genX);

	//Random Y
	random_device rdY;
	mt19937_64 genY(rdY());
	uniform_int_distribution<int> RNGY(0, mapY - 1);
	rngY = RNGY(genY);
}

int rngDirections() {
	int randomNumber{};

	//Random X
	random_device rdX;
	mt19937_64 genX(rdX());
	uniform_int_distribution<int> RNGX(1, 4);
	randomNumber = RNGX(genX);

	return randomNumber;
}