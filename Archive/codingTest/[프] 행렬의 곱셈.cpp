#include <string>
#include <vector>
using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer(arr1.size(), vector<int>(arr2[0].size(), 0));    //첫 행렬의 행, 두번째 행렬의 열 길이만큼 할당

    for (int i = 0; i != arr1.size(); i++) {
        for (int j = 0; j != arr2[0].size(); j++) {
            for (int k = 0; k != arr2.size(); k++) {
                answer[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    return answer;
}
void main() {
    solution({ {1, 2, 3, 4}, {4, 5, 6, 7} }, { {1, 4}, {2, 5}, {3, 6}, {2, 4} });
}