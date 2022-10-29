#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char* str = malloc(13 * sizeof(char));
    free(str);

    return 0;
}