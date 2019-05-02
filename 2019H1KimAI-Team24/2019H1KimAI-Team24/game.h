#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <cstdio>

struct State {
#pragma region variable and operators for emulating long long
	b64 value;
	State(const b64 &v) : value(v) {}
	operator b64&() { return value; }
	operator b64() const { return value; }

	static Game& instance() {
		static Game inst;
		return inst;
#pragma endregion
#pragma region helper function
	// (col, row) ï¿½ï¿½Ä¡ index
	static constexpr int posIdx(int col, int row) {
		return (col * 7) + row;
	}

	// (col, row) ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½Å¸ï¿½ï¿½ï¿½ï¿½ bitmask ï¿½ï¿½ï¿½ï¿½
	static constexpr b64 posBit(int col, int row) {
		return 1LL << posIdx(col, row);
	}

	// long longï¿½ï¿½ 64ï¿½Ú¸ï¿½ 2ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
	static void print(b64 state) {
		for (int i = 63; i >= 0; i--)
			putchar('0' + (char)((state >> i) & 1));
	}
#pragma endregion
#pragma region method
	// boardï¿½ï¿½ (col, row) ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½Ö´ï¿½ bit ï¿½ï¿½ï¿½ï¿½ 
	inline bool get(int col, int row) {
		return (value >> posIdx(col, row)) & 1;
	}

	// boardï¿½ï¿½ (col, row) ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	inline auto& set(int col, int row) {
		value = value | posBit(col, row);
		return *this;
	}
#pragma endregion
};

struct Game {
	byte step = 0;	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ü°ï¿½ -> 0 ~ 42
	byte turn = FST;	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ -> FST | SND
	State player1 = 0;	// player1ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½Ä¡ (ï¿½ï¿½ï¿½ï¿½ ï¿½Óµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ shallow copyï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ïµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
	State player2 = 0;	// player2ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½Ä¡

	bool putStone(int column);
	void printBoard();
	bool endGame(); //°¡¸Á¾øÀ½
	void debugPrint();

	long long pos(int col, int row) const {
		return 1LL << ((col * 7) + row);
	static constexpr byte FST = 0, SND = 1, DRAW = 2, PLAYING = 4;
	}
};

#endif //GAME_H