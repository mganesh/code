Exchange Feed - Ganesh Muniyandi

C++ - Linux
============

To build the Exchange Feed program execute the following:

    $ make
    $ ./ExchangeFeed <input file name>

To build the Test program which can generate automated test data
base on random number generation execute the following:

    $ cd Test
    $ make
    $ ./TestData [ no of test case ] 

By default, no of test case is limited to 32767 ( short max) if 
command line argument is omitted

    (e.g) ./TestData 100 > input.txt

The above example will generate 100 test cases with a combination of
Add, Modify, Remove both legal and illegal data and redirects the output
to a file named input.txt in this case.
