#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const vector<string> split_vec(string s, const int& cut) {
    vector<string> v;
    int coef = 0;
    int size = s.size();
    if (size % cut != 0) {
        coef = 1;
    }
    for (int i = 0; i != size / cut + coef; i++) {
        v.push_back(s.substr(0, cut));
        s.erase(0, cut);
    }
    return v;
}
int solution(string s) {
    int answer = 0;
    vector<string> v;
    vector<int> nums;
    int same_previous = 0;
    int idx = 0;
    if (s.size() == 1) {
        return 1;
    }
    for (int cut = 1; cut <= s.size() / 2; cut++) {   //cut == �ڸ� ���ڼ�
        v = split_vec(s, cut); //��Ʈ�� ���Ϳ� split�� ��Ʈ������ ��ҷ� ����
        nums.push_back(cut);
        for (int elem = 0;; elem++) {
            if (elem == v.size() - 1) {
                break;
            }
            if (v[elem] == v[elem + 1]) {
                if (!same_previous) {
                    nums[idx]++;
                }
                //���� ���ڿ��� ������, ������ ���� �������� (ex. 2ab -> 3ab) ���ڿ� ���� ������ ����.
                same_previous++;
                //ex. 9a -> 10a : ���ڿ� ���� +1
                if (same_previous == 9 || same_previous == 99) {
                    nums[idx]++;
                }
            }
            else {
                if (v[elem].size() == v[elem + 1].size()) {
                    nums[idx] += cut;
                }
                //������ ���ڿ��� ��Ȯ�� �������� ���� ���.
                else {
                    nums[idx] += v[elem + 1].size();
                }
                same_previous = 0;
            }
        }
        same_previous = 0;
        idx++;
    }
    answer = *min_element(nums.begin(), nums.end());
    return answer;
}
void main() {
    printf("%d", solution("aaaaaaaaaaaaaaaaaaaaaaaa"));
}