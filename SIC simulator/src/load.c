#include"simulator.h"

void load(char * target, void * memory, int * program_begin,  int * program_end, int * loaded)
{
    char buffer[100];
    FILE * load_obj = fopen(target,"r");
    if(load_obj == NULL)
    {
        printf("error\n");
    }
    else
    {
        *loaded = 1;
        char begin[20];
        int size = 0;
        while(fgets(buffer, 100, load_obj))
        {
            if(*buffer == 'H')
            {
                for(int i = 0 ; i < 6 ; i++)
                {
                    begin[i] = buffer[i + 7];
                }
                begin[6] = '\0';
                printf("%d ", hex_to_dex(begin));
                *program_begin = hex_to_dex(begin);
                        
                size = hex_to_dex(buffer+13);
                printf("%d \n", size);
                *program_end = *program_begin + size;
                        
            }

            if(*buffer == 'T')
            {
                for(int i = 0 ; i < 6 ; i++)
                {
                    begin[i] = buffer[i + 1];
                }
                begin[6] = '\0';

                printf("%X ", hex_to_dex(begin));
                int memory_count = hex_to_dex(begin);
                int state = 0;

                for(int i = 9 ; i < strlen(buffer) - 1 ; i++)
                {
                    if(state == 0)
                    {
                        *((uint8_t *)memory + memory_count) = (hex_to_dex_c(buffer[i]) << 4) ;
                        printf("%c", buffer[i]);
                        state = 1;
                    }
                    else if(state == 1)
                    {
                        *((uint8_t *)memory + memory_count) |= (hex_to_dex_c(buffer[i]) << 0) ;
                        memory_count++;
                        printf("%c", buffer[i]);
                        state = 0;
                    }
                }
                printf("\n");                       
            }
        }
        fclose(load_obj);
    }
}