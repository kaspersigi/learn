#include <iostream>
#include <unordered_set>

// #define __MY_ANSWER__
#define __ANSWER_SLIDING_WINDOW__

//官方答案比我的好23倍，好好学习一下

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
#ifdef __MY_ANSWER__
        int max = 0;
        for (size_t i = 0; i < s.length(); i++) {
            unordered_set<char> hashtable;
            hashtable.insert(s[i]);
            int length = 1;
            for (size_t j = i + 1; j < s.length(); j++) {
                if (hashtable.end() != hashtable.find(s[j])) {
                    break;
                } else {
                    hashtable.insert(s[j]);
                }
                length = hashtable.size();
            }
            hashtable.clear();
            if (length > max)
                max = length;
        }
        return max;
#endif

#ifdef __ANSWER_SLIDING_WINDOW__
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> occ;
        int n = s.size();
        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int rk = -1, ans = 0;
        // 枚举左指针的位置，初始值隐性地表示为 -1
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                // 左指针向右移动一格，移除一个字符
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) {
                // 不断地移动右指针
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // 第 i 到 rk 个字符是一个极长的无重复字符子串
            ans = max(ans, rk - i + 1);
        }
        return ans;
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    auto result = s.lengthOfLongestSubstring("au");
    cout << result << endl;

    return 0;
}