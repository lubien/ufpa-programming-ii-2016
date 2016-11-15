#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int board[3][3];

void clearScreen() {
	printf("\e[1;1H\e[2J");
}

char renderSquare(int square) {
	if (square == 0) {
		return '.';
	} else if (square == 1) {
		return 'O';
	}
	return 'X';
}

void render() {
	clearScreen();
	int i, j;
	for (i = 2; i >= 0; i--) {
		for (j = 0; j < 3; j++) {
			printf("%c ", renderSquare(board[i][j]));
		}
		printf("\n");
	}
}

int validMove(int x, int y) {
	if (x > 3 || y > 3) {
		printf("Out of the board;\n");
		return 0;
	} else if (board[y - 1][x - 1] != 0) {
		printf("Already being used.\n");
		return 0;
	}

	return 1;
}

void askMove(int player) {
	int x, y;
	do {
		printf("What's your move, Player %i?\n", player);

		printf("X:\n");
		scanf("%i", &x);

		printf("Y:\n");
		scanf("%i", &y);
	} while (!validMove(x, y));

	board[y - 1][x - 1] = player;
}

int won(int p) {
	if (
			board[0][0] == p &&
			board[0][1] == p &&
			board[0][2] == p
		 ) {
		return 1;
	} else if (
			board[1][0] == p &&
			board[1][1] == p &&
			board[1][2] == p
		 ) {
		return 1;
	} else if (
			board[2][0] == p &&
			board[2][1] == p &&
			board[2][2] == p
		 ) {
		return 1;
	} else if (
			board[0][0] == p &&
			board[1][0] == p &&
			board[2][0] == p
		 ) {
		return 1;
	} else if (
			board[0][1] == p &&
			board[1][1] == p &&
			board[2][1] == p
		 ) {
		return 1;
	} else if (
			board[0][2] == p &&
			board[1][2] == p &&
			board[2][2] == p
		 ) {
		return 1;
	} else if (
			board[0][0] == p &&
			board[1][1] == p &&
			board[2][2] == p
		 ) {
		return 1;
	} else if (
			board[0][2] == p &&
			board[1][1] == p &&
			board[2][0] == p
		 ) {
		return 1;
	}

	return 0;
}

int someoneWon() {
	if (won(1)) {
		printf("Player 1 won.\n");
		return 1;
	} else if (won(2)) {
		printf("Player 2 won.\n");
		return 1;
	}

	return 0;
}

int main() {
	do {
		render();

		askMove(1);
		render();

		if (someoneWon()) {
			return 0;
		}

		askMove(2);
	} while (!someoneWon());

	return 0;
}
