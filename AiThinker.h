#pragma once
#include "GameLogicData.h"
#include "GameLogicBase.h"
#include <array>

//Класс отвечающий за игру ИИ

class AiThinker {

	Move ai_moves[9*4];
	int ai_moves_cnt;

public:
	Desk init_desk;
	Desk desigion_desk;

	void registerAiMove(int sx, int sy, int x, int y);
	void generateAiMoves(void);

	AiThinker(Desk* init);
	void generateAiMoves(void); 

	bool FindPass(Desk& d, int& passlen, int temp_pathlen, int fromx, int fromy, int tox, int toy);
	
	double getAiRang(Desk& desk);

	void calcRangOfMoves(void);
	void sortMovesByRank(void);

	bool OptimizeAiTurn(void);

	void makeBestMove();

	void Think(void) {

	void generateAiMoves();

	void calcRangOfMoves(void);
	void sortMovesByRank(void);

	bool OptimizeAiTurn(void);

	void makeBestMove(void);

	void Think(void);

	~AiThinker(void);
};
