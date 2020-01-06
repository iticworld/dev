#include <novemberizing.h>

int main(int argc, char ** argv)
{
    printf("nint8: %ld\n", sizeof(nint8));
    printf("nint16: %ld\n", sizeof(nint16));
    printf("nint32: %ld\n", sizeof(nint32));
    printf("nint64: %ld\n", sizeof(nint64));
    printf("nuint8: %ld\n", sizeof(nuint8));
    printf("nuint16: %ld\n", sizeof(nuint16));
    printf("nuint32: %ld\n", sizeof(nuint32));
    printf("nuint64: %ld\n", sizeof(nuint64));
    printf("nchar: %ld\n", sizeof(nchar));
    printf("npointer: %ld\n", sizeof(npointer));

    return 0;
}

