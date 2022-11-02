#include <bits/stdc++.h>
using namespace std;

int solution(int chicken) {
    map<int, int> dic;
    dic[1] = 1;
    dic[2] = 7;
    dic[5] = 4;
    pair<int, int> i = *max_element(dic.begin(), dic.end());
    return i.first;
}

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solution(1999);
    return 0;
}