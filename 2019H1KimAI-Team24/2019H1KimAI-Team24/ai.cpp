#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>



int Ai::putStoneAI(Game game) {
	int maxScore = -23, put;
	

	for (int i=0; i < 7; i++) {
		if (game.puttable(i)) {		// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결
			Game currentGame = game.putStone(i);
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

	if (g.state() != g.PLAYING) return 22 - (checkOne(g.board())+1) / 2; //게임 종료, 22 - 승리한 player가 둔 돌 갯수가 score.
	if (g.board() == 0b111111011111101111110111111011111101111110111111) return 0; // 비김




	for (int i = 0; i < 3; i++) {
		if (g.puttable(i)) {
			Game tmpGame = g.putStone(i);
			score = -getScore(tmpGame);						//putStone이 true면 재귀
			if (maxScore < score) maxScore = score;				//score가 max보다 크면 max로 저장


//			printf("score = %d\n", score);
//			system("pause");
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