#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n = 10000;
	int** a = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
//		printf("%p\n", &a[i]);
	}
	printf("malloc 2\n");
	for (int i = 0; i < n; i++) {
		a[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
//			printf("%p ", &a[i][j]);
		}
//		printf("\n");
	}
}