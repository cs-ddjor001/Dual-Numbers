#ifndef DUALS_H
#define DUALS_H

#include <iostream>
#include <cmath>
#include <stdexcept>

template<typename T>
class Duals {
    private:
        T value;
        T deriv;
    public:
        // Default constructor initializes to zero
        Duals() : value(T()), deriv(T()) {}

        // Constructor for value with zero derivative
        Duals(T val) : value(val), deriv(T()) {}

        // Constructor for both value and derivative
        Duals(T val, T der) : value(val), deriv(der) {}

        // Getter for value (for const correctness)
        T getValue() const { return value; }

        // Getter for derivative
        T getDerivative() const { return deriv; }

        // Setter for value
        void setValue(T val) {value = val;}

        // Setter for derivative
        void setDerivative(T der) {deriv = der;}

        // Operator overloads as member functions for better encapsulation
        Duals<T> operator+(const Duals<T>& other) const 
        {
            return Duals<T>(value + other.value, deriv + other.deriv);
        }

        Duals<T> operator-(const Duals<T>& other) const 
        {
            return Duals<T>(value - other.value, deriv - other.deriv);
        }

        Duals<T> operator*(const Duals<T>& other) const 
        {
            return Duals<T>(value * other.value, value * other.deriv + deriv * other.value);
        }

        Duals<T> operator/(const Duals<T>& other) const 
        {
            if (other.value == T()) 
            {
                throw std::runtime_error("Division by zero in dual numbers");
            }
            return Duals<T>(value / other.value, (deriv * other.value - value * other.deriv) / (other.value * other.value));
        }

        // Friend function for operator<< to allow access to private members for printing
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Duals<U>& d);
};

// Non-member functions for mathematical operations using the public interface
template<typename T>
Duals<T> sin(const Duals<T>& d) 
{
    using std::sin;
    using std::cos;
    return Duals<T>(sin(d.getValue()), d.getDerivative() * cos(d.getValue()));
}

template<typename T>
Duals<T> cos(const Duals<T>& d) 
{
    using std::cos;
    using std::sin;
    return Duals<T>(cos(d.getValue()), -d.getDerivative() * sin(d.getValue()));
}

template<typename T>
Duals<T> pow(const Duals<T>& d, double p)
{
    return Duals<T>(std::pow(d.getValue(), p), p * d.getDerivative() * std::pow(d.getValue(), p-1));
}

// Overload of operator<< as a non-member function
template<typename U>
std::ostream& operator<<(std::ostream& outs, const Duals<U>& d) 
{
    return outs << "Value: " << d.value << ", Derivative: " << d.deriv;
}

#endif