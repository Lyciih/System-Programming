#include"tool.h"


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

//將讀取的字元視為16進位，並轉換為10進位數字的函數
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