#ifndef AI_H
#define AI_H

#include "common.h"
#include "cache.h"

class Ai {
public:
	int putStoneAI(Game game);
	int getScoreHeuristic(Game g, int a, int b, int depth);
	int getScorePerpect(Game g, int a, int b);
	int scoreFunction(b64 g);

	int order[7] = { 3,2,4,1,5,0,6 };
	Cache table = Cache();
};


#endif //AI_H