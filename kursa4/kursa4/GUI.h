#pragma once
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include "consoleGraphic.h"
#include "functions.h"
#include "immovables.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

class menu
{
protected:
    static const int line_size = 30;
    vector<string> menu;
    void virtual visual() = 0;
public:
    void virtual logic() = 0;
};

class welcome_menu : protected menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    welcome_menu();
    void logic();
};

class bye_menu : protected menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    bye_menu();
    void logic();
};

class log_in_menu : protected menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    log_in_menu();
    void logic();
};

class main_menu : protected menu
{
private:
    static const int num_of_lines = 6;
    void visual();
public:
    void logic();
    main_menu();
};

class login_state_menu : protected menu
{
protected:
    static const int num_of_lines = 5;
    void visual();
public:
    void virtual logic() = 0;
};

class login_error_id : protected login_state_menu
{
private:
public:
    void logic();
    login_error_id();
};

class login_error_pass : protected login_state_menu
{
private:
public:
    void logic();
    login_error_pass();
};

class login_error_id_pass : protected login_state_menu
{
private:
public:
    void logic();
    login_error_id_pass();
};

class login_success : protected login_state_menu
{
private:
public:
    void logic();
    login_success();
};

class sign_in_menu : private menu
{
private:
    static const int num_of_lines = 8;
    void visual();
public:
    sign_in_menu();
    void logic();
};

class signin_error_id_exist : protected login_state_menu
{
protected:
public:
    void logic();
    signin_error_id_exist();
};

class signin_error_passes_dont_match : protected login_state_menu
{
protected:
public:
    void logic();
    signin_error_passes_dont_match();
};

class program_menu : protected menu
{
protected:
    static const int num_of_lines = 6;
    void visual();
public:
    void logic();
};

template<class T>
class immovable_window2 : protected menu
{
private:
    T *house;
    int y;
    void visual();
public:
    immovable_window2(T& _imm);
    void setMenuPoles();
    void logic();
    int getY();
};
template <class T> immovable_window2<T>::immovable_window2(T& _imm)
{
    house = new T;
    house = &_imm;
    setMenuPoles();
    y = menu.size() + 4;
}
template <class T> void immovable_window2<T>::setMenuPoles()
{

    menu = house->getPoles();
}
template <class T> void immovable_window2<T>::visual()
{
    print_border(line_size, 0);
    print_menu_el(menu[0], line_size, 1);
    print_line(line_size);
    for (int i = 1; i < menu.size(); i++)
        print_menu_el(menu[i], line_size, 0);
    print_line(line_size);
    print_menu_el("[VIEW MORE]   [ADD TO COMPARE]", line_size, 0);
    print_border(line_size, 1);
}
template <class T> void immovable_window2<T>::logic()
{
    visual();
}
template <class T> int immovable_window2<T>::getY()
{
    return y;
}

