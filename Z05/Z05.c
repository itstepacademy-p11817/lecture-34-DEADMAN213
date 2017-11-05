#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <inttypes.h>

#define MAXLINE 11

FILE* filePrint(FILE* in, FILE* out) {
	char str[MAXLINE] = "";

	fseek(in, 0, SEEK_SET);

	while (fgets(str, MAXLINE, in)) {
		fputs(str, out);
	}

	return in;
}

int32_t fileSize(FILE* fl) {
	int32_t size = 0L;
	int32_t pos = ftell(fl);

	fseek(fl, 0, SEEK_END);
	size = ftell(fl);
	fseek(fl, pos, SEEK_SET);

	return size;
}

char* reverce(char* bgn) {
	char* end = bgn;
	uint8_t i = 0;

	while (*end) {
		end++;
	}
	end--;

	while (end > bgn) {
		char box = *bgn;
		*bgn = *end;
		*end = box;

		bgn++;
		end--;
	}

	return bgn;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Меню:\n");
	printf("1 - Печать файлов.\n");
	printf("2 - Копирование исходного файла.\n");
	printf("3 - Выход.\n");
	printf("Ваш выбор: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	setlocale(LC_ALL, "Russian");

	uint8_t ch = 0;

	FILE* in = fopen("in.txt", "r");
	if (in == NULL) {
		printf("Ошибка открытия файла.\n");
		return 1;
	}

	FILE* out = fopen("out.txt", "w+");
	if (out == NULL) {
		printf("Ошибка создания файла.\n");
		return 1;
	}

	while ((ch = menu()) != 3) {
		switch (ch) {
		case 1:
			if (fileSize(in)) {
				printf("\nИсходный файл:\n");
				filePrint(in, stdout);
				putchar('\n');
			}

			if (fileSize(out)) {
				printf("\nВыходной файл:\n");
				filePrint(out, stdout);
				putchar('\n');
			}

			break;

		case 2: {
			fseek(in, -1, SEEK_END);

			char* str = NULL;
			char ch = 0;
			uint8_t ln = 0;
			int32_t pos = ftell(in);

			while (pos >= 0) {
				ch = getc(in);

				if (ch == '\n') {
					str = (char*)realloc(str, ln * sizeof(char) + 1);
					*(str + ln) = '\0';

					reverce(str);
					fputs(str, out);
					putc(ch, out);
					fflush(out);

					free(str);
					str = NULL;
					ln = 0;
					fseek(in, --pos, SEEK_SET);
				}
				else {
					str = (char*)realloc(str, ln * sizeof(char) + 1);
					*(str + ln++) = ch;
				}

				fseek(in, --pos, SEEK_SET);
			}

			str = (char*)realloc(str, ln * sizeof(char) + 1);
			*(str + ln) = '\0';

			reverce(str);
			fputs(str, out);
			fflush(out);

			free(str);

			break;
		}

		default:
			printf("Неверный ввод.\n");
			pass();
			break;
		}

		printf("Нажмите любую клавишу.\n");
		_getch();
	}

	fclose(in);
	fclose(out);

	return 0;
}