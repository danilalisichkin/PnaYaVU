#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

int LenghSM = 30;

struct Complex
{
    double dp;
    double mp;
};

ostream& operator << (ostream& os, const Complex c)
{
    return os << right << setw(4) << c.dp << showpos << left << setw(4) << c.mp << noshowpos << 'i';
}

class matrix
{
    friend matrix operator - (matrix& mat, double a);
    friend matrix operator - (matrix& mat1, matrix& mat2);
    friend matrix operator - (matrix& mat, Complex a);

    friend matrix operator -- (matrix& mat);
    friend matrix operator -- (matrix& mat, int);

    friend bool operator != (matrix mat1, matrix mat2);

    friend ostream& operator << (ostream& os, const matrix& mat);

private:

    int n;
    int m;
    Complex** p;

public:

    matrix()
    {
        *this = matrix(5, 5);
    }

    matrix(int _n, int _m)
    {
        n = _n;
        m = _m;

        p = new Complex * [n];
        for (int i = 0; i < n; i++)
            p[i] = new Complex[m];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                (*this)[i][j].dp = i;
                (*this)[i][j].mp = j;
            }
    }

    matrix(matrix& mat)
    {
        n = mat.n;
        m = mat.m;

        p = new Complex * [n];
        for (int i = 0; i < n; i++)
            p[i] = new Complex[m];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                (*this)[i][j].dp = mat[i][j].dp;
                (*this)[i][j].mp = mat[i][j].mp;
            }
    }

    ~matrix()
    {
        for (int i = n - 1; i >= 0; i--)
            delete p[i];
        delete p;
    }

    operator Complex ()
    {
        Complex Sum;
        Sum.dp = 0;
        Sum.mp = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                Sum.dp += (*this)[i][j].dp;
                Sum.mp += (*this)[i][j].mp;
            }
        return Sum;
    }

    operator int()
    {
        return n * m;
    }

    matrix operator ()(const Complex data)
    {
        (*this) = data;
        return *this;
    }

    Complex* operator [] (int index)
    {
        return p[index];
    }

    Complex* operator [] (int index)const
    {
        return p[index];
    }

    matrix operator = (const matrix& mat)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                (*this)[i][j].dp = mat[i][j].dp;
                (*this)[i][j].mp = mat[i][j].mp;
            }
        return *this;
    }

    matrix operator = (const Complex comp)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                (*this)[i][j].dp = comp.dp;
                (*this)[i][j].mp = comp.mp;
            }
        return *this;
    }

    matrix operator ++ ()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j].dp++;
        return *this;
    }

    matrix operator ++ (int)
    {
        matrix temp = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j].dp++;
        return temp;
    }

    matrix operator + (matrix& mat)
    {
        matrix temp = *this;
        if (temp.m != mat.m || temp.n != mat.n)
            return temp;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                temp[i][j].dp += mat[i][j].dp;
                temp[i][j].mp += mat[i][j].mp;
            }
        return temp;
    }

    matrix operator + (double a)
    {
        matrix temp = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                temp[i][j].dp += a;
        return temp;
    }

    matrix operator + (Complex a)
    {
        matrix temp = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                temp[i][j].dp += a.dp;
                temp[i][j].mp += a.mp;
            }
        return temp;
    }

    matrix operator += (matrix mat)
    {
        matrix temp = *this;
        temp = temp + mat;
        return temp;
    }

    matrix operator += (double a)
    {
        matrix temp = *this;
        temp = temp + a;
        return temp;
    }

    matrix operator -= (matrix mat)
    {
        matrix temp = *this;
        temp = temp - mat;
        return temp;
    }

    matrix operator -= (double a)
    {
        matrix temp = *this;
        temp = temp - a;
        return temp;
    }

    matrix operator * (double a)
    {
        matrix temp = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                temp[i][j].dp *= a;
                temp[i][j].mp *= a;
            }
        return temp;
    }

    bool operator == (matrix mat)
    {
        if (n != mat.n || m != mat.m) return false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if ((*this)[i][j].dp != mat[i][j].dp || (*this)[i][j].mp != mat[i][j].mp)
                    return false;
        return true;
    }

    operator int() const
    {
        return n * m;
    }

    operator Complex() const
    {
        Complex sum;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                sum.dp += (*this)[i][j].dp;
                sum.mp += (*this)[i][j].mp;
            }
        return sum;
    }
};

matrix operator - (matrix& mat1, matrix& mat2)
{
    if (mat1.m != mat2.m || mat1.n != mat2.n)
        return mat1;
    matrix temp = mat1;
    for (int i = 0; i < temp.n; i++)
        for (int j = 0; j < temp.m; j++)
        {
            temp[i][j].dp -= mat2[i][j].dp;
            temp[i][j].mp -= mat2[i][j].mp;
        }
    return temp;
}

matrix operator - (matrix& mat, double a)
{
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
        {
            mat[i][j].dp -= a;
        }
    return mat;
}

matrix operator - (matrix& mat, Complex a)
{
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
        {
            mat[i][j].dp -= a.dp;
            mat[i][j].mp -= a.mp;
        }
    return mat;
}

matrix operator -- (matrix& mat)
{
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
            --mat[i][j].dp;
    return mat;
}

matrix operator -- (matrix& mat, int)
{
    matrix temp = mat;
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
            mat[i][j].dp--;
    return temp;
}

bool operator != (matrix mat1, matrix mat2)
{
    if (mat1 == mat2)
        return false;
    else
        return true;
}

ostream& operator << (ostream& os, const matrix& mat)
{
    os << endl;
    for (int i = 0; i < mat.n; i++)
    {
        for (int j = 0; j < mat.m; j++)
            os << setw(4) << left << mat[i][j] << " |";
        os << endl;
    }
    return os;
}

void WaitForBack()
{
    cout << endl << "(!)Press 0 to return back!";
    char choice;
    do
    {
        choice = _getch();
    } while (choice != '0');
}

int GetValidData(int l, int r)
{
    int data;
    bool success = false;
    while (!success)
    {
        cin >> data;
        if (data < l || data > r || cin.fail()) {
            cout << endl << "(!)Invalid format!";
            cout << endl << "(*)This number must be from " << l << " to " << r << " !";
            cout << endl << "   Please repeat: ";
        }
        else
            success = true;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    return data;
}

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

void PrintWall(int side)
{
    if (side == 1) {
        cout << char(201); // стена верхняя
        for (int i = 1; i < LenghSM - 1; i++)
            cout << (char)(205);
        cout << char(187) << endl;
    }
    else if (side == 0) {
        cout << char(200);  // стена нижняя
        for (int i = 1; i <= LenghSM - 2; i++)
            cout << (char)(205);
        cout << char(188) << endl;
    }
    else return;
}

void Menu_Show()
{
    char menuEl[][22] = { "CHOOSE THE OPERATION!", " ", " 1 - '+'"," 2 - '-'", " 3 - '*'"," 4 - '='"," 5 - '++'", " 6 - '--'", " 7 - '[][]'", " 8 - '()'" , " 9 - '==' and '!='", "10 - 'transform type'", " ", " 0 - EXIT THE PROGRAM" };
    int NofEls = 14;
    system("cls");

    PrintWall(1);
    for (int k = 0; k < NofEls; k++) // сердце
    {
        if (k == 0)
            PrintMenu(menuEl[k], 1);
        else
            PrintMenu(menuEl[k], 0);
    }
    PrintWall(0);
}

void OperatorPlus()
{
    matrix m1(5, 5);
    matrix m2(5, 5);
    Complex c1;
    c1.dp = 2;
    c1.mp = -3.5;
    double a = -9;

    system("cls");
    cout << "Operation: '+' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << "2nd matrix:" << endl;
    cout << m2;
    cout << endl << endl << "Complex number:" << endl;
    cout << endl << c1;
    cout << endl << endl << "Double number:" << endl;
    cout << endl << right << setw(4) << a << endl;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix + 2nd matrix =" << endl;
    matrix m3(5, 5);
    m3 = m1 + m2;
    cout << m3 << endl;

    cout << endl << "1st matrix + Complex number =" << endl;
    m1 = m1 + c1;
    cout << m1 << endl;

    cout << endl << "2nd matrix + Double number =" << endl;
    m2 = m2 + a;
    cout << m2 << endl;

    WaitForBack();
}

void OperatorMinus()
{
    matrix m1(5, 5);
    matrix m2(5, 5);
    Complex c1;
    c1.dp = 2;
    c1.mp = -3.5;
    double a = -9;

    system("cls");
    cout << "Operation: '-' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << "2nd matrix:" << endl;
    cout << m2;
    cout << endl << endl << "Complex number:" << endl;
    cout << endl << c1;
    cout << endl << endl << "Double number:" << endl;
    cout << endl << right << setw(4) << a << endl;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix - 2nd matrix =" << endl;
    matrix m3(5, 5);
    m3 = m1 - m2;
    cout << m3 << endl;

    cout << endl << "1st matrix - Complex number =" << endl;
    m1 = m1 - c1;
    cout << m1 << endl;

    cout << endl << "2nd matrix - Double number =" << endl;
    m2 = m2 - a;
    cout << m2 << endl;

    WaitForBack();
}

void OperatorMultiplex()
{
    matrix m1(5, 5);
    double a = 5;

    system("cls");
    cout << "Operation: '*' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << endl << "Double number:" << endl;
    cout << endl << right << setw(4) << a << endl;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix * Double number =" << endl;
    m1 = m1 * a;
    cout << m1 << endl;

    WaitForBack();
}

void OperatorEqual()
{
    matrix m1(5, 5);
    matrix m2(5, 5);
    m1 = m1 * 3.0;
    m1 = m1 - 1.5;
    Complex c1;
    c1.dp = 2;
    c1.mp = -3.5;
    double a = -9.0;

    system("cls");
    cout << "Operation: '=' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << "2nd matrix:" << endl;
    cout << m2;
    cout << endl << endl << "Complex number:" << endl;
    cout << endl << c1;
    cout << endl << endl << "Double number:" << endl;
    cout << endl << right << setw(4) << a << endl;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix = 2nd matrix" << endl;
    m1 = m2;
    cout << m1 << endl;

    cout << endl << "1st matrix = Complex number" << endl;
    m1 = c1;
    cout << m1 << endl;

    WaitForBack();
}

void OperatorInc()
{
    matrix m1(5, 5);

    system("cls");
    cout << "Operation: '++' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix ++" << endl;
    cout << m1++ << endl;

    m1--;

    cout << endl << "++ 1st matrix" << endl;
    cout << ++m1 << endl;

    WaitForBack();
}

void OperatorDec()
{
    matrix m1(5, 5);

    system("cls");
    cout << "Operation: '--' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;

    cout << endl << "Test of current operation:" << endl;

    cout << endl << "1st matrix --" << endl;
    cout << m1-- << endl;

    m1++;

    cout << endl << "-- 1st matrix" << endl;
    cout << --m1 << endl;

    WaitForBack();
}

void OperatorIndex()
{
    matrix m1(5, 5);

    system("cls");
    cout << "Operation: '[][]' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "matrix:" << endl;
    cout << m1;

    cout << endl << "Test of current operation:" << endl;

    char choice;
    do
    {

        cout << endl << "Choose the matrix element to display!" << endl;
        cout << "line: ";
        int line = GetValidData(0, 4);
        cout << "row: ";
        int row = GetValidData(0, 4);

        cout << endl << "matrix[" << line << "][" << row << "]:" << m1[line][row] << endl;
        cout << "Press '1' to repeat or press any other key to exit!" << endl;
        choice = _getch();
    } while (choice == '1');
    WaitForBack();
}

void OperatorMake()
{

    matrix m1(5, 5);
    matrix m2(3, 3);
    Complex c1;
    c1.dp = 2;
    c1.mp = -3.5;

    system("cls");
    cout << "Operation: '()' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << "2nd matrix:" << endl;
    cout << m2;
    cout << endl << endl << "Complex number:" << endl;
    cout << endl << c1;

    char choice;
    do
    {
        cout << endl << "Choose the matrix!" << endl;
        cout << endl << "Matrix number: ";
        int number = GetValidData(1, 2);

        matrix* mat1 = &m1, * mat2 = &m2;
        if (number == 2) {
            mat1 = &m2;
            mat2 = &m1;
        }

        cout << endl << "(!)   Choose the data to inicialize matrix!" << endl;
        cout << endl << "(1) - complex number";

        char choose;
        do
        {
            choose = _getch();
        } while (choose != '1');

        (*mat1)(c1);

        if (number == 2)
            cout << endl << endl << "Your new 2nd matrix:" << endl << *mat1;
        else
            cout << endl << endl << "Your new 1st matrix:" << endl << *mat1;

        cout << endl << "Press '1' to repeat or press any other key to exit!" << endl;
        choice = _getch();

    } while (choice == '1');

    WaitForBack();
}

void OperatorIsEqual()
{
    matrix m1(5, 5);
    matrix m2(5, 5);
    matrix m3(3, 3);
    matrix m4(3, 3);
    m4 = m3 * 2.0 + 1.0;

    system("cls");
    cout << "Operation: '==' and '!=' ." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "1st matrix:" << endl;
    cout << m1;
    cout << endl << "2nd matrix:" << endl;
    cout << m2;
    cout << endl << "3rd matrix:" << endl;
    cout << m3;
    cout << endl << "4th matrix:" << endl;
    cout << m4;

    cout << endl << "Test of current operation:" << endl;

    char choice;
    do
    {
        cout << endl << "Choose the 1st matrix to compare!" << endl;
        int p1 = GetValidData(1, 4);
        cout << endl << "Choose the 2nd matrix to compare!" << endl;
        int p2 = GetValidData(1, 4);

        matrix* mat1 = &m1;
        switch (p1)
        {
        case (1): mat1 = &m1; break;
        case (2): mat1 = &m2; break;
        case (3): mat1 = &m3; break;
        case (4): mat1 = &m4; break;
        default: break;
        }
        matrix* mat2 = &m2;
        switch (p2)
        {
        case (1): mat2 = &m1; break;
        case (2): mat2 = &m2; break;
        case (3): mat2 = &m3; break;
        case (4): mat2 = &m4; break;
        default: break;
        }

        m2 = m1;

        if (*mat1 == *mat2)
            cout << endl << "This matrix are equal.";
        else if (*mat1 != *mat2)
            cout << endl << "This matrix are NOT equal.";

        cout << endl << "Press '1' to repeat or press any other key to exit!" << endl;
        choice = _getch();
    } while (choice == '1');

    WaitForBack();
}

void OperatorTransform()
{
    matrix m1(5, 5);

    system("cls");
    cout << "Operation: transform to type." << endl;
    cout << endl << "Previous data:" << endl;
    cout << endl << "matrix:" << endl;
    cout << m1;

    cout << endl << "Test of current operation:" << endl;

    char choice;
    do
    {
        cout << endl << "(!)   Choose the type!";
        cout << endl << "(1) - int        number of matrix elements";
        cout << endl << "(2) - Complex    summ of matrix elements" << endl;

        char choice2;
        do
        {
            choice2 = _getch();
        } while (choice2 != '1' && choice2 != '2');

        if (choice2 == '1')
            cout << endl << "Number of matrix elements is " << (int)m1;
        else if (choice2 == '2')
            cout << endl << "Summ of matrix elements is " << (Complex)m1;

        cout << endl << "Press '1' to repeat or press any other key to exit!" << endl;
        choice = _getch();
    } while (choice == '1');

    WaitForBack();
}

void Menu()
{
    char choice;
    do
    {
        Menu_Show();
        choice = _getch();
        switch (choice)
        {
        case '1': OperatorPlus(); break;
        case '2': OperatorMinus(); break;
        case '3': OperatorMultiplex(); break;
        case '4': OperatorEqual(); break;
        case '5': OperatorInc(); break;
        case '6': OperatorDec(); break;
        case '7': OperatorIndex(); break;
        case '8': OperatorMake(); break;
        case '9': OperatorIsEqual(); break;
        case 'x': OperatorTransform(); break;
        }
    } while (choice != '0');
}

int main()
{
    setlocale(LC_ALL, "C");
    Menu();
}