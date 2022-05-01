#pragma once
//Игровые данные

#include <map>
#include <stack>

#include "GameLogicBase.h"

using namespace std;

class GameLogicData {
	stack <Desk*> gameHistory;

public:

	Desk currDesk;

	int player_old_x;
	int player_old_y;
	int player_new_x;
	int player_new_y;

	void saveDesk(void);
	bool undoDesk(void);
	GameLogicData(void);
	bool findPlayerMoveIndexes(void);
	void PlayerMove(void);
	bool Restart(void);

};