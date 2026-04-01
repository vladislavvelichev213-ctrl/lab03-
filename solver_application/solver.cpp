#include <iostream>
#include <string>
#include <cstdlib>
#include "formatter_ex.h"
#include "solver.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: solver <a> <b> <c> <eps> [x1] [x2]" << std::endl;
        std::cerr << "  a, b, c - coefficients of quadratic equation ax^2 + bx + c = 0" << std::endl;
        std::cerr << "  eps - precision" << std::endl;
        std::cerr << "  x1, x2 - initial interval (optional, default: -1000, 1000)" << std::endl;
        return 1;
    }
    
    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);
    double eps = 1e-6;
    
    if (argc >= 5)
    {
        eps = std::stod(argv[4]);
    }
    
    // Начальный интервал (по умолчанию -1000, 1000)
    double x1 = -1000;
    double x2 = 1000;
    
    if (argc >= 6)
    {
        x1 = std::stod(argv[5]);
    }
    if (argc >= 7)
    {
        x2 = std::stod(argv[6]);
    }
    
    std::cout << "Searching root on interval [" << x1 << ", " << x2 << "]" << std::endl;
    
    Solver solver;
    double root = solver.findRoot(a, b, c, eps, x1, x2);
    
    std::cout << formatter_ex("Root: " + std::to_string(root));
    
    return 0;
}
