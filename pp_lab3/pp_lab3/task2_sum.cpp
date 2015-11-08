#include "stdafx.h"

template <typename T>
void fill(T arr[], size_t size, int max, int min){
	min = abs(max);
	for (int i = 0; i < size; i++){
		arr[i] = static_cast <T> (rand() % (max + min + 1) - min) / 1.1;

	}
	cout << endl;
}

// Task 2.
template<typename T>
void sum(const T *x, const T *y, T *z, size_t size){
	for (size_t i = 0; i < size; i++){
		z[i] = x[i] + y[i];
	}
}

void sumSSEInt(const int *x, const int *y, int *z, size_t size){
	__m128i *px = (__m128i*) x;
	__m128i *py = (__m128i*) y;
	__m128i *pz = (__m128i*) z;

	for (int i = 0; i < size / 4; i++){
		pz[i] = _mm_add_epi32(px[i], py[i]);
	}
}

void sumSSEByte(const BYTE *x, const BYTE *y, BYTE *z, size_t size){
	__m128i *px = (__m128i*) x;
	__m128i *py = (__m128i*) y;
	__m128i *pz = (__m128i*) z;

	for (int i = 0; i < size / 16; i++){
		pz[i] = _mm_add_epi8(px[i], py[i]);
	}
}

void sumSSEFloat(const float *x, const float *y, float *z, size_t size){
	__m128 *px = (__m128*) x;
	__m128 *py = (__m128*) y;
	__m128 *pz = (__m128*) z;

	for (int i = 0; i < size / 4; i++){
		pz[i] = _mm_add_ps(px[i], py[i]);
	}
}

void sumSSEDouble(const double *x, const double *y, double *z, size_t size){
	__m128d *px = (__m128d*) x;
	__m128d *py = (__m128d*) y;
	__m128d *pz = (__m128d*) z;

	for (int i = 0; i < size / 2; i++){
		pz[i] = _mm_add_pd(px[i], py[i]);
	}
}

void testInt(){
	printf("--------------int--------------\n");
	__declspec(align(16)) int a[SIZE];
	__declspec(align(16)) int b[SIZE];
	__declspec(align(16)) int c[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sum(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sumSSEInt(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}
void testByte(){
	printf("--------------byte--------------\n");
	__declspec(align(16)) BYTE a[SIZE];
	__declspec(align(16)) BYTE b[SIZE];
	__declspec(align(16)) BYTE c[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sum(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sumSSEByte(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void testFloat(){
	printf("--------------float--------------\n");
	__declspec(align(16)) float a[SIZE];
	__declspec(align(16)) float b[SIZE];
	__declspec(align(16)) float c[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sum(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sumSSEFloat(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void testDouble(){
	printf("--------------double--------------\n");
	__declspec(align(16)) double a[SIZE];
	__declspec(align(16)) double b[SIZE];
	__declspec(align(16)) double c[SIZE] = {};

	fill(a, SIZE);
	fill(b, SIZE);

	start1 = __rdtsc();
	sum(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time: " << finish1 - start1 << endl;

	start1 = __rdtsc();
	sumSSEDouble(a, b, c, SIZE);
	finish1 = __rdtsc();
	std::cout << "time SSE: " << finish1 - start1 << endl << endl;
}

void Task2(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task2~~~~~~~~~~~~~~~~~~~~~~~\n");
	testByte();
	testInt();
	testFloat();
	testDouble();
}