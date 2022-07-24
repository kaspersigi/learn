#include <iostream>
#include <vector>

#define __MY_ANSWER__
// #define __SORT_BY_ROW__
// #define __VISIT_BY_ROW__

using namespace std;

class Solution {
public:
    string convert(string s, int numRows)
    {
#ifdef __MY_ANSWER__
        if (numRows == 1)
            return s;
        char array[1000][1000] = {};
        string str, result;
        for (size_t i = 0; i < s.length(); i++) {
            if (i % (numRows - 1) == 0 && i != 0) {
                str += '#';
            }
            str += s[i];
        }
        for (size_t row = 0, column = 0, i = 0; i < str.length(); i++) {
            row = i % numRows;
            if (row == 0 && i != 0) {
                column++;
            }
            if (column % 2 == 0)
                array[row][column] = str[i];
            else
                array[numRows - row - 1][column] = str[i];
        }
        // for (int i = 0; i < numRows; i++) {
        //     for (int j = 0; array[i][j] != '\0'; j++)
        //         cout << array[i][j];
        //     cout << endl;
        // }
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; array[i][j] != '\0'; j++)
                if (array[i][j] != '#')
                    result += array[i][j];
        }
        return result;
#endif

#ifdef __SORT_BY_ROW__
        if (numRows == 1)
            return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1)
                goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (string row : rows)
            ret += row;
        return ret;
#endif

#ifdef __VISIT_BY_ROW__
        if (numRows == 1)
            return s;

        string ret;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j + i < n; j += cycleLen) {
                ret += s[j + i];
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                    ret += s[j + cycleLen - i];
            }
        }
        return ret;
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    auto str = "PAYPALISHIRING";
    auto rows = 4;
    auto result = s.convert(str, rows);
    cout << result << endl;
    return 0;
}