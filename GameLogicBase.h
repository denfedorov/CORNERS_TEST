#pragma once
#include "AiMove.h"

//Файл описания игровой доски

typedef enum { FREE_CELL, AI_CELL, PLAYER_CELL } cellType;
typedef enum { UNSELECTED, SELECTED, POINTED } cellAction;

class Cell {
public:
	cellType type;
	cellAction action;
	int Goal;
	bool pass;
};

class Desk {
public:
	Cell field[8][8];


	void fillAiGoals() {
		field[7 - 0][7 - 0].Goal = 250;

		field[7 - 0][7 - 1].Goal = 240;
		field[7 - 1][7 - 0].Goal = 240;
		field[7 - 1][7 - 1].Goal = 200;

		field[7 - 0][7 - 2].Goal = 190;
		field[7 - 1][7 - 2].Goal = 185;

		field[7 - 2][7 - 0].Goal = 190;
		field[7 - 2][7 - 1].Goal = 185;

		field[7 - 2][7 - 2].Goal = 160;

		/*
		field[0][2].Goal = -1;

		
		field[0][1].Goal = -1;
		field[1][0].Goal = -1;
		field[1][1].Goal = -1;

		field[0][2].Goal = -1;
		field[1][2].Goal = -1;

		field[2][0].Goal = -1;
		field[2][1].Goal = -1;

		field[2][2].Goal = -1;
*/



	};

	Cell *getCell(int x, int y) {
		return &field[y][x];
	}

	void genDefault(void) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				Cell* tc = getCell(x, y);
				tc->type = cellType::FREE_CELL;
				tc->action = cellAction::UNSELECTED;
				tc->Goal = 0;
				tc->pass = false;
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				getCell(x, y)->type = cellType::AI_CELL;
			}
		}

		for (int y = 5; y < 8; y++) {
			for (int x = 5; x < 8; x++) {
				getCell(x, y)->type = cellType::PLAYER_CELL;
			}
		}

		fillAiGoals();
	}

	Desk() {
		genDefault();
	}

	Desk(Desk& from) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				field[y][x] = from.field[y][x];
			}
		}
	}

	bool checkSelected(int x, int y) {
		if (x < 0 || y < 0 || x>7 || y>7) return false;
		return field[y][x].action == SELECTED;
	}

	bool mayPoint(int x, int y) {
		bool yes = false;
		yes = yes || checkSelected(x - 1, y);
		yes = yes || checkSelected(x + 1, y);
		yes = yes || checkSelected(x, y - 1);
		yes = yes || checkSelected(x, y + 1);
		return yes;
	}

	void unselect(void) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				field[y][x].action = UNSELECTED;
			}
		}
	}

	void unpoint(void) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				if (field[y][x].action == POINTED) {
					field[y][x].action = UNSELECTED;
				}
			}
		}
	}

	void aiMove(Move *m) {
		field[m->to_y][m->to_x].type = AI_CELL;
		field[m->from_y][m->from_x].type = FREE_CELL;
	}
	
	bool canMove(int x, int y, bool player=false ) {
		if (x >= 0 && x < 8 && y >= 0 && y < 8) {
			if (field[y][x].type == FREE_CELL) {
				return true;
			}
			if (player && field[y][x].Goal == -1) {
				return true;
			}
		}
		return false;
	}

	bool playerWins(void) {
		bool result = true;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				result &= getCell(x, y)->type == PLAYER_CELL;
			}
		}
		return result;
	}

	bool aiWins(void) {
		bool result = true;
		for (int y = 8-3; y < 8; y++) {
			for (int x = 8-3; x < 8; x++) {
				result &= getCell(x, y)->type == AI_CELL;
			}
		}
		return result;
	}


	void operator=(Desk& source) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				field[y][x] = source.field[y][x];
			}
		}
	}
};