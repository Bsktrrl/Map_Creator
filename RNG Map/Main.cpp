#include "Includes.h"
#include "MapMaker.h"

int main() {

	int mapX{};
	int mapY{};
	bool game{true};

	while (game)
	{
		map(mapX, mapY);
		system("cls");
	}
	
	//--------------------------------------------------------------------------------------------------------------------

	system("pause > 0");
	return 0;
}