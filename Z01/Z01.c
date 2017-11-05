#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdarg.h>
#include <math.h>

bool isSimple(uint8_t val) {
	for (uint8_t i = 2; i <= sqrt(val); i++) {
		if (val%i == 0) {
			return false;
		}
	}

	return true;
}

uint8_t howSimple(uint8_t num, ...) {
	va_list valist;
	uint8_t n = 0;
	uint8_t val = 0;

	va_start(valist, num);

	printf("Simple numbers are:");

	for (int i = 0; i < num; i++) {
		val = va_arg(valist, uint8_t);
		if (isSimple(val)) {
			n++;
			printf("%3hhu", val);
		}
	}

	va_end(valist);

	printf("\n");

	return n;
}

int main(void) {
	printf("There are %hhu simple numbers.\n", howSimple(5, 2, 4, 5, 7, 3));

	return 0;
}