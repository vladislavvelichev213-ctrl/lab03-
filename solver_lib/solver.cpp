#include "solver.h"
#include <cmath>
#include <algorithm>

double Solver::findRoot(double a, double b, double c, double eps, 
                        double x1, double x2)
{
    // Убедимся, что x1 < x2
    if (x1 > x2) {
        std::swap(x1, x2);
    }
    
    // Поиск корня методом бисекции
    while (std::abs(x2 - x1) > eps)
    {
        double mid = (x1 + x2) / 2;
        double f_mid = a * mid * mid + b * mid + c;
        double f_x1 = a * x1 * x1 + b * x1 + c;
        
        if (std::abs(f_mid) < eps)
        {
            return mid;
        }
        else if (f_x1 * f_mid < 0)
        {
            x2 = mid;
        }
        else
        {
            x1 = mid;
        }
    }
    
    return (x1 + x2) / 2;
}
