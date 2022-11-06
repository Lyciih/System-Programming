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

        char buffer[50];
        char temp1[50];
        char temp2[50];
        char temp3[50];



        while(fgets(buffer, 50, ass))
        {
            memset(temp1, 0, 50);
            memset(temp2, 0, 50);
            memset(temp3, 0, 50);
            

            sscanf(buffer, "%s %s %s", temp1, temp2, temp3);
            printf("%s %s %s\n", temp1, temp2, temp3);
            printf("%d %d %d\n", strlen(temp1), strlen(temp2), strlen(temp3));
        }

        






        fclose(ass);
        fclose(obj_file);
    }
    
}
