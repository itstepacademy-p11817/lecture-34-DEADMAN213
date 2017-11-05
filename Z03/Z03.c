#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>

int main(void) {
	setlocale(LC_ALL, "Russian");

	char* word = NULL;
	uint8_t ln = 0;
	char ch = 0;

	FILE* in = fopen("in.txt", "r");
	if (in == NULL) {
		printf("Ошибка открытия файла.\n");
		return 1;
	}

	FILE* out = fopen("out.txt", "w");
	if (out == NULL) {
		printf("Ошибка открытия файла.\n");
		return 1;
	}

	while (fscanf(in, "%c", &ch) != EOF) {
		if (isalpha(ch)) {
			word = (char*)realloc(word, ln * sizeof(char) + 1);
			*(word + ln++) = ch;
		}
		else if (word) {
				word = (char*)realloc(word, ln * sizeof(char) + 1);
				*(word + ln) = '\0';
				printf("%s\n", word);

				if (strlen(word) >= 7) {
					fprintf(out, "%s\n", word);
				}

				free(word);
				word = NULL;
				ln = 0;
			}
	}

	if (word) {
		word = (char*)realloc(word, ln * sizeof(char) + 1);
		*(word + ln) = '\0';
		printf("%s\n", word);

		if (strlen(word) >= 7) {
			fprintf(out, "%s\n", word);
		}

		free(word);
		word = NULL;
		ln = 0;
	}

	fclose(in);
	fclose(out);

	return 0;
}