#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    mtrace();
    char* str = malloc(13 * sizeof(char));
    free(str);
    muntrace();

    return 0;
}