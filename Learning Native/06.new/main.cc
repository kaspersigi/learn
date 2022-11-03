extern "C" {
#include <string.h>
#include <unistd.h>
}

auto main(int argc, char* argv[]) -> int
{
    const char* str = "Hello World";
    write(1, "begin", 5);
    char* my_str = new char[12];
    write(1, "end", 3);
    memcpy(my_str, str, 12);
    delete[] my_str;

    return 0;
}