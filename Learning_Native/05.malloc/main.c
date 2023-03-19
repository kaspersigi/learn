#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// sizeof(Chunk) == 4;
typedef struct Chunk {
    int length;
    char data[0];
} Chunk;

int main(int argc, char* argv[])
{
    const char* str = "Hello World";
    write(1, "begin", 5);
    Chunk* my_chunk = malloc(sizeof(Chunk) + 12);
    write(1, "end", 3);
    my_chunk->length = 12;
    memcpy(my_chunk->data, str, 12);
    free(my_chunk);

    return 0;
}