#include "game.h"
#include <cstdio>
#include <cstdlib>

// Game의 현재 상태를 리턴 -> [NONE | FST | SND | DRAW]
byte Game::state() {
	if (board() == 0b111111011111101111110111111011111101111110111111)
		return DRAW;

	byte lastTurn = !turn;
	auto playerState = player(lastTurn);
	constexpr int direction[] = { 1, 7, 8, 6 };

	for (int i = 0; i < 4; i++) {
		auto d = direction[i];
		auto mask = playerState & (playerState >> d);
		if (mask & (mask >> (2 * d)))
			return lastTurn;
	}

	return PLAYING;
}

// column 자리에 돌 놓은 다음 step의 Game을 리턴함
Game Game::putStone(int column) {
	auto b = board();
	b = b | (b + State::posBit(column, 0));
	return Game {
		(byte)(step + 1),
		!turn,
		turn == FST ? b ^ player2 : (b64)player1,
		turn == SND ? b ^ player1 : (b64)player2
	};
}

// Game 상태 출력
void Game::print() {
	printf("(bitstate)               |--6-| |--5-| |--4-| |--3-| |--2-| |--1-| |--0-|");
	printf("\n  board: "); State::print(board());
	printf("\nplayer1: "); State::print(player1);
	printf("\nplayer2: "); State::print(player2);
	printf("\n\n----------------------- Player1 = O / Player2 = X -----------------------\n");
	for (int i = 5; i >= 0; i--) {
		printf("\n                            %d │", i);
		for (int j = 0; j < 7; j++) {
			auto bit = State::posBit(j, i);
			char t = (player1 & bit) ? 'O' : (player2 & bit) ? 'X' : '_';
			printf("% c│", t);
		}
	}
	printf("\n                               0 1 2 3 4 5 6 \n\n");
	printf("------------------------- %2hhd 단계, player%hhd 차례 -------------------------\n\n", step, turn + 1);
}