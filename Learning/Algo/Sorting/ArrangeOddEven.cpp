/* Problem Statement :

There is an array of odd and even numbers. Now, sort them in such a
way that the top portion of the array contains odd numbers, bottom
portion contains even numbers. The odd numbers are to be sorted in
descending order and the even numbers in ascending order. You are not
allowed to use any extra array and it has to use a conventional
sorting mechanism and should not do any pre or post processing.

Source : http://tinyurl.com/lfdhnsj
*/

#include <iostream>
#include <stdlib.h>

int compare(const void *left, const void *right) {
	int a = *(int *)left;
	int b = *(int *)right;

	if (a == b)
		return 0; // i dont know where to place

	else if (a & 1) // Odd Number
	{
		if (b & 1)
			return (b-a); // descending order
		else
			return -1;
	}
	else { // a is even
		if ( b & 1)
			return 1;
		else
			return (a-b); // ascending order
	}
}

int main() {
	int array[ ] = { 2, 5, 8, 1, 4, 6, 3, 7, 9 , 10};
	const int size = sizeof(array)/sizeof(array[0]);
	qsort(array, size, sizeof(int), compare);

	for(int i=0; i<size; ++i)
		std::cout << array[i] << " ";
	std::cout << std::endl;

	return 0;
}
