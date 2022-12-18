#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uint8_t;

//將指數乘開的函數
int exponent_Int(const int base, int n)
{
    int p = base;
    if(n == 0)
    {
        p = 1;
    }
    else
    {
        for (int i = 1; i < n; i++)
        {
            p *= base;
        }
    }
    return p;
}


//將讀取的字串視為16進位，並轉換為10進位數字的函數
int hex_to_dex(char *hex)
{
    char *char_temp = (char *)malloc(strlen(hex));
    strcpy(char_temp, hex);
    char_temp = strtok(char_temp, "\n");
    char temp[2];
    int total = 0;
    int count = strlen(char_temp);

    while(count-- && count >= 0)
    {
        sprintf(temp, "%c", *char_temp);
        if(strcmp(temp, "A") == 0){total += exponent_Int(16, count)*10;}
        if(strcmp(temp, "B") == 0){total += exponent_Int(16, count)*11;}
        if(strcmp(temp, "C") == 0){total += exponent_Int(16, count)*12;}
        if(strcmp(temp, "D") == 0){total += exponent_Int(16, count)*13;}
        if(strcmp(temp, "E") == 0){total += exponent_Int(16, count)*14;}
        if(strcmp(temp, "F") == 0){total += exponent_Int(16, count)*15;}
        else{total += exponent_Int(16, count)*atoi(temp);}    
        char_temp++;    
    }

    return total;
}

int hex_to_dex_c(char hex)
{
    if(hex == 'A'){return 10;}
    if(hex == 'B'){return 11;}
    if(hex == 'C'){return 12;}
    if(hex == 'D'){return 13;}
    if(hex == 'E'){return 14;}
    if(hex == 'F'){return 15;}
    if(hex == '9'){return 9;}
    if(hex == '8'){return 8;}
    if(hex == '7'){return 7;}
    if(hex == '6'){return 6;}
    if(hex == '5'){return 5;}
    if(hex == '4'){return 4;}
    if(hex == '3'){return 3;}
    if(hex == '2'){return 2;}
    if(hex == '1'){return 1;}
    if(hex == '0'){return 0;}
    return 0;
}




void show(void * memory, char * begin, char * end)
{

    int offset = 0;
    if(hex_to_dex(begin) <= hex_to_dex(end)-1)
    {               
        if(hex_to_dex(begin) % 16 != 0)
        {
            printf("%06x   ", hex_to_dex(begin));
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
                printf("%06x   ", i);
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



void load(char * target, void * memory)
{
    char buffer[100];
    FILE * load_obj = fopen(target,"r");
    if(load_obj == NULL)
    {
        printf("error\n");
    }
    else
    {
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
                        
                size = hex_to_dex(buffer+13);
                printf("%d \n", size);
                        
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
                        //*((char *)memory + 1) = 10 << 0;
                        printf("%c", buffer[i]);
                        state = 1;
                    }
                    else if(state == 1)
                    {
                        *((uint8_t *)memory + memory_count) |= (hex_to_dex_c(buffer[i]) << 0) ;
                        //*(char *)memory = 10 << 0;
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




int main(int argc, char *argv[]){
    char input[100];
    char temp1[100];
    char temp2[100];
    void * memory = NULL;
    if(argv[1] == 0)
    {
        printf("10000\n");
        memory = malloc(hex_to_dex("10000"));
        memset(memory, '.', hex_to_dex("10000"));
    }
    else
    {
        printf("%d\n",  hex_to_dex(argv[1]));
        memory = malloc(hex_to_dex(argv[1]));
        memset(memory, '.',  hex_to_dex(argv[1]));
    }


    while(1)
    {
        printf(">>> ");
        gets(input);
        sscanf(input, "%s %s", temp1, temp2);

        if(strcmp(input, "exit") == 0)
        {
            free(memory);
            break;
        }

        else if(strcmp(temp1, "show") == 0)
        {
            show(memory, temp2, argv[1]);
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
        }

        else if(strcmp(temp1, "load") == 0)
        {
            load(temp2, memory);
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
            //show(memory, temp2, argv[1]);
        }
    }
}
