#include "stdio.h"
#define n 8

int main()

  {
    int i,j,a[n][n];
    printf("program to print the latin matrix n*n");
    for(i=0 ; i<n ; i++)
      for(j=0;j<n;j++)
       {
          a[i][j]=(i+j+n-1)%n;
       }
       
    for(i=0;i<n;i++)
      {
        printf("\n");
        for(j=0;j<n;j++)
        printf("%d ",a[i][j]);
      }
    return 0;
  }