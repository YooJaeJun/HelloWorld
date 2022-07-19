#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	map<int, int> stu_clothes;	//<ÇÐ»ý¹øÈ£, Ã¼À°º¹¼ö>
	for (int i = 0; i != n; i++) {
		stu_clothes[i] = 1;
	}
	for (const int elem : reserve) {
		stu_clothes[elem - 1]++;
	}
	for (const int elem : lost) {
		stu_clothes[elem - 1]--;
	}
	//¿Ê ºô·ÁÁÖ±â
	for (int i = 0; i != stu_clothes.size(); i++) {
		if (stu_clothes[i] == 0) {
			if (i > 0 && stu_clothes[i - 1] == 2) {
				stu_clothes[i]++;
				stu_clothes[i - 1]--;
			}
			else if (i < n - 1 && stu_clothes[i + 1] == 2) {
				stu_clothes[i]++;
				stu_clothes[i + 1]--;
			}
		}
	}
	int answer = 0;
	for (int i = 0; i != stu_clothes.size(); i++) {
		if (stu_clothes[i] > 0) {
			answer++;
		}
	}
	return answer;
}