#include<stdio.h>
#include<stdlib.h>

#define BASE 64

typedef enum { UL = 1, UR, BL, BR, ERROR } type;

int board[BASE][BASE] = { 0 };

bool check_coordinate(int c, int min, int max) {
	return c >= min && c <= max;
}

type get_sub_region_type(int x, int y, int min_x, int max_x, int min_y, int max_y) {
	if (!check_coordinate(x, min_x, max_x) || !check_coordinate(y, min_y, max_y)) {
		return ERROR;
	}
	bool is_left = y <= (min_y + max_y) / 2;
	bool is_up = x <= (min_x + max_x) / 2;
	return type(!is_up * 2 + !is_left + 1);
}

void cover_board(int target_x, int target_y, int min_x, int max_x, int min_y, int max_y) {
	type region = get_sub_region_type(target_x, target_y, min_x, max_x, min_y, max_y);
	if (max_x - min_x == 1) {
		switch (region) {
		case UL:
			board[target_x][target_y + 1] = board[target_x + 1][target_y] = board[target_x + 1][target_y + 1] = BR;
			break;
		case UR:
			board[target_x][target_y - 1] = board[target_x + 1][target_y - 1] = board[target_x + 1][target_y] = BL;
			break;
		case BL:
			board[target_x - 1][target_y] = board[target_x - 1][target_y + 1] = board[target_x][target_y + 1] = UR;
			break;
		case BR:
			board[target_x - 1][target_y - 1] = board[target_x][target_y - 1] = board[target_x - 1][target_y] = UL;
			break;
		case ERROR:
		default:
			printf("Error\n");
		}
		return;
	}
	int half_x = (min_x + max_x) / 2;
	int half_y = (min_y + max_y) / 2;
	switch (region) {
	case UL:
		board[half_x][half_y + 1] = board[half_x + 1][half_y] = board[half_x + 1][half_y + 1] = BR;
		cover_board(target_x, target_y, min_x, half_x, min_y, half_y);
		cover_board(half_x, half_y + 1, min_x, half_x, half_y + 1, max_y);
		cover_board(half_x + 1, half_y, half_x + 1, max_x, min_y, half_y);
		cover_board(half_x + 1, half_y + 1, half_x + 1, max_x, half_y + 1, max_y);
		break;
	case UR:
		board[half_x][half_y] = board[half_x + 1][half_y] = board[half_x + 1][half_y + 1] = BL;
		cover_board(half_x, half_y, min_x, half_x, min_y, half_y);
		cover_board(target_x, target_y, min_x, half_x, half_y + 1, max_y);
		cover_board(half_x + 1, half_y, half_x + 1, max_x, min_y, half_y);
		cover_board(half_x + 1, half_y + 1, half_x + 1, max_x, half_y + 1, max_y);
		break;
	case BL:
		board[half_x][half_y] = board[half_x][half_y + 1] = board[half_x + 1][half_y + 1] = UR;
		cover_board(half_x, half_y, min_x, half_x, min_y, half_y);
		cover_board(half_x, half_y + 1, min_x, half_x, half_y + 1, max_y);
		cover_board(target_x, target_y, half_x + 1, max_x, min_y, half_y);
		cover_board(half_x + 1, half_y + 1, half_x + 1, max_x, half_y + 1, max_y);
		break;
	case BR:
		board[half_x][half_y] = board[half_x][half_y + 1] = board[half_x + 1][half_y] = BL;
		cover_board(half_x, half_y, min_x, half_x, min_y, half_y);
		cover_board(half_x, half_y + 1, min_x, half_x, half_y + 1, max_y);
		cover_board(half_x + 1, half_y, half_x + 1, max_x, min_y, half_y);
		cover_board(target_x, target_y, half_x + 1, max_x, half_y + 1, max_y);
		break;
	case ERROR:
	default:
		printf("Error\n");
	}
}

int main(void) {
	cover_board(0, 0, 0, BASE - 1, 0, BASE - 1);
	for (int i = 0; i < BASE; i++) {
		for (int j = 0; j < BASE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	getchar();
}
