#pragma once
#include "GameLogicData.h"
#include "engineheaders.h"

void GameLogicData::saveDesk(void) {
	gameHistory.push(new Desk(currDesk));
}

bool GameLogicData::undoDesk(void) {
	if (!gameHistory.empty()) {
		Desk* t = gameHistory.top();
		currDesk = *t;
		delete t;
		gameHistory.pop();
		return true;
	}
	else {
		currDesk.genDefault();
		saveDesk();
	}
	return false;
}

GameLogicData::GameLogicData(void) {
	player_old_x = -1;
	player_old_y = -1;
	player_new_x = -1;
	player_new_y = -1;
	currDesk.genDefault();
	saveDesk();
}

bool GameLogicData::findPlayerMoveIndexes(void) {
	int found = 0;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (currDesk.field[y][x].action == POINTED) {
				player_new_x = x;
				player_new_y = y;
				found++;
			}
			if (currDesk.field[y][x].action == SELECTED) {
				player_old_x = x;
				player_old_y = y;
				found++;
			}
		}
	}
	if (found == 2) {
		return currDesk.mayPoint(player_new_x, player_new_y);
	}
	return false;
}

void GameLogicData::PlayerMove(void) {
	currDesk.unselect();
	currDesk.field[player_old_y][player_old_x].type = cellType::FREE_CELL;
	currDesk.field[player_new_y][player_new_x].type = cellType::PLAYER_CELL;
}


bool GameLogicData::Restart(void) {
	while (undoDesk()) {};
	return true;
}