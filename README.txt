-----
Thread Synchronization Primitives
By: Hannah Lyhne
03/31/2014
-----

This is my solution for assignment 4 in CSCI 340.

This program shows how to use pthread's synchronization 
mechanisms to solve a problem of mutual exclusion and a 
problem of deadlock using mutexs and condition variables.

These files have been changed so that mutex creates and
announces enumerated threads and then has these threads
count in order now (initially they counted out of order).
The file deadlock has two threads, 1 and 2, and two 
resources, A and B. Initially the program experienced
deadlock but has been modified so that it doesn't now.

To see this:
$ make
$ ./mutex
$ ./deadlock
