#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <conio.h>
#include <locale.h>
#include <stdio.h>

#include <list>
#include<vector>
#include<string>
#include<iostream>
#include"menu.h"
#include"functions.h"

#define clear_ system("cls")
#define left_arrow 75
#define right_arrow 77
#define space 32

using namespace std;

void frame()
{
	clear_;
	int i = 0;
	while (i < 79)
	{
		gotoxy(i, 0);
		cout << "=";
		gotoxy(i, 24);
		cout << "=";
		i++;
	}
}
struct Date
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
	void print(ofstream& a)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		year = 1900 + ltm->tm_year;
		month = 1 + ltm->tm_mon;
		day = ltm->tm_mday;
		hour = ltm->tm_hour;
		minute = ltm->tm_min;
		a << " | Время попытки: ";
		if (hour < 10)
			a << "0";
		a << hour << ":";
		if (minute < 10)
			a << "0";
		a << minute << " ";
		if (day < 10)
			a << "0";
		a << day << "/";
		if (month < 10)
			a << "0";
		a << month << "/" << year;
	}
};
struct Rate
{
	Date date;
	char* name;
	int score;
};
struct Game
{
	int size = 0;
	Rate* p = nullptr;
	void save(int score)
	{
		Rate m;
		char buffer[80];
		bool flag = true;
		while (flag)
		{
			cout << "Введите свое имя(от 3 символов): "; cin.getline(buffer, 80);
			if (strlen(buffer) <= 2)
			{
				for (size_t i = 0; i < 3; i++)
				{
					gotoxy((80-28)/2,i+12);
					cout << "Введите действительное имя!";
					Sleep(250);
				}
				clear_;
			}
			else {
				m.name = new char[strlen(buffer) + 1];
				strcpy(m.name, buffer);
				clear_;
				m.score = score;
				push_back_Array(p, size, m);
				ofstream a("rate.txt", ios::app);
				for (size_t i = 0; i < size; i++)
				{
					for (size_t i = 0; i < size; i++)
						a << p[i].name << " | Счёт: " << m.score; m.date.print(a);
					a << endl;
				}
				a.close();
				gotoxy((80 - 24) / 2, 13);
				cout << "Твой прогресс сохранен.";
				flag = false;
			}
		}
	}
	void load()
	{
		ifstream check("rate.txt");
		check.seekg(0, ios::end);
		char buff[80]; int size = 0, file_size = check.tellg(); size_t i = 23;
		check.close();
		if (file_size == 0) {
			gotoxy((80 - 26) / 2, 12);
			cout << "Статистика отсутствует.\n";
		}
		else {
			ifstream save("rate.txt");
			while (save.getline(buff, 80))
			{
				gotoxy((80 - strlen(buff)) / 2, i--);
				cout << buff << endl;
				if (i == 0) {
					frame();
					i = 23;
				}
				Sleep(150);
			}
			save.close();
		}
		system("pause>0");
	}
};

int count_lenth()
{
	ifstream entity("entity.txt");
	char t[80], temp[80]; int i = 3, tempmax = 0;
	while (entity.getline(t, 80))
	{
		if (strlen(t) > strlen(temp))
		{
			strcpy(temp, t);
		}
	}
	tempmax = strlen(temp);
	entity.close();
	return tempmax;
}
void clear_str(int x)
{
	gotoxy(x, 1);
	cout << ' ';
}
void set_score_array(int* shots)
{
	int barrier = (80 - count_lenth()) / 2;
	for (size_t i = 0; i < 79; i++)
	{
		if (i >= barrier && i <= barrier + count_lenth() - 1)
			shots[i] = 1;
		else
			shots[i] = 0;
		/*gotoxy(i, 24);
		cout << shots[i];*/
	}
}

void entity_to_destroy()
{
	ifstream entity("entity.txt");
	char t[80], b[80], bt[80]; int i = 3, tempmax;
	while (entity.getline(t, 80))
	{
		int x = ((80 - strlen(t)) / 2);
		i++;
		gotoxy(x, i);
		cout << t << endl;
	}
	entity.close();
}
void print_plane(int shift, int key, bool f)
{
	ifstream plane("plane.txt");
	char t[80]; int i = 15;
	while (plane.getline(t, 80))
	{
		int x = ((80 - strlen(t)) / 2);
		if (x + strlen(t) != 79)
		{
			x += shift;
			i++;
			gotoxy(x, i);
			cout << t << endl;
			if (f) 
			{
				if (key == right_arrow)
					x--;
				if (key == left_arrow)
					x += strlen(t);
				gotoxy(x, i);
				cout << ' ';
			}
		}
	}
	plane.close();
}
int shot(int shift, int* shots)
{
	int x = 39 + shift, y = 16, ty = y - 1, f = 0, check = 0; char snaryad[2] = "!";
	int barrier = (80 - count_lenth()) / 2;
	while (y != 1)
	{
		y--;
		gotoxy(x, y);
		SetColor(LightGreen, Black);
		cout << '!';
		SetColor(LightGray, Black);
		if (f >= 1)
		{
			gotoxy(x, ty);
			cout << ' ';
			ty--;
		}
		Sleep(15);
		++f;
	}
	clear_str(x);
	if (shots[x] != 0)
	{
		shots[x] = 0;
		return 1;
	}
	if (!shots[x])
		return 0;
}
void game_process()
{
	entity_to_destroy();
	print_plane(0, 0, 0);
	int barrier = 34, shift = 0, score = 0, shot_temp = 0, health = 3;
	int shots[80];
	bool flag = 0;
	gotoxy(1, 23);
	cout << "Score: " << score;
	gotoxy(1, 1);
	cout << "Health: " << health;
	set_score_array(shots);
	while (flag == 0)
	{
		int key = _getch();
		switch (key)
		{
		case left_arrow:
			if (barrier != 0) {
				shift += -1;
				print_plane(shift, key, 1);
				barrier--;
			}
			break;
		case right_arrow:
			if (barrier != 68) {
				shift += 1;
				print_plane(shift, key, 1);
				barrier++; 
			}
			break;
		case space:
			shot_temp = shot(shift, shots);
			if (shot_temp == 1)
				score++;
			if (shot_temp == 0)
				health--;
			break;
		}
		gotoxy(1, 23);
		cout << "Score: " << score;
		gotoxy(1, 1);
		cout << "Health: " << health;
		if (health == 0 or score == count_lenth())
			flag = 1;
	}
	clear_;
	if (health == 0)
		cout << "Вы проиграли! ";
	else
		cout << "Вы прошли уровень! ";
	cout << "Ваш счёт: " << score << endl;
	Game t;
	t.save(score);
	system("pause>0");
}