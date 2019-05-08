#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>
#include <thread>

#define NEG -1000000

// game�� ���� AI�� ���� ���� ���� ����.
int Ai::putStoneAI(Game game) {
	int result;
	if (game.step < 15) {
		putStoneHeruistic(game, result);
		printf("\n\nResult: %d ����\n\n", result + 1);
	}
	else {
		int pfResult;
		auto perfectThread = std::thread(&Ai::putStonePerfect, this, game, std::ref(pfResult));
		putStoneHeruistic(game, result);
		perfectThread.join();
		printf("\n\nResult: %d ����\n\n", result + 1);
	}
	return result;
}

void printResultArray(std::array<int, 7>& arr) {
	printf("[ ");
	for (int i = 0; i < 7; ++i) {
		if (i != 0) printf(", ");
		switch (arr[i]) {
		case INT_MIN: printf("   -"); break;
		case     NEG: printf("LOSE"); break;
		case    -NEG: printf(" WIN"); break;
		default: printf("%4d", arr[i]);
		}
	}
	puts("]");
}

// �� �� ��
void Ai::putStoneHeruistic(Game game, int& result) {
	int maxScore = NEG;
	std::array<int, 7> resultScore { INT_MIN, INT_MIN, INT_MIN , INT_MIN , INT_MIN , INT_MIN , INT_MIN };

	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ����
			Game nextGame = game.putStone(order[i]);
			int score = -getScoreHeuristic(nextGame, NEG, -maxScore, 1);
			if (maxScore < score) {
				maxScore = score;
				result = order[i];
			}
			printf("\nHeuristic Solver: [%d] = %d", order[i] + 1, score);
			resultScore[order[i]] = score;
		}
		//printf("%d : %d\n", i, maxScore);
	}
	printf("\n\nHeuristic Solution: ");
	printResultArray(resultScore);
}

void Ai::putStonePerfect(Game game, int& result) {
	int maxScore = NEG;
	std::array<int, 7> resultScore { INT_MIN, INT_MIN, INT_MIN , INT_MIN , INT_MIN , INT_MIN , INT_MIN };

	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// ���� state���� �� ������ ������ 7���� state�� ������ ���� ���� ���� ����
			Game nextGame = game.putStone(order[i]);
			int score = -getScorePerfect(nextGame, NEG, -maxScore);
			if (maxScore < score) {
				maxScore = score;
				result = order[i];
			}
			printf("\nPerfect Solver: [%d] = %d", order[i] + 1, score);
			resultScore[order[i]] = score;
		}
		//printf("%d : %d\n", i, maxScore);
	}
	printf("\n\nPerfect Solution: ");
	printResultArray(resultScore);
}

int Ai::getScoreHeuristic(Game g, int a, int b, int depth) {
	int score = -23, maxScore = 21 - (g.step + 1) / 2, val;

	if (g.state() != g.PLAYING) return NEG;				//���� ���� -1000000 return
	if (depth >= 13) return scoreFunction(g.player(g.turn)) - scoreFunction(g.player(!g.turn));

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}

	for (int i = 0; i < 7; i++) {
		if (g.puttable(order[i])) {
			Game tmpGame = g.putStone(order[i]);
			score = -getScoreHeuristic(tmpGame, -b, -a, depth + 1);
			if (b <= score) return score;
			if (a < score) a = score;

		}

	}
	return a;
}

int Ai::scoreFunction(b64 player) {
	int sum = 0;
	int dir[4] = { 1, 7, 6, 8 };
	int weight[3] = { 1, 10, 100 };				//����� ���� ������ ���� ����ġ
	int count[3] = { 0 };								//����� ��
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			b64 mask = State::posBit(j, i);
			if (mask & player) {
				for (int k = 0; k < 4; k++) {
					byte tmp = 0;
					for (int p = 1; p <= 2; p++) {
						if ((mask >> (dir[k] * p)) & player) {
							tmp++;
						}
						else {
							break;
						}
					}
					count[tmp]++;
				}
			}
		}
	}
	count[0] = count[0] - count[1] - count[2];
	count[1] = count[1] - count[2];

	for (int i = 0; i < 3; i++) {
		sum += weight[i] * count[i];
	}
	return sum;
}

// negamax Ž�� �Լ�
int Ai::getScorePerfect(Game game, int a, int b) {
	const auto state = game.state();
	if (state == game.DRAW) return 0; // ���
	if (state != game.PLAYING) return -(22 - (game.step + 1) / 2); //���� ����, 22 - �¸��� player�� �� �� ������ score.

	const int cachedScore = table.getValue(game.player(game.turn).value);
	const int maxScore = cachedScore ? (cachedScore + 99) : (21 - (game.step + 1) / 2);

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}

	// ���� ���� �̱� �� ������ �ٷ� ���� (�ڵ� �ߺ� ���� �ʿ���)
	for (int i = 0; i < NCOLUMN; i++)
		if (game.puttable(order[i]) && game.putStone(order[i]).state() == game.turn)
			return (22 - (game.step + 2) / 2);

	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {
			Game nextGame = game.putStone(order[i]);
			int score = -getScorePerfect(nextGame, -b, -a);		//putStone�� true�� ���
			if (b <= score) return score;				//score�� max���� ũ�� max�� ����
			if (a < score) a = score;

			//			printf("score = %d\n", score);
			//			system("pause");
		}
	}

	table.putValue(game.player(game.turn).value, a - 99);

	return a;
}
