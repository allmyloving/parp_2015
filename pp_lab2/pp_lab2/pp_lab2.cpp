// pp_lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "time.h"
#include "Windows.h"

using namespace std;

#define ULONG unsigned long
#define ULLONG unsigned long long
#define SIZE 10000
int a[SIZE];
ULLONG start, finish, min = ULLONG_MAX;

void fill(int arr[], size_t size, int min = -20, int max = 20){
	min = abs(min);
	for (int i = 0; i < size; i++){
		arr[i] = rand() % (max + min + 1) - min;
	}
}

template <typename T>
void fill(T arr[], size_t size, int min = -20, int max = 20){
	min = abs(min);
	for (int i = 0; i < size; i++){
		;
		//arr[i] = static_cast <T> (rand()) / static_cast <T> (6000);
		arr[i] = static_cast <T> (rand() % (max + min + 1) - min)/1.1;
	}
}

template <typename T>
void print(T arr[], size_t size){
	for (size_t i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

// Task 1.
void countPos(int arr[], size_t size){
	int count;
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		count = 0;
		start = __rdtsc();	
		
		for (size_t i = 0; i < size; i++){
			if (arr[i] >= 0){
				count++;
			}
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
	printf("countPos#positive elements: %d\n", count);
	printf("time for %d elements: %d\n\n", SIZE, min);
}

// Optimized.
void countPosOpt(int arr[], size_t size){
	int count;
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		count = 0;
		start = __rdtsc();

		for (size_t i = 0; i < size; i++){
			count += (arr[i] >> 31) & 1;
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
	printf("countPosOpt# positive elements: %d\n", size-count);
	printf("time for %d elements: %d\n\n", SIZE, min);
}

void Task1(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task1~~~~~~~~~~~~~~~~~~~~~~~\n");
	fill(a, SIZE);
	countPos( a, SIZE);
	countPosOpt(a, SIZE);
}

// Task 2.
void sort(int a[], size_t size){
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		start = __rdtsc();

		for (size_t i = 0; i < size - 1; i++){
			for (size_t j = 0; j < size - i - 1; j++){
				if (a[j] > a[j + 1]){
					int temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
		
	printf("sort#time for %d elements: %d\n", SIZE, min);
}

void sortOpt(int a[], size_t size){
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		start = __rdtsc();

		for (int i = 0; i < size - 1; i++){
			for (int j = i; j >= 0; j--){
				if (a[j] > a[j + 1]){
					int temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
	printf("sortOpt#time for %d elements: %d\n\n", SIZE, min);
}

void Task2(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task2~~~~~~~~~~~~~~~~~~~~~~~\n");
	fill(a, SIZE);
	sort(a, SIZE);
	fill(a, SIZE);
	sortOpt(a, SIZE);
}

// Task 3.
void polMul(int p1[], int p2[], int res[], int size1, int size2){
	min = ULLONG_MAX;
	for (int i = 0; i < 5; i++){
		start = __rdtsc();

		for (int i = 0; i < size1; i++){
			for (int j = 0; j < size2; j++){
				res[i + j] += p1[i] * p2[j];
			}
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}

	printf("polMul#time: %d\n", min);
}

void polMulOpt(int p1[], int p2[], int res[], int size1, int size2){
	min = ULLONG_MAX;
	for (int i = 0; i < 5; i++){
		start = __rdtsc();

		for (size_t j = 0; j < size2; j++) {
			if (p2[j] != 0){
				continue;
			}
			BOOL pos = p2[j] == 1;
			for (size_t k = 0; k < size1; k++) {
				if (pos){
					res[k + j] += p1[k];
				}
				else{
					res[k + j] -= p1[k];
				}
			}
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}

	printf("polMulOpt#time: %d\n\n", min);
}

void printPol(int p[], int size){
	for (int i = 0; i < size; i++){
		cout << ((p[i]>0) ? "+" : "");
		cout << p[i];
		if (i != 0){
			cout << "*x^" << i;
		}
		cout << " ";
	}
	cout << endl;
}

void Task3(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task3~~~~~~~~~~~~~~~~~~~~~~~\n");
	const int size1 = 10;
	const int size2 = 10;
	const int size3 = size1 + size2 - 1;

	int p1[size1];
	int p2[size2];
	int p3[size3] = { };

	fill(p1, size1);
	fill(p2, size2, -1, 1);

	polMul(p1, p2, p3, size1, size2);
	print(p3, size3);
	memset(p3, 0, size3*sizeof(int));
	print(p3, size3);
	polMulOpt(p1, p2, p3, size1, size2);
	print(p3, size3);
}

// Task 4.

template <typename T>
void round(T arr[], size_t size, size_t precision){
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		start = __rdtsc();

		for (int i = 0; i < size; i++){
			arr[i] = (arr[i] >= 0) ? (T)(int)(arr[i] + 0.5) : (T)(int)(arr[i] - 0.5);
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
	printf("round#time for %d elements: %d\n", size, min);
}

void Task4(size_t precision){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task4~~~~~~~~~~~~~~~~~~~~~~~\n");
	const int size = 10;
	double a[size];
	fill(a, size);
	//print(a, size);
	
	round(a, size, precision);
	//print(a, size);
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	
	//Task1();
	//Task2();
	//Task3();
	Task4(3);


	return 0;
}

