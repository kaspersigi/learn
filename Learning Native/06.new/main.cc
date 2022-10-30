#include <iostream>

extern "C" {
#include <mcheck.h>
}

int main(int argc, char* argv[])
{
    mtrace();
    char* str = new char[13];
    delete[] str;
    muntrace();

    return 0;
}