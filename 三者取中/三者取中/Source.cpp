#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STEP 30000

int modify(int* array, int length, int start, int end) {
	if (array == NULL || start<0 || end >length || length < 0 || end < start) {
		return -100;
	}
	int front = start;
	int tail = end;
	int pivot = array[start];
	while (front < tail) {
		while (front < tail && array[tail] >= pivot) {
			tail--;
		}
		array[front] = array[tail];
		while (front < tail && array[front] <= pivot) {
			front++;
		}
		array[tail] = array[front];
	}
	array[tail] = pivot;
	return tail;
}

int quickSort(int* array, int length, int start, int end) {
	if (start >= end) {
		return 0;
	}
	int middle = modify(array, length, start, end);
	quickSort(array, length, start, middle - 1);
	quickSort(array, length, middle + 1, end);
}

void compExch(int* a, int*b) {
	if (*a > *b) {
		int temp = *b;
		*b = *a;
		*a = temp;
	}
}

int middle_of_three(int * array, int length, int start, int end) {
	if (start >= end || start < 0 || end >= length) {
		return 0;
	}
	int middle = (end - start) / 2 + start;
	int temp = array[middle];
	array[middle] = array[start + 1];
	array[start + 1] = temp;
	compExch(&array[start], &array[start + 1]);
	compExch(&array[start], &array[end]);
	compExch(&array[start + 1], &array[end]);
	int partition = modify(array, length, start + 1, end - 1);
	middle_of_three(array, length, start, partition - 1);
	middle_of_three(array, length, partition + 1, end);
}

int main(void) {
	int array[MAX_STEP];
	int copy[MAX_STEP];
	double d_quick = 0, d3 = 0;
	for (int step = 0; step < 10; step++) {
		srand(time(0));
		for (int i = 0; i < MAX_STEP; i++) {
			array[i] = rand() % MAX_STEP;
			copy[i] = array[i];
		}

		clock_t start, end;
		double duration;
		start = clock();
		quickSort(array, MAX_STEP, 0, MAX_STEP - 1);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		d_quick += duration;
		start = clock();
		middle_of_three(copy, MAX_STEP, 0, MAX_STEP - 1);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		d3 += duration;
	}
	printf("快排均用时:%lf\n", d_quick / 10);
	printf("三者取中均用时:%lf\n", d3 / 10);
	/*for (int i = 0; i < MAX_STEP; i++) {
	printf("%d\n", array[i]);
	}
	getchar();*/
	getchar();
	return 0;
}