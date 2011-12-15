#include <iostream>
#include <sstream>
#include <string>

#include <boost/math/tools/minima.hpp>

double f(double x) { return x * cos(x); }

int main(int argc, char** argv)
{
    typedef std::pair<double, double> Result;
    Result r2 = boost::math::tools::brent_find_minima(f, 3.0, 4.0, 20);
    std::cout << "x=" << r2.first << " f=" << r2.second << std::endl;
    return 0;
}

// output:
// x=3.42562 f=-3.28837


/* CMakeLists.txt
cmake_minimum_required(VERSION 2.6)
 
Project(brent_test)
 

FIND_PACKAGE(Boost)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
ADD_EXECUTABLE(brent_test main.cpp)
*/
