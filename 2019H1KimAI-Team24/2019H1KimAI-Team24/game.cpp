#include "game.h"
#include <cstdio>
#include <cstdlib>


void Game::debugPrint() {
	printf("\n  board: ");
	for (int i = 63; i >= 0; i--)
		putchar('0' + ((board >> i) & 1));
	printf("\nplayer1: ");
	for (int i = 63; i >= 0; i--)
		putchar('0' + ((player[FIRST] >> i) & 1));
	printf("\nplayer2: ");
	for (int i = 63; i >= 0; i--)
		putchar('0' + ((player[SECOND] >> i) & 1));
	printf("\n\n");
}

bool Game::putStone(int col) {
	if (board & pos(col, 5)) {
		return false; // 둘 수 없을때
	}
	board = board | (board + pos(col, 0));
	player[currentPlayer] = board ^ player[!currentPlayer];
	currentPlayer = !currentPlayer;
	return true;
}

void Game::printBoard() {
	printf("Player1 : O Player2 : X\n");
	for (int i = 5; i >= 0; i--) {
		printf("\n  ├─┼─┼─┼─┼─┼─┼─┤\n");
		printf("%d │", i + 1);
		for (int j = 0; j < 7; j++) {
			auto bit = pos(j, i);
			char t = (player[FIRST] & bit) ? 'O' : (player[SECOND] & bit) ? 'X' : ' ';
			printf("%c│", t);
		}
	}
	printf("\n  └─┴─┴─┴─┴─┴─┴─┘\n");
	printf("   1 2 3 4 5 6 7 \n");
}

bool Game::endGame() {
	long long mask;
	byte lastPlayer = !currentPlayer;
	mask = player[lastPlayer] & (player[lastPlayer] >> 1);
	if (mask & (mask >> 2)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 7);
	if (mask & (mask >> 14)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 8);
	if (mask & (mask >> 16)) {
		return true;
	}
	
	mask = player[lastPlayer] & (player[lastPlayer] >> 6);
	if (mask & (mask >> 12)) {
		return true;
	}
	return false;
}