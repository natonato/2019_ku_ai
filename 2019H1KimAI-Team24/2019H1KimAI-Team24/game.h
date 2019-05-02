#ifndef GAME_H
#define GAME_H

#include "common.h"

	Game() {}
	static constexpr byte FIRST = 0, SECOND = 1;
	byte currentPlayer;
	long long board = 0;
	long long player[2] = { 0 };

	static Game& instance() {
		static Game inst;
		return inst;
	}

	Game(byte cp, long long p1state, long long p2state) : currentPlayer(cp) {
		player[FIRST] = p1state;
		player[SECOND] = p2state;
		board = p1state | p2state;
	}
	Game(const Game &prev) {
		currentPlayer = prev.currentPlayer;
		board = prev.board;
		player[FIRST] = prev.player[FIRST];
		player[SECOND] = prev.player[SECOND];
	}
	Game& operator=(const Game &prev) {
		currentPlayer = prev.currentPlayer;
		board = prev.board;
		player[FIRST] = prev.player[FIRST];
		player[SECOND] = prev.player[SECOND];
	}
struct Game {

	bool putStone(int column);
	void printBoard();
	bool endGame(); //°¡¸Á¾øÀ½
	void debugPrint();

	long long pos(int col, int row) const {
		return 1LL << ((col * 7) + row);
	}
};

#endif //GAME_H