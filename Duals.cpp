#include "Duals.h"

using namespace std;

Duals::Duals()
{
    this->value = 0;
    this->deriv = 0;
}

Duals::Duals(double val)
{
    this->value = val;
    this->deriv = 0;
}

Duals::Duals(double val, double der)
{
    this->value = val;
    this->deriv = der;
}

// following the rules of operator + for dual numbers in the meeting
Duals operator+(const Duals& u, const Duals& v)
{
                    // (a+c),                   (b+d)
    return Duals(u.value + v.value, u.deriv + v.deriv);
}

// following the rules of operator - for dual numbers in the meeting
Duals operator-(const Duals& u, const Duals& v)
{
                    // (a-c),                   (b-d)
    return Duals(u.value - v.value, u.deriv - v.deriv);
}

// following the rules of operator * for dual numbers in the meeting
Duals operator*(const Duals& u, const Duals& v)
{
                    // (a*c),                   (ad+bc)
    return Duals(u.value * v.value, (u.value * v.deriv + v.value * u.deriv));
}

// following the rules of operator / for dual numbers in the meeting
Duals operator/(const Duals& u, const Duals& v)
{
                    // (a/c),                   (bc - ad) / c^2
    return Duals(u.value/v.value, (u.deriv * v.value - u.value * v.deriv) / pow(v.value, 2));
}

ostream& operator<<(ostream& outs, const Duals& d)
{
    outs << d.value << "\n" << d.deriv << endl;
    return outs;
}