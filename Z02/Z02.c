#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	uint8_t val = 0;
	uint8_t even = 0;
	uint8_t neven = 0;

	if (argc < 2) {
		printf("Нет чисел.\n");
		return 1;
	}

	for (uint8_t i = 1; i < argc; i++) {
		val = atoi(argv[i]);
		if (val == 0 && strlen(argv[i]) == 1 && argv[i][0] == '0' || val != 0 && val % 2 == 0) {
			printf("%hhu - четное.\n", val);
			even++;
		}
		else if (val != 0) {
			printf("%hhu - нечетное.\n", val);
			neven++;
		}
		else {
			printf("%s - не число.\n", argv[i]);
		}
	}

	if (even > neven) {
		printf("Четных больше.\n");
	}
	else if (even == neven) {
		printf("Четных и нечетных равное количество.\n");
	}
	else {
		printf("Нечетных больше.\n");
	}

	return 0;
}