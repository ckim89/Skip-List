#include <stdio.h>
#include <stdlib.h>
#include "rand100.h"
#include "sl_repository.h"

typedef struct d_element {
	int key;
	int *data;
	struct d_element *next;
	struct d_element *down;
} element;

/* We declare our global variables outside of our functions */
int percent, num, height, i;
unsigned long int counter;
element *head;
element *record[50];

/* We want to create a sentinel node to start with. The head sentinel will
 * always be the upper-most sentinel node */
void Repository_init(int p) {
	percent = p;
	num = 0;
	counter = 0;
	height = 1;
	head = malloc(sizeof(element));
	head->key = -1;
	head->next = NULL;
	head->down = NULL;
}

/* This function will insert a new element into our list. If necessary, we will
 * create a new node in a higher level of our structure. If there is no sentinel
 * node for that level, we will create a new one.*/
int Repository_insert(int key, int data) {
	int h = height - 1;
	int rand;
	element *newrecord;
	element *newnode;
	element *temp;
	element *search;
	element *newsentinel;
	search = head;
	record[h] = head;
	/* This nested while loop will be used to traverse the list. Once we find a
	 * key that is greater than our inputted key, we know we can go down the
	 * list. */
	while (search != NULL) {
		while (search->next != NULL) {	
			if (search->next->key == key) {
				return 0;
			}
			if (search->next->key > key) {
				record[h] = search;
				break;
			}
			search = search->next;
			counter++;
		}
		record[h] = search;
		search = search->down;
		h--;
		counter++;
	}
	newrecord = malloc(sizeof(element));
	if (newrecord == NULL) {
		return -1;
	}
	/* We make a new node at the bottom level here. */
	h++;
	int *ndata = malloc(sizeof(int));
	*ndata = data;
	newrecord->key = key;
	newrecord->next = record[h]->next;
	newrecord->down = NULL;
	newrecord->data = ndata;
	record[h]->next = newrecord;
	temp = newrecord;
	num++;
	rand = rand100();

	/* We want to check if we want to make a new node. If there is no elements
	 * in an higher level, but we need to make a new node, we create a new
	 * sentinel node to start a new list. */
	while (rand <= percent) {
		newnode = malloc(sizeof(element));
		if (newnode == NULL) {
			return -1;
		}
		if (h >= height - 1) {
			newsentinel = malloc(sizeof(element));
			if (newsentinel == NULL) {
				return -1;
			}
			newsentinel->next = newnode;
			newsentinel->down = head;
			head = newsentinel;
			newnode->next = NULL;
			newnode->key = key;
			newnode->down = temp;
			temp = newnode;
			newnode->data = ndata;
			h++; 
			height++;
		}
		else {
			h++;
			newnode->key = key;
			newnode->down = temp;
			newnode->next = record[h]->next;
			record[h]->next = newnode;
			temp = newnode;
			newnode->data = ndata;
		}
		rand = rand100();
	}
	for (i = 0; i <= height-1; i++) {
		record[i] = NULL;
	}
	return 1;	
}

/* In this function we wish to delete an element if an instance of the key was
 * already found in our list. We need to make sure to reallocate the pointers in
 * thie higher levels once we delete the column. If an entire level is empty, we
 * want to delete the sentinel for that level.*/
int Repository_delete(int key) {
	element *search;
	element *temp;
	element *temp1;
	element *rowhead;
	search = head;
	rowhead = head;
	/* We search through our structure through similar nested while loops. If we
	 * find a key that is greater than the inputted key, we want to go down our
	 * list to keep checking. If we find a value of the key within the list, we
	 * free the data and reallocate the pointers as we go.*/
	while (search != NULL) {
		while (search->next != NULL) {	
			if (search->next->key > key) {
				break;
			}
			if (search->next->key == key) {
				/* This is a case in which we are at the bottom of the list. We
				 * want to free the data*/
				if (search->down == NULL) {
					free(search->next->data);
					num--;
					temp = search->next;
					search->next = temp->next;
					free(temp);
					/* we delete the sentinel nodes if there is nothing inside
					 * of them */
					if (rowhead->next == NULL && rowhead->down != NULL) {
						temp1 = rowhead->down;
						free(temp1);
						rowhead = temp1;
						head = rowhead;
						height--;
						counter++;
					}	
					return 1;
				}
				/* This is the general case where we are traversing the list and
				 * deleting. We want to reallocate pointers as we go.*/
				temp = search->next;
				search->next = temp->next;
				free(temp);
				if (rowhead->next == NULL && rowhead->down != NULL) {
					temp1 = rowhead->down;
					free(rowhead);
					rowhead = temp1;
					head = rowhead;
					height--;
					counter++;
				}
				break;
			}
			search = search->next;
			counter++;
		}
		search = search->down;
		counter++;
	}
	return 0;
}
/* We traverse through our structure and return the data if the element
 * specified by the inputted key is found */
int Repository_get(int key, int *data) {
	element *search;
	search = head;
	/* We want to traverse the list just like in delete and insert, but we only
	 * wish to find an instance of the key, so we just search*/
	while (search != NULL) {
		while (search->next != NULL) {
			if (search->next->key == key) {
				*data = *(search->next->data);
				return 1;
			}
			if (search->next->key > key) {
				break;
			}
			search = search->next;
			counter++;
		}
		search = search->down;
		counter++;
	}
	return 0;
}
/* We want to print the number of unique elements in each level of the structure
 * for every case, the height of the structure, and the number of next steps*/
void Repository_print(int print_elements) {
	element *rowhead = head;
	element *search = head;
	element *dsearch = head;
	int lnum = 0;
	int counts = 0;
	int acounts[height-1];
	int h = height - 1;

	printf("The number of unique elements in our list is: %d\n" , num);
	printf("The \"height\" of the list is: %d\n" , height);
	printf("The number of next steps performed so far is: %lu\n" , counter);
	/* we find the start to every list in our list */	
	while (rowhead != NULL) {
		record[h] = rowhead;
		rowhead = rowhead->down;
		record[h] = record[h]->next;
		h--;
	}
	h = 1;
	/* if the next node in the list above the base level and each successive one
	 * holds the specified node, we print it the number of times it is seen in
	 * our structure.*/

	if (print_elements == 1 || print_elements == 2) {
		while (record[0] != NULL) {
			printf("{ %d , %d } " , record[0]->key , *(record[0]->data));
			while (record[h] != NULL && print_elements == 2) {
				if (record[h]->key == record[0]->key) {
					printf("{ %d , %d } " , record[0]->key , *(record[0]->data));
					record[h] = record[h]->next;
				}
				h++;
			}
			record[0] = record[0]->next;
			h = 1;
			printf("\n");
		}	
	}
	h = height - 1;
	/* we look through our list and count the number of times we see an element
	 * in every level */
	while (search != NULL) {
		while(search != NULL) {
			lnum++;
			search = search->next;
		}
		dsearch = dsearch->down;
		search = dsearch;
		acounts[h] = lnum;
		lnum = 0;
		
		h--;
	}
	counts = height;
	while (counts > 0) {
		printf("The number of elements in level %d is: %d\n", counts, acounts[counts-1]);
		counts--;
	}
	printf("\n");
}
