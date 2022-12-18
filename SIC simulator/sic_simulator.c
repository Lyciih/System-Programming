#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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


void show(void * memory, char * begin, char * end, int * offset)
{
    if(atoi(begin) <= atoi(end)-1)
            {
                printf("%06x   ", atoi(begin));
                if(atoi(begin) % 16 != 0)
                {
                    for(int i = 0 ; i < (atoi(begin) % 16) ; i++)
                    {
                        printf("  ");
                        (*offset)++;
                        if(*offset == 4 || *offset == 8 || *offset == 12)
                        {
                            printf("   ");
                        }
                    }                  
                }

                for(int i = atoi(begin); i < atoi(end); i++)
                {
                    if(i % 16 == 0 && i != 0)
                    {
                        *offset = 0;
                        printf("\n");
                        printf("%06x   ", i);
                    }
                    if(*((char *)(memory+i)) == '.')
                    {
                        printf("..");
                    }
                    (*offset)++;
                    if(*offset == 4 || *offset == 8 || *offset == 12)
                    {
                        printf("   ");
                    }
                }
                *offset = 0;
                printf("\n");
            }
            else
            {
                printf("error %d\n", atoi(begin));
            }
}




int main(int argc, char *argv[]){
    char input[100];
    char temp1[100];
    char temp2[100];
    char buffer[100];
    int line_seg = 0;
    void * memory = NULL;
    if(argv[1] == 0)
    {
        printf("10000\n");
        memory = malloc(10000);
        memset(memory, '.', 10000);
    }
    else
    {
        printf("%d\n", atoi(argv[1]));
        memory = malloc(atoi(argv[1]));
        memset(memory, '.', atoi(argv[1]));
    }
    FILE * load_obj = NULL;


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
            show(memory, temp2, argv[1], &line_seg);
        }

        else if(strcmp(temp1, "load") == 0)
        {
            load_obj = fopen(temp2,"r");
            if(load_obj == NULL)
            {
                printf("error\n");
            }
            else
            {
                int size = 0;
                while(fgets(buffer, 100, load_obj))
                {
                    if(*buffer == 'H')
                    {
                        size = hex_to_dex(buffer+13);
                        memory = (char *)malloc(size);
                        memset(memory, '.', size);
                    }

                    /*


                    if(*buffer == 'T')
                    {
                        char location[6];
                        int location_dex = 0;
                        sscanf(buffer+1, "%6s", location);                        
                        location_dex = hex_to_dex(location);
                        printf("%s %d\n", location, location_dex);

                        for(int i = 0;i < strlen(buffer+9); i++)
                        {
                            memory[location_dex + i] = buffer[9+i];
                        }
                        printf("\n");


                        //strcat(memory, buffer+9);
                        
                    }
                    */
                }

                int line = 0;
                int space = 0;
                printf("%06x   ", 0);
                for(int i=0;i<size;i++)
                {
                    if(*((char *)(memory+i)) == '.')
                    {
                        printf("..");

                    }
                    //printf("%c", *(memory+i));                   
                    line++;
                    if(line == 4 || line == 8 || line == 12)
                    {
                        printf("   ");

                    }
                    if(line == 16)
                    {
                        line = 0;
                        printf("\n");
                        printf("%06x   ", i+1);
                    }
                }
                printf("\n");
                

                
                fclose(load_obj);
            }
        }
    }
}