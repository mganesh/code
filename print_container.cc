#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <iostream>

/* Template function for vector, set, list */
template <typename T>
void print(T& input) {

    typedef typename std::iterator_traits<typename T::iterator>::value_type Type;
    std::copy(input.begin(), input.end(), std::ostream_iterator<Type>(std::cout, " "));
    std::cout << "\n";
}

/* function for arrays */
template<typename T, int size>
void print(T(&input) [size] ) {
    std::cout <<"Reference: ";
    std::copy(input, input+size, std::ostream_iterator<T>(std::cout, " "));
    std::cout << "\n";
}

template<typename T>
void print(T* input, int size) {
    std::cout <<"Pointer: ";
    std::copy(input, input+size, std::ostream_iterator<T>(std::cout, " "));
    std::cout << "\n";
}

struct unique_number {
private:
    int number;
public:
    unique_number()
        : number(0) {
    }
    int operator()() {
        return ++number;
    }
};

int main() {
    using namespace std;

    std::vector<int> V(10);
    std::generate_n(V.begin(), 10, unique_number());
    std::set<int> S(V.begin(), V.end());
    int array_int[] = { 1,2,3,4,5,6,7 };
    char array_char[] = { '1', '2', '3', '4' };

    print(V);
    print(S);
    print(array_int, sizeof(array_int)/sizeof(array_int[0]));
    print(array_char);


    return 0;
}
