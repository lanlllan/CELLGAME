#pragma once
#include"GameMap.h"
class GameRule
{
private:
	bool** aMap;
	int alivecellnum = 0;
public:
	GameRule(GameMap* gameMap)
	{
		setAMap(gameMap);
	}
	void setAMap(GameMap* gameMap);
	void submitMap(GameMap* gameMap);
	void updateMap();
	bool judgeElement(int row, int colume, bool** aMap);
	void DelTempMap(bool** map);
	bool changeCellAlive(int row, int column);
};

