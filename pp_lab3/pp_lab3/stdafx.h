// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "Windows.h"
#include "intrin.h"
#include "time.h"
#include <iostream>


using namespace std;

#define SIZE 4096
#define ULLONG unsigned long

static ULLONG start1, finish1, min = ULLONG_MAX;


// TODO: reference additional headers your program requires here
template <typename T>
void fill(T arr[], size_t size);
template <typename T>
void fill(T arr[], size_t size, int min, int max); 
template <typename T>
void print(T arr[], size_t size);

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();