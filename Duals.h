#ifndef DUALS_H
#define DUALS_H

#include <iostream>
#include <cmath>
#include <stdexcept>

template<typename T>
class Duals;

// Forward declaration of the operator functions as template functions
template<typename T> Duals<T> operator+(const Duals<T>& u, const Duals<T>& v);
template<typename T> Duals<T> operator-(const Duals<T>& u, const Duals<T>& v);
template<typename T> Duals<T> operator*(const Duals<T>& u, const Duals<T>& v);
template<typename T> Duals<T> operator/(const Duals<T>& u, const Duals<T>& v);
template<typename T> Duals<T> sin(const Duals<T>& d);
template<typename T> Duals<T> cos(const Duals<T>& d);
template<typename T> std::ostream& operator<<(std::ostream& outs, const Duals<T>& d);

template<typename T>
class Duals {
private:
    T value;
    T deriv;

public:
    // Constructors
    Duals() : value(T()), deriv(T()) {}
    Duals(T val) : value(val), deriv(T()) {}
    Duals(T val, T der) : value(val), deriv(der) {}

    // Getters and Setters
    T getValue() const { return value; }
    T getDerivative() const { return deriv; }
    void setValue(T val) { value = val; }
    void setDerivative(T der) { deriv = der; }
    
    // Friend declarations, using template instantiation syntax
    friend Duals<T> operator+ <T>(const Duals<T>& u, const Duals<T>& v);
    friend Duals<T> operator- <T>(const Duals<T>& u, const Duals<T>& v);
    friend Duals<T> operator* <T>(const Duals<T>& u, const Duals<T>& v);
    friend Duals<T> operator/ <T>(const Duals<T>& u, const Duals<T>& v);
    friend Duals<T> sin <T>(const Duals<T>& d);
    friend Duals<T> cos <T>(const Duals<T>& d);
    friend std::ostream& operator<< <T>(std::ostream& outs, const Duals<T>& d);
};

// Operator implementations
template<typename T>
Duals<T> operator+(const Duals<T>& u, const Duals<T>& v) 
{
    return Duals<T>(u.value + v.value, u.deriv + v.deriv);
}

template<typename T>
Duals<T> operator-(const Duals<T>& u, const Duals<T>& v) 
{
    return Duals<T>(u.value - v.value, u.deriv - v.deriv);
}

template<typename T>
Duals<T> operator*(const Duals<T>& u, const Duals<T>& v) 
{
    return Duals<T>(u.value * v.value, u.value * v.deriv + v.value * u.deriv);
}

template<typename T>
Duals<T> operator/(const Duals<T>& u, const Duals<T>& v) 
{
    if (v.value == 0) {
        throw std::runtime_error("Division by zero in dual numbers");
    }
    return Duals<T>(u.value / v.value, (u.deriv * v.value - u.value * v.deriv) / (v.value * v.value));
}

template<typename T>
std::ostream& operator<<(std::ostream& outs, const Duals<T>& d) 
{
    outs << "Value: " << d.value << ", Derivative: " << d.deriv;
    return outs;
}

template<typename T>
Duals<T> sin(const Duals<T>& d)
{
    return Duals<T>(std::sin(d.value), d.deriv * std::cos(d.value));
}

template<typename T>
Duals<T> cos(const Duals<T>& d)
{
    return Duals<T>(std::cos(d.value), -d.deriv * std::sin(d.value));
}

#endif // DUALS_H
