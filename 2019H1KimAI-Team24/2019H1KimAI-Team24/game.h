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
	// (col, row) ��ġ index
	static constexpr int posIdx(int col, int row) {
		return (col * 7) + row;
	}

	// (col, row) ��ġ�� ��Ÿ���� bitmask ����
	static constexpr b64 posBit(int col, int row) {
		return 1LL << posIdx(col, row);
	}

	// long long�� 64�ڸ� 2������ ���
	static void print(b64 state) {
		for (int i = 63; i >= 0; i--)
			putchar('0' + (char)((state >> i) & 1));
	}
#pragma endregion
#pragma region method
	// board�� (col, row) ��ġ�� �ִ� bit ���� 
	inline bool get(int col, int row) {
		return (value >> posIdx(col, row)) & 1;
	}

	// board�� (col, row) ��ġ�� ���� ����
	inline auto& set(int col, int row) {
		value = value | posBit(col, row);
		return *this;
	}
#pragma endregion
};

struct Game {
	byte step = 0;	// ������ �ܰ� -> 0 ~ 42
	byte turn = FST;	// ���� �� -> FST | SND
	State player1 = 0;	// player1�� ���� �� ��ġ (���� �ӵ��� ���� shallow copy�� �����ϵ��� ������)
	State player2 = 0;	// player2�� ���� �� ��ġ

	bool putStone(int column);
	void printBoard();
	bool endGame(); //��������
	void debugPrint();

	long long pos(int col, int row) const {
		return 1LL << ((col * 7) + row);
	static constexpr byte FST = 0, SND = 1, DRAW = 2, PLAYING = 4;
	}
};

#endif //GAME_H