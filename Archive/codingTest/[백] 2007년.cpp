#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector<string> dayweak{ "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };		//n%7==0�� �� �� �ֱ⿡ �տ� SUN.
	vector<int> monthlydays{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 };	//1���� ���� ������, 12�� ������ ��� ��� �� ����.
	int x, y;
	string answer;
	scanf("%d %d", &x, &y);
	//y(+?) % 7 ��°�� dayweak�� ����
	//(+?) : 30���̸� ������ +3, 28���̸� ������ +0, 30���̸� ������ +2(== monthlydays[x] % 7)�� ��Ģ �ľ�
	int coef = 0;
	for (int i = 1; i != x; i++) {
		coef += monthlydays[i] % 7;
	}
	answer = dayweak[(y + coef) % 7];
	cout << answer;
	return 0;
}