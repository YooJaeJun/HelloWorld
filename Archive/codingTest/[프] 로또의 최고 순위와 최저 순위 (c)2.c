//Ǯ��2
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// lottos_len�� �迭 lottos�� �����Դϴ�.
// win_nums_len�� �迭 win_nums�� �����Դϴ�.
int* solution(int lottos[], size_t lottos_len, int win_nums[], size_t win_nums_len) {
	// return ���� malloc �� ���� �Ҵ��� ������ּ���. �Ҵ� ���̴� ��Ȳ�� �°� �������ּ���.
	int* answer = (int*)malloc(sizeof(int) * 2);



	int min = 0, plus = 0, minRank = 0, maxRank = 0;

	for (int i = 0; i < lottos_len; i++)
	{
		if (lottos[i] == 0)
			plus++;
		for (int j = 0; j < win_nums_len; j++)
			if (lottos[i] == win_nums[j])
				min++;
	}
	if (min == 0 || min == 1)
		minRank = 6;
	if (min + plus == 0 || min + plus == 1)
		maxRank = 6;
	for (int i = 2; i <= lottos_len; i++)
	{
		if (min == i)
			minRank = 7 - i;
		if (min + plus == i)
			maxRank = 7 - i;
	}

	answer[0] = maxRank;
	answer[1] = minRank;

	return answer;
}


int main()
{
	int lot[6] = { 0, 0, 0, 0, 0, 0 };
	int win[6] = { 38, 19, 20, 40, 15, 25 };
	int* p;
	p = solution(lot, 6, win, 6);
	printf("%d %d", p[0], p[1]);


	return 0;
}

