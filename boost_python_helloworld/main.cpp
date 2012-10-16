#include <boost/python.hpp>
namespace bp = boost::python;

class MyClass {
public:
	MyClass() {}
     void helloworld() { std::cout << "Hello World!\n"; }
};

 
 
BOOST_PYTHON_MODULE(testmodule) {
    bp::class_< MyClass >("MyClass")
        .def("helloworld", &MyClass::helloworld)
    ;

}
 
