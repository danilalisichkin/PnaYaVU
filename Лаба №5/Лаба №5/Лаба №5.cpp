#include <iostream>
#include <vector>

using namespace std;

enum securityType
{
    cctv,
    watchman,
    dog
};

std::ostream& operator<<(std::ostream& out, const securityType value) {
    switch (value) {
    case 0:
        return out << "cctv";
        break;
    case 1:
        return out << "watchman";
        break;
    case 2:
        return out << "dog";
        break;
    }
}

class house
{
private:
protected:
    unsigned int floors;
    double square;
    double cost;
public:
    house(unsigned int _floors = 0, double _square = 0, double _cost = 0) : floors(_floors), square(_square), cost(_cost) {};
    house(house& _house) : floors(_house.floors), square(_house.square), cost(_house.cost) {};
    ~house() = default;
    void virtual show() = 0;
};

class detached : public virtual house
{
private:
protected:
    double yardsquare;
public:
    detached(unsigned int _floors = 0, double _square = 0, double _yardsquare = 0, double _cost = 0)
        : house(_floors, _square, _cost), yardsquare(_yardsquare) {};
    detached(detached& _hause) : house(_hause), yardsquare(_hause.yardsquare) {};
    void virtual show() override
    {
        cout << endl;
        cout << endl << "Detached house, floors: " << floors << ", living square: " << square << ", yard square: " << yardsquare << ", cost: " << cost << "$";
        cout << endl;
    }
};

class villa : public detached
{
private:
protected:
    unsigned int pools;
public:
    villa(unsigned int _floors = 0, unsigned int _pools = 0, double _square = 0, double _yardsquare = 0, double _cost = 0)
        : detached(_floors, _square, _yardsquare, _cost), house(_floors, _square, _cost), pools(_pools)
    {};
    villa(villa& _house) : detached(_house), house(_house), pools(_house.pools) {};
    void virtual show() override
    {
        cout << endl;
        cout << endl << "Villa, " << pools << " pools, " << floors << " floors, living square : " << square << ", yard square : " << yardsquare << ", cost : " << cost << "$.";
        cout << endl;
    }
};

class private_house : public virtual house
{
private:
protected:
    vector <string> comforts;
    securityType t;
public:
    private_house(unsigned int _floors = 0, double _square = 0, double _cost = 0, securityType _t = cctv) :
        house(_floors, _square, _cost)
    {
        comforts.push_back("parking");
        comforts.push_back("barbiq");
        t = _t;
    }
    private_house(private_house& _house) : house(_house), comforts(_house.comforts), t(_house.t) {};
    void virtual show() override
    {
        cout << endl;
        cout << endl << "Private house, " << floors << " floors, living square : " << square << ", cost : " << cost << "$.";
        cout << endl << "Comforts: ";
        for (int i = 0; i < 2; i++)
            cout << comforts[i] << ", ";
        cout << t;
        cout << endl;
    }
};

class private_villa : public villa, public private_house
{
private:
protected:
public:
    private_villa(unsigned int _floors = 0, unsigned int _pools = 0, double _square = 0, double _yardsquare = 0, double _cost = 0, securityType _t = cctv) :
        villa(_floors, _pools, _square, _yardsquare, _cost), private_house(_floors, _square, _cost, _t), house(_floors, _square, _cost)
    {}
    private_villa(private_villa& _house) : villa(_house), private_house(_house)
    {}
    void show() override
    {
        cout << endl;
        cout << endl << "Private villa, " << pools << " pools, " << floors << " floors, living square : " << square << ", yard square : " << yardsquare << ", cost : " << cost << "$.";
        cout << endl << "Comforts: ";
        for (int i = 0; i < 2; i++)
            cout << comforts[i] << ", ";
        cout << t;
        cout << endl;
    }
};

int main()
{
    cout << endl << "(1)";
    detached h1(3, 80.0, 100.0, 999.9);
    h1.show();
    cout << endl << "(2)";
    villa h2(3, 3, 80.0, 100.0, 999.9);
    h2.show();
    cout << endl << "(3)";
    private_house h3(3, 80.0, 999.9, watchman);
    h3.show();
    cout << endl << "(4)";
    private_villa h4(3, 3, 80.0, 100.0, 999.9, watchman);
    h4.show();
}