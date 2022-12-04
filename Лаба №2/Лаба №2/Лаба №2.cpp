#include <iostream>
#include <iomanip>
using namespace std;

class tovar
{
    friend class seller;
    friend void show(tovar& t);
private:
    int static _id;
    int id;
    string name;
    float cost;
public:
    tovar() : id(_id++), name("безымянный"), cost(0.0)
    { }
    tovar(string _name, float _cost) : id(_id++), name(_name), cost(_cost)
    { }
    tovar(static tovar& t)
    {
        id = _id++;
        name = t.name;
        cost = t.cost;
    }
    ~tovar()
    {
        delete& id;
        delete& name;
        delete& cost;
    }
};

int tovar::_id = 0;

class seller
{
private:
public:
    void set_cost(tovar& t)
    {
        cout << endl << endl << "Введите цену " << t.id << "ого товара: ";
        bool success = false;
        while (!success)
        {
            cin >> t.cost;
            if (t.cost < 0 || cin.fail())
                cout << endl << "Введено некорректное значение! Повторите: ";
            else
                success = true;
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
    seller()
    { }
};

void show(tovar& t)
{
    cout.setf(ios::left);
    cout << endl;
    cout << "Товар No " << setw(5) << t.id << " |";
    cout << " наим. \"" << setw(10) << t.name << "\"" << " | ";
    cout << " цена: " << setw(8) << t.cost << " $";
}

int main()
{
    setlocale(LC_ALL, "Rus");

    seller bariga;

    tovar t1;
    tovar t2("Негретёнок", 99.95);

    cout << endl << "1)Товары ДО обработки методом дружественного класса:" << endl;
    show(t1); show(t2);

    bariga.set_cost(t1);
    bariga.set_cost(t2);

    cout << endl << "1)Товары ПОСЛЕ обработки методом дружественного класса:" << endl;
    show(t1); show(t2);

    tovar t[5];

    cout << endl << "2)Товары ДО обработки методом дружественного класса:" << endl;
    for (int i = 0; i < 5; i++)
        show(t[i]);

    for (int i = 0; i < 5; i++)
        bariga.set_cost(t[i]);

    cout << endl << "2)Товары ПОСЛЕ обработки методом дружественного класса:" << endl;
    for (int i = 0; i < 5; i++)
        show(t[i]);

    getchar();
    return 0;
}