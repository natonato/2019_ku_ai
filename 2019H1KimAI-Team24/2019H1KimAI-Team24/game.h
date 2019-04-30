class Game {
private:
	long long board, player[2] = { 0 };
	int currentPlayer, count[7] = { 0 };
	void printBoard();
public:
	Game(int);
	void putStone(int);
};