
#include "stdafx.h"

template <typename T>
void sqrt(T* x, T* y, size_t size){
	for (int i = 0; i < size; i++){
		y[i] = sqrt(x[i]);
	}
}

void sqrtSSE_float(float* x, float* y, size_t size){
	__m128* px = (__m128*) x;
	__m128* py = (__m128*) y;

	for (int i = 0; i < size / 4; i++){
		px[i] = _mm_sqrt_ps(py[i]);
	}
}

void sqrtSSE_double(double* x, double* y, size_t size){
	__m128d* px = (__m128d*) x;
	__m128d* py = (__m128d*) y;

	for (int i = 0; i < size / 2; i++){
		px[i] = _mm_sqrt_pd(py[i]);
	}
}

void testFloatSqrt(){
	printf("--------------float--------------\n");
	__declspec(align(16)) float a[SIZE];
	__declspec(align(16)) float b[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sqrt(a, b, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sqrtSSE_float(a, b, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void testDoubleSqrt(){
	printf("--------------double--------------\n");
	__declspec(align(16)) double a[SIZE];
	__declspec(align(16)) double b[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sqrt(a, b, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sqrtSSE_double(a, b, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void Task3(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task3~~~~~~~~~~~~~~~~~~~~~~~\n");
	testFloatSqrt();
	testDoubleSqrt();
}