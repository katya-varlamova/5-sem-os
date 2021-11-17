#include <vector>
int main(int argc, const char *argv[])
{
    std::vector<int> v;
    for (int i = 1; i < argc; i++)
        v.push_back(atoi(argv[i]));

    std::sort(v.begin(), v.end());

    printf("sorted array: ");
    for (int i = 0; i < v.size(); i++)
        printf("%d ", v[i]);
    printf("\n");
    return 0;
}