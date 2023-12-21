#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "Initializing_of_functions.h"


static char filename[] = "";

// ������������ ����� ����� � �������
#define MAX_LEN_WORD 80
// ������������ ���������� ����
#define MAX_WORDS 20000

char words[MAX_WORDS][MAX_LEN_WORD + 1];
// ���-�� ����
int n = 0;
char newToSort[MAX_WORDS][MAX_LEN_WORD + 1];

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[]);


int LoadWords(char* filename) {
	// ������� ����
	FILE* fin = fopen(filename, "rt");
	if (fin == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s cann't be opened!\n", filename);
		return 0;
	}

	char token[MAX_LEN_WORD + 1];
	// ���� �� ����� �����
	while (!feof(fin)) {
		// ���� ���� ����������� - ����� ���
		while (getNextDelim(fin, token)) {
		}
		// ���� ���� ����� - ����� ���
		if (getNextWord(fin, token)) {
			if (n < MAX_WORDS) {
				strcpy(words[n], token);
				n++;
			}
			else {
				printf("Words are more than elements in array!!\n", filename);
				fclose(fin);
				return 0;
			}
		}
	}
	// ��������� ���� � �������
	fclose(fin);
	return 1;
}


// ���������� 0 - ���� ch - �� �����.
// ���������� 1 - ���� ch - �����.
// ��������� �������� ��� ��������� ���� (� ������ < 128)
// � ��� ������� ���� �� ��������� ANSI
int isalpha_my(unsigned char ch) {

	if (isalpha(ch))
		return 1;

	// ANSI ���������!!!
	if (ch >= 192 && ch <= 223)
		return 1;
	if (ch >= 224 && ch <= 255)
		return 1;

	return 0;
}


// ���������� 1 - ����  �� ����� �������� �����������.
// � ���� ������ � token ������������ ������, ���������� 
// ���� �����������.
// ���� � ����� ��� �� ����������� - ���������� 0.
// � ���� ������ ��������� token ������������.
int getNextDelim(FILE* fp, char token[])
{
	int ch = getc(fp);
	if (ch == EOF) {
		return 0;
	}
	if (isalpha_my((unsigned char)ch)) {
		ungetc(ch, fp);
		return 0;
	}
	token[0] = (unsigned char)ch;
	token[1] = '\0';
	return 1;
}


// ���������� 1 - ����  �� ����� ��������� �����.
// � ���� ������ � token ������������ ������, ���������� 
// ��� �����. ������������� ��� ����� �� ����� MAX_LEN_WORD ��������.
// ���� � ����� �� ���� ����� - ���������� 0.
// � ���� ������ token �������� ������ ������.
int getNextWord(FILE* fp, char token[])
{
	int i = 0;
	int ch;
	while (((ch = getc(fp)) != EOF) && (i < MAX_LEN_WORD)) {
		if (!isalpha_my((unsigned char)(ch))) {
			break;
		}
		token[i++] = ch;
	}
	ungetc(ch, fp);
	token[i] = '\0';
	if (i == 0)
		return 0;
	return 1;
}


void fillArrayStrings() {

	for (int i = 0; i < n; i++) {
		strcpy(newToSort[i], words[i]);
	}

}


int isSortedStrings() {
	for (int i = 0; i < n - 1; i++) {
		if (strcmp(newToSort[i], newToSort[i + 1]) > 0) {
			return 0;
		}
	}
	return 1;
}

// ---------------------------- Sorty-functions ----------------------------

void InsertSortStr() {
	for (int pos = 1; pos < n; pos++) {
		char value[MAX_LEN_WORD];
		strcpy(value, newToSort[pos]);
		int before = pos;

		while ((before > 0) && strcmp(value, newToSort[before - 1]) < 0) {
			strcpy(newToSort[before], newToSort[before - 1]);
			before--;
		}
		strcpy(newToSort[before], value);
	}
}


void merge(char arr[], char* L[], int lenL, char* R[], int lenR) {
	int n = 0, m = 0, k = 0;

	while (n < lenL && m < lenR) {
		if (strcmp(L[n], R[m]) <= 0) {
			strcpy(arr[k], L[n]);
			n++;
		}
		else {
			strcpy(arr[k], R[m]);
			m++;
		}
		k++;
	}
	while (n < lenL) {
		strcpy(arr[k], L[n]);
		n++;
		k++;
	}
	while (m < lenR) {
		strcpy(arr[k], R[m]);
		m++;
		k++;
	}


	if (lenL + lenR <= 5) {
		printf("[ ");
		for (int i = 0; i < lenL + lenR; i++) {
			printf("%s ", arr[i]);
		}
		printf("]\n");
	}
	printf("\n");
}


void MergeSortStr(char array[], int len) {

	if (len > 1) {
		int middle = len / 2;

		// ERRORS OCCURS HERE ---------------------------------->

		char** L = (char**)malloc(sizeof(char*) * (middle));
		for (int i = 0; i < middle; i++) {
			L[i] = (char*)malloc(sizeof(char) * (MAX_LEN_WORD + 1));
		}

		char** R = (char**)malloc(sizeof(char*) * (n - middle));
		for (int i = 0; i < (len - middle); i++) {
			R[i] = (char*)malloc(sizeof(char) * (MAX_LEN_WORD + 1));
		}

		for (int i = 0; i < middle; i++) {
			strcpy(L[i], array[i]);
		}
		for (int i = middle; i < len; i++) {
			strcpy(R[i - middle], array[i]);
		}

		MergeSortStr(L, middle);
		MergeSortStr(R, len - middle);

		merge(array, L, middle, R, len - middle);

		for (int i = 0; i < middle; i++) {
			free(L[i]);
		}

		for (int i = 0; i < (len - middle); i++) {
			free(R[i]);
		}

		free(L);
		free(R);
	}
}


void Calling_MergeFunc() {
	MergeSortStr(newToSort, n);
}


void BubbleSortStr() {
	int len_1 = n;

	while (1) {
		int key = 1;

		for (int i = 0; i < len_1 - 1; i++) {
			if (strcmp(newToSort[i], newToSort[i + 1]) > 0) {
				char tmp[MAX_LEN_WORD + 1];
				strcpy(tmp, newToSort[i]);
				strcpy(newToSort[i], newToSort[i + 1]);
				strcpy(newToSort[i + 1], tmp);
				key = 0;
			}
		}

		if (key) {
			printf("[ Array has been sorted succesfully. ]\n");
			break;
		}

		len_1--;
	}
}


void SelectionSortStrings() {
	for (int i = 0; i < n - 1; i++) {

		int curr_min = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(newToSort[j], newToSort[curr_min]) < 0) {
				curr_min = j;
			}
		}

		if (i != curr_min) {
			char tmp[MAX_LEN_WORD + 1];
			strcpy(tmp, newToSort[i]);
			strcpy(newToSort[i], newToSort[curr_min]);
			strcpy(newToSort[curr_min], tmp);
		}
	}
}


void QuickSortStrings() {
	qsort(newToSort, n, sizeof(newToSort[0]), strcmp);
}
