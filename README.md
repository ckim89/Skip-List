The Design for project 3:

Please refer to problem.txt first to be briefed of what needs to be done.

We are asked to make a super list so that we can try and maximize efficiency
when looking through the list to find a particular element in the list. We want
to keep in mind that our list will still be sorted, just like in project 2, but
this time, we are going to keep "levels" in our data structure to help the
efficiency of the program. The most important part of the program will be that
it will be able to search through the list from top to bottom. We keep this in
mind as we look at our functions:

void repository init ( int p ) :

This function will be used to initialize the percent probability that a new node
will be created in a list above that being scrutinized. This function also will
be used to instantiate global varibles such as our counter and height of the
list. It also instantiates a sentinel node that will be used to start every
search. This will be called head.

This program will have a structure that we call an element. It will hold three
pointers and a key. Two of these pointers will be used to link the data
structure together, while the other pointer will be used to point to a data. The
key will be used to sort the elements. 

int repository_insert( int key , int data ) :

This function will be used to insert an element into our data structure. We need
to make sure that the element does not exist in the list, firstly, then add it
to the bottom level of the structure. Based on a percent probability, the
program will be prompted to either create a new node that is identical in a
level above it. We need to take particular note that while searching through the
structure, it is important to keep track of the pointers that we traverse DOWN
from. We need to reallocate these pointers in case that we need to make a new
node in that level. We return 1 if we have sucessfully added an element to our
structure, 0 if we already have the element in the structure, and -1 if we had
an error.

int repository_get( int key, int *data ) :

This function will look through the structure to look for the existance of a
certain node specified by the user. we traverse the structure much like we did
in insert. If we find the particular element, we return 1. If we did not find
the element, we will return 0. 

void repository_print( int print_elements ) :

This function will be used to print the elements in the structure based on the
particular cases that the user specifies. If the user specifies 1, we will print
the bottom level only. If the user specifies 2, we will print the entire data
structure. If the user specifies 0, we will print only the number of elements in
each level (this last case should be done for both 1 and 2 as well). 


Making and running:
A makefile has been included.
in terminal, just use "make"

running the executible with no command line arguments:
the driver is set to run 1,000,000 random operations (insert, delete, and get),
with a default range of 1-100, a default seed of 1, and a default probability of
creating a node higher up of 50%. You can set all these to different numbers
using command line arguments. Use identifier -r to set range, -o to set number
of operations, -s to set the seed, and -p to set the probability. for example:
"./project3 -r 1000 -o 1000 -s 2 -p 75" 
