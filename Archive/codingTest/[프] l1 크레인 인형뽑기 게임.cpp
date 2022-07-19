#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;
	//board�� �� �ǹ�: ���� ���� //moves�� �� �ǹ�: �� ��°
	vector<int> basket;
	for (int i = 0; i != moves.size(); i++) {
		for (int j = 0; j != board.size(); j++) {
			if (board[j][moves[i] - 1] != 0) {	//�� n��°�� ��������
				basket.push_back(board[j][moves[i] - 1]);
				board[j][moves[i] - 1] = 0;
				if (basket.size() > 1 && basket.back() == basket[basket.size() - 2]) {	//������ ���ҿ� ������ �� ���� ��
					answer += 2;
					basket.pop_back();
					basket.pop_back();	//���� 2����
				}
				break;
			}
		}
	}
	return answer;
}