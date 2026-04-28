#pragma once

class Solver
{
public:
    double findRoot(double a, double b, double c, double eps,
                    double left = -1000, double right = 1000);
};
