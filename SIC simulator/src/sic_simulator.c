#include"simulator.h"



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
        memory = malloc(hex_to_dex("5000"));
        memset(memory, '.', hex_to_dex("5000"));
        system_size = hex_to_dex("5000");
        printf("system memory from 0x0 ~ 0x%X\n", system_size);
    }
    else
    {
        system_size = hex_to_dex(argv[1]);
        printf("system memory from 0x0 ~ 0x%X\n", system_size);
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
                load(temp2, memory, &program_begin, &program_end, &loaded);
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
            printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu.A, cpu.X, cpu.L, cpu.PC, cpu.SW);
        }

        else if(strcmp(temp1, "run") == 0)
        {
            run(&program_begin, &program_end, memory, &cpu);
            temp2[0] = '0';
            temp2[1] = '\0';
            temp1[0] = '\0';
            printf("A : %06X  X : %06X  L : %06X  PC : %06X  SW : %06X\n\n", cpu.A, cpu.X, cpu.L, cpu.PC, cpu.SW);
        }

        else
        {
            printf("command not find\n");
        }
    }
}


