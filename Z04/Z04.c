#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
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
	if (setvbuf (in, NULL, _IOFBF, MAXLINE)) {
		printf("He удается создать буфер ввода.\n ");
		return 1;
	}

	FILE* out = fopen("out.txt", "w+");
	if (out == NULL) {
		printf("Ошибка открытия файла.\n");
		return 1;
	}
	if (setvbuf(out, NULL, _IOFBF, MAXLINE)) {
		printf("He удается создать буфер вывода.\n ");
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

		case 2:
			filePrint(in, out);
			fflush(out);
			break;

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