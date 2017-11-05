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

	printf("����:\n");
	printf("1 - ������ ������.\n");
	printf("2 - ����������� ��������� �����.\n");
	printf("3 - �����.\n");
	printf("��� �����: ");
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
		printf("������ �������� �����.\n");
		return 1;
	}
	if (setvbuf (in, NULL, _IOFBF, MAXLINE)) {
		printf("He ������� ������� ����� �����.\n ");
		return 1;
	}

	FILE* out = fopen("out.txt", "w+");
	if (out == NULL) {
		printf("������ �������� �����.\n");
		return 1;
	}
	if (setvbuf(out, NULL, _IOFBF, MAXLINE)) {
		printf("He ������� ������� ����� ������.\n ");
		return 1;
	}

	while ((ch = menu()) != 3) {
		switch (ch) {
		case 1:
			if (fileSize(in)) {
				printf("\n�������� ����:\n");
				filePrint(in, stdout);
				putchar('\n');
			}

			if (fileSize(out)) {
				printf("\n�������� ����:\n");
				filePrint(out, stdout);
				putchar('\n');
			}

			break;

		case 2:
			filePrint(in, out);
			fflush(out);
			break;

		default:
			printf("�������� ����.\n");
			pass();
			break;
		}

		printf("������� ����� �������.\n");
		_getch();
	}

	fclose(in);
	fclose(out);

	return 0;
}