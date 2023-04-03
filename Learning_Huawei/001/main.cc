// HJ1 字符串最后一个单词的长度
#include <iostream>
#include <string>
extern "C" {
#include <string.h>
}

// 题目明示不会以空格结尾
#if 0
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 5001;
    char buffer[MAX_SIZE] = {};
    std::string answer {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        size_t start_pos = str.find_first_not_of(' ');
        if (std::string::npos == start_pos)
            answer = str;
        else {
            str = str.substr(start_pos);
            size_t pos = str.find_last_of(' ');
            answer = str.substr(pos + 1);
        }
        // std::cout << answer << " " << answer.length() << std::endl;
        std::cout << answer.length() << std::endl;
        memset(buffer, 0, MAX_SIZE);
    }
    return 0;
}
#endif

#if 1
// 如果没有这句话呢？思考后，还是纯c思想更好做，第一个非' '到最后一个非' '
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 5001;
    char buffer[MAX_SIZE] = {};
    std::string answer {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        size_t start_pos = str.find_first_not_of(' ');
        size_t end_pos = str.find_last_not_of(' ');
        size_t pos = str.find_first_of(' ');
        if (std::string::npos == pos)
            answer = str;
        else if (std::string::npos == start_pos && std::string::npos != pos)
            answer = "";
        else {
            str = str.substr(start_pos, end_pos + 1 - start_pos);
            pos = str.find_last_of(' ');
            answer = str.substr(pos + 1);
        }
        // std::cout << answer << " " << answer.length() << std::endl;
        std::cout << answer.length() << std::endl;
        memset(buffer, 0, MAX_SIZE);
    }
    return 0;
}
#endif

#if 0
1、如何接收整行字符串
  cin >> 空格、回车截断
  cin.getline() 回车截断
  cin.get() 不截断
2、rfind find_last_of first_find_of的使用
3、substr的使用 注意第二个参数是字串长度 #46
#endif