// pp_lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <typeinfo> 

#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" //early engineering samples of AMD K5 processor
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA          "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"


// http://wiki.osdev.org/CPUID
//EBX = 'u' 'n' 'e' 'G'
//EDX = 'I' 'e' 'n' 'i'
//ECX = 'l' 'e' 't' 'n'

void getVendorId(int ebx, int ecx, int edx){
	char c[13];
	int i = 0;
	c[i++] = (char)(ebx & 0xFF);
	c[i++] = (char)((ebx >> 8) & 0xFFFF);
	c[i++] = (char)((ebx >> 16) & 0xFFFFFF);
	c[i++] = (char)((ebx >> 24) & 0xFFFFFFFF);

	c[i++] = (char)(edx & 0xFF);
	c[i++] = (char)((edx >> 8) & 0xFFFF);
	c[i++] = (char)((edx >> 16) & 0xFFFFFF);
	c[i++] = (char)((edx >> 24) & 0xFFFFFFFF);

	c[i++] = (char)(ecx & 0xFF);
	c[i++] = (char)((ecx >> 8) & 0xFFFF);
	c[i++] = (char)((ecx >> 16) & 0xFFFFFF);
	c[i++] = (char)((ecx >> 24) & 0xFFFFFFFF);
	c[i++] = '\0';

	printf("vendor: ");
	for (int j = 0; j < 12; j++){
		std::cout << c[j];
	}
	std::cout << endl;
}

void Task1(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task1~~~~~~~~~~~~~~~~~~~~~~~\n");

	int r[4] = {};
	__cpuid(r, 0);
	getVendorId(r[1], r[2], r[3]);
	__cpuid(r, 1);


	BOOL bSSE = ((r[3] >> 25) & 1) != 0;
	BOOL bSSE2 = ((r[3] >> 26) & 1) != 0;
	BOOL bSSE3 = (r[2] & 1) != 0;
	BOOL bSSSE3 = ((r[2] >> 9) & 1) != 0;
	BOOL bSSE4_1 = ((r[2] >> 19) & 1) != 0;
	BOOL bSSE4_2 = ((r[2] >> 20) & 1) != 0;
	BOOL bAVX = ((r[2] >> 26) & 7) != 0;
	BOOL bAVX2 = bAVX & ((r[1] >> 5) & 1 != 0);


	printf("SSE support: %d\n", bSSE);
	printf("SSSE2 support: %d\n", bSSE2);
	printf("SSE3 support: %d\n", bSSE3);
	printf("SSSE3 support: %d\n", bSSSE3);
	printf("SSE4.1 support: %d\n", bSSE4_1);
	printf("SSE4.2 support: %d\n", bSSE4_2);
	printf("AVX support: %d\n", bAVX);
	printf("AVX2 support: %d\n", bAVX2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	Task1();
	Task2();
	Task3();
	Task4();
	Task5();

	
	//func1(print);
	return 0;
}

