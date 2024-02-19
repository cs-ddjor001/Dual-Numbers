#ifndef DUALS
#define DUALS

#include <iostream>
#include <cmath>

class Duals
{
    private:
        double value;
        double deriv;

        //opetators, 4 basic ones based on the their rules for dual numbers
        friend Duals operator+(const Duals& u, const Duals& v);
        friend Duals operator-(const Duals& u, const Duals& v);
        friend Duals operator*(const Duals& u, const Duals& v);
        friend Duals operator/(const Duals& u, const Duals& v);

        //operator << for easy printing
        friend std::ostream& operator<<(std::ostream& outs, const Duals& d) ;

    public:
        Duals();
        Duals(double val);
        Duals(double val, double der);

        // getters and setters
        double getDerivative() const;
        void setDerivative(double der);
};

inline
double Duals::getDerivative() const
{
    return this->deriv;
}

inline 
void Duals::setDerivative(double der)
{
    this->deriv = der;
}
#endif