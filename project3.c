
/* 
 * Project 3 template: to be modified by students to incorporate 
 *                     command line arguments exclusively 
 *                     (no input while program is running)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sl_repository.h"
#include <time.h>

clock_t start, end;
double cpu_time_used;
unsigned long int next =1;

void Get_next_op( char *random_op, int *random_int, int range );
int  rand( void ); 
void srand( unsigned int seed );

int main(int argc, char *argv[])
{
	start = clock();
    unsigned int s = 1;

    int    Max_range=100;
    int    num_op = 1000000;
    int    rand_key;
    char   rand_op;
    int    ret; 
    int	   ret_data;
	int    p = 50;
    int    i;

    unsigned int sum_data;
    int num_get, num_delete, num_insert;
	
	while(--argc > 0) {
		argv++;
		if (!strncmp(*argv, "-r", 2)) {
			sscanf(argv[1], "%d" , &Max_range);
			argc--; argv++;
		}
		else if (!strncmp(*argv, "-o", 2)) {
			sscanf(argv[1], "%d" , &num_op);
			argc--; argv++;
		}
		else if (!strncmp(*argv, "-s", 2)) {
			sscanf(argv[1], "%d" , &s);
			argc--; argv++;
		}
		else if (!strncmp(*argv, "-p", 2)) {
			sscanf(argv[1], "%d" , &p);
			argc--; argv++;
		}
	}

    printf("-------------------------------------------------------------------------\n");

    srand( s );

    sum_data   = 0;

    num_get    = 0;
    num_delete = 0;
    num_insert = 0;

    Repository_init( p );

    for( i = 1; i <= num_op; i++ )
    {
        Get_next_op( &rand_op, &rand_key, Max_range );

	/* printf("%c %8d %d\n", rand_op, rand_key, Max_range ); */

	switch( rand_op )
	{
	    case 'G':
                num_get++;
		ret = Repository_get( rand_key, &ret_data );
		if( ret < 0 ) {
			printf("\nError in Get with return value %d \n", ret );
		}
		if( ret == 1 ) sum_data = sum_data + (ret_data%100);
		break;

	    case 'I':
                num_insert++;
		ret = Repository_insert( rand_key, i );
		if( ret < 0 ) {
			printf("\nError in Insert with return value %d \n", ret );
		}
		break;

	    case 'D':
                num_delete++;
		ret = Repository_delete( rand_key );
		if( ret < 0 ) {
			printf("\nError in Delete with return value %d \n", ret );
		}
		break;

	    default:
		printf("\nError!!!, Illegal operation %c\n", rand_op );
		return 0;
	}

        if( (i % (num_op/10)) == 0 )
	{
		printf("Printing after %d operations\n", i );
		if( num_op <= 10000 ) Repository_print( 2 );
		if( num_op <= 1000000 && num_op > 10000 ) Repository_print( 1 ); 
		if( num_op >= 10000000)  Repository_print( 0 );
	}
    }
    printf("Operation summary: get %d, delete %d, insert %d\n", num_get, num_delete, num_insert );
    printf("Sum of all Repository_get data modulo 100 is %d\n", sum_data );
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("The total time is %f\n", cpu_time_used);
}	

void Get_next_op( char *random_op, int *random_int, int range )
{
    int  random_number;
    int  limit;

    random_number = rand() % 4;

    switch( random_number )
    {
	case 0:
	case 1:
		*random_op = 'G';
		break;
	case 2:
		*random_op = 'D';
		break;
	case 3:
		*random_op = 'I';
    }

    limit = (32768 / range ) * range;
    while( ( random_number = rand() ) >= limit ) ;

    *random_int = random_number % range + 1;
    
}

/* Pseudo random generator on 0..32767 */
int  rand(void)
{
    next = next *1103515245 + 12345;
    return (unsigned int)(next/65536)%32768;
}

void srand( unsigned int seed )
{
    next = seed;
}

