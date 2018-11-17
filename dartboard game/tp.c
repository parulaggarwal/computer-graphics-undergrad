#include<stdio.h>

int main()
{
	int i;
	srand();
	for(i=0; i<15; i++)
	printf("%d\n", rand()%150);
	return 0;
}
