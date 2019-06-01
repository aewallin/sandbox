/* Minimal boost python example with cmake
 * 
 * https://github.com/aewallin/sandbox
 * 
*/
#include <iostream>
#include <boost/python.hpp>
namespace bp = boost::python;

// Pure c++, no need to include or reference boost-python here
class MyClass {
public:
	MyClass() {}
     void helloworld() { std::cout << "Hello World!\n"; }
};

 
// wrapper to create python-module and python bindings for the class
// need boost/python.hpp headers for this
//
// in python, this is used like so:
//
// import testmodule
// obj = testmodule.MyClass()
// obj.helloworld()
//
BOOST_PYTHON_MODULE(testmodule) {
    bp::class_< MyClass >("MyClass")
        .def("helloworld", &MyClass::helloworld)
    ;

}
 
