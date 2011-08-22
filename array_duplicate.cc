/*

Problem description: 
---------------------

   You have a read-only array A[1..n] which is populated by numbers from 1..n-1, which implies atleast one repetition. However, there can be more. Find any one repeated number in linear time using constant space.

Solution:
-----------

   As the A[n] =‚ n (The array contains elements between 1 c n-1) then A[n] contains some other element from 1 to n-1. Now starting from A[n] you can think of a linked list. Assume that A[n] points to k if A[n] = k. The linked list starting from A[n] must have a loop at the end as there are duplicate elements.  
    
Proof: If there is no loop. Then there are no two nodes pointing to the same node. In that case the linked list starting from A[n] will be of length n and all n node will contain different values. Which is not true.  
 
Now it just boils down to cycle detection algorithm in a linked list. You need to find out the start node of the cycle. 
*/

#include <iostream>

#define SIZE sizeof(input)/sizeof(input[0])

int findDuplicate(const int *A, int n)
{
	int x = n, y = n; 
    
  do {
		x = A[A[x]]; 
		y = A[y]; 
  } while (x!=y);  
   
  x = n;  
	 
	do {
		x = A[x]; 
		y = A[y]; 
	} while (x!=y);  
   
  return x;   
}

int main()
{
	int input[] = {3,3,4,4,1,2};
	std::cout << "Duplicate no: " << findDuplicate(input, SIZE-1) << std::endl;
	return 0;
}
