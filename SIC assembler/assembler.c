#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linked_list.h"

 
typedef struct sic24_t{
    unsigned int addres : 15;
    unsigned int index : 1;
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



//將目標檔名作為命令列參數傳進main裡面
int main(int argc, char *argv[])
{

//*******************************   第一階段 檔案處理    *********************************************//

    //依序組譯每個來源檔，argc代表參數(來源檔)的數量，第0個是main本身的檔名，不取用
    for (int i = 1; i < argc; i++) 
    {  
        //以唯讀模式開啟來源檔
        FILE *ass = fopen(argv[i],"r");
        
        //宣告用來分割檔名與副檔名的字元為cut
        char cut = '.';
        //計算來源檔名從第一個字元到cut總共有幾個字元
        size_t cut_position = strcspn(argv[i], &cut);
        //以計算出來的數量宣告目標檔名的字元陣列
        char obj_file_name[cut_position];
        //宣告要加在檔名後方的副檔名字串
        char *obj= ".o";
        //將來源檔副檔名之前的字串複製到目標檔名的字元陣列中
        memcpy(obj_file_name, argv[i], cut_position);
        //將目標檔名後方接上.o副檔名       
        strcat(obj_file_name, obj);
        //以目標檔名開啟新檔
        FILE *obj_file = fopen(obj_file_name,"w");

        //顯示當前處理的來源檔名
        printf("[%d] [source] %s\n", i, argv[i]);
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

        int line_count = 1;
        int code_count = 0;
        char buffer[50];
        char write_buffer[50];
        char *saveptr = NULL;
        char *substr = NULL;
        int START_state = 0; 
        int COMMAND_state = 0;
        int RESW_state = 0;
        int RESB_state = 0;
        label *new;
        label * free_top_temp;
        llNode_t * free_temp;


        while(fgets(buffer, 50, ass))
        {
            

            if(*buffer != '.')
            {
                printf("_________________________________\n");
                printf("%-5d  %-5X  %s", line_count, code_count, buffer);
                printf("---------------------------------\n");
//------------------------------------------------------------------------------------------------               

                substr = strtok_r(buffer, " ", &saveptr);
                printf("%-8s", substr);

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

                printf("\n");
//------------------------------------------------------------------------------------------------



                substr = strtok_r(saveptr, " ", &saveptr);
                if(substr != NULL)
                {
                    printf("%-8s", substr);
                    for(int i = 0; i < 26; i++)
                    {
                        if(strcmp(substr, sic[i].command) == 0)
                        {
                            COMMAND_state = 1;
                            code.opcode = sic[i].code;
                        }
                    }
                }
                printf("\n");
                if(strcmp(substr, "START") == 0){
                    
                    START_state = 1;
                }
                else if(strcmp(substr, "BYTE") == 0){
                    code_count+=3;
                }
                else if(strcmp(substr, "WORD") == 0){
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
                if(substr != NULL){
                    printf("%-8s", substr);
                }
                printf("\n");

//------------------------------------------------------------------------------------------------

                if(START_state == 1){
                    code_count += 4096;
                }

                if(RESW_state == 1){
                    code_count += 3*atoi(substr);
                }

                if(RESB_state == 1){
                    code_count += atoi(substr);
                }

                if(COMMAND_state == 1){
                    code_count+=3;
                    printf("                                    %02x%x%03x\n", code.opcode, code.index, code.addres);
                    sprintf(write_buffer, "%02x", code.opcode);
                    fputs(write_buffer, obj_file);
                    fputs("\n", obj_file);
                }


                
                code.opcode = 0;
                code.index = 0;
                code.addres = 0;                
                START_state = 0;
                COMMAND_state = 0;
                RESW_state = 0;
                RESB_state = 0;
                line_count++;
            }
        }
        


//*****************************   第三階段 收尾並關閉所有檔案    **************************************//
        
        //將來源檔與目標檔關起來
        fclose(ass);
        fclose(obj_file);
        printf_all_list(label_list);

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