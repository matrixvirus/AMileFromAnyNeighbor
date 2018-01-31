// 输入是一个十进制整数或小数，和2到16以内的目标进制，输出是目标进制数
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
// 1 先检查一字串是否符合是一个浮动点数的条件:
//     1 只有数字0~9或点号
//     2 点号最多出现在次
// 2 把这个字串转成浮动点数
double safed_atof(char * s)
{
    int i;
    int point_n = 0; // 点号出现的次数。数字中点号最多出现一次
    for (i = 0; i < strlen(s); i ++)
    {
        if (s[i]>= 48 && s[i]<=57)
        {
            continue;
        }
        else if (s[i] == 46)
        {
            point_n ++;
            
        }
        else
        {
            printf("参数 %s 不是数字\n", s);
            exit(0);
        }
        if (point_n >= 2)
        {
            printf("参数 %s 不是数字\n", s);
            exit(0);
        }
    }
    double t = atof(s);
    return(t);
}
// 1 先检查一个字串是否满足是一个整数的条件:
//     1 只有0~9
// 2 把这个字串转成一个整数
int safed_atoi(char * s)
{
    int i;
    for (i = 0; i < strlen(s); i ++)
    {
        if (!(s[i]>=48 && s[i] <= 57))
        {
            printf("参数 %s 不是整数\n", s);
            exit(0);
        }
    }
    int t = atoi(s);
    return(t);
} 
// 把十进制数转成十六进制表示法
// 输入十进制数范围是0 ~ 15
char dig2hex(int a)
{
    char c;
    if (a >= 0 && a <= 9)
    {
        c = a + 48;
    }
    else if (a >= 10 && a <= 15)
    {
        c = a + 55;
    }
    return(c);
}
    
// 把一个十进制数转成希望的目标进制整数
// 参数 dec_int 是要转的十进制整数
// 参数 tbase 是目标进制
char * dec2base_int(double dec_int, int tbase)
{
    char * tar_int = (char *)malloc(64);
    int dec_int2 = dec_int;
    int rems[64];
    int i,i2;
    for (i = 0; i < 64; i ++)
    {
        rems[i] = 0;
    }
    i = 0;
    while (dec_int2 != 0)
    {
        int rem = dec_int2 % tbase;
        dec_int2 = dec_int2 / tbase;
        rems[i] = rem;
        i += 1;
    }
    for (i2 = 0; i2 < i; i2 ++)
    {
        tar_int[i2] = dig2hex(rems[i2]);
    }
    tar_int[i] = 0;
        
    return(tar_int);
}
// 把一个十进制小数转成希望的目标进制小数
// 参数dec_dec 是要转的十进制小数
// 参数 tbase 是目标进制
char * dec2base_dec(double dec_dec, int tbase)
{
    char * tar_dec = (char *)malloc(64);
    double dec_dec2 = dec_dec;
    int precise = 8;
    int i,i2;
    int ints[64];
    i = 0;
    while(dec_dec2 != 0 && i < precise)
    {
        dec_dec2 *= tbase;
        ints[i] = floor(dec_dec2);
        dec_dec2 = dec_dec2 - ints[i];
        i += 1;
    }
    int len = i;
    for (i2 = 0; i2 < len; i2 ++)
    {
        tar_dec[i2] = dig2hex(ints[i2]);
    }
    tar_dec[len] = 0;
    return(tar_dec);
}
// 组合整数和小数
char * comb_int_dec(char * tar_int, char * tar_dec)
{
    char * tar_full = (char *)malloc(128);
    if (strlen(tar_int) == 0 && strlen(tar_dec) == 0)
    {
        snprintf(tar_full, 1, "0");
    }
    else if (strlen(tar_int) == 0 && strlen(tar_dec) > 0)
    {
        snprintf(tar_full, 128, "0.%s", tar_dec);
    }
    else if (strlen(tar_int) > 0 && strlen(tar_dec) == 0)
    {
        snprintf(tar_full, 128, "%s", tar_int);
    }
    else if (strlen(tar_int) > 0 && strlen(tar_dec) > 0)
    {
        snprintf(tar_full, 128, "%s.%s", tar_int, tar_dec);
    }
    return(tar_full);
}
int main(int argc, char ** argv)
{
    double ori_dec = safed_atof(argv[1]); //原十进制数
    int tar_base = safed_atoi(argv[2]); // 目标进制
    double ori_dec_int = floor(ori_dec); // 原十进制数整数部分
    double ori_dec_dec = ori_dec - ori_dec_int; // 原十进制数小数部分
    printf("输入十进制数:%lf\n", ori_dec);
    printf("目标进制:%d\n", tar_base);
    char * tar_int = dec2base_int(ori_dec_int, tar_base); 
        // 整数部分的目标进制整数
    char * tar_dec = dec2base_dec(ori_dec_dec, tar_base); 
        // 小数部分的目标进制小数
    char * tar_ful = comb_int_dec(tar_int, tar_dec);
    printf("目标进制数:%s\n", tar_ful);
    return(0);
}
