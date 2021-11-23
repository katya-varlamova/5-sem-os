#include <iostream>
#define ERROR 1
void sort(int *data, int length, int (*cmp)(int, int))
{
    bool fl;
    for (size_t j = 1; j < length; j++) {
        fl = false;
        for (size_t i = 0; i < length - j; i++) {
            if (cmp(data[i], data[i + 1]) > 0) {
                std::swap(data[i], data[i + 1]);
                fl = true;
            }
        }
        if (!fl)
            break;
    }
    return;
}
int compare_int(int f, int s)
{
    return f - s;
}
int main(int argc, const char *argv[])
{
    if (argc - 1 <= 0)
        return ERROR;
    int *a = (int *)malloc((argc - 1) * sizeof(int));
    if (a == NULL)
        return ERROR;
    for (int i = 1; i < argc; i++)
        a[i - 1] = atoi(argv[i]);

    sort(a, argc - 1, compare_int);

    printf("sorted array: ");
    for (int i = 0; i < argc - 1; i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);

    return 0;
}