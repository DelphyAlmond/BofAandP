#pragma once

int LoadWords(char* filename);
void fillArrayStrings();

void SelectionSortStrings();
void QuickSortStrings();
void InsertSortStr();
void MergeSortStr(char array[], int len);
void BubbleSortStr();

void Calling_MergeFunc();

//int LinearSearchStrings(char* value);
//int BinarySearchStrings(char* value);
int isSortedStrings();

extern int n;
