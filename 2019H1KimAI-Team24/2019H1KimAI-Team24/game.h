#ifndef GAME_H
#define GAME_H

#include "common.h"

class Game {
public:
	static constexpr byte FIRST = 0, SECOND = 1;
private:
	long long board = 0;
	long long player[2] = { 0 };
	byte currentPlayer;
	byte count[7] = { 0 };
public:
	Game(byte first) : currentPlayer(first) {}
	bool putStone(int column);
	void printBoard();
	bool endGame(); //��������
};

#endif //GAME_H