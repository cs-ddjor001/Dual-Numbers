#include "Duals.h"

using namespace std;

template <typename T>
inline T SimpleFunction(const T& x) 
{
    return x * x * (T(3.0) - T(2.0) * x);
}

template <typename T>
Duals<2, T> TwoD(const Duals<2, T>& x, const Duals<2, T>& y)
{
    // Calculate the value of the function
    T value = x.getValue() * x.getValue() * y.getValue() + 2 * x.getValue();

    // Calculate the derivatives with respect to x and y
    std::array<T, 2> derivatives;
    derivatives[0] = 2 * x.getValue() * y.getValue() + 2;  // dz/dx
    derivatives[1] = x.getValue() * x.getValue();          // dz/dy

    // Return a Duals object with the computed value and derivatives
    return Duals<2, T>(value, derivatives);
}

template <size_t VARIABLES, typename T>
void TestSmoothStep(T input) 
{
    // Create a dual number as the value of x
    Duals<VARIABLES, T> x(input, 1);

    // Calculate value and derivative using dual numbers
    Duals<VARIABLES, T> y = SimpleFunction(x);

    // Calculate numeric derivative using central differences
    T derivNumeric = (SimpleFunction(x + EPSILON).getValue() - SimpleFunction(x - EPSILON).getValue()) / (T(2.0) * EPSILON);

    // Calculate actual derivative
    T derivActual = T(6.0) * input - T(6.0) * input * input;

    // Show value and derivatives
    cout << "(SimpleFunction) y = 3x^2 - 2x^3  (x = " << input << ")" << std::endl;
    cout << "  y = " << y.getValue() << endl;
    cout << "  dual# dy/dx = " << y.getDerivative(0) << endl;
    cout << "  actual dy/dx = " << derivActual << endl;
    cout << "  numeric dy/dx = " << derivNumeric << endl;
}

template <typename T>
void TestTwoD(T x_val, T y_val) 
{
    Duals<2, T> x(x_val, 1);  // Setting derivative of x to 1
    Duals<2, T> y(y_val, 1);  // Setting derivative of y to 1

    // Calculate the function value and derivatives
    Duals<2, T> z = TwoD(x, y);

    // Show value and derivatives
    cout << "(2D) z = x^2 * y + 2x  (x = " << x_val << ", y = " << y_val << ")\n";
    cout << "  z = " << z.getValue() << '\n';
    cout << "  dz/dx = " << z.getDerivative(0) << "  (expected: 14)\n";
    cout << "  dz/dy = " << z.getDerivative(1) << "  (expected: 4)\n";
}

template <typename T>
void Test2D(T inputx, T inputy)
{
    // Create dual numbers as the value of x and y
    Duals<2, T> x(inputx, {1, 0}); // Setting derivative of x to 1
    Duals<2, T> y(inputy, {0, 1}); // Setting derivative of y to 1

    // Calculate z = 3x^2 - 2y^3
    {
        // Calculate value and partial derivatives using dual numbers
        Duals<2, T> z = Duals<2, T>(3.0) * x * x - Duals<2, T>(2.0) * y * y * y;

        // Calculate numeric partial derivatives using central differences
        auto f = [](T x, T y) {
            return 3.0 * x * x - 2.0 * y * y * y;
        };
        T derivNumericX = (f(inputx + EPSILON, inputy) - f(inputx - EPSILON, inputy)) / (2.0 * EPSILON);
        T derivNumericY = (f(inputx, inputy + EPSILON) - f(inputx, inputy - EPSILON)) / (2.0 * EPSILON);

        // Calculate actual partial derivatives
        T derivActualX = 6.0 * inputx;
        T derivActualY = -6.0 * inputy * inputy;

        // Show value and derivatives
        cout << "z = 3x^2 - 2y^3 (x = " << inputx << ", y = " << inputy << ")\n";
        cout << "  z = " << z.getValue() << '\n';
        cout << "  dz/dx = " << z.getDerivative(0) << '\n';
        cout << "  dz/dy = " << z.getDerivative(1) << '\n';
        cout << "  actual dz/dx = " << derivActualX << '\n';
        cout << "  actual dz/dy = " << derivActualY << '\n';
        cout << "  numeric dz/dx = " << derivNumericX << '\n';
        cout << "  numeric dz/dy = " << derivNumericY << '\n';
    }
}

int main() 
{
    TestSmoothStep<1, float>(0.5f);
    TestSmoothStep<1, float>(0.75f);

    float x_val = 2.0f;
    float y_val = 3.0f;
    TestTwoD(x_val, y_val);

    Test2D(5.0f, 4.0f);

    return 0;
}
