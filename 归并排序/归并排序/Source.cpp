#include <stdio.h>
#include <stdlib.h>

void merge(int* array, int* aux, int start, int middle, int end) {
	int i = start, j = middle + 1, k = start;
	for (int index = start; index <= end; index++) {
		aux[index] = array[index];
	}
	while (i <= middle && j <= end) {
		if (aux[i] < aux[j]) {
			array[k++] = aux[i++];
		}
		else {
			array[k++] = aux[j++];
		}
	}
	while (i <= middle) {
		array[k++] = aux[i++];
	}
	while (j <= end) {
		array[k++] = aux[j++];
	}
}

int sort(int* array, int * aux, int start, int end, int length) {
	int middle = (start + end) / 2;
	if (start >= end) {
		return 0;
	}
	sort(array, aux, start, middle, length);
	sort(array, aux, middle + 1, end, length);
	merge(array, aux, start, middle, end);
}



int main(void) {
	int array[] = { 10,9,8,7,6,0,5,4,3,2,1 };
	int* auxiliary = (int*)malloc(sizeof(int)*11);
	sort(array, auxiliary, 0, 10, 11);
	for (int i = 0; i < 11; i++) {
		printf("%d\n", array[i]);
	}
	getchar();
	return 0;
}