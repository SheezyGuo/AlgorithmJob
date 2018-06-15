#include<stdlib.h>
#include<stdio.h>
typedef struct {
	double frequency;
	int left;
	int right;
}node;

#define NUM 7
node node_list[2 * NUM - 1];
double value[NUM] = { 0.31,0.12,0.05,0.02,0.1,0.18,0.22 };
int used[2 * NUM - 1]{ 0 };

int min1, min2;

void init_node_list() {
	for (int i = 0; i < 2 * NUM - 1; i++) {
		node temp;
		temp.left = temp.right = -1;
		temp.frequency = -1;
		node_list[i] = temp;
	}
	for (int i = 0; i < NUM; i++) {
		node_list[i].frequency = value[i];
	}
}

void find_min(int step) {
	min1 = 0;
	while (used[min1] && min1 < NUM + step) {
		min1++;
	}
	min2 = min1 + 1;
	while (used[min2] && min2 < NUM + step) {
		min2++;
	}
	if (node_list[min1].frequency > node_list[min2].frequency) {
		int temp = min1;
		min1 = min2;
		min2 = temp;
	}

	for (int i = 0; i < NUM + step; i++) {
		if (!used[i] && node_list[i].frequency < node_list[min1].frequency) {
			min2 = min1;
			min1 = i;
		}
		else if (!used[i] && i != min1 && node_list[i].frequency < node_list[min2].frequency) {
			min2 = i;
		}
	}
	node_list[NUM + step].frequency = node_list[min1].frequency + node_list[min2].frequency;
	node_list[NUM + step].left = min1;
	node_list[NUM + step].right = min2;
	used[min1] = used[min2] = 1;
}

void main(void) {
	init_node_list();
	for (int step = 0; step < NUM - 1; step++) {
		find_min(step);
	}
	for (int i = 0; i < 2 * NUM - 1; i++) {
		printf("%d->%f:%d %d\n", i, node_list[i].frequency, node_list[i].left, node_list[i].right);
	}
	getchar();
}



