#include <iostream>
#include <string>
#include <boost/regex.hpp>
 
using namespace boost;
 
int main() {
        //std::string uri("session id = /279-2000001-0452557/");
        std::string uri("/279-2000001-0452557/");
        boost::smatch what;
        boost::regex sessionIdRegex("/([0-9]{3}-[0-9]{7}-[0-9]{7})/");
        if(boost::regex_match(uri, what, sessionIdRegex)) {
                printf("happy\n");
        } else {
                printf("sad\n");
        }
        return 0;
}
