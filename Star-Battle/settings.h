#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <conio.h>
#include <locale.h>

#include <list>
#include<iostream>
#include<fstream>

#include"functions.h"
#include"process.h"
#include"menu.h"

#define central_output(n) (80 - n)/2
#define clear_ system("cls")

using namespace std;
void sett_controls(int& contr)
{
	clear_;
	gotoxy(central_output(41),2); cout << "����� ���������� � ��������� ����������!\n";
	gotoxy(central_output(35),3); cout << "��� �� ������� ��������� ��������?";
	gotoxy(central_output(49),4); cout << "�� ���������: (�������� ������ � ����� � ������)";
	Menu menu;
	vector<string> m = {
		"A-�����, D-������, Shift-�������",
		"�� ���������",
		"�����"
	};
	int ch = menu.select_vertical(m);
	switch (ch)
	{
	case 0:
		contr = 1;
		break;
	case 1:
		contr = 0;
		break;
	case 2:
		return;
	default:
		break;
	}
	/*ofstream save("settings.bin", ios::binary);
	for (size_t i = 0; i < 5; i++)
	{
		save.write((char*)&, sizeof(int));
	}
	int* a = nullptr; int size = 0;
	ifstream load("settings.bin", ios::binary);
	int t;
	while (load.read((char*)&t, sizeof(int)))
	{
		push_back_Array(a, size, t);
	}*/
}
void sett_shuttleSkin()
{

}
void settings(int &contr)
{
	clear_;
	Menu menu;
	vector<string> m = {
		"��������� ����������",
		"��� �����",
		"�����"
	};
	int ch = menu.select_vertical(m);
	switch (ch)
	{
	case 0:
		sett_controls(contr);
		break;
	case 1:
		/*sett_shuttleSkin();*/
		break;
	case 2:
		return;
	default:
		break;
	}
}