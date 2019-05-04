#ifndef AI_H
#define AI_H

#include "common.h"

class Ai {
public:
	int putStoneAI(Game game);
	int getScore(Game game, int a, int b);
	int checkOne(long long a);

	int order[7] = { 4,3,5,2,6,1,7 };

};


#endif //AI_H