#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
using namespace std;

struct coords
{
    float x;
    float y;
};
int Timer;
int TimerIncrease;
int Point;

char movement;
const int HeighSM = 30, LenghSM = 3 * HeighSM / 2 + 1;
char difficulty = 'm';

coords Snake, * Apple, PrevTail, PrevTail2, * SnakeTail;
int SnakeScore;
int TailLengh;
int NofApples, CurApples;

void PrintMenu(char* menuEl, int mode)
{
    int i;
    int lengh = strlen(menuEl);
    cout << char(186);

    if (mode == 1) {
        for (i = 1; i < (LenghSM - 1 - lengh) / 2; i++)
            cout << ' ';
        i += lengh + 1;
    }
    else if (mode == 0) {
        i = lengh + 2;
    }
    else return;

    cout << menuEl;
    for (i; i <= LenghSM - 1; i++)
        cout << ' ';
    cout << char(186) << endl;
} 

void SnakeMainMenu();
void Snake_Play();

void CreditsMenu_Show()
{
        char menuEl[][29] = { "CREDITS", " ", "This game was developed by", "Danila Lisichkin, student of","the 150505th group for", "practice project.", " ", "1 - RETURN BACK" };
        int NofEls = 8;
        system("cls");

        cout << char(201);
        for (int i = 1; i < LenghSM - 1; i++)
            cout << (char)(205);
        cout << char(187) << endl;

        for (int k = 0; k < NofEls; k++)
        {
            if (k == 0) PrintMenu(menuEl[k], 1);
            else
                PrintMenu(menuEl[k], 0);
        }

        cout << char(200);
        for (int i = 1; i <= LenghSM - 2; i++)
            cout << (char)(205);
        cout << char(188) << endl;
}

void CreditsMenu()
{
    char choice;
    do
    {
        CreditsMenu_Show();
        choice = _getch();
    } while (choice != '1');
}

void DifficultyMenu_Show()
{
    char menuEl[][29] = { "CHOOSE YOUR DIFFICULTY", " ", "1 - EASY","2 - MEDIUM", "3 - HARD", " ", "", "4 - RETURN BACK" };
    int NofEls = 8;
    system("cls");

    switch (difficulty)
    {
    case 'e': strcpy(menuEl[6], "*Current difficult: EASY"); break;
    case 'm': strcpy(menuEl[6], "*Current difficult: MEDIUM"); break;
    case 'h': strcpy(menuEl[6], "*Current difficult: HARD"); break;
    }

    cout << char(201); // стена верхняя
    for (int i = 1; i < LenghSM - 1; i++)
        cout << (char)(205);
    cout << char(187) << endl;

    for (int k = 0; k < NofEls; k++) // сердце
    {
        if (k == 0)
            PrintMenu(menuEl[k], 1);
        else
            PrintMenu(menuEl[k], 0);
    }

    cout << char(200);  // стена нижняя
    for (int i = 1; i <= LenghSM - 2; i++)
        cout << (char)(205);
    cout << char(188) << endl;
}

void DifficultyMenu()
{
        char choice;
        do
        {
            DifficultyMenu_Show();
            choice = _getch();
            switch (choice)
            {
            case '1': difficulty = 'e'; break;
            case '2': difficulty = 'm'; break;
            case '3': difficulty = 'h'; break;
            }
        } while (choice != '4');
}

void SnakeControl()
{
    if (GetAsyncKeyState('W'))
        movement = 'u';
    else if (GetAsyncKeyState('S'))
        movement = 'd';
    else if (GetAsyncKeyState('D'))
        movement = 'r';
    else if (GetAsyncKeyState('A'))
        movement = 'l';
}

void SnakeMove()
{
    switch (movement)
    {
    case 'u': Snake.y++; break;
    case 'd': Snake.y--; break;
    case 'r': Snake.x++; break;
    case 'l': Snake.x--; break;
    }
}

bool SnakeLogic()
{
    if (difficulty == 'h') {
        if (Snake.x == LenghSM || Snake.x == 1 || Snake.y == HeighSM+1 || Snake.y == 0)
            return true;
    }
    else {
        if (Snake.x == LenghSM)
            Snake.x = 2;
        else if (Snake.x == 1)
            Snake.x = LenghSM - 1;

        if (Snake.y == HeighSM + 1)
            Snake.y = 1;
        else if (Snake.y == 0)
            Snake.y = HeighSM;
    }

    for (int i = 0; i < TailLengh; i++)
        if (SnakeTail[i].x == Snake.x && SnakeTail[i].y == Snake.y)
            return true;

    SnakeTail[0].x = Snake.x;
    SnakeTail[0].y = Snake.y;
    PrevTail.x = SnakeTail[0].x;
    PrevTail.y = SnakeTail[0].y;

    for (int i = 1; i < TailLengh; i++) {
        PrevTail2.x = SnakeTail[i].x;
        PrevTail2.y = SnakeTail[i].y;
        SnakeTail[i].x = PrevTail.x;
        SnakeTail[i].y = PrevTail.y;
        PrevTail.x = PrevTail2.x;
        PrevTail.y = PrevTail2.y;
    }

    int IndexOfApple;
    for(int i=0; i<NofApples; i++) 
    {
        if (Snake.x == Apple[i].x && Snake.y == Apple[i].y) {
            SnakeScore+=Point;
            Timer -= Timer * TimerIncrease / 100;
            SnakeTail = (coords*)realloc(SnakeTail, (++TailLengh) * sizeof(coords));
            CurApples--;
            IndexOfApple = i;
        }
    }

    while (CurApples < NofApples)
    {
        bool isCorrectly = false;
        while (!isCorrectly)
        {
            Apple[IndexOfApple].x = 2 + rand() % (LenghSM - 1);
            Apple[IndexOfApple].y = 2 + rand() % (HeighSM - 1);
            isCorrectly = true;
            if (Apple[IndexOfApple].x == Snake.x && Apple[IndexOfApple].y == Snake.y)
                isCorrectly = false;
            for (int i = 0; i < NofApples && isCorrectly; i++)
            {
                if (i == IndexOfApple)
                    continue;
                else if (Apple[IndexOfApple].x == Apple[i].x && Apple[IndexOfApple].y == Apple[i].y)
                    isCorrectly = false;
            }
            if (isCorrectly)
                for (int i = 0; i < TailLengh && isCorrectly; i++)
                    if (Apple[IndexOfApple].x == SnakeTail[i].x && Apple[IndexOfApple].y == SnakeTail[i].y)
                        isCorrectly = false;
        }
        CurApples++;
    }

    return false;
}

void SnakeDrawMap()
{
    system("cls");
    cout << "Your score is : " << SnakeScore << endl;
    cout << char(201);
    for (int i = 1; i < LenghSM - 1; i++)
        cout << (char)(205);
    cout << char(187) << endl;

    for (int j = HeighSM; j > 0; j--)
    {
        for (int i = 1; i <= LenghSM; i++)
        {
            bool isPrinted = false;
            if (!isPrinted && (i == 1 || i == LenghSM)) {
                cout << char(186);
                isPrinted = true;
            }
            if (!isPrinted && j == Snake.y && i == Snake.x) {
                cout << 'O';
                isPrinted = true;
            }
            if(!isPrinted)
                for (int k=0; k<NofApples; k++) 
                    if (j == Apple[k].y && i == Apple[k].x) {
                        cout << char(2); 
                        isPrinted = true;
                    }
           if (!isPrinted) {
                bool isTail = false;
                for (int k = 1; k <= TailLengh && !isTail; k++)
                    if (j == SnakeTail[k].y && i == SnakeTail[k].x) {
                        cout << char(253);
                        isTail = true;
                    }
                if (!isTail)
                    cout << " ";
           }
        }
        cout << endl;
    }
    cout << char(200);
    for (int i = 1; i <= LenghSM - 2; i++) // стена нижняя
        cout << (char)(205);
    cout << char(188) << endl;
}

void ShowScoresS_Show()
{
    char menuEl[][22] = { "RECORDS", " ", "0 - RETURN BACK" };
    int NofEls = 3;
    system("cls");

    cout << char(201);
    for (int i = 1; i < LenghSM - 1; i++)
        cout << (char)(205);
    cout << char(187) << endl;

    for (int k = 0; k < NofEls; k++)
    {
        if (k == 0) PrintMenu(menuEl[k], 1);
        else
            PrintMenu(menuEl[k], 0);
    }

    cout << char(200);
    for (int i = 1; i <= LenghSM - 2; i++)
        cout << (char)(205);
    cout << char(188) << endl;
}

void ShowScoresS()
{
    char choice;
    do
    {
        ShowScoresS_Show();
        FILE* f;
        if (!(f = fopen("SnakeScores.txt", "r"))) {
            cout << "No records." << endl;
            for (int i = 0; i <= LenghSM - 1; i++)
                cout << (char)(205);
        }
        else {
            char str[20];
            int i = 1;
            while (fgets(str, 20, f))
            {
                cout << "Player No " << i++ << endl;
                cout << "Nickname: " << str;
                cout << "Score: " << fgets(str, 20, f) << endl;
                for (int j = 0; j <= LenghSM - 1; j++)
                    cout << (char)(205);
                cout << endl;
            }
            fclose(f);
        }
        choice = _getch();
    } while (choice != '0');
}

void SaveScoreS()
{
    while (_kbhit())
        _getch();
    FILE* f1;
    cout << endl << "Your score is: " << SnakeScore << endl;
    cout << "Write your nickname:" << endl;
    char nickname[20];
    cin >> nickname;
    if (!(f1 = fopen("SnakeScores.txt", "r"))) {
        f1 = fopen("SnakeScores.txt", "w");
        fprintf(f1, "%s\n%d\n", nickname,SnakeScore);
        fclose(f1);
    }
    else {
        FILE* f2;
        f2 = fopen("SnakeScores1.txt", "a");
        bool isSaved = false;
        while (!feof(f1))
        {
            char nick[20];
            if(fscanf(f1, "%s", &nick)==EOF)
                break;
            int a;
            fscanf(f1, "%d", &a);
            if (a < SnakeScore && !isSaved) {
                isSaved = true;
                fprintf(f2, "%s\n%d\n", nickname, SnakeScore);
            }
            fprintf(f2, "%s\n%d\n", nick,a);
        }
        if (!isSaved)
            fprintf(f2, "%s\n%d\n", nickname, SnakeScore);
        fclose(f2);
        fclose(f1);
        remove("SnakeScores.txt");
        rename("SnakeScores1.txt", "SnakeScores.txt");
    }
}

void SnakeMainMenu_Show()
{
    char menuEl[][22] = { "MAIN MENU", " ", "1 - PLAY GAME", "2 - CHOOSE DIFFICULTY", "3 - VIEW SCORES", "4 - VIEW CREDITS", "5 - EXIT"};
    int NofEls = 7;
    system("cls");

    cout << char(201);
    for (int i = 1; i < LenghSM - 1; i++)
        cout << (char)(205);
    cout << char(187) << endl;

    for (int k = 0; k < NofEls; k++)
    {
        if (k == 0) PrintMenu(menuEl[k], 1);
        else
            PrintMenu(menuEl[k], 0);
    }

    cout << char(200); 
    for (int i = 1; i <= LenghSM - 2; i++)
        cout << (char)(205);
    cout << char(188) << endl;
}

void SnakeMainMenu()
{
    char choice;
    do
    {
        SnakeMainMenu_Show();
        choice = _getch();
        switch (choice)
        {
        case '1': Snake_Play(); break;
        case '2': DifficultyMenu(); break;
        case '3': ShowScoresS(); break;
        case '4': CreditsMenu(); break;
        }
    } while (choice != '5');
}

void Snake_End_OG_Show()
{
    char menuEl[][20] = { "Game is over.","Whanna save record?", "y - yes", "n - no" };
    int NofEls = 4;
    system("cls");

    cout << char(201);
    for (int i = 1; i < LenghSM - 1; i++)
        cout << (char)(205);
    cout << char(187) << endl;

    for (int k = 0; k < NofEls; k++)
    {
        if (k == 0 || k == 1) PrintMenu(menuEl[k], 1);
        else
            PrintMenu(menuEl[k], 0);
    }

    cout << char(200);
    for (int i = 1; i <= LenghSM - 2; i++)
        cout << (char)(205);
    cout << char(188) << endl;
}

void Snake_End_OG()
{
    Snake_End_OG_Show();
    while (1)
    {
        if (GetAsyncKeyState('N')) 
            break;
        else if (GetAsyncKeyState('Y')) {
            SaveScoreS();
            break;
        }
    }
}

void SetDifficulty()
{
    switch (difficulty)
    {
    case 'e':
        Timer = 180;
        TimerIncrease = 3;
        Point = 1;
        break;
    case 'm':
        Timer = 130;
        TimerIncrease = 5;
        Point = 2;
        break;
    case 'h':
        Timer = 80;
        TimerIncrease = 7;
        Point = 3;
        break;
    }
}

void Snake_Setup()
{
    Snake.y = HeighSM / 2;
    Snake.x = LenghSM / 2;
    movement = 'u';
    SnakeScore = 0;
    TailLengh = 1;
    SnakeTail = (coords*)calloc(TailLengh, sizeof(coords));

    CurApples = 0;
    NofApples = 30;
    Apple = (coords*)calloc(NofApples, sizeof(coords));
    for (int j = 0; CurApples < NofApples && j < NofApples; j++)
    {
        bool isCorrectly = false;
        while (!isCorrectly)
        {
            Apple[j].x = 1 + rand() % (LenghSM - 1);
            Apple[j].y = 1 + rand() % (HeighSM - 1);
            isCorrectly = true;
            for (int k = 0; k < TailLengh - 1; k++)
                if (isCorrectly && ((Apple[j].x == SnakeTail[k].x && Apple[j].y == SnakeTail[k].y) || (Apple[j].x == Snake.x && Apple[j].y == Snake.y)))
                    isCorrectly = false;
        }
        CurApples++;
    }

    SetDifficulty();
}

void Snake_Play()
{
    Snake_Setup();
    bool isGameOver = false;
    while (!isGameOver)
    {
        SnakeControl();
        isGameOver = SnakeLogic();
        SnakeMove();
        SnakeDrawMap();
        Sleep(Timer);
    }
    Snake_End_OG();
}

int main()
{
    setlocale(LC_ALL, "C");
    SnakeMainMenu();
    return 0;
}