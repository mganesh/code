#include <iostream>
#include <iterator>
#include <vector>

/* Bubble Sort
 * 
 * Compare two values in the data structure.
 *  If left > right - then swap 2 elements.
 *  Continue till the end of the elements,
 *  which, at the time, would have moved the 
 *  largest element to the end.
 */

template <typename T>
void bubble_sort(T first, T last) {
    typename std::iterator_traits<T>::difference_type size = std::distance(first, last);
    for(int i=0; i<size; ++i) {
        T start = first;
        for(int j=0; j<size-i-1; ++j) {
            typename std::iterator_traits<T>::value_type left = *start;
            typename std::iterator_traits<T>::value_type right = *(start+1);
            if (left > right) {
                *start = right;
                *(start+1) = left;
            }
            ++start;
        }
    }
}

int main() {

    std::vector<int> input;
    std::vector<int>::iterator it;
    input.push_back(2);
    input.push_back(4);
    input.push_back(5);
    input.push_back(1);

    std::cout << "Before:";
    for(it = input.begin(); it != input.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;

    bubble_sort(input.begin(), input.end());

    std::cout << "After:";
    for(it = input.begin(); it != input.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;

    return 0;
}
