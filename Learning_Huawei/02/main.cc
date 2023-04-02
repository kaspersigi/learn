// HJ2 计算某字符出现次数
#include <iostream>
#include <unordered_map>

// 题目明示最后一个字符不是空格
#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr int MAX_SIZE = 1001;
    char buffer[MAX_SIZE] = {};
    char ch[2] = {};
    size_t answer = {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::cin.getline(ch, 2);
        std::unordered_map<char, size_t> hash {};
        for (int i = 0; buffer[i] != '\0' && i < MAX_SIZE; i++) {
            char temp = buffer[i];
            if ('a' <= temp && temp <= 'z')
                temp -= 'a' - 'A';
            auto it = hash.find(temp);
            if (it == hash.end())
                hash.insert(std::pair(temp, 1));
            else
                it->second++;
        }
        char temp = ch[0];
        if ('a' <= temp && temp <= 'z')
            temp -= 'a' - 'A';
        auto it = hash.find(temp);
        if (it == hash.end())
            answer = 0;
        else
            answer = it->second;
        std::cout << answer << std::endl;
    }
    return 0;
}
#endif

#if 0
教训：MAX_SIZE设置+1
#endif