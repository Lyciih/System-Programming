#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linked_list.h"
#include<math.h>

 
typedef struct sic24_t{
    unsigned int addres : 16;
    unsigned int opcode : 8; 
    }sic24_t;


typedef struct opcode{
    char *command;
    int code;
}opcode;


typedef struct label{
	char *label_name;
    int addres;
	llNode_t node;
}label;

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


//將目標檔名作為命令列參數傳進main裡面
int main(int argc, char *argv[])
{

//*******************************   第一階段 檔案處理    *********************************************//

    //依序組譯每個來源檔，argc代表參數(來源檔)的數量，第0個是main本身的檔名，不取用
    for (int i = 1; i < argc; i++) 
    {  
        //以唯讀模式開啟來源檔
        FILE *ass = fopen(argv[i],"r");
        
        //顯示當前處理的來源檔名
        printf("[%d] [source] %s\n", i, argv[i]);
     
        //以'.'切割檔名
        char *obj_file_name = strtok(argv[i], ".");
        //宣告要加在檔名後方的副檔名字串
        char *obj= ".o";

        //將目標檔名後方接上.o副檔名       
        strcat(obj_file_name, obj);
        //以目標檔名開啟新檔
        FILE *obj_file = fopen(obj_file_name,"w");

        
        
        //顯示目標檔名
        printf("[%d] [target] %s\n\n", i, obj_file_name);

//*******************************   第二階段 開始編譯    *********************************************//
        opcode sic[26];
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
//因為編譯過程會用到雙層迴圈( while + switch )，為了能在處理完後用return回來，把編譯過程寫成副程式 translter
        //translter(ass, obj_file);


        sic24_t code;

        llNode_t *label_list = LL_init();
        llNode_t *label_list_temp;

        int line_count = 1;
        int code_count = 0;
        char buffer[50];
        char argbuffer[50];
        char write_buffer[50];
        char *saveptr = NULL;
        char *substr = NULL;
        char *savearg = NULL;
        char *subarg = NULL;
        //char program_name[50];
        //int total_code = 0;
        //int start_code = 0;
        int segment_count = 0;
        

 
 


        int START_state = 0; 
        int COMMAND_state = 0;
        int COMMAND_state_two = 0;
        int RESW_state = 0;
        int RESB_state = 0;
        int WORD_state = 0;
        int BYTE_state = 0;
        int ARG_state_one= 0;
        int arg_get = 0;
        int RSUB_state = 0;
        label *new;
        label * free_top_temp;
        llNode_t * free_temp;


        while(fgets(buffer, 50, ass))
        {
            

            if(*buffer != '.')
            {
//------------------------------------------------------------------------------------------------               

                substr = strtok_r(buffer, " ", &saveptr);
                for(int i = 0; i < 26; i++)
                {
                    if(strcmp(substr, sic[i].command) == 0)
                    {
                        COMMAND_state = 1;
                        code.opcode = sic[i].code;
                    } 
                }

                if(COMMAND_state == 0)
                {
                    new = malloc(sizeof(label));
                    new->label_name = malloc(strlen(substr));
                    strcpy(new->label_name, substr);
                    new->addres = code_count;
                    LL_add_tail(&new->node, label_list);
                }
//------------------------------------------------------------------------------------------------



                substr = strtok_r(saveptr, " ", &saveptr);
                if(substr != NULL)
                {
                    for(int i = 0; i < 26; i++)
                    {
                        if(strcmp(substr, sic[i].command) == 0)
                        {
                            COMMAND_state = 1;
                            code.opcode = sic[i].code;
                        }
                    }
                }
                if(strcmp(substr, "START") == 0){
                    
                    START_state = 1;
                }
                else if(strcmp(substr, "BYTE") == 0){
                    BYTE_state = 1;
                }
                else if(strcmp(substr, "WORD") == 0){
                    WORD_state = 1;
                    code_count+=3;
                }
                else if(strcmp(substr, "RESW") == 0){
                    RESW_state = 1;
                }
                else if(strcmp(substr, "RESB") == 0){
                    RESB_state = 1;
                }
//------------------------------------------------------------------------------------------------



                substr = strtok_r(saveptr, " ", &saveptr);

                if(START_state == 1){
                    code_count += hex_to_dex(substr);
                    //start_code = code_count;
                }

                if(RESW_state == 1){
                    code_count += 3*atoi(substr);
                }

                if(RESB_state == 1){
                    code_count += atoi(substr);
                }

                if(BYTE_state == 1){
                    if(*substr == 'X')
                    {
                        strcpy(argbuffer, substr);
                        subarg = strtok_r(argbuffer, "'", &savearg);
                        subarg = strtok_r(savearg, "'", &savearg);
                        code_count += strlen(subarg)/2;
                    }

                    if(*substr == 'C')
                    {
                        strcpy(argbuffer, substr);
                        subarg = strtok_r(argbuffer, "'", &savearg);
                        subarg = strtok_r(savearg, "'", &savearg);
                        code_count += strlen(subarg);
                    }

                }


//------------------------------------------------------------------------------------------------

                if(COMMAND_state == 1){
                    code_count+=3;
                }


                
                code.opcode = 0;
                code.addres = 0;                
                START_state = 0;
                COMMAND_state = 0;
                RESW_state = 0;
                RESB_state = 0;
                WORD_state = 0;
                BYTE_state = 0;
                line_count++;
            }
        }
        line_count = 1;

        //total_code = code_count - start_code; 
        code_count = 0;










        printf_all_list(label_list);
        rewind(ass);
















        while(fgets(buffer, 50, ass))
        {
            

            if(*buffer != '.')
            {
                printf("________________________________________________\n");
                printf("%-5d  %-5X  %s", line_count, code_count, buffer);
                printf("--------------------------------------\n");
//------------------------------------------------------------------------------------------------               

                substr = strtok_r(buffer, " ", &saveptr);
                //printf("%-8s", substr);

                for(int i = 0; i < 26; i++)
                {
                    if(strcmp(substr, sic[i].command) == 0)
                    {
                        COMMAND_state = 1;
                        code.opcode = sic[i].code;
                        if(!strcmp(sic[i].command, "RSUB"))
                        {
                            RSUB_state = 1;
                        }
                    } 
                }

                if(COMMAND_state == 1)
                {
                    ARG_state_one = 1;
                }


//------------------------------------------------------------------------------------------------


                substr = strtok_r(saveptr, " ", &saveptr);
                if(substr != NULL)
                {
                    //printf("%-8s", substr);
                    for(int i = 0; i < 26; i++)
                    {
                        if(strcmp(substr, sic[i].command) == 0)
                        {
                            COMMAND_state = 1;
                            COMMAND_state_two = 1;
                            code.opcode = sic[i].code;
                        }
                    }
                }
                //printf("\n");
                if(strcmp(substr, "START") == 0){

                    //sprintf(write_buffer, "%s\n", subarg);
                    //fputs("H ", obj_file);
                    //sprintf(program_name, "%-6s ", return_to_user_struct_pointer(label, node, label_list->next)->label_name);
                    //fputs(program_name, obj_file);
                    START_state = 1;
                }
                else if(strcmp(substr, "BYTE") == 0){
                    BYTE_state = 1;
                }
                else if(strcmp(substr, "WORD") == 0){
                    WORD_state = 1;

                }
                else if(strcmp(substr, "RESW") == 0){
                    RESW_state = 1;
                }
                else if(strcmp(substr, "RESB") == 0){
                    RESB_state = 1;
                }


                if(ARG_state_one == 1  && RSUB_state == 0)
                {
                    label_list_temp = label_list;
                    while(label_list_temp->next != NULL)
                    {
                        label_list_temp = LL_next_node(label_list_temp);
                        if(strcmp(strtok(substr, "\n"), strtok(return_to_user_struct_pointer(label, node, label_list_temp)->label_name, " ")) == 0)
                        {
                            code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                            arg_get = 1;
                        }
                    }
                    
                    if(!arg_get)
                    {
                        substr = strtok_r(substr, ",", &saveptr);
                        label_list_temp = label_list;
                        while(label_list_temp->next != NULL)
                        {
                            label_list_temp = LL_next_node(label_list_temp);
                            if(strcmp(substr, return_to_user_struct_pointer(label, node, label_list_temp)->label_name) == 0)
                            {
                                code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                            }
                        }
                        substr = strtok_r(saveptr, " ", &saveptr);
                        if(*substr == 'X')
                        {
                            code.addres +=  32768;
                        }
                    }
                    ARG_state_one = 0;
                    
                }
//------------------------------------------------------------------------------------------------



                substr = strtok_r(saveptr, " ", &saveptr);
                if(substr != NULL){
                    //printf("%-8s", substr);
                }
                //printf("\n");


                if(START_state == 1){
                    printf("%d\n", hex_to_dex(substr));
                    //sprintf(write_buffer, "%06X %06X\n", hex_to_dex(substr), total_code);
                    //fputs(write_buffer, obj_file);
                    code_count += hex_to_dex(substr);

                    
                }

                if(RESW_state == 1){
                    code_count += 3*atoi(substr);
                }

                if(RESB_state == 1){
                    code_count += atoi(substr);

                }

                if(BYTE_state == 1){
                    if(*substr == 'X')
                    {
                        strcpy(argbuffer, substr);
                        subarg = strtok_r(argbuffer, "'", &savearg);
                        subarg = strtok_r(savearg, "'", &savearg);
                        
                        printf("                                            %s\n",subarg);
                        sprintf(write_buffer, "DATA   %06X %-6s\n", code_count, subarg);
                        fputs(write_buffer, obj_file);
                        code_count += strlen(subarg)/2;
                    }

                    if(*substr == 'C')
                    {
                        strcpy(argbuffer, substr);
                        subarg = strtok_r(argbuffer, "'", &savearg);
                        subarg = strtok_r(savearg, "'", &savearg);
                        
                        printf("                                        ");
                        fputs("DATA   ", obj_file);
                        sprintf(write_buffer, "%06X ", code_count);
                        fputs(write_buffer, obj_file);
                        while(*subarg)
                        {
                            printf("%X", *subarg);
                            sprintf(write_buffer, "%X", *subarg);
                            fputs(write_buffer, obj_file);
                            subarg++;
                            code_count++;
                        }
                        fputs("\n", obj_file);
                        printf("\n");
                       
                    }


                }

                if(WORD_state == 1){
                    printf("                                        %06X\n",atoi(substr));
                    sprintf(write_buffer, "DATA   %06X %06X\n", code_count, atoi(substr));
                    fputs(write_buffer, obj_file);
                    code_count+=3;

                }

                if(COMMAND_state_two == 1)
                {
                    label_list_temp = label_list;
                    while(label_list_temp->next != NULL)
                    {
                        label_list_temp = LL_next_node(label_list_temp);
                        if(strcmp(strtok(substr, "\n"), strtok(return_to_user_struct_pointer(label, node, label_list_temp)->label_name, " ")) == 0)
                        {
                            
                            code.addres = return_to_user_struct_pointer(label, node, label_list_temp)->addres;
                        }
                    }  
                }


//------------------------------------------------------------------------------------------------

                if(COMMAND_state == 1){
                    printf("                                        %02X%04X\n", code.opcode, code.addres);
                    sprintf(write_buffer, "       %06X %02X%04X\n",code_count,  code.opcode, code.addres);
                    fputs(write_buffer, obj_file);
                    segment_count += 6;
                    //if(segment_count == 60)
                    //{
                        //fputs("\n", obj_file);
                        //segment_count = 0;
                    //}

                   
                    
                    code_count+=3;

                }


                
                code.opcode = 0;
                code.addres = 0;                
                START_state = 0;
                COMMAND_state = 0;
                COMMAND_state_two = 0;
                RESW_state = 0;
                RESB_state = 0;
                WORD_state = 0;
                BYTE_state = 0;
                ARG_state_one = 0;
                arg_get = 0;
                RSUB_state = 0;
                line_count++;
            }
        }


//------------------------------------------------------------------------------------------------------------------------------------------

//*****************************   第三階段 收尾並關閉所有檔案    **************************************//
        
        //將來源檔與目標檔關起來
        fclose(ass);
        fclose(obj_file);

         //釋放之前申請的空間
        while(!LL_isEmpty(label_list))
	    {
            free_temp = LL_next_node(label_list);
            free_top_temp = return_to_user_struct_pointer(label, node, free_temp);
		    LL_delete_next(label_list);
            memset(free_top_temp->label_name, 0, strlen(free_top_temp->label_name));
            free(free_top_temp->label_name);
            free_top_temp->label_name = NULL;
            free(free_top_temp);
            free_top_temp = NULL;
            free_temp = NULL;
	    }
	    LL_free_head(label_list);


    }

    printf("\n");  
}