#pragma once
#define HEIGHT 12
#define WIDE  12

class GameMap
{
private:
	bool map[HEIGHT][WIDE];
	int aliveCellNum;
	int step;
public:
	GameMap() {
		srand(time(nullptr));
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDE ; j++) {
				map[i][j] = 0;
			}
		}

		for (int i = 1; i < HEIGHT - 1; i++) {
			for (int j = 1; j < WIDE - 1; j++) {
				int level = rand() % 3;
				if (level > 1)map[i][j] = 1;
				else map[i][j] = 0;
			}
		}
		aliveCellNum = 0;
		step = 0;
	}
	void setMap(bool** aMap, int aliveCellNum);
	bool** getMap();
	void setAliveCellNum(int num);
	int getAilveCellNum();
	void StepPP();
	int getStep();
	bool isAlive(int row, int colume);
	//bool changeCellAlive(int row, int column);
	bool getElement(int row, int colume);
};

