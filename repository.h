#ifndef INC_REPOSITORY
#define INC_REPOSITORY

/* 
 * Repository access functions
 */

void Repository_init();
int  Repository_invert( int key, int data );
int  Repository_get   ( int key, int *data );
void Repository_print ( int print_elements );

#endif /* INC_REPOSITORY */
