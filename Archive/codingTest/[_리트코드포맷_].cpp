#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<int> height;
        stack<int> st;
        int ans = 0;

        for (int y = 0; y < matrix.size(); y++)
        {
            for (int x = 0; x < matrix[y].size(); x++)
            {
                if (matrix[y][x] == '1')
                {
                    height[x]++;
                }

                while (!st.empty() && height[x] < height[st.top()])
                {
                    int h = height[st.top()];
                    st.pop();
                    if (!st.empty())
                    {
                        int w = x - 1 - st.top();
                        ans = max(ans, h * w);
                    }
                }
                st.push(x);
            }
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<vector<char>> v = { {'1', '0'}, {'1', '0'}, {'1', '0'} };
    cout << s.maximalRectangle(v);
}