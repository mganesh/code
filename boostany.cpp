#include <boost/any.hpp>
#include <map>
#include <iostream>

int main() {
    std::map<std::string, boost::any> hetroMap;

    hetroMap["0"] = 1;
    hetroMap["1"] = std::string("Ganesh");

    try {
        int i = boost::any_cast<int>(hetroMap["0"]);
        std::string s = boost::any_cast<std::string>(hetroMap["1"]);
        std::cout << i << " - " << s << std::endl;
    } catch (const boost::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
