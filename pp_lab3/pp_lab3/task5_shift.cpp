#include "stdafx.h"

void shift(int* a, int* b, size_t size){
	for (int i = 0; i < size; i++){
		b[i] = (a[i] << 1);
	}
}

void shiftSSE(int* a, int* b, size_t size){
	__m128i* pa = (__m128i*) a;
	__m128i* pb = (__m128i*) b;

	for (int i = 0; i < size / 4; i++){
		pb[i] = _mm_slli_epi32(pa[i], 1);
	}
}
void print(int arr[], size_t size){
	for (size_t i = 0; i < size; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
}
void Task5(){
	const int size = 10;
	__declspec(align(16)) int a[size];
	__declspec(align(16)) int b[size] = {};

	fill(a, size);
	print(a, size);

	shiftSSE(a, b, size);
	print(b, size);
}