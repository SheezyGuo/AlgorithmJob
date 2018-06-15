#include <stdlib.h>
#include <stdio.h>

#define NUM 5
double p[NUM] = { 0.15,0.1,0.05,0.1,0.2 };
double q[NUM + 1] = { 0.05,0.1,0.05,0.05,0.05 ,0.1 };
double E[NUM][NUM] = { 0 };
int marker[NUM][NUM] = { 0 };


double weight(int i, int j) {
	double sum = 0;
	for (int k = i; k <= j; k++) {
		sum += p[k];
	}
	for (int k = i; k <= j + 1; k++) {
		sum += q[k];
	}
	return sum;
}

double cal_e(int i, int j) {
	if (E[i][j] != 0) {
		return E[i][j];
	}
	if (i == j + 1) {
		E[i][j] = 0;
		return 0; //p���㿪ʼ,q���Ǵ�-1��ʼ,���㿪ʼ�൱��q��ÿ���±����1
	}
	double e = INT_MAX;
	int kfalg = -1;
	//i��j��ѡ����,ÿ�����л���
	for (int k = i; k <= j; k++) {
		double temp = cal_e(i, k - 1) + cal_e(k + 1, j);
		if (temp < e) {
			e = temp;
			kfalg = k;
		}
	}
	e += weight(i, j);
	marker[i][j] = kfalg;
	E[i][j] = e;
	return e;
}

int main(void) {
	for (int step = 0; step < NUM; step++) {
		int i = 0;
		int j = step;
		for (int increment = 0; j + increment < NUM; increment++) {
			cal_e(i + increment, j + increment);
		}
	}
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			printf("%.3f ", E[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			printf("%d ", marker[i][j]);
		}
		printf("\n");
	}
	getchar();
}