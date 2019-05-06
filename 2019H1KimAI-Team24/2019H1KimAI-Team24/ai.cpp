#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>


int Ai::putStoneAI(Game game) {
	int maxScore = -1000000, put;
	

	for (int i=0; i < 7; i++) {
		if (game.puttable(order[i])) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ��
			Game currentGame = game.putStone(order[i]);
			int score = -getScore(currentGame, -1000000, -maxScore, 1);
			//int score = tmpScore(currentGame, maxScore, 23, false);
			if (maxScore < score) {
				maxScore = score;
				put = order[i];

			}

		}
		printf("%d : %d\n", i, maxScore);
		//system("pause");
	}
	return put;
}

int Ai::getScore(Game g, int a, int b, int depth) {
	//Game tmpGame = g;
	int score = -23, maxScore = 21 - (g.step + 1) / 2, val;

	if (g.state() != g.PLAYING) return -100000; //���� ����, 22 - �¸��� player�� �� �� ������ score.
	if (depth >= 13) return heuristicValue(g);

	//if (g.board() == 0b111111011111101111110111111011111101111110111111) return 0; // ���
	//if (g.board() == 0b000000000000001111110111111011111101111110000000) return 0;
	
/*	if (val = table.getValue(g.turn ? g.player2.value : g.player1.value)) {
		maxScore = val + 99;
	}
	else {
		maxScore = 21 - (g.step + 1) / 2;
	}*/


	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}


	for (int i = 0; i < 7; i++) {
		if (g.puttable(order[i])) {
			Game tmpGame = g.putStone(order[i]);
			score = -getScore(tmpGame, -b, -a, depth + 1);						//putStone�� true�� ���
			if (b <= score) return score;				//score�� max���� ũ�� max�� ����
			if (a < score) a = score;

//			printf("score = %d\n", score);
//			system("pause");
		}
		
	}
//	table.putValue(g.player(g.turn) ? g.player2.value : g.player1.value, a - 99);

	return a;
}

int Ai::heuristicValue(Game g) {
	return scoreFunction(g.player(g.turn)) - scoreFunction(g.player(!g.turn));
}

int Ai::scoreFunction(b64 player) {
	int sum = 0;
	int dir[4] = { 1, 7, 6, 8 };
	int weight[3] = { 1, 10, 100};				//����� ���� ������ ���� ����ġ
	int count[3] = { 0 };								//����� ��
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			b64 mask = State::posBit(j, i);
			if (mask & player) {
				for (int k = 0; k < 4; k++) {
					byte tmp = 0;
					for (int p = 1; p <= 2; p++) {
						if ((mask >> (dir[k] * p)) & player) {
							tmp++;
						}
						else {
							break;
						}
					}
					count[tmp]++;
				}
			}
		}
	}
	count[0] = count[0] - count[1] - count[2];
	count[1] = count[1] - count[2];

	for (int i = 0; i < 3; i++) {
		sum += weight[i] * count[i];
	}
	return sum;
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

int Ai::checkOne(b64 n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}