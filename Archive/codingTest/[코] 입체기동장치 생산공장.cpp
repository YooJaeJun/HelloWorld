//c++ 스타일로 코딩
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
	int t;
	cin >> t;
	std::map<int, int> m;
	vector<int> idxs(t);
	int val;
	for (int& elem : idxs) {
		cin >> elem >> val;
		m[elem] = val;
	}
	for (auto it = m.begin(); it != m.end(); it++) {
		cout << it->first << ' ' << it->second << endl;
	}
	return 0;
}


//c 스타일로 코딩
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Device
{
	int a;
	int b;
} device;



int main()
{
	device dev[100];
	int n = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &dev[i].a, &dev[i].b);
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n", dev[i].a, dev[i].b);
	}

	device temp;
	for (int i = 0; i != n; i++)
	{
		for (int j = 0; j != n - 1 - i; j++)
		{
			if (dev[j].a > dev[j + 1].a)
			{
				temp = dev[j];
				dev[j] = dev[j + 1];
				dev[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n", dev[i].a, dev[i].b);
	}

	return 0;
}
*/







