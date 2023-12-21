#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "Initializing_of_functions.h"


char filename[] = "..\\dict0.txt";  // or dict1.txt, dict2.txt, ...
//char arr_tmp[];

void main() {
	// t0 - сколько прошло времени от старта программы до момента входа в функцию main()
	long t0 = clock();
	printf("t0 = %.10f sec \n", t0 / (float)CLOCKS_PER_SEC);

	LoadWords(filename);
	printf("> Array lenth: %d\n> File: %s\n", n, filename);

	// время от старта программы до окончания загрузки массива - [1 этап]
	int t1 = clock();
	printf("t1 = %.10f sec \n", t1 / (float)CLOCKS_PER_SEC);


	for (int i = 0; i < 1; i++) {
		fillArrayStrings();

		//SelectionSortStrings();
		//QuickSortStrings();
		//InsertSortStr();

		Calling_MergeFunc();
		// \-> MergeSortStr(newToSort, n);

		//BubbleSortStr();

		if (!isSortedStrings()) {
			printf("Array is not sorted!!!\n");
		}
	}

	// время от старта программы до окончания сортировки - [2 этап]
	long t2 = clock();
	printf("t2 = %.10f sec \n", t2 / (float)CLOCKS_PER_SEC);

	printf("t1 - t0 = %.10f sec (Run time of array loading)\n",
		(t1 - t0) / (float)CLOCKS_PER_SEC);
	printf("t2 - t1 = %.10f sec (Run time of sorting)\n",
		(t2 - t1) / (float)CLOCKS_PER_SEC);
}
