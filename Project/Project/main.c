#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char INPUT_FILE_PATH[] = "input.txt";
const char OUTPUT_FILE_PATH[] = "output.txt";

typedef struct {
	int front;
	int tail;
} splited_str;

int count[10];

int mypow(int base,int index) {
	if(index==0) {
		return 1;
	}
	if(index <0) {
		return INT_MIN;
	}
	int temp=1;
	for(int i=0; i<index; i++) {
		temp*=base;
	}
	return temp;
}

char* read_str(FILE* pfile) {
	char* buff = malloc(sizeof(char)*256);
	memset(buff,0,256);
	fscanf_s(pfile,"%s",buff,256);
	return buff;
}

int str2int(char* str) {
	if(!str) {
		return -1;
	}
	int size = strlen(str);
	int sum=0;
	for(int i=0; i<size; i++) {
		sum += (str[i]-'0')*mypow(10,size-i-1);
	}
	return sum;
}

char* strsub(char* str,int start,int end) {
	if(!str||start<0) {
		return NULL;
	}
	int size = strlen(str);
	if(end>=size) {
		end=size-1;
	}
	if(end<start){
		return "0";
	}
	int length = end-start+2;
	char* temp = (char*)malloc(sizeof(char)*length);
	memset(temp,0,length);
	for(int i=0; i<length-1; i++) {
		temp[i]=str[start+i];
	}
	return temp;
}

splited_str split_str_by_digit(char* str,int digit) {
	int str_len = strlen(str);
	splited_str ss;
	ss.front=str2int(strsub(str,0,digit-1));
	ss.tail=str2int(strsub(str,digit+1,str_len-1));
	return ss;
}

void set_count(int digit,int num,char* str) {
	splited_str ss = split_str_by_digit(str,digit);
	int front = ss.front;
	int tail = ss.tail;
	if(str[digit]-'0'<num) {
		int times= front*mypow(10,strlen(str)-digit-1);
		count[num]+=times;
	}
	if(str[digit]-'0'==num) {
		int times= front*mypow(10,strlen(str)-digit-1)+tail+1;
		count[num]+=times;
	}
	if(str[digit]-'0'>num) {
		int times= (front+1)*mypow(10,strlen(str)-digit-1);
		count[num]+=times;
	}
}

int main(void) {
	memset(count,0,10);
	errno_t err;
	FILE * p_input;
	err = fopen_s(&p_input,INPUT_FILE_PATH, "r");
	char* str = read_str(p_input);
	fclose(p_input);
	int size= strlen(str);
	for(int digit=0; digit<size; digit++) {
		for (int i=0; i<10; i++) {
			set_count(digit,i,str);
		}
	}
	for (int i = 1; i < size; i++) {
		count[0] -= 9 * mypow(10, size - i-1)*i;
	}
	count[0] -= size;

	FILE * output;
	err = fopen_s(&output, OUTPUT_FILE_PATH, "w");
	if (err) {
		return -1;
	}
	for (int i = 0; i<10; i++) {
		fprintf(output,"%d:%d\n", i, count[i]);
	}
	fclose(output);
	return 0;
}
