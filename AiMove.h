#pragma once
// Класс описания хода в игре
class Move {
public:
	int from_x;
	int from_y;
	int to_x;
	int to_y;

	double rang;

	Move(void) {
		from_x=0;
		from_y=0;
		to_x=0;
		to_y=0;
	}

	Move(int f_x, int f_y, int t_x, int t_y) {
		from_x = f_x;
		from_y = f_y;
		to_x = t_x;
		to_y = t_y;
		rang = 0;
	}

	void setRang(double sr) {
		rang = sr;
	}
};