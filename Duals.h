#ifndef DUALS_H
#define DUALS_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <compare>

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

        bool operator==(const Duals<T>& other) const 
        {
            const double epsilon = 1e-9; // Example tolerance
            return (std::abs(value - other.value) < epsilon && std::abs(deriv - other.deriv) < epsilon);
        }


        bool operator<(const Duals<T>& other) const 
        {
            if (value < other.value) return true;
            if (value > other.value) return false;
            return deriv < other.deriv; // Use deriv as a tiebreaker if values are equal
        }

        // Friend function for operator<< to allow access to private members for printing
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Duals<U>& d);
};

// Non-member functions for mathematical operations using the public interface
template<typename T>
Duals<T> sin(const Duals<T>& d) 
{
    return Duals<T>(std::sin(d.getValue()), d.getDerivative() * std::cos(d.getValue()));
}

template<typename T>
Duals<T> cos(const Duals<T>& d) 
{
    return Duals<T>(std::cos(d.getValue()), -d.getDerivative() * std::sin(d.getValue()));
}

template<typename T>
Duals<T> tan(const Duals<T>& d)
{
    if (std::cos(d.getValue()) == T())
    {
        throw std::runtime_error("Tangent is undefined when cos(x) = 0");
    }
    return Duals<T>(std::tan(d.getValue()), d.getDerivative() * 1/std::pow(std::cos(d.getValue()), 2));
}

template<typename T>
Duals<T> arcsin(const Duals<T>& d) 
{
    if (d.getValue() < -1 || d.getValue() > 1) 
    {
        throw std::runtime_error("arcsin is undefined for values outside the range [-1, 1]");
    }
    return Duals<T>(std::asin(d.getValue()), d.getDerivative() * 1/std::sqrt(1 - std::pow(d.getValue(), 2)));
}

template<typename T>
Duals<T> arccos(const Duals<T>& d) 
{
    if (d.getValue() < -1 || d.getValue() > 1) 
    {
        throw std::runtime_error("arccos is undefined for values outside the range [-1, 1]");
    }
    return Duals<T>(std::acos(d.getValue()), -d.getDerivative() * 1/std::sqrt(1 - std::pow(d.getValue(), 2)));
}


template<typename T>
Duals<T> arctan(const Duals<T>& d)
{
    return Duals<T>(std::atan(d.getValue()), d.getDerivative() * 1/(1 + std::pow(d.getValue(), 2)));
}

template<typename T>
Duals<T> pow(const Duals<T>& d, double p)
{
    return Duals<T>(std::pow(d.getValue(), p), p * d.getDerivative() * std::pow(d.getValue(), p-1));
}

template<typename T>
Duals<T> exp(const Duals<T>& d)
{
    return Duals<T>(std::exp(d.getValue()), d.getDerivative()*std::exp(d.getValue()));
}

template<typename T>
Duals<T> log(const Duals<T>& d)
{
    if (d.getValue() <= 0)
    {
        throw std::runtime_error("Log is undefined for values 0 or less");
    }
    return Duals<T>(std::log(d.getValue()), d.getDerivative()/d.getValue());
}

template<typename T>
Duals<T> abs(const Duals<T>& d) 
{
    if (d.getValue() == T()) 
    {
        throw std::runtime_error("Derivative for the absolute value function doesn't exist at 0.");
    }
    int sign = d.getValue() > T() ? 1 : 1;
    return Duals<T>(std::abs(d.getValue()), d.getDerivative() * sign);
}

template<typename T>
Duals<T> sqrt(const Duals<T>& d)
{
    return Duals<T>(std::sqrt(d.getValue()), 0.5 * d.getDerivative() * std::pow(d.getValue(), -0.5));
}

// Overload of operator<< as a non-member function
template<typename U>
std::ostream& operator<<(std::ostream& outs, const Duals<U>& d) 
{
    return outs << "Value: " << d.value << ", Derivative: " << d.deriv;
}

#endif