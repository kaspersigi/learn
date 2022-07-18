#include <iostream>

using namespace std;

// #define __MY_ANSWER__
#define __OFFICIAL_ANSWER__

class Solution {
public:
    int reverse(int x)
    {
#ifdef __MY_ANSWER__
        if (x == 0)
            return 0;
        long num = abs(x);
        int sign = num / x;
        string str = to_string(num);
        std::reverse(str.begin(), str.end());
        num = atol(str.c_str()) * sign;
        if (num < INT32_MIN || num > INT32_MAX)
            return 0;
        else
            return num;
#endif

#ifdef __OFFICIAL_ANSWER__
        int rev = 0;
        while (x != 0) {
            if (rev < INT32_MIN / 10 || rev > INT32_MAX / 10) {
                return 0;
            }
            int digit = x % 10;
            x /= 10;
            rev = rev * 10 + digit;
        }
        return rev;
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    int x = 123;
    auto result = s.reverse(x);
    cout << result << endl;
    // cout << INT32_MIN << endl;
    // cout << INT32_MAX << endl;
    return 0;
}