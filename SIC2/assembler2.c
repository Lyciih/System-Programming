#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[])
{

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

        char buffer[8];

        while (fgets(buffer, 8 , ass))
        {
            printf("%s %d", buffer, strlen(buffer));
        }
        






        fclose(ass);
        fclose(obj_file);
    }
    
}
