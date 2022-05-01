#pragma once
#include "Cell.h"

class Desk {
public:
	Cell field[8][8];


	void fillAiGoals();

	Cell* getCell(int x, int y);

	void genDefault(void);
	Desk(void);

	Desk(Desk& from);

	bool checkSelected(int x, int y);

	bool mayPoint(int x, int y);

	void unselect(void);

	void unpoint(void);

	void aiMove(Move* m);

	bool canMove(int x, int y, bool player);

	bool playerWins(void);
	bool aiWins(void);

	void operator=(Desk& source);
};