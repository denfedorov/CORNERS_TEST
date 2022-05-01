#include "GameLogicBase.h"
#include "Desk.h"

void Desk::fillAiGoals() {

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

Cell* Desk::getCell(int x, int y) {
	return &field[y][x];
}

void Desk::genDefault(void) {
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

Desk::Desk() {
	genDefault();
}

Desk::Desk(Desk& from) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			field[y][x] = from.field[y][x];
		}
	}
}

bool Desk::checkSelected(int x, int y) {
	if (x < 0 || y < 0 || x>7 || y>7) return false;
	return field[y][x].action == SELECTED;
}

bool Desk::mayPoint(int x, int y) {
	bool yes = false;
	yes = yes || checkSelected(x - 1, y);
	yes = yes || checkSelected(x + 1, y);
	yes = yes || checkSelected(x, y - 1);
	yes = yes || checkSelected(x, y + 1);
	return yes;
}

void Desk::unselect(void) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			field[y][x].action = UNSELECTED;
		}
	}
}

void Desk::unpoint(void) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (field[y][x].action == POINTED) {
				field[y][x].action = UNSELECTED;
			}
		}
	}
}

void Desk::aiMove(Move* m) {
	field[m->to_y][m->to_x].type = AI_CELL;
	field[m->from_y][m->from_x].type = FREE_CELL;
}

bool Desk::canMove(int x, int y, bool player) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		if (this->getCell(x,y)->type == FREE_CELL) {
			return true;
		}
		if (player && this->getCell(x, y)->Goal == -1) {
			return true;
		}
	}
	return false;
}

bool Desk::playerWins(void) {
	bool result = true;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			result &= getCell(x, y)->type == PLAYER_CELL;
		}
	}
	return result;
}

bool Desk::aiWins(void) {
	bool result = true;
	for (int y = 8 - 3; y < 8; y++) {
		for (int x = 8 - 3; x < 8; x++) {
			result &= getCell(x, y)->type == AI_CELL;
		}
	}
	return result;
}


void Desk::operator=(Desk& source) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			field[y][x] = source.field[y][x];
		}
	}
}