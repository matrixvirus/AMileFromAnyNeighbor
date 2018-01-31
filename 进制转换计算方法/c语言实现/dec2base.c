// 输入参数：十进制数，目标进制
// 输入的十进制数可以是整数或带小数
// 目标进制是2到16

int safed_atof(char * argv)
{
    int i;
    int dot_num = 0; // 记录点号出现次数
    for (i = 0; i < strlen(argv); i ++)
    {
        // 如果出现不是数字也不是点号
        if (! ((argv[i]>=48 && argv[i]<=57) || (argv[i] == 46)))
        {
            exit(1);
        }
        // 是点号，把点号出现次数加1
        else if (argv[i] == 46)
        {
            dot_num += 1;
    }
}
int main(int argc, char ** argv)
{
    double dec = safed_atof(argv[1]); // 输入十进制数
    int obase = safed_atoi(argv[2]); // 目标进制
    double dec_integer = floor(dec); // 十进制数整数部分
    double dec_decimal = dec - dec_integer; // 十进制数小数部分
    return(0);
}
