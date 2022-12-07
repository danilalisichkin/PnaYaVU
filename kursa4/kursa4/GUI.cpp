#include "GUI.h"

welcome_menu::welcome_menu()
{
    string temp_menu[] = { " ", " ", "WELCOME!", " "," " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void welcome_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(this->menu_list[0], line_size, 0);
    print_menu_el(this->menu_list[1], line_size, 0);
    print_menu_el(this->menu_list[2], line_size, 1);
    print_menu_el(this->menu_list[3], line_size, 0);
    print_menu_el(this->menu_list[4], line_size, 0);
    print_border(line_size, 1);
}
void welcome_menu::logic()
{
    welcome_menu::visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/starting.wav"), NULL, SND_SYNC);
}

bye_menu::bye_menu()
{
    string temp_menu[] = { " ", " ", "GOOD BYE!", " "," " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void bye_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(this->menu_list[0], line_size, 0);
    print_menu_el(this->menu_list[1], line_size, 0);
    print_menu_el(this->menu_list[2], line_size, 1);
    print_menu_el(this->menu_list[3], line_size, 0);
    print_menu_el(this->menu_list[4], line_size, 0);
    print_border(line_size, 1);
}
void bye_menu::logic()
{
    bye_menu::visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/endng.wav"), NULL, SND_SYNC);
    system("cls");
}

log_in_menu::log_in_menu()
{
    string temp_menu[] = { "PLEASE LOG IN!", " (1)[ID]: xxxxxxxx", " (2)[PIN]: xxxx", ""," (0) - RETURN BACK" };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void log_in_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(this->menu_list[0], line_size, 1);
    print_line(line_size);
    print_menu_el(this->menu_list[1], line_size, 0);
    print_menu_el(this->menu_list[2], line_size, 0);
    print_menu_el(this->menu_list[3], line_size, 0);
    print_menu_el(this->menu_list[4], line_size, 0);
    print_border(line_size, 1);
}
void log_in_menu::logic()
{
    string id;
    string pass;
    WORD choice;
    bool isPass = false;
    bool isId = false;
    do
    {
        bool isAnyButtonPressed = false;
        visual();
        setup_console();
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        while (InputRecord.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED && !isAnyButtonPressed)
        {
            ReadConsoleInput(hin, &InputRecord, 1, &Events);
            if (InputRecord.Event.KeyEvent.bKeyDown && isBelongs(InputRecord.Event.KeyEvent.wVirtualKeyCode, (WORD)'0', (WORD)'2')) {
                isAnyButtonPressed = true;
                choice = InputRecord.Event.KeyEvent.wVirtualKeyCode;
            }
        }
        if (!isAnyButtonPressed) {
            choice = 'x';
        }
        if (choice == (WORD)'1' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 18) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 3))) {
            SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ~ENABLE_MOUSE_INPUT);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 11,3 });
            cin >> id;
            cin.clear();
            menu_list[1].replace(10, 8, id);
            isId = true;
        }
        else if (choice == (WORD)'2' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 15) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 4))) {
            SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ~ENABLE_MOUSE_INPUT);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 12,4 });
            cin >> pass;
            cin.clear();
            menu_list[2].replace(11, 4, pass);
            isPass = true;
        }
        if (isPass && isId) {
            if (id != "12345678") {
                login_error_id m;
                m.logic();
                menu_list[1] = " (1)[ID]: xxxxxxxx";
                menu_list[2] = " (2)[PIN]: xxxx";
                isId = false;
                isPass = false;
            }
            else if (pass != "1111" && id == "12345678") {
                login_error_pass m;
                m.logic();
                menu_list[2] = " (2)[PIN]: xxxx";
                isPass = false;
            }
            else {
                login_success m;
                m.logic();
                immovable_list l;
                l.logic();
            }
        }
    } while (choice != (WORD)'0' && !(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
        && isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 18) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 6));
}

main_menu::main_menu()
{
    string temp_menu[] = { "WELCOME!", "PLEASE LOG OR SIGN IN!", " (1) - LOG IN", " (2) - SIG IN", " "," (0) - EXIT THE PROGRAM" };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void main_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(menu_list[0], line_size, 1);
    print_menu_el(menu_list[1], line_size, 1);
    print_line(line_size);
    print_menu_el(menu_list[2], line_size, 0);
    print_menu_el(menu_list[3], line_size, 0);
    print_menu_el(menu_list[4], line_size, 0);
    print_menu_el(menu_list[5], line_size, 0);
    print_border(line_size, 1);
}
void main_menu::logic()
{
    char choice;
    do
    {
        bool isAnyButtonPressed = false;
        visual();
        setup_console();
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        while (InputRecord.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED && !isAnyButtonPressed)
        {
            ReadConsoleInput(hin, &InputRecord, 1, &Events);
            if (InputRecord.Event.KeyEvent.bKeyDown && isBelongs((char)InputRecord.Event.KeyEvent.wVirtualKeyCode, '0', '2')) {
                isAnyButtonPressed = true;
                choice = InputRecord.Event.KeyEvent.wVirtualKeyCode;
            }
        }
        if (!isAnyButtonPressed) {
            choice = 'x';
        }
        if (choice == '1' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 13) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 4))) {
            log_in_menu lgm;
            lgm.logic();
        }
        else if (choice == '2' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 13) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 5))){
            sign_in_menu snm;
            snm.logic();
        }

    }while(choice != '0' && !(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
        && isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 23) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 7));
    bye_menu b;
    b.logic();
}

void login_state_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(menu_list[0], line_size, 0);
    print_menu_el(menu_list[1], line_size, 1);
    print_menu_el(menu_list[2], line_size, 1);
    print_menu_el(menu_list[3], line_size, 1);
    print_menu_el(menu_list[4], line_size, 0);
    print_border(line_size, 1);
}

login_error_id::login_error_id()
{
    string temp_menu[] = { " ", "LOGIN FAIL:", "INCORRECT USER ID", "*pls repeat", " " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void login_error_id::logic()
{
    visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/error.wav"), NULL, SND_ASYNC);
    Sleep(3000);
}

login_error_pass::login_error_pass()
{
    string temp_menu[] = { " ", "LOGIN FAIL:", "INCORRECT PASSWORD", "*pls repeat", " " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void login_error_pass::logic()
{
    visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/error.wav"), NULL, SND_ASYNC);
    Sleep(3000);
}

login_success::login_success()
{
    string temp_menu[] = { " ", " ", "WELCOME!", " ", " " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void login_success::logic()
{
    visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/success.wav"), NULL, SND_ASYNC);
    Sleep(3000);
}

sign_in_menu::sign_in_menu()
{
    string temp_menu[] = { "PLS SIGN IN!"," "," (1)[ID]: xxxxxxxx"," "," (2)[    PIN    ] : xxxx", " (3)[CONFIRM PIN] : xxxx"," "," (0) - RETURN BACK" };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void sign_in_menu::visual()
{
    system("cls");
    print_border(line_size, 0);
    print_menu_el(this->menu_list[0], line_size, 1);
    print_line(line_size);
    print_menu_el(this->menu_list[1], line_size, 0);
    print_menu_el(this->menu_list[2], line_size, 0);
    print_menu_el(this->menu_list[3], line_size, 0);
    print_menu_el(this->menu_list[4], line_size, 0);
    print_menu_el(this->menu_list[5], line_size, 0);
    print_menu_el(this->menu_list[6], line_size, 0);
    print_menu_el(this->menu_list[7], line_size, 0);
    print_border(line_size, 1);
}
void sign_in_menu::logic()
{
    string id;
    string pass1;
    string pass2;
    char choice;
    bool isPass1 = false;
    bool isPass2 = false;
    bool isId = false;
    do
    {
        bool isAnyButtonPressed = false;
        visual();
        setup_console();
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        while (InputRecord.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED && !isAnyButtonPressed)
        {
            ReadConsoleInput(hin, &InputRecord, 1, &Events);
            if (InputRecord.Event.KeyEvent.bKeyDown && isBelongs((char)InputRecord.Event.KeyEvent.wVirtualKeyCode, '0', '3')){
                isAnyButtonPressed = true;
                choice = InputRecord.Event.KeyEvent.wVirtualKeyCode;
            }
        }
        if (!isAnyButtonPressed) {
            choice = 'x';
        }
        if (choice == '1' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 18) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 4))) {
            SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ~ENABLE_MOUSE_INPUT);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 11,4 });
            cin >> id;
            cin.clear();
            menu_list[2].replace(10, 8, id);
            isId = true;
        }
        else if (choice == '2' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 24) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 6))) {
            SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ~ENABLE_MOUSE_INPUT);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 21,6 });
            cin >> pass1;
            cin.clear();
            menu_list[4].replace(20, 4, pass1);
            isPass1 = true;
        }
        else if (choice == '3' || (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
            && (isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 24) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 7))) {
            SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ~ENABLE_MOUSE_INPUT);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 21,7 });
            cin >> pass2;
            cin.clear();
            menu_list[5].replace(20, 4, pass2);
            isPass2 = true;
        }
        if (isId && isPass1 && isPass2)
            if (pass1 != pass2) {
                signin_error_passes_dont_match m;
                m.logic();
                menu_list[4] = " (2)[    PIN    ] : xxxx";
                menu_list[5] = " (3)[CONFIRM PIN] : xxxx";
                isPass1 = false;
                isPass2 = false;
            }
            else {
                login_success m1;
                m1.logic();
                immovable_list l;
                l.logic();
            }
    } while (choice != '0' && !(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
        && isBelongs((int)InputRecord.Event.MouseEvent.dwMousePosition.X, 2, 18) && InputRecord.Event.MouseEvent.dwMousePosition.Y == 9));
}

signin_error_id_exist::signin_error_id_exist()
{
    string temp_menu[] = { " ", "SIGN IN FAIL:", "THIS ID IS ALREADY EXISTS!", "*pls repeat", " " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void signin_error_id_exist::logic()
{
    visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/error.wav"), NULL, SND_ASYNC);
    Sleep(3000);
}

signin_error_passes_dont_match::signin_error_passes_dont_match()
{
    string temp_menu[] = { " ", "SIGN IN FAIL:", "PASSWORDS DO NOT MATCH", "*pls repeat", " " };
    for (int i = 0; i < num_of_lines; i++)
        menu_list.push_back(temp_menu[i]);
}
void signin_error_passes_dont_match::logic()
{
    visual();
    PlaySound(TEXT("C:/Users/danil/source/repos/kursa4/kursa4/sounds/error.wav"), NULL, SND_ASYNC);
    Sleep(3000);
}

void create_more_info(immovables* _ptr)
{
    if (*(_ptr->type) == "Detached house") {
        more_info<detached_house> w(*(detached_house*)(_ptr));
        w.logic();
    }
    else if (*(_ptr->type) == "Bungalo") {
        more_info<bungalo> w(*(bungalo*)(_ptr));
        w.logic();
    }
    else if (*(_ptr->type) == "Villa") {
        more_info<villa> w(*(villa*)(_ptr));
        w.logic();
    }
}