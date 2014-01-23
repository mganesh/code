// A Dynamic Programming solution for subset sum problem
#include <stdio.h>
#include <iostream>
 
// Returns true if there is a subset of set[] with sun equal to given sum
bool isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];
 
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;
 
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;
 
     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= set[j-1])
           subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
       }
     }
 
    // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     }
 	
 	if (subset[sum][n])
 	{
 		int j = sum;
 		for(int i = n; i>=1 && j > 0; --i) {
 			if (! subset[j][i-1]) {
 				j -= set[i-1];
 				std::cout << "Use item : " << set[i-1] << ", j=" << j << std::endl;
 			}
 		}
 	}

     return subset[sum][n];
}
 
// Driver program to test above function
int main()
{
  int set[] = { 1,3,5,4,7,6,5,8};
  int sum = 4;
  int n = sizeof(set)/sizeof(set[0]);
  if (isSubsetSum(set, n, sum) == true)
     printf("Found a subset with given sum [%d]\n", sum);
  else
     printf("No subset with given sum [%d]\n", sum);
  return 0;
}