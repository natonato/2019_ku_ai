#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>

// game�� ���� AI�� ���� ���� ���� ����.
int Ai::putStoneAI(Game game) {
	int maxScore = -23, put;
	
	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ����
			Game nextGame = game.putStone(order[i]);
			int score = - getScore(nextGame, -23, 23);
			//int score = tmpScore(nextGame, maxScore, 23, false);
			if (maxScore < score) {
				maxScore = score;
				put = order[i];
			}
		}
//		printf("%d : %d\n", i, maxScor);
		//system("pause");
	}
	return put;
}

// negamax Ž�� �Լ�
int Ai::getScore(Game game, int a, int b) {
	//Game tmpGame = g;
	int score = -23;

	const auto state = game.state();
	if (state == game.DRAW) return 0; // ���
	if (state != game.PLAYING) return -(22 - (game.step + 1) / 2); //���� ����, 22 - �¸��� player�� �� �� ������ score.
	
	const int cachedScore = table.getValue(game.player(game.turn).value);
	const int maxScore = cachedScore ? (cachedScore + 99) : (21 - (game.step + 1) / 2);

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}
	
	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {
			Game nextGame = game.putStone(order[i]);
			score = -getScore(nextGame, -b, -a);		//putStone�� true�� ���
			if (b <= score) return score;				//score�� max���� ũ�� max�� ����
			if (a < score) a = score;

//			printf("score = %d\n", score);
//			system("pause");
		}
	}

	table.putValue(game.player(game.turn).value, a - 99);

	return a;
}

int Ai::tmpScore(Game g, int a, int b, bool max) {
	int flag = -1;
	if (!max) {
		flag = 1;
	}
	if (g.state() != g.PLAYING) return flag * (22 - (g.step + 1) / 2);
	if (g.board() == 0b111111011111101111110111111011111101111110111111) return 0; // ���
	if (g.board() == 0b000000000000001111110111111011111101111110000000) return 0;
	if (max) {
		int maxScore = -23;
		for (int i = 0; i < 4; i++) {
			if (g.puttable(order[i])) {
				Game tmpGame = g.putStone(order[i]);
				int score = tmpScore(tmpGame, a, b, !max);
				if (maxScore < score) {
					maxScore = score;
				}
				if (a < maxScore) {
					a = maxScore;
				}
				if (a >= b) break;
			}
		}
		return maxScore;
	}
	else {
		int minScore = 23;
		for (int i = 0; i < 4; i++) {
			if (g.puttable(order[i])) {
				Game tmpGame = g.putStone(order[i]);
				int score = tmpScore(tmpGame, a, b, !max);
				if (minScore > score) {
					minScore = score;
				}
				if (b > minScore) {
					b = minScore;
				}
				if (a >= b) break;
			}
		}
		return minScore;
	}
}

int Ai::checkOne(long long n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}