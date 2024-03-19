#ifndef DUALS_H
#define DUALS_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <array> // Required for handling multiple derivatives

#define PI 3.14159265359f
 
#define EPSILON 0.001f  // for numeric derivatives calculation

template<size_t NUMVARIABLES = 1, typename T = double>
class Duals 
{
    private:
        T value;
        std::array<T, NUMVARIABLES> derivatives;

    public:
        // Default constructor initializes to zero
        Duals() : value(T()), derivatives({}) {}

        // Constructor for value with zero derivative
        Duals(T val) : value(val), derivatives({}) {}

        // Constructor for both value and derivative
        Duals(T val, T der) : value(val), derivatives({der}) {}

        // Constructor for value and multiple derivatives
        Duals(T val, const std::array<T, NUMVARIABLES>& der) : value(val), derivatives(der) {}

        // Getter for value (for const correctness)
        T getValue() const { return value; }

        // Getter for derivative (single variable)
        T getDerivative() const { return derivatives[0]; }

        // Getter for derivative (multiple variables)
        T getDerivative(size_t index) const 
        {
            if (index >= NUMVARIABLES) 
            {
                throw std::out_of_range("Index out of range for derivative access");
            }
            return derivatives[index];
        }

            // Getter for the entire array of derivatives
        const std::array<T, NUMVARIABLES>& getAllDerivatives() const 
        {
            return derivatives;
        }

        // Setter for value
        void setValue(T val) { value = val; }

        // Setter for derivative (single variable)
        void setDerivative(T der) { derivatives[0] = der; }

        // Setter for derivative (multiple variables)
        void setDerivative(size_t index, T der) 
        {
            if (index >= NUMVARIABLES) 
            {
                throw std::out_of_range("Index out of range for derivative access");
            }
            derivatives[index] = der;
        }

            // Setter for the entire array of derivatives
        void setAllDerivatives(const std::array<T, NUMVARIABLES>& newDerivatives) 
        {
            derivatives = newDerivatives;
        }

        bool operator==(const Duals<NUMVARIABLES, T>& other) const 
        {
           return (this->value == other.value && this->derivatives == other.derivatives);
        }

        bool operator<(const Duals<NUMVARIABLES, T>& other) const 
        {
            if (this->value < other.value) return true;
            if (this->value > other.value) return false;
            return this->derivatives < other.derivatives; // Use deriv as a tiebreaker if values are equal
        }

        bool operator>(const Duals<NUMVARIABLES, T>& other) const
        {
            if (this->value > other.value) return true;
            if (this->value < other.value) return false;
            return this->derivatives > other.derivatives; // Use deriv as a tiebreaker if values are equal
        }

        bool operator!=(const Duals<NUMVARIABLES, T>& other) const
        {
            return !(*this == other);
        }

        bool operator<=(const Duals<NUMVARIABLES, T>& other) const 
        {
            return *this < other || *this == other;
        }

        bool operator>=(const Duals<NUMVARIABLES, T>& other) const 
        {
            return *this > other || *this == other;
        }

        // Friend function for operator<< to allow access to private members for printing
        template<size_t VARIABLES, typename U>
        friend std::ostream& operator<<(std::ostream& os, const Duals<VARIABLES, U>& d);
};

// Overloaded operator+ for addition between Duals and primitive types
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator+(const Duals<NUMVARIABLES, T>& lhs, const T& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() + rhs);
    const auto& derivatives = lhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Overloaded operator+ for addition between primitive types and Duals
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator+(const T& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs + rhs.getValue());
    const auto& derivatives = rhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Original operator+ for addition between two Duals remains unchanged
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator+(const Duals<NUMVARIABLES, T>& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() + rhs.getValue());
    for (size_t i = 0; i < NUMVARIABLES; ++i)
    {
         result.setDerivative(i, lhs.getDerivative(i) + rhs.getDerivative(i));
    }
    return result;
}

// Overloaded operator- for addition between Duals and primitive types
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator-(const Duals<NUMVARIABLES, T>& lhs, const T& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() - rhs);
    const auto& derivatives = lhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Overloaded operator- for addition between primitive types and Duals
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator-(const T& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs - rhs.getValue());
    const auto& derivatives = rhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Original operator+ for addition between two Duals remains unchanged
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator-(const Duals<NUMVARIABLES, T>& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() - rhs.getValue());
    for (size_t i = 0; i < NUMVARIABLES; ++i)
    {
         result.setDerivative(i, lhs.getDerivative(i) - rhs.getDerivative(i));
    }
    return result;
}

// Overloaded operator* for addition between Duals and primitive types
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator*(const Duals<NUMVARIABLES, T>& lhs, const T& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() * rhs);
    const auto& derivatives = lhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Overloaded operator* for addition between primitive types and Duals
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator*(const T& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs * rhs.getValue());
    const auto& derivatives = rhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Original operator* for addition between two Duals remains unchanged
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator*(const Duals<NUMVARIABLES, T>& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() * rhs.getValue());
    for (size_t i = 0; i < NUMVARIABLES; ++i)
    {
         result.setDerivative(i, lhs.getValue() * rhs.getDerivative(i) + lhs.getDerivative(i) * rhs.getValue());
    }
    return result;
}

// Overloaded operator/ for addition between Duals and primitive types
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator/(const Duals<NUMVARIABLES, T>& lhs, const T& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() / rhs);
    const auto& derivatives = lhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Overloaded operator/ for addition between primitive types and Duals
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator/(const T& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs / rhs.getValue());
    const auto& derivatives = rhs.getAllDerivatives();
    result.setAllDerivatives(derivatives);
    return result;
}

// Original operator/ for addition between two Duals remains unchanged
template<size_t NUMVARIABLES, typename T>
Duals<NUMVARIABLES, T> operator/(const Duals<NUMVARIABLES, T>& lhs, const Duals<NUMVARIABLES, T>& rhs) 
{
    Duals<NUMVARIABLES, T> result;
    result.setValue(lhs.getValue() / rhs.getValue());
    for (size_t i = 0; i < NUMVARIABLES; ++i)
    {
         result.setDerivative(i, (lhs.getDerivative(i) * rhs.getValue() - rhs.getDerivative(i) * lhs.getValue()) / (rhs.getValue() * rhs.getValue()));
    }
    return result;
}

// Non-member functions for mathematical operations using the public interface
template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> sin(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::sin(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) * std::cos(d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> cos(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::cos(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, -d.getDerivative(i) * std::sin(d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> tan(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::tan(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) / (std::cos(d.getValue()) * std::cos(d.getValue())));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> arcsin(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::asin(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) / std::sqrt(U(1.0) - d.getValue() * d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> arccos(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::acos(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, -d.getDerivative(i) / std::sqrt(U(1.0) - d.getValue() * d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> arctan(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::atan(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) / (U(1.0) + d.getValue() * d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> pow(const Duals<VARIABLES, U>& d, float p)
{
    Duals<VARIABLES, U> result;
    result.setValue(std::pow(d.getValue(), p));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, U(p) * d.getDerivative(i) * std::pow(d.getValue(), p - U(1.0)));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> exp(const Duals<VARIABLES, U>& d) 
{
    Duals<VARIABLES, U> result;
    result.setValue(std::exp(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) * std::exp(d.getValue()));
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> log(const Duals<VARIABLES, U>& d)
{
    if (d.getValue() <= U(0))
    {
        throw std::runtime_error("Log is undefined for values 0 or less");
    }
    Duals<VARIABLES, U> result;
    result.setValue(std::log(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) / d.getValue());
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> abs(const Duals<VARIABLES, U>& d)
{
    if (d.getValue() == U(0)) 
    {
        throw std::runtime_error("Derivative for the absolute value function doesn't exist at 0.");
    }
    int sign = d.getValue() > U(0) ? 1 : -1;
    Duals<VARIABLES, U> result;
    result.setValue(std::abs(d.getValue()));
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, d.getDerivative(i) * sign);
    }
    return result;
}

template<size_t VARIABLES, typename U>
Duals<VARIABLES, U> sqrt(const Duals<VARIABLES, U>& d)
{
    Duals<VARIABLES, U> result;
    U squareRoot = std::sqrt(d.getValue());
    result.setValue(squareRoot);
    for (size_t i = 0; i < VARIABLES; ++i)
    {
        result.setDerivative(i, U(0.5) * d.getDerivative(i) / squareRoot);
    }
    return result;
}

// Overload of operator<< as a non-member function
template<size_t VARIABLES, typename U>
std::ostream& operator<<(std::ostream& outs, const Duals<VARIABLES, U>& d) 
{
    outs << "Value: " << d.getValue() << ", Derivatives: [";
    for (size_t i = 0; i < VARIABLES; ++i) 
    {
        outs << d.getDerivative(i);
        if (i < VARIABLES - 1) 
        {
            outs << ", ";
        }
    }
    outs << "]";
    return outs;
}

#endif