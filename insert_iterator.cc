#include <iostream>
#include <list>
#include <iterator>
#include <set>
/* Insert_iterator is an iterator adaptor 
   that functions as an Output Iterator: 
   assignment through an insert_iterator 
   inserts an object into a Container. 
   Specifically, if ii is an insert_iterator, 
   then ii keeps track of a Container c 
   and an insertion point p; 
   the expression *ii = x performs the insertion c.insert(p, x).
*/

/* insert a range of elements to list */
using namespace std;
void TestInsert()
{
	list<int> L;
	L.push_front(3);
	insert_iterator<list<int> > ii(L, L.begin());
	*ii++ = 0;
	*ii++ = 1;
	*ii++ = 2;
	copy(L.begin(), L.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	// The values that are printed are 0 1 2 3.
}

/* Merge two sorted lists, inserting the resulting range into a set. 
   Note that a set never contains duplicate elements.
*/

int main() 
{
	const int N = 6;

	int A1[N] = {1, 3, 5, 7, 9, 11};
	int A2[N] = {1, 2, 3, 4, 5, 6};
	set<int> result;

	TestInsert();
	merge(A1, A1 + N, A2, A2 + N, 
		inserter(result, result.begin()));
			   
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// The output is "1 2 3 4 5 6 7 9 11".

	return 0;
}
