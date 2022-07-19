#include <string>
#include <vector>
#include <map>
using namespace std;

//Ư����ȣ�� ���ڿ� split�� user ����. //sstream �� ���� �Ẹ�� �Լ�
const vector<string> split(const string str, const char sign) {
	vector<string> ret;
	string tmp;
	int sign_point = 0;
	for (int i = 0; i != 3; i++) {	//act, uid, name �� 3ȸ
		if (sign_point >= str.size()) { break; }	//���ڿ� ������ Ż��
		if (i == 0) {	//���ʿ� 0���� ��ȸ
			for (int j = 0; str[j] != sign; j++) {
				tmp += str[j];
				sign_point = j + 1;
			}
		}
		else {
			for (int j = sign_point + 1; str[j] != sign; j++) {	//���б�ȣ�� ���� ĭ���� ��ȸ
				tmp += str[j];
				sign_point = j + 1;
				if (sign_point >= str.size()) { break; }	//���ڿ� ���̸� Ż��
			}
		}
		switch (i)
		{
		case 0: ret.push_back(tmp); break;	//act
		case 1: ret.push_back(tmp); break;	//uid
		case 2: ret.push_back(tmp); break;	//name *Leave�� ����
		}
		tmp.clear();
	}
	return ret;
}
vector<string> solution(vector<string> record) {
	vector<string> answer;
	map<string, string> users;
	vector<string> tmp;	//split�� ���ڿ��� ���� �뵵
	string act, uid, name;
	for (int i = 0; i != record.size(); i++) {
		//���� ���� split�ؼ� �ֱ�
		tmp = split(record[i], ' ');
		act = tmp[0];
		uid = tmp[1];
		if (act == "Enter" || act == "Change") {
			name = tmp[2];
			users[uid] = name;
		}
	}
	for (int i = 0; i != record.size(); i++) {
		tmp = split(record[i], ' ');
		act = tmp[0];
		uid = tmp[1];
		if (act == "Enter") {
			answer.push_back(users[uid] + "���� ���Խ��ϴ�.");
		}
		else if (act == "Leave") {
			answer.push_back(users[uid] + "���� �������ϴ�.");
		}
	}
	return answer;
}