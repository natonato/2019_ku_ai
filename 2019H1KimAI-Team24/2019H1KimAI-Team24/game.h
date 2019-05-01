#ifndef GAME_H
#define GAME_H

#include "common.h"

class Game {
public:
	static constexpr byte FIRST = 0, SECOND = 1;
	byte currentPlayer;
private:
	long long board = 0;
	long long player[2] = { 0 };

public:
	Game(byte first) : currentPlayer(first) {}
	bool putStone(int column);
	void printBoard();
	bool endGame(); //°¡¸Á¾øÀ½

	long long pos(int col, int row) const {
		return 1LL << ((col * 7) + row);
	}
};

#endif //GAME_H