#pragma once
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include "consoleGraphic.h"
#include "function.h"
#include "immovables.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

void create_more_info(immovables* _ptr);

class menu
{
protected:
    static const int line_size = 30;
    vector<string> menu_list;
    void virtual visual() = 0;
public:
    void virtual logic() = 0;
    virtual ~menu() {};
};

class welcome_menu : public menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    welcome_menu();
    void logic();
};

class bye_menu : public menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    bye_menu();
    void logic();
};

class log_in_menu : public menu
{
private:
    static const int num_of_lines = 5;
    void visual();
public:
    log_in_menu();
    void logic();
};

class main_menu : public menu
{
private:
    static const int num_of_lines = 6;
    void visual();
public:
    void logic();
    main_menu();
};

class login_state_menu : public menu
{
protected:
    static const int num_of_lines = 5;
    void visual();
public:
    void virtual logic() = 0;
    //virtual ~login_state_menu();
};

class login_error_id : public login_state_menu
{
private:
public:
    void logic();
    login_error_id();
};

class login_error_pass : public login_state_menu
{
private:
public:
    void logic();
    login_error_pass();
};

class login_error_id_pass : public login_state_menu
{
private:
public:
    void logic();
    login_error_id_pass();
};

class login_success : public login_state_menu
{
private:
public:
    void logic();
    login_success();
};

class sign_in_menu : public menu
{
private:
    static const int num_of_lines = 8;
    void visual();
public:
    sign_in_menu();
    void logic();
};

class signin_error_id_exist : public login_state_menu
{
protected:
public:
    void logic();
    signin_error_id_exist();
};

class signin_error_passes_dont_match : public login_state_menu
{
protected:
public:
    void logic();
    signin_error_passes_dont_match();
};

class program_menu : public menu
{
protected:
    static const int num_of_lines = 6;
    void visual();
public:
    void logic();
};

template<class T>
class immovable_window2 : public menu
{
protected:
    T* house;
    int y;
    void virtual visual();
public:
    immovable_window2(T& _imm);
    void setMenuPoles();
    void virtual logic();
    int getY();
};
template <class T> immovable_window2<T>::immovable_window2(T& _imm)
{
    house = new T;
    house = &_imm;
    setMenuPoles();
    y = menu_list.size() + 4;
}
template <class T> void immovable_window2<T>::setMenuPoles()
{
    menu_list = house->getPoles();
}
template <class T> void immovable_window2<T>::visual()
{
    print_border(line_size, 0);
    print_menu_el(menu_list[0], line_size, 1);
    print_line(line_size);
    for (int i = 1; i < menu_list.size(); i++)
        print_menu_el(menu_list[i], line_size, 0);
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

template <class T>
class more_info : protected immovable_window2<T>, public menu
{
protected:
    vector<string> description;
    void visual();
public:
    more_info(T& _imm);
    void logic();
};
template <class T> more_info<T>::more_info(T& _imm) : immovable_window2<T>(_imm)
{
    ifstream f;
    f.open(DESCRIPTION_FILE, ios::in);
    find_description(f, immovable_window2<T>::house->id);
    string temp;
    getline(f, temp);
    description.push_back(temp);
}
template <class T> void more_info<T>::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(immovable_window2<T>::menu_list[0], line_size, 1);
    print_line(line_size);

    for (int i = 1; i < immovable_window2<T>::menu_list.size(); i++)
        print_menu_el(immovable_window2<T>::menu_list[i], line_size, 0);

    print_line(line_size);

    vector <string>* ptr = immovable_window2<T>::house->conveniences;
    for (int i = 0; i < ptr->size(); i++)
        print_menu_el((*ptr)[i], line_size, 0);

    print_line(line_size);

    for (int i = 0; i < description.size(); i++)
        print_menu_el(description[i], line_size, 0);

    print_line(line_size);
    print_menu_el("(1) - SEE OWNER'S CONTACTS", line_size, 0);
    print_menu_el("(0) - RETURN BACK", line_size, 0);
    print_border(line_size, 1);
}
template <class T> void more_info<T>::logic()
{
    visual();
    _getch();
}

class immovable_list : public menu
{
protected:
    unsigned int num_of_lines = 2;
    void visual()
    {
        system("cls");
        print_border(line_size, 0);
        print_menu_el(menu_list[0], line_size, 1);
        print_border(line_size, 1);
    }
public:
    immovable_list()
    {
        string temp_menu[] = { "GOOD LUCK!", "[<-]  [ 1 ]  [->]"};
        for (int i = 0; i < num_of_lines; i++)
            menu_list.push_back(temp_menu[i]);
    }
    void logic()
    {
        ifstream f;
        f.open(FILE_NAME, ios::in);
        vector<immovables*> vec;
        int _count;
        int _curEl = 0;
        int pageNumber = 1;
        int loadedObjects = 0;
        int lastPage = -1;
        bool isEndReached = false;
        string buffer;
        WORD choice;
        int y[2];
        do
        {
            if (isEndReached && pageNumber == lastPage)
                _count = vec.size() - _curEl;
            else
                _count = 2;
            int i = 0;
            bool isAnyButtonPressed = false;

            visual();

            if (loadedObjects <= _curEl) {
                _count = load_base(&vec, f, _count);
                loadedObjects += _count;
            }
            for (int i = _curEl; i < _curEl + _count; i++)
            {
                immovables* ptr = vec[i];
                if (*(ptr->type) == "Detached house") {
                    immovable_window2<detached_house> w(*(detached_house*)(ptr));
                    w.logic();
                    y[i - _curEl] = w.getY();
                }
                else if (*(ptr->type) == "Bungalo") {
                    immovable_window2<bungalo> w(*(bungalo*)(ptr));
                    w.logic();
                    y[i - _curEl] = w.getY();
                }
                else if (*(ptr->type) == "Villa") {
                    immovable_window2<villa> w(*(villa*)(ptr));
                    w.logic();
                    y[i - _curEl] = w.getY();
                }
            }
            if (!isEndReached && (f.eof() || _count == 0)) {
                menu_list[1].replace(14, 2, "  ");
                lastPage = pageNumber;
                isEndReached = true;
                y[1] = -2;
            }
            if (pageNumber == 1)
                menu_list[1].replace(1, 2, "  ");
            else
                menu_list[1].replace(1, 2, "<-");
            if (pageNumber == lastPage)
                menu_list[1].replace(14, 2, "  ");
            else
                menu_list[1].replace(14, 2, "->");
            print_border(line_size, 0);
            print_menu_el(menu_list[1], line_size, 1);
            print_border(line_size, 1);
            setup_console();

            ReadConsoleInput(hin, &InputRecord, 1, &Events);
            while (InputRecord.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED && !isAnyButtonPressed)
            {
                ReadConsoleInput(hin, &InputRecord, 1, &Events);
                if (InputRecord.Event.KeyEvent.bKeyDown && ((InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && pageNumber != 1) || (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && pageNumber != lastPage))) {
                    isAnyButtonPressed = true;
                    choice = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                }
            }
            if (!isAnyButtonPressed) {
                choice = (WORD)'x';
            }
            if (pageNumber != lastPage && (choice == VK_RIGHT || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
                && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 21, 24) && InputRecord.Event.MouseEvent.dwMousePosition.Y == y[0] + y[1] + 6)))) {
                menu_list[1].replace(8, 1, to_string(++pageNumber));
                _curEl += 2;
            }
            else if (pageNumber != 1 && (choice == VK_LEFT || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
                && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 8, 11) && InputRecord.Event.MouseEvent.dwMousePosition.Y == y[0] + y[1] + 6)))){
                menu_list[1].replace(8, 1, to_string(--pageNumber));
                _curEl -= 2;
            }
            else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
                && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 1, 11) && InputRecord.Event.MouseEvent.dwMousePosition.Y == y[0] + 2)) {
                immovables* ptr = vec[_curEl];
                create_more_info(ptr);
            }
            else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
                && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 1, 11) && InputRecord.Event.MouseEvent.dwMousePosition.Y == y[0] + y[1] + 3)) {
                immovables* ptr = vec[_curEl+1];
                create_more_info(ptr);
                }
        } while (choice != '0' && !(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 18) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 6));
    }
};