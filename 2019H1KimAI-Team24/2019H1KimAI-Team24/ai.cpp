#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>

// game을 보고 AI가 놓을 다음 수를 리턴.
int Ai::putStoneAI(Game game) {
	int maxScore = -23, put;
	
	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결정
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

// negamax 탐색 함수
int Ai::getScore(Game game, int a, int b) {
	//Game tmpGame = g;
	int score = -23;

	const auto state = game.state();
	if (state == game.DRAW) return 0; // 비김
	if (state != game.PLAYING) return -(22 - (game.step + 1) / 2); //게임 종료, 22 - 승리한 player가 둔 돌 갯수가 score.
	
	const int cachedScore = table.getValue(game.player(game.turn).value);
	const int maxScore = cachedScore ? (cachedScore + 99) : (21 - (game.step + 1) / 2);

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}
	
	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {
			Game nextGame = game.putStone(order[i]);
			score = -getScore(nextGame, -b, -a);		//putStone이 true면 재귀
			if (b <= score) return score;				//score가 max보다 크면 max로 저장
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
	if (g.board() == 0b111111011111101111110111111011111101111110111111) return 0; // 비김
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