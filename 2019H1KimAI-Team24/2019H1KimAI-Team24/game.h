#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <cstdio>

struct State {
#pragma region constants
	static constexpr b64 VALID  = 0b0111111011111101111110111111011111101111110111111;
	static constexpr b64 BOTTOM = 0b0000001000000100000010000001000000100000010000001;
#pragma endregion
#pragma region variable and operators for emulating long long
	b64 value;
	State(const b64 &v) : value(v) {}
	operator b64&() { return value; }
	operator b64() const { return value; }

#pragma endregion
#pragma region helper function
	// board�� top bit
	static constexpr b64 topBit(b64 board) {
		return (board + State::BOTTOM) & State::VALID;
	}

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
#pragma region constants
	static constexpr byte FST = 0, SND = 1, DRAW = 2, PLAYING = 4;

#pragma endregion
#pragma region variables
	byte step = 0;	// ������ �ܰ� -> 0 ~ 42
	byte turn = FST;	// ���� �� -> FST | SND
	State player1 = 0;	// player1�� ���� �� ��ġ (���� �ӵ��� ���� shallow copy�� �����ϵ��� ������)
	State player2 = 0;	// player2�� ���� �� ��ġ

#pragma endregion
#pragma region properties
	auto board() const { return (b64)player1 | player2; }	// board ���� ���� ���� �Ұ�
	auto& player(byte n) { return n ? player2 : player1; }	// player(FST) = ...; ���� ��� ����

#pragma endregion
#pragma region helper function
	// board�� player�� �޾� player�� ���� �Ͽ� �̱� �� �ִ� bit�� ����.
	static b64 winPosBit(b64 p, b64 b);
#pragma endregion
#pragma region method
	// column �ڸ��� �� ���� �� �ִ� �� ���� -> true | false
	bool puttable(int column) const {
		return !(board() & State::posBit(column, 5));
	}

	// ���� player�� ���� �Ͽ� ���� ���� bit�� ����.
	b64 safePutBit() {
		b64 nextPut = State::topBit(board());
		b64 losePos = winPosBit(player(!turn), board());
		if (auto losePut = nextPut & losePos) {
			if (losePut & (losePut - 1)) return 0;	// ���� ���� 2�� �̻��� ��
			else nextPut = losePut;
		}
		return nextPut & ~(losePos >> 1);	// ������ �̱� �� �ִ� �� ȸ��
	}

	// Game�� ���� ���¸� ���� -> NONE | FST | SND | DRAW
	byte state();

	// column �ڸ��� �� ���� ���� step�� Game�� ������
	Game putStone(int column);

	// Game ���� ���
	void print();

#pragma endregion
};

#endif //GAME_H