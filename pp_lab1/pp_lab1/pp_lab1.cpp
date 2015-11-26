#include "stdafx.h"
#include "time.h"
#include <iostream>
#include "Windows.h"
#include "Matrix.h"
#include <vector>
#include <typeinfo>

using namespace std;

#define N 10
#define SIZE 1000
#define ULLONG unsigned long long
#define LLONG long long
#define SECONDS 2000

int* arr;
ULLONG start, finish,  min;

ULLONG func(int* a = arr, int size = SIZE){
	ULLONG sum = 0;

	for (int i = 0; i < size; i++){
		sum += a[i];
	}
	return sum;
}

void initialize(){
	arr = new int[SIZE];
	for (int i = 0; i < SIZE; i++){
		arr[i] = i;
	}
}

UINT64 fileTimeToUint64(FILETIME* ft) {
	return (((UINT64)ft->dwHighDateTime << 32) | ft->dwLowDateTime);
}

// Task 1.
void Task1(){
	time_t time = 0x7FFFFFFF;
	FILETIME ft;
	_SYSTEMTIME st;
	LLONG ll;

	ll = Int32x32To64(time, 10000000) + 116444736000000000; // jan 1st 1970
	ft.dwLowDateTime = (DWORD)ll;
	ft.dwHighDateTime = ll >> 32;

	FileTimeToSystemTime(&ft, &st);

	printf("~~~~~~~~~~~~~~~~~~~~~~~Task1~~~~~~~~~~~~~~~~~~~~~~~\n");
	_tprintf(_T("Time limit for time_t: %d.%d.%d \n\n"), st.wDay, st.wMonth, st.wYear);
}

// Task 2.
void getSys(){
	FILETIME ft, ft1;
	UINT64 min = (1 << 64) - 1; // max
	for (int i = 0; i < N; i++){
		GetSystemTimePreciseAsFileTime(&ft);
		GetSystemTimePreciseAsFileTime(&ft1);
		while (ft.dwLowDateTime == ft1.dwLowDateTime){
			GetSystemTimePreciseAsFileTime(&ft1);
		}
		UINT64 dif = fileTimeToUint64(&ft1) - fileTimeToUint64(&ft);
		if (min > dif){
			min = dif;
		}
	}
	printf("GetSystemTimePreciseAsFileTime: %I64d\n", min);
}

void getTick(){
	DWORD start, end, min = ULONG_MAX;
	for (int i = 0; i < 10; i++) {
		start = GetTickCount(),
			finish = GetTickCount();
		while (start == finish){
			finish = GetTickCount();
		}
		if (min > finish - start){
			min = finish - start;
		}
	}
	std::cout << "GetTickCount: " << min << endl << endl;
}

void Task2(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task2~~~~~~~~~~~~~~~~~~~~~~~\n");
	getSys();
	getTick();
}

// Task 3.
inline UINT64 getTacts(){
	__asm{
		mov eax, 0
			rdtsc
	}
}

void asm1(){
	min = ULLONG_MAX;
	for (int i = 0; i < 10; ++i) {
		start = getTacts();
		func();
		finish = getTacts();
		if (min > finish - start) {
			min = finish - start;
		}
	}

	std::cout << "asm: " << min << endl;
}

ULLONG rdtsc(int* ar, int size){
	min = ULLONG_MAX;
	LLONG sum = 0;
	for (int i = 0; i < N; i++){
		start = __rdtsc();
		sum = func(ar, size);
		finish= __rdtsc();
		if (finish- start < min){
			min = finish- start;
		}
	}
	return min;
}

void query(){
	LARGE_INTEGER freq, start, finish, count;
	LLONG dif, min = LLONG_MAX;
	QueryPerformanceFrequency(&freq);
	for (int j = 0; j < N; ++j){
		QueryPerformanceCounter(&start);
		func();
		QueryPerformanceCounter(&finish);
		dif = finish.QuadPart - start.QuadPart;
		//printf("s = %d\tTime = %I64d\n", s, dif - min);
		if (dif < min) {
			min = dif;
		}
	}
	std::cout << "query: " << min << endl << endl;
}

void Task3(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task3~~~~~~~~~~~~~~~~~~~~~~~\n");
	asm1();
	std::cout << "rdtsc: " << rdtsc(arr, SIZE) << endl;
	query();
}

// Task 4.
UINT countIter(int arr[], size_t size){
	min = ULLONG_MAX;
	UINT iter = 0;
	start = GetTickCount();
	do{
		func(arr, size);
		finish = GetTickCount();
		iter++;
	} while (finish - start < SECONDS);

	return iter;
}

void Task4(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task4~~~~~~~~~~~~~~~~~~~~~~~\n");

	int size1 = 100000;
	int size2 = 200000;
	int size3 = 300000;

	int* arr = new int[size3];
	for (int i = 0; i < size3; i++){
		arr[i] = i;
	}

	ULLONG time1 = rdtsc(arr, size1);
	ULLONG time2 = rdtsc(arr, size2);
	ULLONG time3 = rdtsc(arr, size3);
	printf("T(200000)/T(100000)=%f\n", (double)time2 / time1);
	printf("T(300000)/T(100000)=%f\n", (double) time3 / time1);
	
	UINT iter1 = countIter(arr, size1);
	UINT iter2 = countIter(arr, size2);
	UINT iter3 = countIter(arr, size3);
	printf("iterations for size %d ==> %d\n", size1, iter1);
	printf("iterations for size %d ==> %d\n", size2, iter2);
	printf("iterations for size %d ==> %d\n", size3, iter3);

	delete[] arr;
}

// Task 5.

template <typename T>
void fill(T** a, size_t size){
	for (size_t i = 0; i < size; i++){
		a[i] = new T[size];
		for (size_t j = 0; j < size; j++){
			T temp = rand() % 101;
			a[i][j] = temp;
		}
	}
}

template <typename T>
ULLONG mul(Matrix<T> a,	Matrix<T> b, Matrix<T> &c, int size) {
	min = ULLONG_MAX;
	for (int i = 0; i < 3; i++){
		start = GetTickCount();

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				c.Arr[i][j] = 0;
				for (int k = 0; k < size; k++) {
					c.Arr[i][j] += a.Arr[i][k] * b.Arr[k][j];
				}
			}
		}

		finish = GetTickCount();
		if (finish - start < min){
			min = finish - start;
		}
	}
	return min;
}

template <typename T>
ULLONG mulArr(T** a, T** b, T** c, int size) {
	min = ULLONG_MAX;
	for (int i = 0; i < 5; i++){
		start = GetTickCount();

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				c[i][j] = 0;
				for (int k = 0; k < size; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		
		finish = GetTickCount();
		if (finish - start < min){
			min = finish - start;
		}
	}
	return min;
}

template<typename T>
void Task5_7(int size, T type){
	cout << "defining type" << endl;
	cout << "type: " << typeid(type).name() << endl;

	T** a = new T*[size];
	T** b = new T*[size];
	T** c = new T*[size];
/*
	vector<vector<T> > a1(size, vector<T>(size));
	vector<vector<T> > b1(size, vector<T>(size));
	vector<vector<T> > c1(size, vector<T>(size));*/

	fill(a, size);
	fill(b, size);
	for (int i = 0; i < size; i++){
		c[i] = new T[size];
	}

	/*Matrix<T> a1(size, a);
	Matrix<T> b1(size, b);
	Matrix<T> c1(size, c);*/
	
	ULLONG arTime = mulArr(a, b, c, size);;
	printf("Using arrays: %d\n", arTime);

	ULLONG vecTime = 0; // mul(a1, b1, c1, size);
	printf("Using vectors: %d\n", vecTime);

	if (arTime != 0){
		printf("vTime/aTime=%d\n", vecTime / arTime); // == ~50 for 512 elements
	}
	else{
		printf("Too little elements for GetTickCount().\n");
	}
	cout << "met end" << endl;
}

void Task5_7(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task5 Task7~~~~~~~~~~~~~~~~~~~~~~~\n");
	int a = 1;
	int size = 200;
	Task5_7(size, (float)a);
	//printf("----------------------------------------------------------\n");
	Task5_7(size, (double)a);
	printf("----------------------------------------------------------\n");
	Task5_7(size, (__int8)a);
	printf("----------------------------------------------------------\n");
	Task5_7(size, (__int16)a);
	printf("----------------------------------------------------------\n");
	Task5_7(size, a);
	printf("----------------------------------------------------------\n");
	Task5_7(size, (__int64)a);
}

int _tmain(int argc, _TCHAR* argv[])
{
	initialize();
/*
	Task1();
	Task2();
	Task3();
	Task4();*/
	Task5_7();


	delete[] arr;
	return 0;
}