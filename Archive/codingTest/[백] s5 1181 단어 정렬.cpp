#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> sorted;
//���� ����
void merge(vector<string>& data, const int& start, const int& mid, const int& end) {
	int i = start;
	int j = mid + 1;
	int k = start;

	while (i <= mid && j <= end) {
		//����1. ���ڿ� ���̷� �Ǵ�
		if (data[i].size() < data[j].size()) {
			sorted[k++] = data[i++];
		}
		else if (data[i].size() > data[j].size()) {
			sorted[k++] = data[j++];
		}
		else {	//���� �� ����2. ������ 
			if (strcmp(data[i].c_str(), data[j].c_str()) < 0) {
				sorted[k++] = data[i++];
			}
			else {
				sorted[k++] = data[j++];
			}
		}
	}
	while (i <= mid) {
		sorted[k++] = data[i++];
	}
	while (j <= end) {
		sorted[k++] = data[j++];
	}
	//���ĵ� �迭�� ����
	for (int t = start; t <= end; t++) {
		data[t] = sorted[t];
	}
}
void merge_sort(vector<string>& data, const int& start, const int& end) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(data, start, mid);	//���� ����
		merge_sort(data, mid + 1, end);	//���� ����
		merge(data, start, mid, end);
	}
}

int main() {
	int size;
	cin >> size;
	vector<string> vs(size);
	for (string& elem : vs) {
		cin >> elem;
	}
	sorted.resize(size);
	merge_sort(vs, 0, size - 1);

	cout << vs[0] << endl;
	for (int i = 1; i != size; i++) {
		if (vs[i] != vs[i - 1]) {
			cout << vs[i] << endl;
		}
	}
	return 0;
}