#include "pch.h"
#include "GameRule.h"
void GameRule::setAMap(GameMap* gameMap)
{
	aMap = gameMap->getMap();
}
void GameRule::submitMap(GameMap* gameMap)
{
	gameMap->setMap(aMap,alivecellnum);
}
bool GameRule::judgeElement(int row, int colume,bool**aMap) {
	int count = 0;
	if (aMap[row - 1][colume - 1])count++;
	if (aMap[row - 1][colume])count++;
	if (aMap[row - 1][colume + 1])count++;
	if (aMap[row][colume - 1])count++;
	if (aMap[row][colume + 1])count++;
	if (aMap[row + 1][colume - 1])count++;
	if (aMap[row + 1][colume])count++;
	if (aMap[row + 1][colume + 1])count++;
	if (count < 2)return false;
	if (count == 2)return aMap[row][colume];
	if (count == 3)return true;
	return false;
}
void GameRule::updateMap()
{
	alivecellnum = 0;
	bool** tempMap = new bool*[WIDE];
	for (int i = 0; i < WIDE; i++)
	{
		tempMap[i] = new bool[HEIGHT];
		for (int j = 0; j < HEIGHT; j++)
		{
			tempMap[i][j] = aMap[i][j];
		}
	}
	for (int i = 1; i < HEIGHT-1; i++)
	{
		for (int j = 1; j < WIDE-1; j++)
		{
			aMap[i][j] = judgeElement(i, j,tempMap);
			if (aMap[i][j])alivecellnum++;
		}
	}
	DelTempMap(tempMap);
}

void GameRule::DelTempMap(bool** map)
{
	for (int i = 0; i < HEIGHT; i++) {
		delete[] map[i];
	}
}


bool GameRule::changeCellAlive(int row, int column)
{
	return aMap[row][column] = !aMap[row][column];
}
