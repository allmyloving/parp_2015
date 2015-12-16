// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include "math.h"
#include "Windows.h"
#include "omp.h"
#include "time.h"


using namespace std;

#define CreateThreadU(threadFunc, params) CreateThread(0, 0, threadFunc, params, 0, 0);

#define ULLONG unsigned long long
#define PI_PRECISION 100000000

void Task4();
