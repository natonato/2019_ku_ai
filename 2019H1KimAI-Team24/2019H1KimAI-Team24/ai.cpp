#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>



int Ai::putStoneAI(Game game) {
	int maxScore = -23, put;
	

	for (int i=1; i <= 7; i++) {
		Game currentGame = game;
		if (currentGame.putStone(i - 1)) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ��
			int score = getScore(currentGame);

			if (maxScore < score) {
				maxScore = score;
				put = i;

			}
		}
	}
	return put;
}

int Ai::getScore(Game g) {
	//Game tmpGame = g;
	int score=-23, maxScore = -23;

	if (g.endGame()) return 22 - (checkOne(g.board)+1) / 2; //���� ����, 22 - �¸��� player�� �� �� ������ score.
	if (g.board == 0b111111011111101111110111111011111101111110111111) return 0; // ���




	for (int i = 1; i <= 3; i++) {
		Game tmpGame = g;
		if (tmpGame.putStone(i - 1)) {
			score = -getScore(tmpGame);						//putStone�� true�� ���
			if (maxScore < score) maxScore = score;				//score�� max���� ũ�� max�� ����


			printf("score = %d\n", score);
			system("pause");
		}
		
	}
	

	return maxScore;
}

int Ai::checkOne(long long n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}