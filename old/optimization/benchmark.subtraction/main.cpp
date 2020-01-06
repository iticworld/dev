#include <cstdlib>
#include <ctime>
#include <cstdio>

int main() {
    srand((unsigned int) time(nullptr));
    int i = rand();

    i -= 1;
    printf("%d\n", i);
    i--;
    printf("%d\n", i);
    return 0;
}