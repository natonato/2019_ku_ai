#ifndef GAME_H
#define GAME_H

#include "common.h"

class Game {
private:
	Game() {}
public:
	static constexpr byte FIRST = 0, SECOND = 1;
	byte currentPlayer;
	long long board = 0;
	long long player[2] = { 0 };

	static Game& instance() {
		static Game inst;
		return inst;
	}

	bool putStone(int column);
	void printBoard();
	bool endGame(); //°¡¸Á¾øÀ½
	void debugPrint();

	long long pos(int col, int row) const {
		return 1LL << ((col * 7) + row);
	}
};

#endif //GAME_H