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
    virtual ~house() = default;
    void virtual show() = 0;
};

class detached : public house
{
private:
protected:
    double yardsquare;
public:
    detached(unsigned int _floors = 0, double _square = 0, double _yardsquare = 0, double _cost = 0)
        : house(_floors, _square, _cost), yardsquare(_yardsquare) {};
    detached(detached& _house) : house(_house), yardsquare(_house.yardsquare) {};
    ~detached() = default;
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
        : detached(_floors, _square, _yardsquare, _cost), pools(_pools)
    {};
    villa(villa& _house) : detached(_house), pools(_house.pools) {};
    ~villa() = default;
    void show() override
    {
        cout << endl;
        cout << endl << "Villa, " << pools << " pools, " << floors << " floors, living square : " << square << ", yard square : " << yardsquare << ", cost : " << cost << "$.";
        cout << endl;
    }
};

class private_house : public house
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
    ~private_house()
    {
        comforts.clear();
    }
    void show() override
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

int main()
{
    house* p[3];
    p[0] = new detached(2, 120.0, 200.0, 20000);
    p[1] = new villa(2, 1, 450.0, 300.0, 150000);
    p[2] = new private_house(2, 180.0, 50000, cctv);
    cout << endl << "(1)";
    p[0]->show();
    cout << endl << "(2)";
    p[1]->show();
    cout << endl << "(3)";
    p[2]->show();
}