#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uint8_t;


typedef struct cpu_t{
    unsigned int A : 24;
    unsigned int X : 24;
    unsigned int L : 24;
    unsigned int PC : 24;
    unsigned int SW : 24;
}cpu_t;

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
    char * char_temp = (char *)malloc(strlen(hex));
    char * temp_begin = char_temp;
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
    free(temp_begin);
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



void load(char * target, void * memory, int * program_begin,  int * program_end)
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


void run(int * program_begin, int * program_end, void * memory, cpu_t * cpu)
{
    printf("%X %X\n", *program_begin, *program_end);
    cpu->PC = *program_begin;
    int temp = 0;
    int temp2 = 0;
    int temp3 = 0;
    int x_mod = 0;
    cpu->L = *program_end;
    
    while(cpu->PC < *program_end)
    {
        x_mod = 0;
        temp = 0;
        temp2 = 0;
        temp3 = 0;
        if(*((uint8_t *)memory + cpu->PC + 1) >= 128)
        {
            x_mod = 1;
        }
        
        switch(*((uint8_t *)memory + cpu->PC))
        {
            case 24:
                //printf("ADD\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = *((uint8_t *)memory + temp + 2);
                cpu->A += temp2;

                temp2 = *((uint8_t *)memory + temp + 1);
                temp2 = temp2 << 8;
                cpu->A += temp2;

                temp2 = *((uint8_t *)memory + temp);
                temp2 = temp2 << 16;
                cpu->A += temp2;


                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 52:
                //printf("JGT\n");
                cpu->PC += 3;
                break;

            case 0:
                printf("LDA\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(*((uint8_t *)memory + temp) == '.')
                {
                    cpu->A = 0;
                }
                else
                {
                    cpu->A = *((uint8_t *)memory + temp);
                }
                
                cpu->A = cpu->A << 8;

                if(*((uint8_t *)memory + temp + 1) == '.')
                {
                    cpu->A |= 0;
                }
                else
                {
                    cpu->A |= *((uint8_t *)memory + temp + 1);
                }
                
                cpu->A = cpu->A << 8;

                if(*((uint8_t *)memory + temp + 2) == '.')
                {
                    cpu->A |= 0;
                }
                else
                {
                    cpu->A |= *((uint8_t *)memory + temp + 2);
                }



                cpu->PC += 3;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 4:
                //printf("LDX\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(*((uint8_t *)memory + temp) == '.')
                {
                    cpu->X = 0;
                }
                else
                {
                    cpu->X = *((uint8_t *)memory + temp);
                }
                
                cpu->X = cpu->X << 8;

                if(*((uint8_t *)memory + temp + 1) == '.')
                {
                    cpu->X |= 0;
                }
                else
                {
                    cpu->X |= *((uint8_t *)memory + temp + 1);
                }
                
                cpu->X = cpu->X << 8;

                if(*((uint8_t *)memory + temp + 2) == '.')
                {
                    cpu->X |= 0;
                }
                else
                {
                    cpu->X |= *((uint8_t *)memory + temp + 2);
                }


                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 216:
                //printf("RD\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                cpu->A = *((uint8_t *)memory + temp);

                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 220:
                //printf("WD\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                *((uint8_t *)memory + temp) = cpu->A;

                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 84:
                //printf("STCH\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(x_mod == 1)
                {
                    temp = temp ^ (1 << 15);
                    *((uint8_t *)memory + temp + cpu->X) = cpu->A;
                }
                else
                {
                    *((uint8_t *)memory + temp) = cpu->A;
                }
                
                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 16:
                printf("STX\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp  << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = cpu->X;

                *((uint8_t *)memory + temp + 2) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp + 1) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp) = temp2;
                printf("%X\n", temp2);
                printf("%02X%02X%02X\n", *((uint8_t *)memory + temp), *((uint8_t *)memory + temp + 1), *((uint8_t *)memory + temp + 2));


                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);

                break;

            case 12:
                printf("STA\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp  << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = cpu->A;

                *((uint8_t *)memory + temp + 2) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp + 1) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp) = temp2;
                printf("%X\n", temp2);
                printf("%02X%02X%02X\n", *((uint8_t *)memory + temp), *((uint8_t *)memory + temp + 1), *((uint8_t *)memory + temp + 2));


                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);

                break;

            case 44:
                //printf("TIX\n");
                cpu->X++;

                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = *((uint8_t *)memory + temp);
                temp2 = temp2 << 8;
                temp2 |= *((uint8_t *)memory + temp + 1);
                temp2 = temp2 << 8;
                temp2 |= *((uint8_t *)memory + temp + 2);


                if(cpu->X == temp2)
                {
                    cpu->SW = '=';
                }
                else if(cpu->X < temp2)
                {
                    cpu->SW = '<';
                }
                else
                {
                    cpu->SW = '>';
                }

                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 64:
                printf("AND\n");
                cpu->PC += 3;
                break;

            case 60:
                printf("J\n");
                temp = cpu->PC;
                cpu->PC = *((uint8_t *)memory + temp + 1);
                cpu->PC = cpu->PC  << 8;
                cpu->PC |= *((uint8_t *)memory + temp + 2);
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 56:
                //printf("JLT\n");
                temp = cpu->PC;
                if(cpu->SW == '<')
                {
                    cpu->PC = *((uint8_t *)memory + temp + 1);
                    cpu->PC = cpu->PC  << 8;
                    cpu->PC |= *((uint8_t *)memory + temp + 2);

                }
                else
                {
                    cpu->PC += 3;
                }
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 80:
                //printf("LDCH\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(x_mod == 1)
                {
                    temp = temp ^ (1 << 15);
                    cpu->A = *((uint8_t *)memory + temp + cpu->X);
                }
                else
                {
                    cpu->A = *((uint8_t *)memory + temp);
                }
                
                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 32:
                printf("MUL\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp3 = cpu->A;
                cpu->A = 0;

                temp2 = *((uint8_t *)memory + temp + 2);
                cpu->A += temp3 * temp2;

                temp2 = *((uint8_t *)memory + temp + 1);
                temp2 = temp2 << 8;
                cpu->A += temp3 * temp2;

                temp2 = *((uint8_t *)memory + temp);
                temp2 = temp2 << 16;
                cpu->A += temp3 * temp2;


                cpu->PC += 3;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 76:
                printf("RSUB\n");
                cpu->PC = cpu->L;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 20:
                printf("STL\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp  << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = cpu->L;

                *((uint8_t *)memory + temp + 2) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp + 1) = temp2;
                printf("%X\n", temp2);
                temp2 = temp2 >> 8;
                *((uint8_t *)memory + temp) = temp2;
                printf("%X\n", temp2);
                printf("%02X%02X%02X\n", *((uint8_t *)memory + temp), *((uint8_t *)memory + temp + 1), *((uint8_t *)memory + temp + 2));


                cpu->PC += 3;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 28:
                printf("SUB\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = *((uint8_t *)memory + temp);
                temp2 = temp2 << 8;

                temp2 = *((uint8_t *)memory + temp + 1);
                temp2 = temp2 << 8;

                temp2 = *((uint8_t *)memory + temp + 2);

                cpu->A = cpu->A - temp2;


                cpu->PC += 3;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            

            case 40:
                //printf("COMP\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                temp2 = *((uint8_t *)memory + temp);
                temp2 = temp2 << 8;
                temp2 |= *((uint8_t *)memory + temp + 1);
                temp2 = temp2 << 8;
                temp2 |= *((uint8_t *)memory + temp + 2);

                if(cpu->A == temp2)
                {
                    cpu->SW = '=';
                }
                else if(cpu->A < temp2)
                {
                    cpu->SW = '<';
                }
                else
                {
                    cpu->SW = '>';
                }

                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 48:
                //printf("JEQ\n");
                temp = cpu->PC;
                if(cpu->SW == '=')
                {
                    cpu->PC = *((uint8_t *)memory + temp + 1);
                    cpu->PC = cpu->PC  << 8;
                    cpu->PC |= *((uint8_t *)memory + temp + 2);

                }
                else
                {
                    cpu->PC += 3;
                }
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);            
                break;

            case 72:
                printf("JSUB\n");
                temp = cpu->PC;
                cpu->L = cpu->PC + 3;
                cpu->PC = *((uint8_t *)memory + temp + 1);
                cpu->PC = cpu->PC  << 8;
                cpu->PC |= *((uint8_t *)memory + temp + 2);
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 8:
                printf("LDL\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(*((uint8_t *)memory + temp) == '.')
                {
                    cpu->L = 0;
                }
                else
                {
                    cpu->L = *((uint8_t *)memory + temp);
                }
                
                cpu->L = cpu->L << 8;

                if(*((uint8_t *)memory + temp + 1) == '.')
                {
                    cpu->L |= 0;
                }
                else
                {
                    cpu->L |= *((uint8_t *)memory + temp + 1);
                }
                
                cpu->L = cpu->L << 8;

                if(*((uint8_t *)memory + temp + 2) == '.')
                {
                    cpu->L |= 0;
                }
                else
                {
                    cpu->L |= *((uint8_t *)memory + temp + 2);
                }



                cpu->PC += 3;
                printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            case 68:
                printf("OR\n");
                cpu->PC += 3;
                break;

            case 232:
                printf("STSW\n");
                cpu->PC += 3;
                break;

            case 224:
                //printf("TD\n");
                temp = *((uint8_t *)memory + cpu->PC + 1);
                temp = temp << 8;
                temp |= *((uint8_t *)memory + cpu->PC + 2);

                if(*((uint8_t *)memory + temp) == '.')
                {
                    cpu->SW = '=';                    
                }
                else
                {
                    cpu->SW = '<';
                }

                cpu->PC += 3;
                //printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu->A, cpu->X, cpu->L, cpu->PC, cpu->SW);
                break;

            //default:
                //cpu->PC += 3;
                //break;
        }
    }

    printf("\n");
}





int main(int argc, char *argv[]){
    char input[100];
    char temp1[100];
    char temp2[100];
    void * memory = NULL;
    int system_size = 0;
    int loaded = 0;
    int program_begin = 0; 
    int program_end = 0; 
    if(argv[1] == 0)
    {
        printf("10000\n");
        memory = malloc(hex_to_dex("10000"));
        memset(memory, '.', hex_to_dex("10000"));
        system_size = 10000;
    }
    else
    {
        system_size = hex_to_dex(argv[1]);
        printf("%d\n",  system_size);
        memory = malloc(system_size);
        memset(memory, '.',  system_size);
        
    }

    temp2[0] = '0';
    temp2[1] = '\0';
    temp1[0] = '\0';

    //CPU
    cpu_t cpu;
    cpu.A = 0;
    cpu.X = 0;
    cpu.L = 0;
    cpu.PC = 0;
    cpu.SW = 0;




    while(1)
    {
        //printf("%06X %06X %06X %06X %06X\n", cpu.A, cpu.X, cpu.L, cpu.PC, cpu.SW);
        printf(">>> ");
        fgets(input, 100, stdin);
        sscanf(input, "%s %s", temp1, temp2);

        if(strcmp(temp1, "exit") == 0)
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
            if(loaded == 0)
            {
                load(temp2, memory, &program_begin, &program_end);
                loaded = 1;
            }
            else
            {
                printf("error , an object code has been load\n");
            }
            
            
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
        }

        else if(strcmp(temp1, "unload") == 0)
        {
            memset(memory, '.',  system_size);
            cpu.A = 0;
            cpu.X = 0;
            cpu.L = 0;
            cpu.PC = 0;
            cpu.SW = 0;
            loaded = 0;
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
        }

        else if(strcmp(temp1, "run") == 0)
        {
            run(&program_begin, &program_end, memory, &cpu);
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
        }
    }
}


