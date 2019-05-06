#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"

class Ai {
public:
	// game�� ���� AI�� ���� ���� ���� ����.
	int putStoneAI(Game game);

private:
	// negamax Ž�� �Լ�
	int getScore(Game game, int a, int b);

	int checkOne(long long a);
	int tmpScore(Game, int, int, bool);

	// Ž�� ����
	int order[7] = { 3, 2, 4, 1, 5, 0, 6 };
	
	// score ĳ��
	Cache table;
};


#endif //AI_H