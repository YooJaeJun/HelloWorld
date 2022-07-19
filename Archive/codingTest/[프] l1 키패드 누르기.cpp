#include <string>
#include <vector>
using namespace std;

//��� ���ڵ��� 2, 5, 8, 0�� ���� �Ÿ�
const int distance_arr[12][4] = { {1, 2, 3, 4}, {0, 1, 2, 3}, {1, 2, 3, 4},
	{2, 1, 2, 3}, {1, 0, 1, 2}, {2, 1, 2, 3},
	{3, 2, 1, 2}, {2, 1, 0, 1}, {3, 2, 1, 2},
	{4, 3, 2, 1}, {3, 2, 1, 0}, {4, 3, 2, 1},
};

const char get_distance(const int& elem, int& left, int& right, const string& hand) {
	char ret;
	int order = -1;	//����׿�
	switch (elem)
	{
		//distance_arr���� 2, 5, 8, 0 ��
	case 2:
		order = 0;
		break;
	case 5:
		order = 1;
		break;
	case 8:
		order = 2;
		break;
	case 11:	//11��°�� ġȯ�� 0
		order = 3;
		break;
	}
	if (distance_arr[left - 1][order] == distance_arr[right - 1][order]) {
		if (hand == "right") {
			right = elem;
			ret = 'R';
			return ret;
		}
		else if (hand == "left") {
			left = elem;
			ret = 'L';
			return ret;
		}
	}
	else if (distance_arr[left - 1][order] > distance_arr[right - 1][order]) {
		right = elem;
		ret = 'R';
		return ret;
	}
	else {
		left = elem;
		ret = 'L';
		return ret;
	}
}

string solution(vector<int> numbers, string hand) {
	string answer = "";

	//0�� *�� # ��ġ ����
	const int pointer_sign = 10;
	const int zero_sign = 11;	//�ڵ�� 0�� 11��°�� ����
	const int sharp_sign = 12;
	int left = pointer_sign;
	int right = sharp_sign;

	for (auto& elem : numbers) {
		switch (elem) {
		case 1:
		case 4:
		case 7:
			left = elem;
			answer += 'L';
			break;
		case 3:
		case 6:
		case 9:
			right = elem;
			answer += 'R';
			break;
		case 0:
			elem = 11;	//0�� 11��°�� ġȯ
		default:
			answer += get_distance(elem, left, right, hand);
			break;
		}
	}

	return answer;
}