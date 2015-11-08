#include "stdafx.h"
#include <string>

/*
Strongly not taken 00
Weakly not taken 01
Weakly taken 10
Strongly taken 11
*/

BYTE table[4] = {};

void setTable(BYTE state, BOOL input){
	BYTE cur = ((input << 1) | input); // check if 0b00 || 0b11

	if (cur != table[state]){
		if (input){
			table[state]++;
		}
		else{
			table[state]--;
		}
	}
}

BOOL predict(BYTE count, BYTE current){
	return ((count >> 1) == current);
}

BYTE getBytes(string s){
	BYTE res = (s[0] - '0') << 1;
	return (res | (s[1] - '0'));
}

void Task5(){
	printf("~~~~~~~~~~~~~~~~~~~~~~~Task5~~~~~~~~~~~~~~~~~~~~~~~\n");
	char res[] = "EO";
	cout << "enter a sequence of 0 and 1: ";

	string str;
	cin >> str;

	while (str != "end"){
		string state = "00";
		string result;
		memset(table, 0, 4);

		for (int i = 0; i < str.length(); i++){
			cout << "table: ";
			for (int i = 0; i < 4; i++){
				printf("%d", table[i]);
			}
			cout << endl;

			BYTE current = str[i] - '0';
			BYTE index = getBytes(state);
			BOOL error = predict(table[index], current);

			setTable(index, current);
			result += res[error];
			state += str[i];
			state = state.substr(1, 2);
		}

		printf("%s\n", result.c_str());

		cout << "\nenter a sequence of 0 and 1: ";
		cin >> str;
	}
}