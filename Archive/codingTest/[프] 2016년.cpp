#include <string>
#include <vector>

using namespace std;

string solution(int a, int b) {
	string answer = "";
	vector<string> dayweak{ "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };		//n%7==0�� �� �� �ֱ⿡ �տ� SUN.
	vector<int> monthlydays{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 };	//1���� ���� ������, 12�� ������ ��� ��� �� ����.

	//y(+?) % 7 ��°�� dayweak�� ����
	//(+?) : 30���̸� ������ +3, 28���̸� ������ +0, 30���̸� ������ +2(== monthlydays[x] % 7)�� ��Ģ �ľ�
	//1�� 1�� �ݿ���
	int coef = 4;
	for (int i = 1; i != a; i++) {
		coef += monthlydays[i] % 7;
	}
	answer = dayweak[(b + coef) % 7];
	return answer;
}
void main() {
	printf("%s", solution(5, 24));
}