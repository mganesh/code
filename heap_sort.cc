#include <iostream>
#include <vector>
#include <exception>
#include <iterator>
#include <algorithm>

template<typename T>
class Heap {
private:
    std::vector<T> elements;
    inline bool empty() {
        return elements.empty();
    }
    int parent(int pos) {
        return (pos-1)/2;
    }

public:
    Heap() {
    }
    Heap(size_t n) {
        elements.reserve(n);
    }
    T top() throw() {
        if (empty()) {
            throw std::string ("invalid index");
        }
        return elements[0];
    }
    size_t size() {
        return elements.size();
    }
    void push(T key); 
    void pop(); 
};

template<typename T>
void Heap<T>::push(T key) {

    // 1. push the element to the end.
    elements.push_back(key);

    // 2. move up till the new key is placed in
    // correct position
    int index = elements.size()-1;
    T temp = elements[index];
    int pIndex = parent(index);

    while (index > 0 && temp >= elements[pIndex]) {
        elements[index] = elements[pIndex];
        index = pIndex;
        pIndex = parent(pIndex);
    }

    elements[index] = temp;
}

template<typename T>
void Heap<T>::pop() {
    int index = 0;
    // copy last element to first
    elements[index] = elements[size()-1];
    // remove last
    elements.pop_back();

    T temp = elements[index];

    int cIndex=0;
    int rIndex=0;
    int lIndex=0;

    int _size = size();

    // move down until first element 
    // placed in correct pos
    while(index < _size/2) {
        lIndex = index*2+1;
        rIndex = lIndex+1;

        if (rIndex < _size &&
                elements[lIndex] < elements[rIndex]) {
            // rIndex is bigger
            cIndex = rIndex;
        } else {
            cIndex = lIndex;
        }

        if (temp >= elements[cIndex])
            break;

        elements[index] = elements[cIndex];
        index = cIndex;
    }

    elements[index] = temp;
}

int main() {
    // Test
    Heap<double> heap;

    heap.push(10);
    heap.push(40);
    heap.push(50);
    heap.push(20);
    heap.push(30);

    while (heap.size() != 0) {
        std::cout << heap.top() << " ";
        heap.pop();
    }
    std::cout << "\n";

    return 0;
}
