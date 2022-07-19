#include <bits/stdc++.h>
using namespace std;

int solution(string s)
{
    int dif = 1;
    vector<int> memo(s.size());
    int ans = 0;

    while (1)
    {
        if (dif % 2 == 0 && dif * 2 < s.size() + 1) break;
        else if (dif % 2 && dif * 2 < s.size()) break;

        for (int i = dif; ; i++)
        {
            if (dif % 2 == 0 && dif * 2 < s.size() + 1) break;
            else if (dif % 2 && dif * 2 < s.size()) break;

            if (dif == 1 || memo[i] == dif * 2 - 1)
            {
                // Â¦¼ö
                if (s[i - dif] == s[i + dif - 1] ||
                    s[i + dif] == s[i - dif + 1])
                {
                    memo[i] = dif * 2;
                    ans = max(ans, memo[i]);
                }
                // È¦¼ö
                if (s[i - dif] == s[i + dif])
                {
                    memo[i] = dif * 2 + 1;
                    ans = max(ans, memo[i]);
                }
            }

        }
        dif++;
    }

    return ans;
}

int main()
{
    solution("aa");

    return 0;
}