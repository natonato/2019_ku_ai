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
	byte count[7] = { 0 };

public:
	Game(byte first) : currentPlayer(first) {}
	bool putStone(int column);
	void printBoard();
	bool endGame(); //°¡¸Á¾øÀ½

	bool pos(byte pl, int row, int col) const {
		return (player[pl] >> ((col * 7) + row)) & 1;
	}
};

#endif //GAME_H