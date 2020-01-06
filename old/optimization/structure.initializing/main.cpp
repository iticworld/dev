#include <stdio.h>

struct hello
{
    int i;
    int v:2;
    int c;
    char buffer[1024];
};

int main(int argc, char ** argv)
{
    struct hello o = {};
    printf("%s\n", o.buffer);
    return 0;
}
