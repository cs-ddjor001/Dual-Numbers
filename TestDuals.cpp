#include "Duals.h"
#include <cassert>

using namespace std;

void TestTrigFunctionsSingleVariable()
{
    {
        /* Testing The Sin Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = sin(x);

        // Check value
        assert(fabs(result.getValue() - sin(0.5)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() - cos(0.5)) < EPSILON);
    }
    
    {
        /* Testing The Cos Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = cos(x);

        // Check value
        assert(fabs(result.getValue() - cos(0.5)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() + sin(0.5)) < EPSILON);
    }

    {
        /* Testing The Tan Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = tan(x);

        // Check value
        assert(fabs(result.getValue() - tan(0.5)) < EPSILON);

        // Check derivative
        double sec_sq = 1 / (cos(0.5) * cos(0.5));
        assert(fabs(result.getDerivative() - sec_sq) < EPSILON);
    }

    {
        /* Testing The ArcSin Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arcsin(x);

        // Check value
        assert(fabs(result.getValue() - asin(0.5)) < EPSILON);

        // Check derivative
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative() - 1.0 / sqrt_val) < EPSILON);
    }

    {
        /* Testing The ArcCos Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arccos(x);

        // Check value
        assert(fabs(result.getValue() - acos(0.5)) < EPSILON);

        // Check derivative
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative() + 1.0 / sqrt_val) < EPSILON);
    }

    {
        /* Testing The ArcTan Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arctan(x);

        // Check value
        assert(fabs(result.getValue() - atan(0.5)) < EPSILON);

        // Check derivative
        double denom = 1.0 + 0.5 * 0.5;
        assert(fabs(result.getDerivative() - 1.0 / denom) < EPSILON);
    }
    
    cout << "All trigonometric function tests passed!" << std::endl;
}

int main() 
{
    TestTrigFunctionsSingleVariable();
    return 0;
}
