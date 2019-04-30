#include "game.h"
#include <cstdio>
#include <cstdlib>

Game::Game(int first) {
	this->board = 0;
	this->currentPlayer = first;
	this->printBoard();
}

void Game::putStone(int col) {
	if (count[col] >= 7) {
		printBoard();
		printf("%d은 둘 수 없는 곳입니다.\n", col);
		return;
	}
	board = board | (board + (1 << (col * 7)));
	player[currentPlayer] = board ^ player[1 - currentPlayer];
	currentPlayer = 1 - currentPlayer;
	count[col]++;
	printBoard();
}

void Game::printBoard() {
	system("cls");
	printf("Player1 : O Player2 : X\n");
	printf("  --------------\n");
	for (int i = 5; i >= 0; i--) {
		long long bit = 1 << i;
		printf("%d |", i + 1);
		for (int j = 0; j < 7; j++) {
			char t = ' ';
			if (player[0] & bit) {
				t = 'O';
			}
			else if (player[1] & bit) {
				t = 'X';
			}
			printf("%c", t);
			printf("|");
			bit <<= 7;
		}
		printf("\n  --------------\n");
	}
	printf("   1 2 3 4 5 6 7 \n");
}