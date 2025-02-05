#include <stdio.h>

#define STRINGIZE(arg) #arg
const unsigned int ScopeEventHAL3Open = 1;

int main(int argc, char* argv[])
{
    printf("%u\n", ScopeEventHAL3Open);
    printf("%s\n", STRINGIZE(ScopeEventHAL3Open));

    return 0;
}