#ifndef GAME_H
#define GAME_H

#include "common.h"

	static constexpr byte FIRST = 0, SECOND = 1;

	static Game& instance() {
		static Game inst;
		return inst;
	}

	}
	}
	}
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
	}
};

#endif //GAME_H