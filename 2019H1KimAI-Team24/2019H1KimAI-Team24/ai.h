#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"

class Ai {
public:
	int putStoneAI(Game game);
	int getScore(Game game, int a, int b, int depth);
	int checkOne(b64 a);
	int tmpScore(Game g, int a, int b, bool max);
	int scoreFunction(b64 g);
	int order[7] = { 3,2,4,1,5,0,6 };
	int heuristicValue(Game g);
	Cache table = Cache();
};


#endif //AI_H