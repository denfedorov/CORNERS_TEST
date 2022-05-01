#pragma once
typedef enum { FREE_CELL, AI_CELL, PLAYER_CELL } cellType;
typedef enum { UNSELECTED, SELECTED, POINTED } cellAction;

class Cell {
public:
	cellType type;
	cellAction action;
	int Goal;
	bool pass;
};
