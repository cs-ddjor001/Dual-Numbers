#include <vector>
#include <functional>
#include "Duals.h"

using namespace std;

template <typename T>
inline T SimpleFunction(const T& x) 
{
    return x * x * (T(3.0) - T(2.0) * x);
}

void TestMath(float input)
{
    // create a dual number as the value of x
    Duals<1, float> x(input, 1);

    // sqrt
    {
        // calculate value and derivative using dual numbers
        Duals<1, float> y = 3.0f / sqrt(x);

        // calculate numeric derivative using central differences
        float derivNumeric = ((3.0f / sqrt(input + EPSILON)) - (3.0f / sqrt(input - EPSILON))) / (2.0f * EPSILON);

        // calculate actual derivative
        float derivActual = -3.0f / (2.0f * pow(input, 3.0f / 2.0f));

        // show value and derivatives
        cout << "3/sqrt(" << input << ") = " << y.getValue() << "\n";
        cout << "  dual# dy/dx = " << y.getDerivative() << "\n";
        cout << "  actual dy/dx = " << derivActual << "\n";
        cout << "  numeric dy/dx = " << derivNumeric << "\n";
    }

    // pow
    {
        // calculate value and derivative using dual numbers
        Duals<1, float> y = pow(x + Duals<1, float>(1.0f), 1.337f);

        // calculate numeric derivative using central differences
        float derivNumeric = ((pow(input + 1.0f + EPSILON, 1.337f)) - (pow(input + 1.0f - EPSILON, 1.337f))) / (2.0f * EPSILON);

        // calculate actual derivative
        float derivActual = 1.337f * pow(input + 1.0f, 0.337f);

        // show value and derivatives
        cout << "(" << input << "+1)^1.337 = " << y.getValue() << "\n";
        cout << "  dual# dy/dx = " << y.getDerivative() << "\n";
        cout << "  actual dy/dx = " << derivActual << "\n";
        cout << "  numeric dy/dx = " << derivNumeric << "\n";
    }
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
void TestSimpleFunction(T input) 
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
    cout << "  dz/dx = " << z.getDerivative(0) << "\n";
    cout << "  dz/dy = " << z.getDerivative(1) << "\n";
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
        Duals<2, T> z = 3.0f * x * x - 2.0f * y * y * y;

        // Calculate numeric partial derivatives using central differences
        auto f = [](T x, T y) 
        {
            return 3.0f* x * x - 2.0f * y * y * y;
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

void Test3D(float inputx, float inputy, float inputz)
{
    // Create dual numbers as the value of x, y, and z
    Duals<3, float> x(inputx, {1, 0, 0}); // Setting derivative of x to 1
    Duals<3, float> y(inputy, {0, 1, 0}); // Setting derivative of y to 1
    Duals<3, float> z(inputz, {0, 0, 1}); // Setting derivative of z to 1

    // w = sin(x*cos(2*y)) / tan(z)
    {
        // Calculate value and partial derivatives using dual numbers
        Duals<3, float> w = sin(x * cos(2.0f * y)) / tan(z);

        // Calculate numeric partial derivatives using central differences
        auto f = [](float x, float y, float z) 
        {
            return sin(x * cos(2.0f * y)) / tan(z);
        };
        float derivNumericX = (f(inputx + EPSILON, inputy, inputz) - f(inputx - EPSILON, inputy, inputz)) / (2.0f * EPSILON);
        float derivNumericY = (f(inputx, inputy + EPSILON, inputz) - f(inputx, inputy - EPSILON, inputz)) / (2.0f * EPSILON);
        float derivNumericZ = (f(inputx, inputy, inputz + EPSILON) - f(inputx, inputy, inputz - EPSILON)) / (2.0f * EPSILON);

        // Calculate actual partial derivatives
        float derivActualX = cos(inputx * cos(2.0f * inputy)) * cos(2.0f * inputy) / tan(inputz);
        float derivActualY = cos(inputx * cos(2.0f * inputy)) * -2.0f * inputx * sin(2.0f * inputy) / tan(inputz);
        float derivActualZ = sin(inputx * cos(2.0f * inputy)) / -(sin(inputz) * sin(inputz));

        // Show value and derivatives
        cout << "w = sin(x * cos(2 * y)) / tan(z) (x = " << inputx << ", y = " << inputy << ", z = " << inputz << ")\n";
        cout << "  w = " << w.getValue() << '\n';
        cout << "  dual# dw/dx = " << w.getDerivative(0) << '\n';
        cout << "  dual# dw/dy = " << w.getDerivative(1) << '\n';
        cout << "  dual# dw/dz = " << w.getDerivative(2) << '\n';
        cout << "  actual dw/dx = " << derivActualX << '\n';
        cout << "  actual dw/dy = " << derivActualY << '\n';
        cout << "  actual dw/dz = " << derivActualZ << '\n';
        cout << "  numeric dw/dx = " << derivNumericX << '\n';
        cout << "  numeric dw/dy = " << derivNumericY << '\n';
        cout << "  numeric dw/dz = " << derivNumericZ << '\n';
    }
}

void TestTrig(float input)
{
    // Create a dual number as the value of x
    Duals<1, float> x(input, 1); // Setting derivative of x to 1

    // sin
    {
        // Calculate value and derivative using dual numbers
        Duals<1, float> y = sin(x);

        // Calculate numeric derivative using central differences
        float derivNumeric = (sin(input + EPSILON) - sin(input - EPSILON)) / (2.0f * EPSILON);

        // Calculate actual derivative
        float derivActual = cos(input);

        // Show value and derivatives
        cout << "sin(" << input << ") = " << y.getValue() << '\n';
        cout << "  dual# dy/dx = " << y.getDerivative() << '\n';
        cout << "  actual dy/dx = " << derivActual << '\n';
        cout << "  numeric dy/dx = " << derivNumeric << '\n';
    }

    // cos
    {
        // Calculate value and derivative using dual numbers
        Duals<1, float> y = cos(x);

        // Calculate numeric derivative using central differences
        float derivNumeric = (cos(input + EPSILON) - cos(input - EPSILON)) / (2.0f * EPSILON);

        // Calculate actual derivative
        float derivActual = -sin(input);

        // Show value and derivatives
        cout << "cos(" << input << ") = " << y.getValue() << '\n';
        cout << "  dual# dy/dx = " << y.getDerivative() << '\n';
        cout << "  actual dy/dx = " << derivActual << '\n';
        cout << "  numeric dy/dx = " << derivNumeric << '\n';
    }

    // tan
    {
        // Calculate value and derivative using dual numbers
        Duals<1, float> y = tan(x);

        // Calculate numeric derivative using central differences
        float derivNumeric = (tan(input + EPSILON) - tan(input - EPSILON)) / (2.0f * EPSILON);

        // Calculate actual derivative
        float derivActual = 1.0f / (cos(input) * cos(input));

        // Show value and derivatives
        cout << "tan(" << input << ") = " << y.getValue() << '\n';
        cout << "  dual# dy/dx = " << y.getDerivative() << '\n';
        cout << "  actual dy/dx = " << derivActual << '\n';
        cout << "  numeric dy/dx = " << derivNumeric << '\n';
    }

    // atan
    {
        // Calculate value and derivative using dual numbers
        Duals<1, float> y = arctan(x);

        // Calculate numeric derivative using central differences
        float derivNumeric = (atan(input + EPSILON) - atan(input - EPSILON)) / (2.0f * EPSILON);

        // Calculate actual derivative
        float derivActual = 1.0f / (1.0f + input * input);

        // Show value and derivatives
        cout << "atan(" << input << ") = " << y.getValue() << '\n';
        cout << "  dual# dy/dx = " << y.getDerivative() << '\n';
        cout << "  actual dy/dx = " << derivActual << '\n';
        cout << "  numeric dy/dx = " << derivNumeric << '\n';
    }
}

// Define the function to calculate derivatives
template <typename T>
void calculateDerivatives(const std::vector<T>& variables, std::vector<std::array<T, 2>>& partialDerivatives) 
{
    // Iterate through variable pairs
    for (size_t i = 0; i < variables.size(); i += 2) {
        // Create dual numbers for the pair of variables
        Duals<2, T> x1(variables[i], {1, 0}); // Partial derivative with respect to x1
        Duals<2, T> x2(variables[i + 1], {0, 1}); // Partial derivative with respect to x2

        // Calculate the value of the function using the pair of variables
        T value = x1.getValue() * x2.getValue(); // Example function: f(x1, x2) = x1 * x2

        // Store the partial derivatives of the pair of variables
        partialDerivatives.push_back({x1.getDerivative(0), x2.getDerivative(1)});
    }
}

int main() 
{
    TestSimpleFunction<1, float>(1.5f);
    TestSimpleFunction<1, float>(2.75f);

    TestTrig(PI / 4.0f);

    TestMath(4.0f);

    TestTwoD(2.5f, 3.7f);

    Test2D(5.5f, 6.28f);

    Test3D(12.7f, 7.53f, 5.01f); 

    // Example: Calculate derivatives for 8 variables
    std::vector<float> variables = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    std::vector<std::array<float, 2>> partialDerivatives;

    // Calculate derivatives for pairs of variables
    calculateDerivatives(variables, partialDerivatives);

    // Output the partial derivatives
    for (size_t i = 0; i < partialDerivatives.size(); ++i) {
        std::cout << "Partial derivatives for variables " << (i * 2) + 1 << " and " << (i * 2) + 2 << ": ";
        std::cout << "dx" << (i * 2) + 1 << " = " << partialDerivatives[i][0] << ", ";
        std::cout << "dx" << (i * 2) + 2 << " = " << partialDerivatives[i][1] << std::endl;
    }

    return 0;
}
