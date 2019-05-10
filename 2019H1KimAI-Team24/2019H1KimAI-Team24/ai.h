#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"
#include <array>
#include <atomic>

class Ai {
public:
	// game�� ���� AI�� ���� ���� ���� ����.
	int putStoneAI(Game game);

private:
	// �� �� ��
	void putStoneHeruistic(Game game, int& result);
	void putStonePerfect(Game game, int& result);

	// negamax Ž�� �Լ�
	int getScoreHeuristic(Game game, int a, int b, int depth);
	int getScorePerfect(Game game, int a, int b);

	// �޸���ƽ score ���
	int scoreFunction(b64 player);
	int scoreFunction2(b64 player, b64 board);

	// Ž�� ����
	int order[7] = { 3, 2, 4, 1, 5, 0, 6 };

	// score ĳ��
	Cache table;

	// thread flag
	std::atomic<bool> thTimeout;
};

#endif //AI_H