#include <iostream>
#include <algorithm>
#include <ctime>
#include <Windows.h>
using namespace std;
void printArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i]<<" ";
	}
}
// сортировка вставками
void insertSort(int *arr, int left, int right) {
	for (int i = left + 1; i < right + 1; i++) {
		int element = arr[i];
		int j = i - 1;
		while (j>=left && element<arr[j]) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = element;
	}
}
// слияние
void mergeArrays(int* arr, int a, int b, int c) {
	int left_size = b - a + 1;
	int right_size = c - b;
	int* left = new int[left_size];
	int* right = new int[right_size];
	for (int i = 0; i < left_size; i++) {
		left[i] = arr[a + i];
	}
	for (int i = 0; i < right_size; i++) {
		right[i] = arr[b + 1 + i];
	}
	int i = 0;
	int j = 0;
	int k = 0;
	while (j < right_size && i < left_size) {
		if (left[i] <= right[j]) {
			arr[k] = left[i];
		}
		else {
			arr[k] = right[j];
			j += 1;
		}
		k += 1;
	}
	while (i < left_size) {
		arr[k] = left[i];
		k += 1;
		i += 1;
	}
	while (j < right_size) {
		arr[k] = right[j];
		k += 1;
		j += 1;
	}
}
// timsort.
void timSort(int* arr, int size, int minrun) {
	for (int i = 0; i < size; i = i + minrun) {
		int end = min(i + minrun - 1, size - 1);
		insertSort(arr, i, end);
	}
	int minrun_size = minrun;
	while (minrun_size < size) {
		for (int left_size = 0; left_size < size; left_size = left_size + size * 2) {
			int middle = min(size - 1, left_size + minrun_size - 1);
			int right_size = min((left_size + size * 2 - 1), size - 1);
			mergeArrays(arr, left_size, middle, right_size);
		}
		minrun_size = minrun_size * 2;
	}
}
// определяем minrun для нашего массива.
int minrun(int size) {
	int r = 0;
	while (size >= 64) {
		r |= size & 1;
		size>>= 1;
	}
	return (size + r);
}
int main() {
	SetConsoleTitle(L"Timsort");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int arrSize;
	int userInput;
	cout << "Введите количество элементов массива (максимум - 63, элементы массива заполняются случайными значениями): \n";
	cin >> userInput;
	if (userInput <= 0 || userInput > 63) {
		cout << "Некорректное значение. \n";
	}
	else {
		arrSize = userInput;
		int* arr = new int[arrSize];
		for (int i = 0; i < arrSize; i++) {
			arr[i] = rand() % 50;
		}
		int minrun_value = minrun(arrSize);
		cout << "Массив до сортировки: \n";
		printArray(arr, arrSize);
		cout << "\nМассив после сортировки: \n";
		timSort(arr, arrSize, minrun_value);
		printArray(arr, arrSize);
	}
		return 0;
}