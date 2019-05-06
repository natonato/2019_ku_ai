#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"
#include <array>

class Ai {
public:
	// game을 보고 AI가 놓을 다음 수를 리턴.
	int putStoneAI(Game game);

private:
	// negamax 탐색 함수
	int getScoreHeuristic(Game game, int a, int b, int depth);
	int getScorePerfect(Game game, int a, int b);

	// 휴리스틱 score 계산
	int scoreFunction(b64 game);

	// 탐색 순서
	int order[7] = { 3, 2, 4, 1, 5, 0, 6 };
	
	// score 캐시
	Cache table;
};


#endif //AI_H