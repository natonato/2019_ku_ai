#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>



int Ai::putStoneAI(Game game) {
	int maxScore = -50, put;
	

	for (int i=1; i <= 7; i++) {
		Game currentGame = game;
		currentGame.putStone(i-1);			// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결정
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

	if (tmpGame.endGame()) return 22 - (checkOne(tmpGame.board)+1) / 2; //게임 종료, 22 - 승리한 player가 둔 돌 갯수가 score.
	if (tmpGame.board == 0b111111011111101111110111111011111101111110111111) return 0; // 비김




	for (int i = 1; i <= 7; i++) {
		if(tmpGame.putStone(i-1))
			score = -getScore(tmpGame);						//putStone이 true면 재귀
		if (maxScore < score) maxScore = score;				//score가 max보다 크면 max로 저장
		
	}


	return maxScore;
}

int Ai::checkOne(long long n) {
	int i;
	for (i = 0; n != 0; i++)
		n &= (n - 1);
	return i;
}