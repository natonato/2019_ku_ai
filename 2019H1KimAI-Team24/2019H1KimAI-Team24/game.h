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

#pragma endregion
#pragma region helper function
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
#pragma region method
	// column 자리에 돌 놓을 수 있는 지 리턴 -> true | false
	bool puttable(int column) const {
		return !(board() & State::posBit(column, 5));
	}

	// Game의 현재 상태를 리턴 -> NONE | FST | SND | DRAW
	byte state();

	// column 자리에 돌 놓은 다음 step의 Game을 리턴함
	Game putStone(int column);

	// Game 상태 출력
	void print();

#pragma endregion
#pragma region constructor
	// 현재 게임 상태, 전역 변수
	static Game& current() {
		static Game _current;
		return _current;
	}

#pragma endregion
};

#endif //GAME_H