//풀이2
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// lottos_len은 배열 lottos의 길이입니다.
// win_nums_len은 배열 win_nums의 길이입니다.
int* solution(int lottos[], size_t lottos_len, int win_nums[], size_t win_nums_len) {
	// return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
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

