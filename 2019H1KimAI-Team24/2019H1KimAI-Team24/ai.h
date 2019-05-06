#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"
#include <array>

class Ai {
public:
	// game�� ���� AI�� ���� ���� ���� ����.
	int putStoneAI(Game game);

private:
	// negamax Ž�� �Լ�
	int getScoreHeuristic(Game game, int a, int b, int depth);
	int getScorePerfect(Game game, int a, int b);

	// �޸���ƽ score ���
	int scoreFunction(b64 game);

	// Ž�� ����
	int order[7] = { 3, 2, 4, 1, 5, 0, 6 };
	
	// score ĳ��
	Cache table;
};


#endif //AI_H