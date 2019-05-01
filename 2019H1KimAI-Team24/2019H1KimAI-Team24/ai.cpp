#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>



int Ai::putStoneAI(Game game) {
	int maxScore = -50, put;
	

	for (int i=1; i <= 7; i++) {
		Game currentGame = game;
		currentGame.putStone(i-1);			// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ����
		int score = getScore(currentGame);

		printf("input = %d\n", score);
		system("pause");
		if (maxScore < score) {
			maxScore = score;
			put = i;
		}
	}
	//printf("input = %d\n", put);
	//system("pause");
	return put;
}

int Ai::getScore(Game g) {
	Game tmpGame = g;
	int score=0, maxScore = -23;

	if (tmpGame.endGame()) return 22 - (checkOne(tmpGame.board)+1) / 2; //���� ����, 22 - �¸��� player�� �� �� ������ score.
	if (tmpGame.board == 0b111111011111101111110111111011111101111110111111) return 0; // ���




	for (int i = 1; i <= 7; i++) {
		if(tmpGame.putStone(i-1))
			score = -getScore(tmpGame);						//putStone�� true�� ���
		if (maxScore < score) maxScore = score;				//score�� max���� ũ�� max�� ����
		
	}


	return maxScore;
}

int Ai::checkOne(long long n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}