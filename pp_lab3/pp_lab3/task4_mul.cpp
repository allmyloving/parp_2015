
#include "stdafx.h"

template <typename T>
void mul(T* x, T* y, T* z, size_t size){
	for (int i = 0; i < size; i++){
		z[i] = x[i] * y[i];
	}
}

void mulSSE_float(const float* x, const float* y, float* z, size_t size){
	__m128* px = (__m128*) x;
	__m128* py = (__m128*) y;
	__m128* pz = (__m128*) z;

	for (int i = 0; i < size / 4; i++){
		pz[i] = _mm_mul_ps(px[i], py[i]);
	}
}

void testFloatMul(){
	printf("--------------float--------------");
	__declspec(align(16)) float a[SIZE];
	__declspec(align(16)) float b[SIZE];
	__declspec(align(16)) float c[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	mul (a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	mulSSE_float(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void Task4(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task4#mul~~~~~~~~~~~~~~~~~~~~~~~\n");
	testFloatMul();
}