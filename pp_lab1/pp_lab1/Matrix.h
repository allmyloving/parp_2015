#pragma once
#include <Windows.h>
#include "stdafx.h"

template <typename T>
class Matrix
{
public:
	T** Arr;

	Matrix(int size, T** arr);
	~Matrix();

	int getSize();
	T get(int i, int j);
private:
	int size;
};


template <typename T>
Matrix<T>::Matrix(int sizeOfMatrix, T** arr){
	size = sizeOfMatrix;
	Arr = new T*[size];
	for (int i = 0; i < size; ++i){
		Arr[i] = new T[size];
		for (int j = 0; j < size;  j++){
			Arr[i][j] = arr[i][j];
		}
	}
}

template <typename T>
Matrix<T>::~Matrix(){
	for (int i = 0; i < size; ++i){
		delete Arr[i];
	}
	delete Arr;
}

template <typename T>
T Matrix<T>::get(int i, int j){
	return Arr[i][j];
}

template <typename T>
int Matrix<T>::getSize(){
	return size;
}