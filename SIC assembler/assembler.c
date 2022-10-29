#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) 
    {
        printf("[%d] %s\n\n", i, argv[i]);
        

        int count = 0;
        char ch;

        FILE *ass = fopen(argv[i],"r");
    



        char cut = '.';
        size_t cut_position = strcspn(argv[i], &cut);
        char obj_file_name[cut_position];
        char *obj= ".o";

        memcpy(obj_file_name, argv[i], cut_position);
        
        strcat(obj_file_name, obj);
        printf("%s\n", &obj_file_name);
        FILE *obj_file = fopen(obj_file_name,"w");

        while(1)
        {
            ch = fgetc(ass);
            if(ch != EOF)
            {
                printf("%c", ch);
                fputc(ch, obj_file);
                count++;
            }
            else
            {
                break;
            }
        }


        

    
        fclose(ass);
        fclose(obj_file);
    }



    


    //scanf("%d",i);
    //printf("%d", *i);   
}