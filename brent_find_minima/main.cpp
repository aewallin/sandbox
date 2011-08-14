#include <iostream>
#include <sstream>
#include <string>

#include <boost/math/tools/minima.hpp>

double f(double x) { return x * cos(x); }

int main(int argc, char** argv)
{
    typedef std::pair<double, double> Result;
    Result r1 = boost::math::tools::brent_find_minima(f, 3.0, 4.0, 1e-8);
    Result r2 = boost::math::tools::brent_find_minima(f, 3.0, 4.0, 20);
    std::cout << "x=" << r1.first << " f=" << r1.second << std::endl;
    std::cout << "x=" << r2.first << " f=" << r2.second << std::endl;
    return 0;
}

