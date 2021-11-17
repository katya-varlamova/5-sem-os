#include <stdio.h>
#include <cstdlib>
#define ERROR 1
int main(int argc, const char *argv[])
{
    if (argc < 2)
        return ERROR;
    int max = atoi(argv[1]), tmp;
    for (int i = 2; i < argc; i++)
        if ((tmp = atoi(argv[i])) > max)
            max = tmp;
    printf("max in array: %d\n", max);
    return 0;
}
