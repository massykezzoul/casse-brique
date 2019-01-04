#include <iostream>
#include <algorithm> //transform()
#include <string> 

int main() {
    std::string data = "AbcAAA"; 
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    std::cout << data << std::endl;
    return 0;
}