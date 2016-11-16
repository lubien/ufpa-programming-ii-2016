#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct moves {
	int player;
	int x;
	int y;
	struct moves * next;
};

int board[3][3];
struct moves * move_list = NULL;

void add_move(struct moves ** move_list, int player, int x, int y) {
	struct moves * current = *move_list;

	struct moves * new_node = (struct moves *) malloc(sizeof(struct moves));
	new_node->player = player;
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;

	if (current == NULL) {
		*move_list = new_node;
	} else {
		struct moves * ref = *move_list;

		new_node->next = ref;

		*move_list = new_node;
		/* while (current->next != NULL) { */
		/* 	current = current->next; */
		/* } */

		/* current->next = new_node; */
	}
}

void render_wall() {
	printf("::::::::::::::::::::::::::\n");
}

void render_last_moves(struct moves * move_list) {
	struct moves * current = move_list;

	int i;

	render_wall();
	printf("::     Latest plays     ::\n");
	render_wall();

	for (i = 0; i < 5; i++) {
		if (current == NULL) {
			break;
		}

		printf("Player %i at (%i, %i)\n", current->player, current->x, current->y);
		current = current->next;
	}

	if (i == 0) {
		printf("-- No moves have been played --\n\n");
	}
}

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

	render_wall();
	printf("::        Field         ::\n");
	render_wall();

	int i, j;
	for (i = 2; i >= 0; i--) {
		printf("          ");
		for (j = 0; j < 3; j++) {
			printf("%c ", renderSquare(board[i][j]));
		}
		printf("\n");
	}

	printf("\n");
	render_last_moves(move_list);
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
		render_wall();
		printf("::        Prompt        ::\n");
		render_wall();

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
