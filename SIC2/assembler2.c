#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linked_list.h"


typedef struct opcode{
    char *command;
    int code;
}opcode;


opcode sic[26];

typedef struct label{
	char *label_name;
    int addres;
	llNode_t node;
}label;


typedef struct sic24_t{
    unsigned int addres : 16;
    unsigned int opcode : 8; 
    }sic24_t;





int printf_all_list(llNode_t *head)
{
	llNode_t *current = head;
	while(current->next != NULL )
	{
		current = current->next;
		printf("%-8s " , return_to_user_struct_pointer(label, node, current)->label_name);
        printf("%X\n" , return_to_user_struct_pointer(label, node, current)->addres);
	}
	printf("end\n");
    return 0;
}




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




int main(int argc, char *argv[])
{
    sic[0].command = "ADD";
        sic[0].code = 24;

        sic[1].command = "DIV";
        sic[1].code = 36;

        sic[2].command = "JGT";
        sic[2].code = 52;

        sic[3].command = "LDA";
        sic[3].code = 0;

        sic[4].command = "LDX";
        sic[4].code = 4;

        sic[5].command = "RD";
        sic[5].code = 216;

        sic[6].command = "STCH";
        sic[6].code = 84;

        sic[7].command = "STX";
        sic[7].code = 16;

        sic[8].command = "TIX";
        sic[8].code = 44;

        sic[9].command = "AND";
        sic[9].code = 64;

        sic[10].command = "J";
        sic[10].code = 60;

        sic[11].command = "JLT";
        sic[11].code = 56;

        sic[12].command = "LDCH";
        sic[12].code = 80;

        sic[13].command = "MUL";
        sic[13].code = 32;

        sic[14].command = "RSUB";
        sic[14].code = 76;

        sic[15].command = "STL";
        sic[15].code = 20;

        sic[16].command = "SUB";
        sic[16].code = 28;

        sic[17].command = "WD";
        sic[17].code = 220;

        sic[18].command = "COMP";
        sic[18].code = 40;

        sic[19].command = "JEQ";
        sic[19].code = 48;

        sic[20].command = "JSUB";
        sic[20].code = 72;

        sic[21].command = "LDL";
        sic[21].code = 8;

        sic[22].command = "OR";
        sic[22].code = 68;

        sic[23].command = "STA";
        sic[23].code = 12;

        sic[24].command = "STSW";
        sic[24].code = 232;
        
        sic[25].command = "TD";
        sic[25].code = 224;

//*******************************   第一階段 檔案處理    *********************************************//


    for (int i = 1; i < argc; i++) 
    {  

        FILE *ass = fopen(argv[i],"r");
        printf("[%d] [source] %s\n", i, argv[i]);
        char *obj_file_name = strtok(argv[i], ".");
        char *obj= ".o";    
        strcat(obj_file_name, obj);
        FILE *obj_file = fopen(obj_file_name,"w");
        printf("[%d] [target] %s\n\n", i, obj_file_name);

        char buffer[50];
        char obj_temp[100];
        char obj_cat_temp[60];
        char record_head_temp[50];
        char temp1[50];
        char temp2[50];
        char temp3[50];
        char temp4[50];
        char temp5[50];
        int code_address = 0;
        llNode_t *label_list = LL_init();
        llNode_t *label_list_temp;
        label *new = NULL;
        char program_name[10];
        int START_address = 0;
        int END_address = 0;
        sic24_t obj_code;
        char *BYTE_temp;
        int arg_get = 0;
        int T_count = 0;
        int T_start_count = 0;



        while(fgets(buffer, 50, ass))
        {   
            
            memset(temp1, 0, 50);
            memset(temp2, 0, 50);
            memset(temp3, 0, 50);
            memset(obj_cat_temp, 0, 50);
            

            sscanf(buffer, "%s %s %s", temp1, temp2, temp3);
            if(strcmp(temp1, ".") != 0 )
            {
                if(strcmp(temp2, "START") != 0)
                {
                    if(strcmp(temp1, "END") != 0)
                    {
                        
                        for(int i = 0; i < 26; i++)
                        {
                            if(strcmp(temp1, sic[i].command) == 0)
                            {
                                code_address+=3;
                            } 
                        }

                        for(int i = 0; i < 26; i++)
                        {
                            if(strcmp(temp2, sic[i].command) == 0)
                            {
                                new = malloc(sizeof(label));
                                new->label_name = malloc(strlen(temp1));
                                strcpy(new->label_name, temp1);
                                new->addres = code_address;
                                LL_add_tail(&new->node, label_list);

                                //printf("%06X    %s\n", code_address, temp1);
                                code_address+=3;
                            } 
                        }

                        if(strcmp(temp2, "RESB") == 0)
                        {
                            //printf("%06X    %s\n", code_address, temp1);
                            

                            new = malloc(sizeof(label));
                            new->label_name = malloc(strlen(temp1));
                            strcpy(new->label_name, temp1);
                            new->addres = code_address;
                            LL_add_tail(&new->node, label_list);

                            code_address += atoi(temp3);
                        }

                        if(strcmp(temp2, "RESW") == 0)
                        {
                            //printf("%06X    %s\n", code_address, temp1);

                            new = malloc(sizeof(label));
                            new->label_name = malloc(strlen(temp1));
                            strcpy(new->label_name, temp1);
                            new->addres = code_address;
                            LL_add_tail(&new->node, label_list);

                            code_address += 3*atoi(temp3);
                        }

                        if(strcmp(temp2, "BYTE") == 0)
                        {

                            new = malloc(sizeof(label));
                            new->label_name = malloc(strlen(temp1));
                            strcpy(new->label_name, temp1);
                            new->addres = code_address;
                            LL_add_tail(&new->node, label_list);

                            sscanf(temp3, "%[^']'%[^']", temp4, temp5);
                            
                            if(*temp4 == 'C')
                            {

                                //printf("%06X    %s\n", code_address, temp1);
                                
                                
                                code_address += strlen(temp5);
                            }

                            if(*temp4 == 'X')
                            {

                                //printf("%06X    %s\n", code_address, temp1);
                                
                                code_address += strlen(temp5)/2 + strlen(temp5)%2;
                            }
                            
                        }

                        if(strcmp(temp2, "WORD") == 0)
                        {
                            new = malloc(sizeof(label));
                            new->label_name = malloc(strlen(temp1));
                            strcpy(new->label_name, temp1);
                            new->addres = code_address;
                            LL_add_tail(&new->node, label_list);


                            //printf("%06X    %s\n", code_address, temp1);
                            code_address += 3;
                        }
                    }
                    else
                    {
                        END_address = code_address;

                    }
                
                }
                else
                {
                    


                    code_address += hex_to_dex(temp3);
                    START_address = code_address;
                    strcpy(program_name, temp1);
                }
            }
            
        }



        printf("H^%-6s^%06X^%06X\n", program_name, START_address, END_address - START_address);
        sprintf(record_head_temp, "H^%-6s^%06X^%06X\n", program_name, START_address, END_address - START_address);
        fputs(record_head_temp, obj_file);
        rewind(ass);
        code_address = 0;





        while(fgets(buffer, 50, ass))
        {   
            
            memset(temp1, 0, 50);
            memset(temp2, 0, 50);
            memset(temp3, 0, 50);
            

            sscanf(buffer, "%s %s %s", temp1, temp2, temp3);
            if(strcmp(temp1, ".") != 0 )
            {
                if(strcmp(temp2, "START") != 0)
                {
                    if(strcmp(temp1, "END") != 0)
                    {
                        
                        for(int i = 0; i < 26; i++)
                        {
                            if(strcmp(temp1, sic[i].command) == 0)
                            {
                                
                                obj_code.opcode = sic[i].code;

                                label_list_temp = label_list;
                                while(label_list_temp->next != NULL)
                                {
                                    label_list_temp = LL_next_node(label_list_temp);
                                    if(strcmp(temp2, return_to_user_struct_pointer(label, node, label_list_temp)->label_name) == 0)
                                    {
                                        obj_code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                                        arg_get = 1;
                                    }
                             
                                }

                                if(strcmp(temp1,"RSUB") != 0 && arg_get == 0)
                                {
                                    sscanf(temp2, "%[^,],%s",temp4, temp5);
                                    

                                    label_list_temp = label_list;
                                    while(label_list_temp->next != NULL)
                                    {
                                        label_list_temp = LL_next_node(label_list_temp);
                                        if(strcmp(temp4, return_to_user_struct_pointer(label, node, label_list_temp)->label_name) == 0)
                                        {
                                            //printf("%s", return_to_user_struct_pointer(label, node, label_list_temp)->label_name);
                                            obj_code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                                            
                                        }
                                
                                    }

                                    if(*temp5 == 'X')
                                            {
                                                obj_code.addres += 32768;
                                            }



                                }

                                if(T_count + 3 > 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);
                                    T_count = 0;
                                }



                                if(T_count == 0)
                                {
                                    sprintf(obj_temp, "^%02X%04X", obj_code.opcode, obj_code.addres);
                                    T_start_count = code_address;
                                }
                                else
                                {
                                    sprintf(obj_cat_temp, "^%02X%04X", obj_code.opcode, obj_code.addres);
                                    strcat(obj_temp, obj_cat_temp);
                                }

                                T_count += 3;

                                if(T_count == 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);                                    
                                    T_count = 0;
                                }

                                code_address+=3;
                                obj_code.opcode = 0;
                                obj_code.addres = 0;
                            } 
                        }

                        for(int i = 0; i < 26; i++)
                        {
                            if(strcmp(temp2, sic[i].command) == 0)
                            {
                                
                                obj_code.opcode = sic[i].code;

                                label_list_temp = label_list;
                                while(label_list_temp->next != NULL)
                                {
                                    label_list_temp = LL_next_node(label_list_temp);
                                    if(strcmp(temp3, return_to_user_struct_pointer(label, node, label_list_temp)->label_name) == 0)
                                    {
                                        obj_code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                                    }
                                }


                                if(T_count + 3 > 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);
                                    T_count = 0;
                                }

                                if(T_count == 0)
                                {
                                    T_start_count = code_address;
                                    sprintf(obj_temp, "^%02X%04X", obj_code.opcode, obj_code.addres);
                                }
                                else
                                {
                                    sprintf(obj_cat_temp, "^%02X%04X", obj_code.opcode, obj_code.addres);
                                    strcat(obj_temp, obj_cat_temp);
                                }

                                T_count += 3;

                                if(T_count == 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);                                    
                                    T_count = 0;
                                }


                                code_address+=3;
                                obj_code.opcode = 0;
                                obj_code.addres = 0;
                            } 
                        }

                        if(strcmp(temp2, "RESB") == 0)
                        {
                            
                            if(T_count + atoi(temp3) > 30)
                            {
                                printf("T^%06X^%02X", T_start_count, T_count);
                                sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                fputs(record_head_temp, obj_file);

                                printf("%s\n", obj_temp);
                                fputs(obj_temp, obj_file);
                                fputs("\n", obj_file);
                                memset(obj_temp, 0, 100);
                                T_count = 0;
                            }

                            if(T_count == 30)
                            {
                                printf("T^%06X^%02X", T_start_count, T_count);
                                sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                fputs(record_head_temp, obj_file);

                                printf("%s", obj_temp);
                                fputs(obj_temp, obj_file);
                                fputs("\n", obj_file);
                                memset(obj_temp, 0, 100);                                    
                                T_count = 0;
                            }
                            code_address += atoi(temp3);
  
                        }

                        if(strcmp(temp2, "RESW") == 0)
                        {
                            code_address += 3*atoi(temp3);

                        }

                        if(strcmp(temp2, "BYTE") == 0)
                        {


                            sscanf(temp3, "%[^']'%[^']", temp4, temp5);
                            
                            if(*temp4 == 'C')
                            {
                                if(T_count + strlen(temp5) > 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);
                                    T_count = 0;
                                }

                                if(T_count == 0)
                                {
                                    T_start_count = code_address;
                                    strcat(obj_temp, "^");                                   
                                    //sprintf(obj_temp, "^%s", temp5);
                                    BYTE_temp = temp5;
                                    for(int i = 0 ; i < strlen(temp5) ; i++)
                                    {
                                        sprintf(obj_cat_temp, "%X" , *BYTE_temp);
                                        strcat(obj_temp, obj_cat_temp);
                                        BYTE_temp++;
                                    
                                    }
                                    
                                }
                                else
                                {
                                    strcat(obj_temp, "^");
                                    BYTE_temp = temp5;
                                    for(int i = 0 ; i < strlen(temp5) ; i++)
                                    {
                                        sprintf(obj_cat_temp, "%X" , *BYTE_temp);
                                        strcat(obj_temp, obj_cat_temp);
                                        BYTE_temp++;
                                    
                                    }
                                }

                                T_count += strlen(temp5);

                                if(T_count == 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);                                    
                                    T_count = 0;
                                }

                                code_address += strlen(temp5);

                            }

                            if(*temp4 == 'X')
                            {
                                if(T_count + strlen(temp5)/2 + strlen(temp5)%2 > 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);
                                    T_count = 0;
                                }

                                if(T_count == 0)
                                {
                                    T_start_count = code_address;                                  
                                    sprintf(obj_temp, "^%s", temp5);         
                                }
                                else
                                {
                                    sprintf(obj_cat_temp, "^%s", temp5);
                                    strcat(obj_temp, obj_cat_temp);

                                }

                                T_count += strlen(temp5)/2 + strlen(temp5)%2;

                                if(T_count == 30)
                                {
                                    printf("T^%06X^%02X", T_start_count, T_count);
                                    sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                    fputs(record_head_temp, obj_file);

                                    printf("%s\n", obj_temp);
                                    fputs(obj_temp, obj_file);
                                    fputs("\n", obj_file);
                                    memset(obj_temp, 0, 100);                                    
                                    T_count = 0;
                                }

                                code_address += strlen(temp5)/2 + strlen(temp5)%2;

                            }
                            
                        }

                        if(strcmp(temp2, "WORD") == 0)
                        {
                            if(T_count + 3 > 30)
                            {
                                printf("T^%06X^%02X", T_start_count, T_count);
                                sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                fputs(record_head_temp, obj_file);

                                printf("%s\n", obj_temp);
                                fputs(obj_temp, obj_file);
                                fputs("\n", obj_file);
                                memset(obj_temp, 0, 100);
                                T_count = 0;
                            }

                            if(T_count == 0)
                            {
                                T_start_count = code_address;
                                sprintf(obj_temp, "^%06X", atoi(temp3));
                            }
                            else
                            {
                                sprintf(obj_cat_temp, "^%06X", atoi(temp3));
                                strcat(obj_temp, obj_cat_temp);
                            }

                            T_count += 3;

                            if(T_count == 30)
                            {
                                printf("T^%06X^%02X", T_start_count, T_count);
                                sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
                                fputs(record_head_temp, obj_file);

                                printf("%s\n", obj_temp);
                                fputs(obj_temp, obj_file);
                                fputs("\n", obj_file);
                                memset(obj_temp, 0, 100);                                    
                                T_count = 0;
                            }

                            code_address += 3;
                        }


                    }
                    
                
                }
                else
                {
                    code_address += hex_to_dex(temp3);
                }
            }
            arg_get = 0;
            
            
        }

        if(strcmp(obj_temp, "") != 0)
        {
            printf("T^%06X^%02X", T_start_count, T_count);
            sprintf(record_head_temp, "T^%06X^%02X", T_start_count, T_count);
            fputs(record_head_temp, obj_file);

            printf("%s\n", obj_temp);
            fputs(obj_temp, obj_file);
            fputs("\n", obj_file);
        }

        printf("E^%06X", START_address);
        sprintf(record_head_temp, "E^%06X", START_address);
        fputs(record_head_temp, obj_file);
        

        


        fclose(ass);
        fclose(obj_file);
    }
    
}
