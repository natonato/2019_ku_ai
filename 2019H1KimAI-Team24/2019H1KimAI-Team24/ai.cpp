#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

#define NEG -1000000

// game을 보고 AI가 놓을 다음 수를 리턴.
int Ai::putStoneAI(Game game) {
	int result;
	if (false) {
	//if (game.step < 15) {
		putStoneHeruistic(game, result);
		printf("\n\nResult: %d 선택\n\n", result + 1);
	}
	else {
		int pfResult;
		thTimeout = false;
		auto timerThread = std::thread([this](){
			auto end = std::chrono::system_clock::now() + std::chrono::seconds(110);
			while (!thTimeout) {
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				auto now = std::chrono::system_clock::now();
				if (now >= end)
					thTimeout = true;
			}
		});
		auto pfThread = std::thread(&Ai::putStonePerfect, this, game, std::ref(pfResult));
		putStoneHeruistic(game, result);
		pfThread.join();
		if (!thTimeout) {
			result = pfResult;
			thTimeout = true;
		} 
		else {
			printf("\nPerfect solver 시간초과, Heuristic 선택\n");
		}
		printf("\n\nResult: %d 선택\n\n", result + 1);
		timerThread.join();
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

// 나 눈 다
void Ai::putStoneHeruistic(Game game, int& result) {
	int maxScore = NEG;
	std::array<int, 7> resultScore { INT_MIN, INT_MIN, INT_MIN , INT_MIN , INT_MIN , INT_MIN , INT_MIN };

	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {		// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결정
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
		if (game.puttable(order[i])) {		// 현재 state에서 각 열별로 진행한 7개의 state의 점수를 보고 어디로 갈지 결정
			Game nextGame = game.putStone(order[i]);
			int score = -getScorePerfect(nextGame, NEG, -maxScore);
			if (maxScore < score) {
				maxScore = score;
				result = order[i];
			}
			if (thTimeout) return;
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

	if (g.state() != g.PLAYING) return NEG;				//게임 종료 -1000000 return
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

int Ai::scoreFunction2(b64 player, b64 board) {
	int cnt;
	int weight[3] = { 1, 10, 100 }, connect[4] = { 0 };
	int sum = 0;
	//가로
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cnt = 0;
			for (int k = 0; k < 4; k++) {
				b64 bit = State::posBit(j + k, i);
				if (!(player & bit)) {
					if (board & bit) {
						cnt = -1;
						break;
					}
				}
				else {
					cnt++;
				}
			}
			if (cnt > 0) {
				connect[cnt - 1]++;
			}
		}
	}
	//세로
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			cnt = 0;
			for (int k = 0; k < 4; k++) {
				b64 bit = State::posBit(j, i + k);
				if (!(player & bit)) {
					if (board & bit) {
						cnt = -1;
						break;
					}
				}
				else {
					cnt++;
				}
			}
			if (cnt > 0) {
				connect[cnt - 1]++;
			}
		}
	}
	//우하단 대각선
	for (int i = 3; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cnt = 0;
			for (int k = 0; k < 4; k++) {
				b64 bit = State::posBit(j + k, i - k);
				if (!(player & bit)) {
					if (board & bit) {
						cnt = -1;
						break;
					}
				}
				else {
					cnt++;
				}
			}
			if (cnt > 0) {
				connect[cnt - 1]++;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			cnt = 0;
			for (int k = 0; k < 4; k++) {
				b64 bit = State::posBit(j + k, i + k);
				if (!(player & bit)) {
					if (board & bit) {
						cnt = -1;
						break;
					}
				}
				else {
					cnt++;
				}
			}
			if (cnt > 0) {
				connect[cnt - 1]++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		sum += connect[i] * weight[i];
	}
	return sum;
}

int Ai::scoreFunction(b64 player) {
	int sum = 0;
	int dir[4] = { 1, 7, 6, 8 };
	int weight[3] = { 1, 10, 100 };				//연결된 돌의 갯수에 대한 가중치
	int count[3] = { 0 };								//경우의 수
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

// negamax 탐색 함수
int Ai::getScorePerfect(Game game, int a, int b) {
	if (thTimeout) return a;

	const auto state = game.state();
	if (state == game.DRAW) return 0; // 비김
	if (state != game.PLAYING) return -(22 - (game.step + 1) / 2); //게임 종료, 22 - 승리한 player가 둔 돌 갯수가 score.

	const int cachedScore = table.getValue(game.player(game.turn).value);
	const int maxScore = cachedScore ? (cachedScore + 99) : (21 - (game.step + 1) / 2);

	if (b > maxScore) {
		b = maxScore;
		if (a >= b) return b;
	}

	// 다음 수에 이길 수 있으면 바로 리턴 (코드 중복 제거 필요함)
	for (int i = 0; i < NCOLUMN; i++)
		if (game.puttable(order[i]) && game.putStone(order[i]).state() == game.turn)
			return (22 - (game.step + 2) / 2);

	for (int i = 0; i < NCOLUMN; i++) {
		if (game.puttable(order[i])) {
			Game nextGame = game.putStone(order[i]);
			int score = -getScorePerfect(nextGame, -b, -a);		//putStone이 true면 재귀
			if (thTimeout) return a;
			if (b <= score) return score;				//score가 max보다 크면 max로 저장
			if (a < score) a = score;

			//			printf("score = %d\n", score);
			//			system("pause");
		}
	}

	table.putValue(game.player(game.turn).value, a - 99);

	return a;
}
