#include <iostream>
#include <sstream>
#include <string>


#include <boost/math/tools/roots.hpp>

class Test {
public:
    double operator()(const double x) {
        return x * cos(x);
    }
};

// see: 
// http://www.boost.org/doc/libs/1_47_0/libs/math/doc/sf_and_dist/html/math_toolkit/toolkit/internals1/roots2.html

int main(int argc, char** argv) {
    Test t;
    typedef std::pair<double, double> Result;
    boost::uintmax_t max_iter=500;
    boost::math::tools::eps_tolerance<double> tol(30);

    Result r1 = boost::math::tools::toms748_solve(t, 1.0, 2.0, tol, max_iter);
    std::cout << "root bracketed: [ " << r1.first << " , " << r1.second <<  " ]" << std::endl;
    std::cout << "f("<< r1.first << ")=" << t(r1.first) << std::endl;
    std::cout << "f("<< r1.second << ")=" << t(r1.second) << std::endl;
    std::cout << "max_iter=" << max_iter << std::endl;
    return 0;
}

/* Output:
root bracketed: [ 1.5708 , 1.5708 ]
f(1.5708)=9.61835e-17
f(1.5708)=-1.99654e-15
max_iter=9
 */

/* CMakeLists.txt: 
cmake_minimum_required(VERSION 2.6) 
Project(toms748_test)
FIND_PACKAGE(Boost)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
ADD_EXECUTABLE(toms748_test main.cpp)
*/
