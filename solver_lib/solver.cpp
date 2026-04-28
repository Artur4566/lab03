#include "solver.h"
#include <cmath>
#include <algorithm>

double Solver::findRoot(double a, double b, double c, double eps,
                        double left, double right)
{
    if (left > right) {
        std::swap(left, right);
    }

    while (std::abs(right - left) > eps)
    {
        double mid = (left + right) / 2;
        double f_mid = a * mid * mid + b * mid + c;
        double f_left = a * left * left + b * left + c;

        if (std::abs(f_mid) < eps)
        {
            return mid;
        }
        else if (f_left * f_mid < 0)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    return (left + right) / 2;
}
