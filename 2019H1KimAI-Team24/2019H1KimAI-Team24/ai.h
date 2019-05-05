#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"

class Ai {
public:
	int putStoneAI(Game game);
	int getScore(Game game, int a, int b);
	int checkOne(long long a);
	int tmpScore(Game, int, int, bool);
	int order[7] = { 3,2,4,1,5,0,6 };
	Cache table = Cache();
};


#endif //AI_H