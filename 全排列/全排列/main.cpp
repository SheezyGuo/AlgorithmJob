#include <stdio.h>

char char_list[26];

void quanpai(int index) {
	if (index == 25) {
		for (int i = 0; i < 26; i++) {
			printf("%c", char_list[i]);
		}
		printf("\n");
	}
	for (int i = index; i < 26; i++) {
		char temp = char_list[i];
		int j;
		for (j = i; j > index; j--) {
			char_list[j] = char_list[j - 1];
		}
		char_list[j] = temp;
		quanpai(index + 1);
		temp = char_list[j];
		for (; j < i; j++) {
			char_list[j] = char_list[j + 1];
		}
		char_list[j] = temp;
	}
}

int main(void) {
	for (int i = 'A'; i <= 'Z'; i++) {
		char_list[i - 'A'] = i;
	}
	quanpai(0);
}