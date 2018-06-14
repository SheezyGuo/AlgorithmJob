#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int start;
	int end;
}position;

position binary_search(int* array, int start, int end, int length, int value) {
	if (array == NULL || start < 0 || end < start || end >= length) {
		position p = { -1,-1 };
		return p;
	}
	position p = { -1,-1 };
	int middle = (end + start) / 2;
	if (array[middle] == value) {
		p.start = middle;
		p.end = middle;
		return p;
	}
	if (start == end) {
		if (array[middle] > value) {
			p.start = middle - 1 >= 0 ? middle - 1 : 0;
			p.end = middle;
			return p;
		}
		else if (array[middle] < value) {
			p.start = middle;
			p.end = middle + 1 < length ? middle + 1 : length - 1;
			return p;
		}
	}
	else if (array[middle] > value) {
		return binary_search(array, start, middle - 1, length, value);
	}
	else if (array[middle] < value) {
		return binary_search(array, middle + 1, end, length, value);
	}

}

void print_position(position p) {
	if (p.start == p.end) {
		if (p.start != -1) {
			printf("%d\n", p.start);
		}
		else {
			printf("Error\n");
		}
	}
	else if (p.start < p.end) {
		printf("%d,%d\n", p.start, p.end);
	}
	else {
		printf("Error\n");
	}
}

int main(void) {
	int array[] = { 1,2,3,4,5,6,7,8,10 };
	print_position(binary_search(array, 0, 8, 9, 8));
	print_position(binary_search(array, 0, 8, 9, 10));
	print_position(binary_search(array, 0, 8, 9, 9));
	getchar();
	return 0;
}