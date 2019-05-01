#include "game.h"
#include <cstdio>
#include <cstdlib>


bool Game::putStone(int col) {
	if (count[col] >= 6) {
		return false; // 둘 수 없을때
	}
	board = board | (board + (1LL << (col * 7)));
	player[currentPlayer] = board ^ player[!currentPlayer];
	currentPlayer = !currentPlayer;
	count[col]++;
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