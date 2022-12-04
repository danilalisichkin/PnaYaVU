#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

void print_line(unsigned int window_widht)
{
    cout << char(204);
    cout << setfill(char(205)) << right << setw(window_widht) << (char)205;
    cout << char(185) << endl;
}

void print_border(unsigned int window_widht, int mode)
{
    if (mode == 0) {
        cout << char(201);
        cout << setfill(char(205)) << right << setw(window_widht) << (char)205;
        cout << char(187) << endl;
    }
    else if (mode == 1) {
        cout << char(200);
        cout << setfill(char(205)) << right << setw(window_widht) << (char)205;
        cout << char(188) << endl;
    }
    else return;
}

void print_menu_el(char* menuEl, unsigned int window_widht, int mode)
{
    int i;
    unsigned int lengh = strlen(menuEl) - 1;
    cout << char(186);

    if (mode == 1) {
        i = (window_widht - lengh) / 2;
        cout << setfill(' ') << setw(i) << ' ';
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - i - lengh - 1) << ' ';
    }
    else if (mode == 0) {
        cout << menuEl;
        cout << setfill(' ') << setw(window_widht - lengh - 1) << ' ';
    }
    else return;

    cout << char(186) << endl;
}

template <typename T>
class queue
{
private:
    inline static T array[5];
    T* head;
    T* tail;
    bool isEmpty;
    template <class T> friend class Submenu;
public:
    queue()
    {
        head = array;
        tail = head;
        isEmpty = true;
    }
    queue(T _param)
    {
        head = array;
        *head = _param;
        tail = head;
        isEmpty = false;
    }
    queue(T _param1, T _param2)
    {
        head = array;
        *head = _param1;
        tail = array + 1;
        *tail = _param2;
        isEmpty = false;
    }
    ~queue()
    { }
    T pop()
    {
        if (isEmpty) {
            cout << endl << "Equeue is empty!";
            return 0;
        }
        else if (head == tail) {
            isEmpty = true;
            return *head;
        }
        T help = *head;
        T* ptr;
        ptr = head;
        while (ptr != tail) {
            *ptr = *(ptr + 1);
            ptr++;
        }
        *(tail--) = 0;
        if (tail == head && head == nullptr)
            isEmpty = true;
        return help;
    }
    void push(T _param)
    {
        if (isEmpty) {
            *head = _param;
            isEmpty = false;
        }
        else
            *(++tail) = _param;
    }
    void show()
    {
        if (isEmpty) {
            cout << endl << "Equeue is empty!" << endl;
            return;
        }
        T* help = head;
        while (help <= tail)
            cout << *help++ << '\t';
        cout << endl;
    }
    void sort(int mode = 1)
    {
        if (isEmpty) {
            cout << endl << "Equeue is empty!";
            return;
        }
        if (mode != 0 && mode != 1) {
            cout << endl << "Incorrect sorting mode!";
            return;
        }
        T m;
        T* _toExChange;
        for (T* i = tail; i > head; i--) {
            m = *i;
            _toExChange = i;
            for (T* j = i - 1; j >= head; j--) {
                if ((mode == 0 && *j < m) || (mode == 1 && *j > m)) {
                    _toExChange = j;
                    m = *_toExChange;
                }
            }
            *_toExChange = *i;
            *i = m;
        }
    }
};

template <class T>
class Submenu
{
private:
    queue<T> q;
    void submenu_visual()
    {
        char menu[][24] = { "CHOOSE THE OPERATION!", " (1) - PUSH", " (2) - POP", " (3) - SORT ./|", " (4) - SORT |\\.",
           "", " (0) - exit" };
        system("cls");
        print_border(30, 0);
        print_menu_el(menu[0], 30, 1);
        print_line(30);
        print_menu_el(menu[1], 30, 0);
        print_menu_el(menu[2], 30, 0);
        print_menu_el(menu[3], 30, 0);
        print_menu_el(menu[4], 30, 0);
        print_menu_el(menu[5], 30, 0);
        print_menu_el(menu[6], 30, 0);
        print_line(30);
    }
    void pushing()
    {
        T data;
        bool success = false;
        cout << "Try to push: ";
        while (!success)
        {
            cin >> data;
            if (cin.fail()) {
                cout << endl << "(!)Invalid format!";
                cout << endl << "   Please repeat: ";
            }
            else
                success = true;
            cin.clear();
            cin.ignore(32767, '\n');
        }
        q.push(data);
    }
    void poping()
    {
        q.pop();
    }
    void sorting_inc()
    {
        q.sort(1);
    }
    void sorting_dec()
    {
        q.sort(0);
    }
    void showing()
    {
        q.show();
    }
public:
    void submenu()
    {
        char choice;
        do
        {
            submenu_visual();
            showing();
            choice = _getch();
            switch (choice)
            {
            case '1': pushing(); break;
            case '2': poping(); break;
            case '3': sorting_inc(); break;
            case '4': sorting_dec(); break;
            }
        } while (choice != '0');
    }
    Submenu() {}
    ~Submenu() = default;
};

class Menu
{
private:
    static void menu_visual()
    {
        char menu[][24] = { "WELCOME!", " (!) Choose class type:", " (1) - int", " (2) - double", " (3) - char",
            "", " (0) - exit" };
        int NofEls = 4;
        system("cls");
        print_border(30, 0);
        print_menu_el(menu[0], 30, 1);
        print_line(30);
        print_menu_el(menu[1], 30, 0);
        print_menu_el(menu[2], 30, 0);
        print_menu_el(menu[3], 30, 0);
        print_menu_el(menu[4], 30, 0);
        print_menu_el(menu[5], 30, 0);
        print_menu_el(menu[6], 30, 0);
        print_border(30, 1);
    }
public:
    static void menu()
    {
        char choice;
        do
        {
            menu_visual();
            choice = _getch();
            switch (choice)
            {
            case '1': {
                Submenu<int> sb;
                sb.submenu();
                break;
            }
            case '2': {
                Submenu<double> sb;
                sb.submenu();
                break;
            }
            case '3': {
                Submenu<char> sb;
                sb.submenu();
                break;
            }
            }
        } while (choice != '0');
    }
    Menu() {}
    ~Menu() = default;
};

int main()
{
    setlocale(LC_ALL, "C");
    Menu::menu();
}