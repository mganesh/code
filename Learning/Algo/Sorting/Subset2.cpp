#include <iostream>
 
void printMatrix(bool **matrix, int row, int col) {
    std::cout << "Print Matrix: " << std::endl;
 
    for(int i=0; i<row; ++i) {
        for(int j=0; j<col; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}
 
void init(bool **&matrix, int row, int col){
    for(int i=0; i<row; ++i)
        for(int j=0; j<col; ++j)
            matrix[i][j] = false;
}
 
bool hasSubsetSum(int input[], int n, int sum) {
 
    const int row = n+1;
    const int col = sum+1;
 
    bool **matrix = new bool*[row];
 
    for(int i=0; i<row; ++i)
        matrix[i] = new bool [col];
 
    init(matrix, row, col);
 
    // row --> items
    // col --> sum
 
    // case 1: if no more items
    for(int i=1; i<col; ++i)
        matrix[0][i] = false;
 
    // case 2: if sum is zero, then we are done
    for(int i=0; i<row; ++i)
        matrix[i][0] = true;
 
    // case 3
    for(int i=1; i<row; ++i) {
        for(int j=1; j<col; ++j) {
 
            matrix[i][j] = matrix[i-1][j] ||
                    ( input[i-1] <= j && 
                            matrix[i-1][j - input[i-1]]);
        }
    }
 
    printMatrix(matrix, row, col);
    bool found = matrix[n][sum];
    if (!found) return false;
 
    int j = sum;
    for (int i = n; i >= 1 && j > 0; i --) {
        if (! matrix [i - 1] [j]) {
            std::cout << "Use item: " << input[i-1] << std::endl;
            j -= input [i-1];
        }
    }

    return true;
}
 
int main() {
    int array [] = { 1,3,5,4,7,6,5,8};
    const int size = sizeof(array)/sizeof(array[0]);
    int sum = 26;
    bool found = hasSubsetSum(array, size, sum);
    if (found)
        std::cout << "Subset Sum found [" << sum << "]" << std::endl;
    else
        std::cout << "Subset Sum not found [" << sum << "]" << std::endl;
 
    return 0;
}