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

	void registerAiMove(int sx, int sy, int x, int y) {
		Move nm(sx, sy, x, y);
		ai_moves[ai_moves_cnt++]=nm;
	}

	void generateAiMoves(void) {
		ai_moves_cnt=0;
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				if (init_desk.field[y][x].type == AI_CELL) {
					if (init_desk.canMove(x+1, y)) {
						registerAiMove(x,y,x+1,y);
					}
					if (init_desk.canMove(x,y+1)) {
						registerAiMove(x,y,x,y+1);
					}
					if (init_desk.canMove(x-1, y)) {
						registerAiMove(x,y,x-1,y);
					}
					if (init_desk.canMove(x, y-1)) {
						registerAiMove(x,y,x,y-1);
					}

				}
			}
		}
	}

	AiThinker(Desk *init) {
		init_desk = *init;
	}

	bool FindPass(Desk& d, int& passlen, int temp_pathlen, int fromx, int fromy, int tox, int toy) {

		if (!init_desk.canMove(fromx, fromy)) {
			return false;
		}

		Cell* current = d.getCell(fromy, fromx);

		if (current->pass) return false;

		current->pass = true;

		if (fromx == tox && fromy == toy) {
			passlen = temp_pathlen;
			
			d.field[fromy][fromx].pass = false;
			return true;
		}

		if (FindPass(d, passlen, temp_pathlen + 1, fromx + 1, fromy, tox, toy)) {
			current->pass = true;
			return true;
		}
		if (FindPass(d, passlen, temp_pathlen + 1, fromx, fromy+1, tox, toy)) {
			current->pass = true;
			return true;
		}
		if (FindPass(d, passlen, temp_pathlen + 1, fromx-1, fromy, tox, toy)) {
			current->pass = true;
			return true;
		}
		if (FindPass(d, passlen, temp_pathlen + 1, fromx, fromy - 1, tox, toy)) {
			current->pass = true;
			return true;
		};

		return false;
	}

	
	double getAiRang(Desk& desk) {
		double waysfound = 0;
		double passlen = 1000;

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				if (desk.getCell(x, y)->type == AI_CELL && (desk.getCell(x, y)->Goal==0)) {
					{
						for (int ty = 5; ty < 8; ty++) {
							for (int tx = 5; tx < 8; tx++) {
								if (desk.getCell(tx, ty)->type == FREE_CELL) {
									int t_passlen = 0;
									if (FindPass(desk, t_passlen, 0, x, y, tx, ty)) {
										if (passlen > t_passlen) {
											passlen = t_passlen;
											waysfound++;
										}
									
									}
								}
							}
						}
					}
				}
			}
		}
		
		if (waysfound>0) {
			return (1. / passlen);
		}
		else {
			return 1. / 100;
		}
	}


	void calcRangOfMoves(void) {
		
		for(int i = 0; i<ai_moves_cnt; i++)
		{
			Desk t_desk = init_desk;
			Move* m = &ai_moves[i];
			if (t_desk.getCell(m->from_x,m->from_y)->Goal == 0) {
				t_desk.aiMove(m);
				m->setRang(getAiRang(t_desk));
			}
			else {
				m->setRang(-100000);
			}
		}
	}
	void sortMovesByRank(void) {
		for (int i = 0; i < ai_moves_cnt; i++){
			for (int c = i + 1; c < ai_moves_cnt; c++) {
				if (ai_moves[i].rang < ai_moves[c].rang) {
					Move t;
					t = ai_moves[i];
					ai_moves[i] = ai_moves[c];
					ai_moves[c] = t;
				}
			}
		}
	}

	bool OptimizeAiTurn(void) {
		
		int goal=0;
		int keymove = -1;

		Desk tdesk = init_desk;


		for (int i = 0; i < ai_moves_cnt; i++) {
			
			Move *cm = &ai_moves[i];
					
			if (cm->to_x > 4 && cm->to_y > 4) {
				
				if (tdesk.canMove(cm->to_x, cm->to_y)) {

					if (cm->from_y >= 4 && cm->from_x >= 4) {

						int prevgoal = tdesk.getCell(cm->from_x, cm->from_y)->Goal;
						int new_goal = tdesk.getCell(cm->to_x, cm->to_y)->Goal; 
						if (prevgoal < new_goal) {
							if (goal < new_goal) {
								keymove = i;
								goal = new_goal;
							}
						}
					}
				}
			}
		}
		if (keymove !=-1) {
			Move* move = &ai_moves[keymove];
			tdesk.aiMove(move);

			desigion_desk = tdesk;
			return true;
		}
		return false;
	}

	void makeBestMove() {
		desigion_desk = init_desk;
		for (int i = 0; i < ai_moves_cnt; i++) {
			Move* tm = &ai_moves[i];
			if (desigion_desk.canMove(tm->to_x, tm->to_y)) {
				desigion_desk.aiMove(tm);
				break;
			}
		}
	}

	void Think(void) {

		generateAiMoves();

		if (!OptimizeAiTurn()) {

			calcRangOfMoves();
			sortMovesByRank();

			makeBestMove();
		}
		
	}

	~AiThinker(void) {

	}
};