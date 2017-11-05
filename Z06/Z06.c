#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <inttypes.h>

#define LINE "------------"

FILE* filePrint(FILE* in, FILE* out) {
	char ch = 0;

	fseek(in, 0, SEEK_SET);

	while ((ch = getc(in)) != EOF) {
		putc(ch, out);
	}
	fflush(out);

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

bool isSpaceSentence(const char* str) {
	while (*str) {
		if (*str == ' ') {
			return true;
		}

		str++;
	}

	return false;
}

bool isSpaceFile(FILE* fl) {
	char* buf = NULL;
	uint8_t ln = 0;
	char ch = 0;

	while ((ch = getc(fl)) != EOF) {
		if (ch == '\n') {
			buf = (char*)realloc(buf, ln * sizeof(char) + 1);
			*(buf + ln) = '\0';

			if (!isSpaceSentence(buf)) {
				return true;
			}

			free(buf);
			buf = NULL;
			ln = 0;
		}
		else {
			buf = (char*)realloc(buf, ln * sizeof(char) + 1);
			*(buf + ln++) = ch;
		}
	}
	buf = (char*)realloc(buf, ln * sizeof(char) + 1);
	*(buf + ln) = '\0';

	if (!isSpaceSentence(buf)) {
		return true;
	}

	free(buf);

	return false;
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
	bool flag = false;

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
			char* buf = NULL;
			char ch = 0;
			uint8_t ln = 0;
			int32_t pos = 0;

			fseek(in, 0, SEEK_SET);
			while ((ch = getc(in)) != EOF) {
				if (flag) {
					putc(ch, out);
					continue;
				}

				if (ch == '\n') {
					buf = (char*)realloc(buf, ln * sizeof(char) + 1);
					*(buf + ln) = '\0';

					fputs(buf, out);
					putc(ch, out);
					fflush(out);

					pos = ftell(in);
					if (!isSpaceSentence(buf) && !isSpaceFile(in)) {
						fseek(in, pos, SEEK_SET);
						fputs(LINE, out);
						putc('\n', out);
						flag = true;
					}
					fseek(in, pos, SEEK_SET);

					free(buf);
					buf = NULL;
					ln = 0;
				}
				else {
					buf = (char*)realloc(buf, ln * sizeof(char) + 1);
					*(buf + ln++) = ch;
				}
			}
			buf = (char*)realloc(buf, ln * sizeof(char) + 1);
			*(buf + ln) = '\0';

			fputs(buf, out);
			if (!flag) {
				putc('\n', out);
				fputs(LINE, out);
			}
			fflush(out);

			free(buf);
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