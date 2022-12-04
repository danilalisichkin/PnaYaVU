#include "consoleGraphic.h"

void setup_console()
{
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши
}

void print_line(unsigned int window_widht)
{
    cout << char(204);
    cout << setfill((char)(205)) << right << setw(window_widht) << (char)(205);
    cout << char(185) << endl;
}

void print_border(unsigned int window_widht, int mode)
{
    if (mode == 0) {
        cout << char(201);
        cout << setfill((char)(205)) << right << setw(window_widht) << (char)(205);
        cout << char(187) << endl;
    }
    else if (mode == 1) {
        cout << char(200);
        cout << setfill((char)(205)) << right << setw(window_widht) << (char)(205);
        cout << char(188) << endl;
    }
    else return;
}

void print_menu_el(const char menuEl[], unsigned int window_widht, int mode)
{
    int i;
    int length = strlen(menuEl) - 1;
    cout << char(186);

    if (mode == 1) {
        i = (window_widht - length) / 2;
        cout << setfill(' ') << setw(i) << ' ';
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - i - length - 1) << char(186) << endl;
    }
    else if (mode == 0) {
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - length - 1) << char(186) << endl; //!!!
    }
    else return;
}

void print_menu_el(string& menuEl, unsigned int window_widht, int mode)
{
    int i;
    int length = menuEl.length() - 1;
    cout << char(186);

    if (mode == 1) {
        i = (window_widht - length) / 2;
        cout << setfill(' ') << setw(i) << ' ';
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - i - length - 1) << ' ';
    }
    else if (mode == 0) {
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - length - 1) << ' '; //!!!
    }
    else return;

    cout << char(186) << endl;
}