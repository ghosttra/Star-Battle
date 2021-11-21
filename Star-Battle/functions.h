#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<Windows.h>

#include<iostream>
#include<fstream>

#include"menu.h"

using namespace std;

template<class T>
void push_back_Array(T*& a, int& n, T elem)
{
	T* b = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		b[i] = a[i];
	}
	b[n] = elem;
	delete[]a;
	n++;
	a = b;
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
