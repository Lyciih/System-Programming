#include"simulator.h"


void show(void * memory, char * begin, char * end)
{

    int offset = 0;
    if(hex_to_dex(begin) <= hex_to_dex(end)-1)
    {               
        if(hex_to_dex(begin) % 16 != 0)
        {
            printf("%04x   ", hex_to_dex(begin));
            for(int i = 0 ; i < (hex_to_dex(begin) % 16) ; i++)
            {
                printf("  ");
                offset++;
                if(offset == 4 || offset == 8 || offset == 12)
                {
                    printf("   ");
                }
            }                  
        }

        for(int i = hex_to_dex(begin); i < hex_to_dex(end); i++)
        {
            if(i % 16 == 0)
            {
                offset = 0;
                printf("%04x   ", i);
            }

            if(*((char *)(memory+i)) == '.')
            {
                printf("..");
            }
            else
            {
                printf("%02X", *((uint8_t *)(memory+i)));
            }

            offset++;

            if(offset == 4 || offset == 8 || offset == 12)
            {
                printf("   ");
            }

            if(offset == 16)
            {
                printf("\n");
            }
        }
        offset = 0;
        printf("\n");
    }
    else
    {
        printf("error %d\n", hex_to_dex(begin));
    }
}