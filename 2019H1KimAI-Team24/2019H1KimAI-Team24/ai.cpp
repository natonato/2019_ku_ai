#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>


int Ai::putStoneAI(Game game) {
	int maxScore = -23, put;
	

	for (int i=0; i < 7; i++) {
		if (game.puttable(order[i])) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ��
			Game currentGame = game.putStone(order[i]);
			int score = getScore(currentGame, -24, 24);

			if (maxScore < score) {
				maxScore = score;
				put = order[i];

			}

		}
	}
	return put;
}

int Ai::getScore(Game g, int a, int b) {
	//Game tmpGame = g;
	int score=-23, maxScore;

	if (g.state() != g.PLAYING) return 22 - (checkOne(g.board())+1) / 2; //���� ����, 22 - �¸��� player�� �� �� ������ score.
	if (g.board() == 0b111111011111101111110111111011111101111110111111) return 0; // ���
	if (g.board() == 0b000000000000000000000000000011111101111110111111) return 0;

	maxScore = 21 - (checkOne(g.board()) + 1) / 2;
	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}


	for (int i = 0; i < 4; i++) {
		if (g.puttable(order[i])) {
			Game tmpGame = g.putStone(order[i]);
			score = -getScore(tmpGame, -b, -a);						//putStone�� true�� ���
			if (b <= score) return score;				//score�� max���� ũ�� max�� ����
			if (a < score) a = score;

//			printf("score = %d\n", score);
//			system("pause");
		}
		
	}
	

	return a;
}

int Ai::checkOne(long long n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}