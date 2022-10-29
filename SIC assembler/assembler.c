#include<stdio.h>
#include<string.h>

 
typedef struct code_24{
    unsigned int addres : 15;
    unsigned int index : 1;
    unsigned int opcode : 8; 
    }code_24;



void translter(FILE *ass, FILE *obj_file)
{
        int count = 0;
        char ch;
        code_24 *code;
        code->addres = (3 << 0);
        code->index = (1 << 0);
        code->opcode = (1 << 0);

       

        char divid[100];
        memset(divid, 0, 100);

        while(1)
        {
            ch = fgetc(ass);
            switch(ch)
            {
                case 10: //10是換行符號 '\n' 的Unicode編碼
                    //divid[count] = '^';
                    //fputc('^', obj_file);
                    printf("\n%02x%x%03x \n", code->opcode, code->index, code->addres);
                    code->addres = 0;
                    code->index = 0;
                    code->opcode = 0;
                    //printf("%s", divid);
                    printf("----------------------------------------\n");
                    //memset(divid, 0, 100);
                    count = 0;
                    break;
                
                case EOF: //EOF是檔案結束符，到這裡時結束 translter 函數
                    return;

                 case 46: //46是 '.'的Unicode編碼，如果遇到代表這裡開始是注釋，需要不停忽略直到遇到換行符號(Unicode編碼為10)
                    while(1)
                    {
                        ch = fgetc(ass);
                        if(ch == 10)
                        {
                            break;
                        }
                    }
                    count = 0;
                    break;

                default: //轉換標籤或指令
                    switch(ch){
                        case 'J':
                            printf("%c", ch);
                            ch = fgetc(ass);
                            switch(ch){
                                case 'E':
                                    printf("%c", ch);
                                    ch = fgetc(ass);
                                    switch(ch){
                                        case 'Q':
                                            code->opcode = 48;
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }

                    printf("%c", ch);
                    fputc(ch, obj_file);
                    divid[count] = ' ';
                    count++;
                    break;

            }
        }
}





//將目標檔名作為命令列參數傳進main裡面
int main(int argc, char *argv[])
{

//*******************************   第一階段 檔案處理    *********************************************//

    //依序組譯每個來源檔，argc代表參數(來源檔)的數量，第0個是main本身的檔名，不取用
    for (int i = 1; i < argc; ++i) 
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
        printf("[%d] [target] %s\n\n", i, &obj_file_name);

//*******************************   第二階段 開始編譯    *********************************************//

//因為編譯過程會用到雙層迴圈( while + switch )，為了能在處理完後用return回來，把編譯過程寫成副程式 translter
        translter(ass, obj_file);


//*****************************   第三階段 收尾並關閉所有檔案    **************************************//
        
        //將來源檔與目標檔關起來
        fclose(ass);
        fclose(obj_file);
    } 
}