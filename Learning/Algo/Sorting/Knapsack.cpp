#include <iostream>
#include <iomanip>

int KnapsackTopDown(int weight, int W[], int V[], int n) {

	// 1. Base case
	if (weight == 0 || n == 0)
		return 0;

	// 2. If current weight is more than total weight
	if (W[n-1] > weight) {
		return KnapsackTopDown(weight, W, V, n-1);
	}

	/* 3. if total weight is not more 
	*/

	else return std::max(KnapsackTopDown(weight, W, V, n-1), 
			KnapsackTopDown(weight - W[n-1], W, V, n-1) + V[n-1]);
}

const int max = 100;
const int items = 100;
int matrix[items][max] = {0};
int picks[items][max] = {0};

int knapsack(int size, int weights[],int values[], int index){
    int take,dontTake;

    take = dontTake = 0;

    // Base case
    if (matrix[index][size] != 0)
        return matrix[index][size];

    // ran out of options
    if (index == 0){
    	
        if (weights[0]<=size){
        	picks[index][size]=1;
            matrix[index][size] = values[0];
            return values[0];
        }
        else{
        	picks[index][size]=-1;
            matrix[index][size] = 0;
            return 0;
        }
    }

    if (weights[index]<=size)
        take = values[index] + knapsack(size - weights[index], weights, values, index-1);

    dontTake = knapsack(size, weights, values, index-1);

    matrix[index][size] = std::max (take, dontTake);

    if (take > dontTake)
    	picks[index][size]=1;
    else // we did not pick it up
    	picks[index][size]=-1;

    return matrix[index][size];

}

void printMatrix(int item, int weight) {
	for(int i=0; i<=item; ++i) {
		for(int j=0; j<=weight; ++j) {
			std::cout << std::setw(3) << picks[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void printPicks(int item, int weight, int weights[], int val[]){
	std::cout << "Picks were: " << std::endl;

    while (item >= 0){
    	
        if (picks[item][weight] == 1){
        	std::cout << "\tpick(" << item << "," << weight <<"," << weights[item] <<") & ";
            std::cout << "\tPicked up: " << val[item] << std::endl;


            weight -= weights[item];
        }
        
        item--;
    }

    return;
}

int main() {
	
    /*
    int val[] = {1, 6, 18, 22, 28};
    int wt[] =  {1, 2, 5 , 6, 7};
    int  W = 11;
*/

    int val[] = { 1, 2, 3,4,5,6,7,8,9,10};
    int wt[] = { 1, 2, 3,4,5,6,7,8,9,10};
    int W = 27;
    
    int n = sizeof(val)/sizeof(val[0]);

    std::cout << "Version 1: " << KnapsackTopDown(W, wt, val, n) << std::endl;
    std::cout << "Version 2: " << knapsack(W, wt, val, n-1) << std::endl;
    
    printMatrix(n-1, W);
    printPicks(n-1,W, wt, val);
    return 0;
}