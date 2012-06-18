#include <iostream>
 
struct is_alpha {
    void operator()(char input) {
        if ((input >= 'a' && input <= 'z')
            || (input >= 'A' && input <= 'Z'))
            std::cout << input;
    }
};
 
int main() {
    freopen("test.easy", "r", stdin);
    std::string input;
    std::getline(std::cin, input);
    std::for_each(input.begin(), input.end(),is_alpha());
    std::cout << std::endl;
    fclose(stdin);
    return 0;
}