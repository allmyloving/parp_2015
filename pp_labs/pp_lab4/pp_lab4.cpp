// pp_lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>

void Task1(){
	printf("-----------Task1-----------\n");
#ifdef _OPENMP
	printf("_OPENMP Defined\n");
#else
	printf("_OPENMP UnDefined\n");
#endif
}

void Task2(){
	printf("\n-----------Task2-----------\n");
	int regs[4];

	//true for Intel processor
	__cpuid(regs, 4);
	int cores = ((regs[0] >> 27) & 0x3f) + 1;
	printf("cpu cores (Windows) ==> %d\n", cores);

	cores = omp_get_max_threads();
	printf("cpu cores (OpenMP) ==> %d\n", cores);
}

double Task3_1(ULLONG p){
	double pi = 1;
	double denom = 3;

	double sign = -1;

	for (ULLONG i = 0; i < p; i++){
		pi += sign / denom;
		denom += 2;
		sign *= -1;
	}

	return pi * 4;
}

double Task3_2(ULLONG p){
	double pi = 0.;
	double dx = 1. / p;
	double x = 0.;
	for (ULLONG i = 0; i < p; i++) {
		pi += sqrt(1 - x * x) * dx;
		x += dx;
	}

	return 4 * pi;
}

double Task3_3(ULLONG p){
	double pi = 0;

	for (long i = 1.0; i < p; i++){
		pi += (1 / ((double)i*i));
		//cout << pi << endl;
	}
	return sqrt(pi * 6);
}

// pi ~ 3.14159...
void Task3(){
	printf("\n-----------Task3-----------\n");

	ULLONG start, end, min = ULLONG_MAX;
	double pi;
	for (int i = 0; i < 1; i++){
		start = GetTickCount();// __rdtsc();
		start = clock();
		pi = Task3_1(PI_PRECISION);
		end = GetTickCount();// __rdtsc();
		end = clock();
		cout << start << " " << end << endl;
		if (min > end - start){
			min = end - start;
		}
	}
	printf("pi=%1.10f\ttime=%llu\n", pi, min);
	min = LONG_MAX;

	for (int i = 0; i < 1; i++){
		start = GetTickCount(); //__rdtsc();
		pi = Task3_2(PI_PRECISION);
		end = GetTickCount(); //__rdtsc();
		if (min > end - start){
			min = end - start;
		}
	}
	printf("pi=%1.10f\ttime=%d\n", pi, min);

	min = LONG_MAX;
	for (int i = 0; i < 3; i++){
		start = GetTickCount(); //__rdtsc();
		pi = Task3_3(PI_PRECISION);
		end = GetTickCount(); //__rdtsc();
		if (min > end - start){
			min = end - start;
		}
	}
	printf("pi=%1.10f\ttime=%d\n", pi, min);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Task1();
	Task2();
	Task3();
	Task4();
	return 0;
}

