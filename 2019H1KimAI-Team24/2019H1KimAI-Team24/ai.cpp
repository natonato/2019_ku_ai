#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>

// game을 보고 AI가 놓을 다음 수를 리턴.
int Ai::putStoneAI(Game game) {
	int maxScore = -1000000, put;
	
	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결정
			Game nextGame = game.putStone(order[i]);
			int score = -getScoreHeuristic(nextGame, -1000000, -maxScore, 1);
			if (maxScore < score) {
				maxScore = score;
				put = order[i];
			}
		}
		//printf("%d : %d\n", i, maxScore);
	}
	return put;
}

int Ai::getScoreHeuristic(Game g, int a, int b, int depth) {
	int score = -23, maxScore = 21 - (g.step + 1) / 2, val;

	if (g.state() != g.PLAYING) return -100000;				//게임 종료 -100000 return
	if (depth >= 13) return scoreFunction(g.player(g.turn)) - scoreFunction(g.player(!g.turn));

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}

	for (int i = 0; i < 7; i++) {
		if (g.puttable(order[i])) {
			Game tmpGame = g.putStone(order[i]);
			score = -getScoreHeuristic(tmpGame, -b, -a, depth + 1);
			if (b <= score) return score;
			if (a < score) a = score;

		}

	}
	return a;
}

int Ai::scoreFunction(b64 player) {
	int sum = 0;
	int dir[4] = { 1, 7, 6, 8 };
	int weight[3] = { 1, 10, 100 };				//연결된 돌의 갯수에 대한 가중치
	int count[3] = { 0 };								//경우의 수
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

// negamax 탐색 함수
int Ai::getScorePerfect(Game game, int a, int b) {
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
