#include <string>
#include <iostream>

class State {
    public :
        State() {
            std::string s = "Hello from State";
            std::cout << s << std::endl;
        }
}