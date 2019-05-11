#include "game.h"
#include <cstdio>
#include <cstdlib>

// board�� player�� �޾� player�� ���� �Ͽ� �̱� �� �ִ� bit�� ����.
b64 Game::winPosBit(b64 p, b64 b)
{
	b64 result = (p << 1) & (p << 2) & (p << 3);
	for (int i = -1; i <= 1; ++i) {
		b64 t = (p << (7 + i)) & (p << 2 * (7 + i));
		result |= (t & (p << 3 * (7 + i))) | (t & (p >> (7 + i)));
		t >>= 3 * (7 + i);
		result |= (t & (p >> 3 * (7 + i))) | (t & (p << (7 + i)));
	}
	return result & (b ^ State::VALID);
}

// Game�� ���� ���¸� ���� -> [NONE | FST | SND | DRAW]
byte Game::state() {
	byte lastTurn = !turn;
	auto playerState = player(lastTurn);
	constexpr int direction[] = { 1, 7, 8, 6 };

	for (int i = 0; i < 4; i++) {
		auto d = direction[i];
		auto mask = playerState & (playerState >> d);
		if (mask & (mask >> (2 * d)))
			return lastTurn;
	}

	if (step == 42)
		return DRAW;

	return PLAYING;
}

// column �ڸ��� �� ���� ���� step�� Game�� ������
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

// Game ���� ���
void Game::print() {
	printf(" (bitstate)              |--7-| |--6-| |--5-| |--4-| |--3-| |--2-| |--1-|");
	printf("\n  board: "); State::print(board());
	printf("\n player: "); State::print(player1);
	printf("\n     AI: "); State::print(player2);
	printf("\n\n------------------------- �÷��̾� = O / AI = X -------------------------\n");
	for (int i = 5; i >= 0; i--) {
		printf("\n                            %d |", i + 1);
		for (int j = 0; j < 7; j++) {
			auto bit = State::posBit(j, i);
			char t = (player1 & bit) ? 'O' : (player2 & bit) ? 'X' : '_';
			printf("% c|", t);
		}
	}
	printf("\n                               1 2 3 4 5 6 7 \n\n");
	printf("------------------------- %2hhd �ܰ�, %s ���� -------------------------\n\n", step, turn == FST ? "�÷��̾�" : "AI");
}
