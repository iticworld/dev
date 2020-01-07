/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 17.
 */

#include <novemberizing.hh>

using namespace novemberizing;

int main(int argc, char ** argv)
{
    if(argc == 2)
    {
        FILE * fp = fopen(argv[1], "r+b");
        if(fp)
        {
            bytes data;
            unsigned char buffer[4096];
            while(!feof(fp))
            {
                ssize_t n = fread(buffer, sizeof(unsigned char), 4096, fp);
                if(n > 0)
                {
                    data.append(buffer, (uint64) n);
                }
            }
            fclose(fp);
            char str[32];
            for(uint64 i = 0; i < data.size(); i++)
            {
                if(i % 16 == 0)
                {
                    printf("| %08X | ", (unsigned int) i);
                }
                byte c = data[i];
                printf("%02X ", c);
                str[i % 16] = (32 <= c && c<=126 ? c : '.');
                str[i % 16 + 1] = 0;
                if(i % 16 == 15)
                {
                    printf("| %s |\n", str);
                }
                else if(i + 1 == data.size())
                {
                    printf("%-*c| %-16s |\n", (int)(3 * (15 - (i % 16))), ' ', str);
                }
            }
        }
        else
        {
            printf("fail to open file: %d\n", errno);
        }
    }
    else
    {
        printf("novemberizing-hex \"path\"\n");
    }
    return 0;
}

