#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
//#include <crtdbg.h>

/*
int cmp(const void* arg1, const void* arg2) {
	const int arg1_ = *(const int*)arg1;
	const int arg2_ = *(const int*)arg2;
	if (arg1_ < arg2_) return -1;
	if (arg1_ > arg2_) return 1;
	return 0;
}
*/

typedef struct Man
{
	int score;
	int rank;
} man;


int main()
{
	int n;
	scanf("%d", &n);
	man * mans = (man*)malloc(sizeof(man) * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &mans[i].score);
	}


	//qsort는 모르겠음
	/*
	qsort(mans, n, sizeof(man), &cmp);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", mans[i].score);
	}
	*/

	for (int i = 0; i < n; i++)
	{
		mans[i].rank = 1;
		for (int j = 0; j < n; j++)
		{
			if (mans[i].score < mans[j].score)
				mans[i].rank++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n", mans[i].score, mans[i].rank);
	}

	free(mans);


	//_CrtDumpMemoryLeaks();

	return 0;
}