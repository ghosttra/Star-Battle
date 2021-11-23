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
#define central_output(n) (80 - n)/2

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
			gotoxy(central_output(40),11);
			cout << "Введите свое имя(от 3 до 15 символов): "; gotoxy(central_output(15), 12); cin.getline(buffer, 15);
			if (strlen(buffer) <= 2)
			{
				for (size_t i = 0; i < 3; i++)
				{
					gotoxy(central_output(28),i+12);
					cout << "Введите действительное имя!";
					Sleep(250);
				}
				clear_;
			}
			else {
				m.name = new char[strlen(buffer) + 1];
				strcpy(m.name, buffer);
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
				frame();
				gotoxy((central_output(24)), 11);
				cout << "Твой прогресс сохранен.";
				flag = false;
			}
		}
	}
	void load()
	{
		ifstream check("rate.txt");
		check.seekg(0, ios::end);
		char buff[80]; int size = 0, file_size = check.tellg(); size_t i =1;
		check.close();
		if (file_size == 0) {
			gotoxy(central_output(25), 12);
			cout << "Статистика отсутствует.\n";
		}
		else {
			ifstream save("rate.txt");
			size_t j = 1;
			while (save.getline(buff, 80))
			{
				gotoxy((80 - strlen(buff)) / 2, i++);
				cout << j++ << ". " << buff << endl;
				if (i == 23) {
					frame();
					i = 1;
				}
				Sleep(150);
			}
			save.close();
		}
		system("pause>0");
	}
};
void clear_str(int x)
{
	gotoxy(x, 1);
	cout << ' ';
}
int entity_to_destroy()
{
	srand(time(0));
	int rand_len = 30 + rand() % (60 - 30);
	char ch; int x, arr[12], max = 0;
	for (size_t i = 0; i < 8; i++)
	{
		arr[i] = 0;
		x = (80 - rand_len) / 2;
		for (size_t j = 0; j < rand_len; j++)
		{
			arr[i]++;
			ch = 34 + (1 + rand()% (4-1));
			gotoxy(x++, i+3);
			SetColor(7+rand()%(13-7), Black);
			cout << ch;
		}
		rand_len = 30 + rand() % (60 - 30);
		cout << endl;
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}
void set_score_array(int* shots, int length)
{
	int barrier = (80 - length) / 2;
	for (size_t i = 0; i < 79; i++)
	{
		if (i >= barrier && i <= barrier + length - 1)
			shots[i] = 1;
		else
			shots[i] = 0;
		/*gotoxy(i, 24);
		cout << shots[i];*/
	}
}
void print_plane(int shift, int key, bool f, int right, int left, int shuttle)
{
	string pl = "plane.txt";
	if (shuttle == 1) { pl = "plane1.txt"; }
	ifstream plane(pl);
	char t[80]; int i = 15;
	SetColor(Yellow, Black);
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
				if (key == right)
					x--;
				if (key == left)
					x += strlen(t);
				gotoxy(x, i);
				cout << ' ';
			}
		}
	}
	SetColor(LightGray, Black);
	plane.close();
}
int shot(int shift, int* shots, int length)
{
	int x = 39 + shift, y = 16, ty = y - 1, f = 0, check = 0; char snaryad[2] = "!";
	int barrier = (80 - (length)) / 2;
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
#define esc 27
void game_process(int contr, int shuttle)
{
	int left_arrow = 75, right_arrow = 77, shot_ = 72;
	if (contr == 1) {
		left_arrow = 97; right_arrow = 100; shot_ = 119;
	}
	int length = entity_to_destroy();
	entity_to_destroy();
	print_plane(0, 0, 0, 0, 0, shuttle);
	int barrier = 34, shift = 0, tscore = 0, score = 0, shot_temp = 0, health = 3, seven = 7;
	int shots[80];
	bool flag = 0;
	gotoxy(1, 23);
	cout << "Score: " << score;
	gotoxy(1, 1);
	SetColor(Red, Black);
	cout << "<3 <3 <3";
	SetColor(LightGray, Black);
	set_score_array(shots, length);
	while (flag == 0)
	{
		
		int key = _getch();
		if (barrier != 0 && key == left_arrow) {
			shift += -1;
			print_plane(shift, key, 1, right_arrow, left_arrow, shuttle);
			barrier--;
		}
		if (barrier != 68 && key == right_arrow) {
			shift += 1;
			print_plane(shift, key, 1, right_arrow, left_arrow, shuttle);
			barrier++;
		}
		if (key == shot_) {
			shot_temp = shot(shift, shots, length);
			if (shot_temp == 1)
			{
				score++;
				tscore++;
			}	
			if (shot_temp == 0) {
				health--;
				gotoxy(seven, 1);
				seven -= 3;
				cout << "  ";
			}

		}
		if (key == esc)
			return;
		gotoxy(1, 23);
		cout << "Score: " << score;
		if (tscore == length)
		{
			tscore = 0;
			length = entity_to_destroy();
			set_score_array(shots, length);
		}
		if (health == 0)
			flag = 1;
	}
	clear_;
	frame();
	gotoxy(central_output(15), 2); cout << "Вы проиграли! ";
	gotoxy(central_output(14), 3);
	cout << "Ваш счёт: " << score;
	Game t;
	t.save(score);
	system("pause>0");
}