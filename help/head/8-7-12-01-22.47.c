/*	8-7-12-01-22.47.c -- µÚ°ËÕÂµÚÆßÌâ	*/
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT (0)
#define SIZE (-1)
#define OSS (-65536)

typedef int Item ;
typedef Item SetType ;
typedef SetType * DisjiontSet ;

void initialize_as_height (DisjiontSet gather, const int size) ;
void initialize_as_size (DisjiontSet gather, const int size) ;
int set_union_as_height (DisjiontSet gather, SetType t1, SetType t2) ;
int set_union_as_size (DisjiontSet gather, SetType t1, SetType t2) ;
SetType find (DisjiontSet gather, const Item item) ;
void print_gather (const DisjiontSet gather, const int size) ;
int menu (void) ;
void eat_line (void) ;
void get_input (Item * const pi1, Item * const pi2) ;
void link (DisjiontSet gather, const Item i1, const Item i2, const int mode) ;
int main (void) ;

int main (void)
{
	DisjiontSet gather ;
	Item i1, i2 ;
	int lenth, size, mode ;
	char choice ;
	
	lenth = sizeof (SetType) ;
	size = 9 ;
	gather = (SetType *) malloc (lenth * (size + 1)) ;

	initialize_as_height (gather, (size + 1)) ;
	mode = HEIGHT ;
	while (choice = menu ())
	{
		switch (choice)
		{
			case 1	:	get_input (&i1, &i2) ;
						link (gather, i1, i2, mode) ;
						break ;
			case 2	:	print_gather (gather, size + 1)	;
						break ;
		}
	}
	free (gather) ;

	return 0 ;
}

void initialize_as_height (DisjiontSet gather, const int size)
{
	int i ;

	gather[0] = size - 1 ;
	/*	Be careful!	*/
	for (i = 1; i < size; i++)
		gather[i] = HEIGHT ;
}

void initialize_as_size (DisjiontSet gather, const int size)
{
	int i ;

	gather[0] = size - 1 ;
	for (i = 1; i < size; i++)
		gather[i] = SIZE ;
}

int set_union_as_height (DisjiontSet gather, SetType t1, SetType t2)
{
	if (gather[t1] > 0 || gather[t2] > 0)
		return 0 ;
	else if (gather[t2] < gather[t1])
		gather[t1] = t2 ;
	else
	{
		if (gather[t1] == gather[t2])
			gather[t1]-- ;
		gather[t2] = t1 ;
	}

	return 1 ;
}

int set_union_as_size (DisjiontSet gather, SetType t1, SetType t2)
{
	if (gather[t1] > 0 || gather[t2] > 0)
		return 0 ;
	else if (gather[t2] < gather[t1])
	{
		gather[t2] += gather[t1] ;
		gather[t1] = t2 ;
	}
	else
	{
		gather[t1] += gather[t2] ;
		gather[t2] = t1 ;
	}

	return 1 ;
}

SetType find (DisjiontSet gather, const Item item)
{
	if (item > gather[0])
		return OSS ;
	else if (gather[item] <= 0)
		return item ;
	else
		return gather[item] = find (gather, gather[item]) ;
}

void print_gather (const DisjiontSet gather, const int size)
{
	int i ;

	for (i = 1; i < size; i++)
		printf ("%-3d", gather[i]) ;
	putchar ('\n') ;
}

int menu (void)
{
	int choice ;

	puts ("<--------Imitation Programme-------->") ;
	puts ("1).Link") ;
	puts ("2).Show Condition") ;
	puts ("q).Exit") ;
	fputs ("( )\b\b", stdout) ;

	scanf ("%d", &choice) ;
	eat_line () ;
	switch (choice)
	{
		case 1	:	return 1 ;
		case 2	:	return 2 ;
		default	:	return 0 ;
	}
}

void eat_line (void)
{
	while (getchar () != '\n')
		continue ;
}

void get_input (Item * const pi1, Item * const pi2)
{
	puts ("Please input the first number:") ;
	while (0 == scanf ("%d", pi1))
	{
		eat_line () ;
		puts ("Please input the first number:") ;
	}
	eat_line () ;
	puts ("Please input the second number:") ;
	while (0 == scanf ("%d", pi2))
	{
		eat_line () ;
		puts ("Please input the second number.") ;
	}
	eat_line () ;
}

void link (DisjiontSet gather, const Item i1, const Item i2, const int mode)
{
	SetType t1, t2 ;

	t1 = find (gather, i1) ;
	t2 = find (gather, i2) ;
	if (OSS == t1 || OSS == t2)
	{
		if (OSS == t1 && OSS == t2)
			puts ("The 1st input and the 2nd input all overflow.") ;
		else if (OSS == t1)
			puts ("The 1st input overflow.") ;
		else
			puts ("The 2nd input overflow.") ;
		return ;
	}
	if (t1 == t2)
		puts ("In the same set.") ;
	else
	{
		if (HEIGHT == mode)
			set_union_as_height (gather, t1, t2) ;
		else if (SIZE == mode)
			set_union_as_size (gather, t1, t2) ;
		puts ("Union operation has happend.") ;
	}
}