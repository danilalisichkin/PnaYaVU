#pragma once
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;

static HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // �������� ����������
static INPUT_RECORD InputRecord; // ������������ ��� ����������� ���������� � ������� ���������� � ���������� ������� ������
static DWORD Events; // unsigned long
/*��������� ��������� �������*/
static DWORD prev_mode;

void setup_console();

void print_line(unsigned int window_widht);

void print_border(unsigned int window_widht, int mode);

void print_menu_el(const char menuEl[], unsigned int window_widht, int mode);

void print_menu_el(string& menuEl, unsigned int window_widht, int mode);

