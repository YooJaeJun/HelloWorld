#include <bits/stdc++.h>
using namespace std;

int solution(string my_string) {
    vector<int> nums;
    string oper;
    string temp;
    for (auto& elem : my_string)
    {
        if (elem == ' ')
        {
            if (temp == "+" || temp == "-")
            {
                oper += temp;
            }
            else
            {
                nums.push_back(stoi(temp));
            }
            temp = "";
        }
        else
        {
            temp += elem;
        }
    }

    int ans = nums[0];
    for (int i = 0; i < oper.size(); i++)
    {
        if (oper[i] == '+') ans += nums[i + 1];
        else ans -= nums[i + 1];
    }
    return ans;
}

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solution("3 + 4");
    return 0;
}