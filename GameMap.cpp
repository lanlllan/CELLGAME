#include "pch.h"
#include "GameMap.h"
void GameMap::setMap(bool** aMap,int aliveCellNum) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDE; j++) {
			this->map[i][j] = aMap[i][j];
		}
	}
	setAliveCellNum(aliveCellNum);
	StepPP();
}
bool** GameMap::getMap() {
	bool** aMap=new bool*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		aMap[i] = new bool[WIDE];
		for (int j = 0; j < WIDE; j++) {
			aMap[i][j] = map[i][j];
		}
	}
	return aMap;
}
void GameMap::setAliveCellNum(int num) {
	aliveCellNum = num;
}
int GameMap::getAilveCellNum() {
	return aliveCellNum;
}
void GameMap::StepPP() {
	step++;
}
int GameMap::getStep() {
	return step;
}

bool GameMap::isAlive(int row, int column)
{
	return map[row][column];
}


//bool GameMap::changeCellAlive(int row, int column)
//{
//	return map[row][column] = !map[row][column];
//}


bool GameMap::getElement(int row, int colume)
{
	
	return map[row][colume];
}
