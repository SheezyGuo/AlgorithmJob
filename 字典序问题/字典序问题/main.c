#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE_PATH[] = "input.txt";
const char OUTPUT_FILE_PATH[] = "output.txt";

int read_count(FILE* pfile) {
    int count =0;
    fscanf_s(pfile,"%d",&count);
    return count;
}

char* read_str(FILE* pfile) {
    char* buff = malloc(sizeof(char)*256);
    memset(buff,0,256);
    fscanf_s(pfile,"%s",buff,256);
    return buff;
}

//连乘 from start to end
int serial_multiply(int start,int end) {
    int temp = 1;
    for(int i=start ; i<=end; i++) {
        temp *= i;
    }
    return temp;
}

//组合数C(n,m)
int combination(int n,int m) {
    if(n<-1||m<-1||m>n) {
        return -1;
    }
    return serial_multiply(n-m+1,n)/serial_multiply(1,m);
}

int calc_previous(int length) {
    if(length<=0) return -1;
    int sum =0;
    for(int i=1; i<length; i++) {
        sum+=combination(26,i);
    }
    return sum;
}

int* get_order_list(char* str) {
    int length = strlen(str);
    int * order_list = malloc(sizeof(int)*length);
    for(int i=0; i<length; i++) {
        order_list[i] = str[i]-'a'+1;
    }
    return order_list;
}

int calc_backward(int* order_list,int length,int step) {
    static int sum=0;
    if(step>length) {
        int temp =sum+1;
        sum =0;
        return temp;
    }
    int current_order = order_list[step];
    int pre_order= step>0?order_list[step-1]:0;
    for(int i=pre_order+1; i<current_order; i++) {
        int residential = 26 -i;
        sum+=combination(residential,length-1-step);
    }
    return calc_backward(order_list,length,step+1);
}

int calc(char* str) {
	errno_t err;
	FILE * pfile;
	err = fopen_s(&pfile,OUTPUT_FILE_PATH, "a+");
	if (err) {
		return INT_MIN;
	}
	int str_len = strlen(str);
    int* order_list = get_order_list(str);
    int result = calc_previous(str_len)+calc_backward(order_list,str_len,0);
    printf("%d\n",result);
    fprintf(pfile,"%d\n",result);
    fclose(pfile);
    return 1;
}

int main() {
	errno_t err;
	FILE* pfile;
	err = fopen_s(&pfile,INPUT_FILE_PATH, "r");
	if (err) {
		return -1;
	}
    int count = read_count(pfile);
    for(int i=0; i<count; i++) {
        char * str = read_str(pfile);
        calc(str);
    }
    fclose(pfile);
    return 0;
}
