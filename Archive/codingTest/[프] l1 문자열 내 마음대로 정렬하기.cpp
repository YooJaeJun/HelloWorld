#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> solution(vector<string> strings, int n) {
    sort(strings.begin(), strings.end(), [n](const auto& str1, const auto& str2) {
        if (str1[n] == str2[n]) return str1 <= str2;
        return str1[n] < str2[n];
        });
    return strings;
}

/*
vector<string> solution(vector<string> strings, int n) {
    for (int i = 0; i != strings.size(); i++) {
        for (int j = i + 1; j != strings.size(); j++) {
            if (strings[i][n] > strings[j][n]) {
                swap(strings[i], strings[j]);
            }
            else if (strings[i][n] == strings[j][n]) {
                int size = min(strings[i].size(), strings[j].size());
                for (int k = 0; k != size; k++) {
                    if (strings[i] > strings[j]) {
                        swap(strings[i], strings[j]);
                    }
                }
            }
        }
    }
    return strings;
}
*/
