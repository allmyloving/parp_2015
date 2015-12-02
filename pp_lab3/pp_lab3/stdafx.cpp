// stdafx.cpp : source file that includes just the standard includes
// pp_lab3.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




template <typename T>
void print(T arr[], size_t size){
	for (size_t i = 0; i < size; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
}

