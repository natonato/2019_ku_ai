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
	// board의 top bit
	static constexpr b64 topBit(b64 board) {
		return (board + State::BOTTOM) & State::VALID;
	}

	// (col, row) 위치 index
	static constexpr int posIdx(int col, int row) {
		return (col * 7) + row;
	}

	// (col, row) 위치를 나타내는 bitmask 리턴
	static constexpr b64 posBit(int col, int row) {
		return 1LL << posIdx(col, row);
	}

	// long long을 64자리 2진수로 출력
	static void print(b64 state) {
		for (int i = 63; i >= 0; i--)
			putchar('0' + (char)((state >> i) & 1));
	}
#pragma endregion
#pragma region method
	// board의 (col, row) 위치에 있는 bit 리턴 
	inline bool get(int col, int row) {
		return (value >> posIdx(col, row)) & 1;
	}

	// board에 (col, row) 위치에 돌을 놓음
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
	byte step = 0;	// 진행한 단계 -> 0 ~ 42
	byte turn = FST;	// 현재 턴 -> FST | SND
	State player1 = 0;	// player1가 놓은 돌 위치 (복사 속도를 위해 shallow copy가 가능하도록 나눴음)
	State player2 = 0;	// player2가 놓은 돌 위치

#pragma endregion
#pragma region properties
	auto board() const { return (b64)player1 | player2; }	// board 값은 직접 갱신 불가
	auto& player(byte n) { return n ? player2 : player1; }	// player(FST) = ...; 같이 사용 가능

#pragma endregion
#pragma region helper function
	// board와 player를 받아 player가 다음 턴에 이길 수 있는 bit를 리턴.
	static b64 winPosBit(b64 p, b64 b);
#pragma endregion
#pragma region method
	// column 자리에 돌 놓을 수 있는 지 리턴 -> true | false
	bool puttable(int column) const {
		return !(board() & State::posBit(column, 5));
	}

	// 현재 player가 다음 턴에 지지 않을 bit를 리턴.
	b64 safePutBit() {
		b64 nextPut = State::topBit(board());
		b64 losePos = winPosBit(player(!turn), board());
		if (auto losePut = nextPut & losePos) {
			if (losePut & (losePut - 1)) return 0;	// 필패 수가 2개 이상일 때
			else nextPut = losePut;
		}
		return nextPut & ~(losePos >> 1);	// 상대방이 이길 수 있는 수 회피
	}

	// Game의 현재 상태를 리턴 -> NONE | FST | SND | DRAW
	byte state();

	// column 자리에 돌 놓은 다음 step의 Game을 리턴함
	Game putStone(int column);

	// Game 상태 출력
	void print();

#pragma endregion
};

#endif //GAME_H