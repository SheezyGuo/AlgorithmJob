#include <stdio.h>
#include <stdlib.h>

#define LEN 8 //9-1
int matrix_chain[LEN + 1] { 10,100,5,50,30,20,60,45,50 };
int cal_steps[LEN][LEN] { 0 };
int marker[LEN][LEN] { 0 };


void set_matrix(int i, int j) {
    if (i == j) cal_steps[i][j] = 0;
    if (i < j && i >= 0 && j < LEN) {
        int kflag = -1;
        int min_flag = INT_MAX;
        for (int k = i + 1; k <= j; k++) {
			// 从i到j挑间断的位置,位置是从i+1到j,表示在第k个的前边断开
            int temp = cal_steps[i][k] + cal_steps[k+1][j] + matrix_chain[i] * matrix_chain[k+1] * matrix_chain[j+1];
            if (temp < min_flag) {
                kflag = k;
                min_flag = temp;
            }
        }
        cal_steps[i][j] = min_flag;
        marker[i][j] = kflag;
    }
}

void print_result(int i, int j) {
    if (i == j) {
        printf("%c", 'A' + i);
        return;
    }
    int k = marker[i][j];
    printf("(");
    print_result(i, k-1);
    printf(")(");
    print_result(k , j);
    printf(")");
}

int main(void) {
    for (int count = 0; count < LEN; count++) {
        int i = 0, j = count;
        for (int increment = 0; j + increment < LEN; increment++) {
            //printf("%d,%d ", i + increment, j + increment);
            set_matrix(i + increment, j + increment);
        }
        //printf("\n");
    }
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            printf("%08d ", cal_steps[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            printf("%d ", marker[i][j]);
        }
        printf("\n");
    }
    print_result(0, LEN - 1);
	getchar();
}
