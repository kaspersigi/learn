#include <iostream>
#include <numeric>

using namespace std;

#define __MY_ANSWER__
// #define __OFFICIAL_ANSWER__

class Solution {
public:
    int myAtoi(string s)
    {
#ifdef __MY_ANSWER__
        auto pos_begin = s.find_first_not_of(' ');
        auto pos_end = s.find_last_not_of(' ');
        // cout << pos_begin << endl;
        // cout << pos_end << endl;
        auto str = s.substr(pos_begin, pos_end - pos_begin + 1);
        // cout << str;
        char head = str[0];
        int sign = 1;
        if (head == '-')
            sign = -1;
        int result = 1;
        return result * sign;
#endif

#ifdef __OFFICIAL_ANSWER__
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    string str = "   42  ";
    auto result = s.myAtoi(str);
    cout << result << endl;
    return 0;
}