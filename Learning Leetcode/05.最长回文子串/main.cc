#include <iostream>
#include <vector>

#define __MY_ANSWER__
//类似答案中的Manacher算法

using namespace std;

class Solution {
public:
    string longestPalindrome(string s)
    {
#ifdef __MY_ANSWER__
        size_t head = 0, middle = 0, tail = 0, length = 0, maxlength = 1, maxhead = 0, maxtail = 0;
        while (middle < s.length()) {
            if (middle == 0) {
                length = 1;
            } else {
                length = 1;
                head = middle - 1;
                tail = middle + 1;
                while (head >= 0 && tail < s.length()) {
                    if (s[head] == s[tail]) {
                        length = length + 2;
                        head--;
                        tail++;
                    } else
                        break;
                }
            }
            if (length > maxlength) {
                maxlength = length;
                maxhead = head + 1;
                maxtail = tail - 1;
            }
            middle++;
        }

        head = 0, middle = 0, tail = 0, length = 0;
        while (middle < s.length()) {
            if (middle == 0) {
                length = 1;
            } else {
                length = 0;
                head = middle - 1;
                tail = middle;
                while (head >= 0 && tail < s.length()) {
                    if (s[head] == s[tail]) {
                        length = length + 2;
                        head--;
                        tail++;
                    } else
                        break;
                }
            }
            if (length > maxlength) {
                maxlength = length;
                maxhead = head + 1;
                maxtail = tail - 1;
            }
            middle++;
        }
        return s.substr(maxhead, maxlength);
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    auto str = "a";
    auto result = s.longestPalindrome(str);
    cout << result << endl;
    return 0;
}