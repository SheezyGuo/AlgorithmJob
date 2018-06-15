#include <stdio.h>
#define NUM 9
bool selected[NUM] = { false };
int s[NUM] = { 2,2,3,4,6,7,9,10,13 };
int f[NUM] = { 3,4,5,7,8,11,12,15,17 };

int main(void) {
	selected[0] = true;
	int cur = 0;
	for (int i = 1; i < NUM; i++) {
		if (s[i] >= f[cur]) {
			selected[i] = true;
			cur = i;
		}
	}
	for (int i = 0; i < NUM; i++) {
		if (selected[i]) {
			printf("#%d: %d~%d\n", i + 1, s[i], f[i]);
		}
	}
	getchar();
	return 0;
}