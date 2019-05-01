#include "game.h"
#include <cstdio>
#include <cstdlib>


bool Game::putStone(int col) {
	if (board & (1LL << ((col * 7) + 5))) {
		return false; // 둘 수 없을때
	}
	board = board | (board + (1LL << (col * 7)));
	player[currentPlayer] = board ^ player[!currentPlayer];
	currentPlayer = !currentPlayer;
	return true;
}

void Game::printBoard() {
	printf("Player1 : O Player2 : X\n");
	for (int i = 5; i >= 0; i--) {
		printf("\n  ├─┼─┼─┼─┼─┼─┼─┤\n");
		long long bit = 1LL << i;
		printf("%d │", i + 1);
		for (int j = 0; j < 7; j++) {
			char t = ' ';
			if (player[0] & bit) {
				t = 'O';
			}
			else if (player[1] & bit) {
				t = 'X';
			}
			printf("%c", t);
			printf("│");
			bit <<= 7;
		}
	}
	printf("\n  └─┴─┴─┴─┴─┴─┴─┘\n");
	printf("   1 2 3 4 5 6 7 \n");
}

bool Game::endGame() {
	long long mask;
	int lastPlayer = 1 - currentPlayer;
	mask = player[lastPlayer] & (player[lastPlayer] >> 1);
	if (mask & (mask >> 2)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] << 1);
	if (mask & (mask << 2)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 7);
	if (mask & (mask >> 14)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] << 7);
	if (mask & (mask << 14)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 8);
	if (mask & (mask >> 16)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] << 8);
	if (mask & (mask << 16)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 6);
	if (mask & (mask >> 12)) {
		return true;
	}

	mask = player[lastPlayer] & (player[lastPlayer] << 6);
	if (mask & (mask << 12)) {
		return true;
	}
	return false;
}