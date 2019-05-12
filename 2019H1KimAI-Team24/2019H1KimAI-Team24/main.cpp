#include "game.h"
#include "ai.h"
#include <cstdio>
#include <cstdlib>

extern const char * crazy_human_text;

int main() {
	puts(crazy_human_text);

	char ibuf[100];
	int input = 0;
	
	Game game;
	Ai ai;

	while (true) {
		printf("선공 입력 (플레이어 = 0, AI = 1): ");
		fgets(ibuf, sizeof(ibuf), stdin);
		if (sscanf(ibuf, "%d", &input) != 1)
			printf("입력값 오류: 숫자가 아님\n");
		else if (input != 0 && input != 1)
			printf("입력값 오류: 범위를 벗어남\n");
		else
			break;
	}

	if (input) {	// AI가 선일 때
		game.turn = Game::SND;
		game = game.putStone(2);
	}

	while (true) {
		system("cls");
		
		game.print();
		if (game.state() != Game::PLAYING)
			break;
		
		try {
			if (game.turn == Game::FST) {
				printf("돌을 놓을 위치 입력 (1 ~ 7) : ");
				fgets(ibuf, sizeof(ibuf), stdin);
				if (sscanf(ibuf, "%d", &input) != 1)
					throw 'n';	// 입력값 오류: 숫자가 아님
				input--;
				if (input < 0 || 6 < input)
					throw 'r';	// 입력값 오류: 범위를 벗어남
				if (game.step == 0 && input == 3)
					throw 'f';	// 선공은 첫 수를 4에 둘 수 없음
				if (!game.puttable(input))
					throw 'v';	// 더 이상 둘 수 없음
			}
			else {
				printf("AI가 진행중...\n");
				input = ai.putStoneAI(game);
				system("pause");
			}
			game = game.putStone(input);
		}
		catch (char e) {
			switch (e) {
			case 'n':
				printf("입력값 오류: 숫자가 아님\n"); 
				break;
			case 'r':
				printf("입력값 오류: 범위를 벗어남\n");
				break;
			case 'f':
				printf("선공은 첫 수를 4에 둘 수 없음\n");
				break;
			case 'v':
				printf("%d에 더 이상 둘 수 없음\n", input); 
				break;
			}
			system("pause");
		}
		fflush(stdin);
	}

	auto st = game.state();
	printf("\n\n%s\n", st == Game::FST ? "플레이어 승" : st == Game::SND ? "AI 승" : "무승부");
	system("pause");

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
