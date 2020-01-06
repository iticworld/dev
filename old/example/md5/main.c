#include <string.h>
#include <stdio.h>
#include <openssl/md5.h>

int main()
{
    unsigned char digest[16];
    const char * str = "The quick brown fox jumps over the lazy dog";
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, str, strlen(str));
    MD5_Final(digest, &ctx);
    for(int i = 0; i<16;i++)
    {
        printf("%02x", digest[i]);
    }
    printf("\n");
    return 0;
}
