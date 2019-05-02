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
	}
};

#endif //GAME_H