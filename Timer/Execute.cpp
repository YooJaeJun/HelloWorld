#include <iostream>
#include <vector>
#include "Timer.h"
using namespace std;

const int vsize = 30;
vector<long long> v(vsize + 1);

void Pibo(const int size)
{
	v[1] = v[2] = 1;
	for (int i = 2; i <= size; i++)
	{
		v[i] = v[i - 2] + v[i - 1];
	}
	cout << v[size] << endl;
}

long long PiboRecur(int cur)
{
	if (cur < 2)
		return cur;
	return PiboRecur(cur - 2) + PiboRecur(cur - 1);
}

long long PiboRecurMemo(int cur)
{
	if (cur < 2)
		return cur;
	else if (v[cur])
		return v[cur];
	return v[cur] = PiboRecur(cur - 2) + PiboRecur(cur - 1);
}

int main()
{
	Timer timer;

	timer.Start();
	{
		Pibo(vsize);
	}
	timer.End();
	cout << "for : " << timer.RunningTime() << endl;
	v.clear();
	v.resize(vsize + 1);

	timer.Start();
	{
		cout << PiboRecur(vsize) << endl;
	}
	timer.End();
	cout << "Recur : " << timer.RunningTime() << endl;
	v.clear();
	v.resize(vsize + 1);


	timer.Start();
	{
		cout << PiboRecurMemo(vsize) << endl;
	}
	timer.End();
	cout << "Memoization : " << timer.RunningTime() << endl;
	v.clear();
	v.resize(vsize + 1);

	return 0;
}