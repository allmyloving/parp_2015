#include "stdafx.h"

void shift(int* a, int* b, size_t size){
	BYTE bit = 0;
	for (int i = size - 1; i >= 0; i--){
		//cout << "bit ==> " << (int)bit << endl;
		//cout << (a[i] << 1) << endl;
		bit = (a[i] >> 31) & 1;
		b[i] = (a[i] << 1) | bit;
	}
}

void shiftSSE(int* a, int* b, size_t size){
	__m128i* pa = (__m128i*) a;
	__m128i* pb = (__m128i*) b;

	__m128i bits[4];
	__m128i one = _mm_set1_epi32(1);

	start1 = __rdtsc();
	for (int i = 0; i < size / 4; i++){
		bits[i] = _mm_srli_epi32(pa[i], 31);

		pb[i] = _mm_slli_epi32(pa[i], 1);
		pb[i] = _mm_or_si128(pb[i], bits[i]);
	}

	finish1 = __rdtsc();
	printf("time with sse:%d\n", finish1 - start1);
}
void print(int arr[], size_t size){
	for (size_t i = 0; i < size; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
}
void Task5(){
	const int size = 16;
	__declspec(align(16)) int a[size];
	__declspec(align(16)) int b[size] = {};

//	print(a, size);
	start1 = __rdtsc();
	shift(a, b, size);
	finish1 = __rdtsc();
	printf("time no sse :%d\n", finish1 - start1);
//	print(b, size);

	//start1 = __rdtsc();
	shiftSSE(a, b, size);
	//finish1 = __rdtsc();
	//print(b, size);
}