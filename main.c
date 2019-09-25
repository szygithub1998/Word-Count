#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
/***定义变量***********************************************************************************************/
    int  i,m,n,on_off;      //循环变量i、计数变量m和n、开关变量on_off
    int  c,w,l,k,d,z,h,f; //字符数、词数、行数、空行、代码行、注释行、三行、代码类型
    FILE *fp;             //文件指针
    char *str;            //用于配给fscanf和fgets函数的字符指针
    char ch;              //用于配给fgetc函数的字符
    char *prog,type,*path;//语法模式字符变量和字符指针——用于接收用户输入
    char *txt;            //文章指针——用于读取储存文章和代码的指针
    int  restart;         //重新运行程序或者退出程序
/***运行程序，打开文件*************************************************************************************/
    start:                //程序开始循行
    prog = (char*)malloc(sizeof(char) * 20);
    if(!prog)
    {
        printf("动态空间申请失败！\n");
        exit(1);
    }
    path = (char*)malloc(sizeof(char) * 100);
    if(!path)
    {
        printf("动态空间申请失败！\n");
        exit(1);
    }

    printf("[wc.exe] [-x] [file.c]\n");
    scanf("%s -%c %s", prog, &type, path);

    while(strcmp(prog, "wc.exe") != 0)
    {
        printf("未找到或无法运行%s！请重新输入：", prog);
        for(i = 0; i <= 19; i++)
            prog[i] = '\0';
        for(i = 0; i <= 99; i++)
            path[i] = '\0';
        scanf("%s -%c %s", prog, &type, path);
    }
    //printf("%s -%c %s", prog, type, path);

    while(type!='c' && type!='w' && type!='l' && type!='s' && type!='h' && type!='k' && type!='d' && type!='z' && type!='f')
    {
        printf("程序wc.exe的操作指令有误，请重新输入操作指令：");
        scanf("%c", &type);
    }

    fp = fopen(path, "r");
    while(fp == NULL)
    {
        printf("文件打开失败，请重新输入文件路径或程序路径下的文件名：");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
/***执行指令**************************************************************************************************************************/
    switch(type)
    {
        case 'c':
            c = 0;
            while(!feof(fp))
            {
                c++;
                fgetc(fp);
            }
            printf("文件%s中的字符数为：%d\n", path, c);
            break;

        case 'w': /*可较完善地应对英语文章*/
            w = 0;
            str = (char*)malloc(sizeof(char) * 30);
            if(!str)
            {
                printf("动态空间申请失败！\n");
                exit(1);
            }
            while(!feof(fp))
            {
                w++;
                fscanf(fp, "%s", str);
            }
            printf("文件%s中的词数为：%d\n", path, w);
            free(str);
            break;

        case 'l': /*可较完善的应对源程序代码*/
            l = 0;
            str = (char*)malloc(sizeof(char) * 1000);
            if(!str)
            {
                printf("动态空间申请失败！\n");
                exit(1);
            }
            while(!feof(fp))                             /*有待改进，改为识别\n\r*/
            {
                l++;
                fgets(str, 1000, fp);
            }
            printf("文件%s中的行数为：%d\n", path, l);
            free(str);
            break;

        case 's':
            /*尚未完善，敬请期待*/
            break;

        case 'k':
            k = 0;
            m = 0;//计数变量，记录每行非空白字符数目
            while(!feof(fp))
            {
                ch = fgetc(fp);
                if(ch == '\n')
                {
                    if(m <= 1)
                        k++;
                    m = 0;
                }
                else
                {
                    if(ch != ' ' && ch != '\0' && ch != '\t' && ch != '\n')
                        m++;
                }
            }
            printf("文件%s中的空行数为：%d\n", path, k);
            ch = '\0';
            break;

        case 'd':
            d = 0;
            m = 0;     //字符'/'前面的非空白字符数——有效非空白字符数
            on_off = 1;//开关变量——在未遇到'/'时允许j自增
            while(!feof(fp))
            {
                ch = fgetc(fp);
                if(ch == '\n')
                {
                    if(m > 1)
                        d++;
                    m = 0;
                }
                else if(ch != ' ' && ch != '\0' && ch != '\t' && ch != '\n' && ch != '/' && on_off == 1)
                {
                    m++;
                }
                else if(ch == '/')
                {
                    on_off = 0;//字符'/'后都算注释，停止计算有效非空白字符数j
                }
            }
            printf("文件%s中的代码行数为：%d\n", path, d);
            ch = '\0';
            break;

        case 'z':        /*有待完善，增加h，减少代码行数，同时计算kdz*/
            z = 0;
            m = 0;//有效非空白字符数
            n = 0;//有无字符'/'
            on_off = 1;
            while(!feof(fp))
            {
                ch = fgetc(fp);
                if(ch == '\n')
                {
                    if(n == 1 && m <= 1)
                        z++;
                    m = n = 0;
                }
                else if(ch != ' ' && ch != '\0' && ch != '\t' && ch != '\n' && ch != '/' && on_off == 1)
                {
                    m++;
                }
                else if(ch == '/')
                {
                    n = 1;
                    on_off = 0;
                }
            }
            printf("文件%s中的注释行数为：%d\n", path, z);
            ch = '\0';
            break;

        case 'f':/*可应对正规完整的源程序代码，可模糊处理不完整源程序代码*/
            i = 0;
            txt = (char*)malloc(sizeof(char) * 10000);
            if(!txt)
            {
                printf("动态空间申请失败！\n");
                exit(1);
            }
            while(!feof(fp))
            {
                txt[i] = fgetc(fp);
                i++;
            }
            if(strstr(txt, "#include") != NULL)
            {
                if(strstr(txt, "<iostream>") != NULL || strstr(txt, "<iostream.h>") != NULL)
                    printf("该源程序代码语言为C++.\n");
                else if(strstr(txt, "<stdio.h>") != NULL || strstr(txt, "<stdlib.h>") != NULL)
                    printf("该源程序代码语言为C语言.\n");
            }
            else if(strstr(txt, "#!/usr/bin/") != NULL)
            {
                printf("该源程序代码语言为Python.\n");
            }
            else if(strstr(txt, "public class") != NULL)
            {
                printf("该源程序代码语言为Java语言.\n");
            }
            else if(strstr(txt, "<!DOCTYPE html>") != NULL)
            {
                printf("该源程序代码语言为HTML语言.\n");
            }
            else if(strstr(txt, "printf(") != NULL || strstr(txt, "scanf(") != NULL)
                printf("该源程序代码语言为C语言.\n");
            else if(strstr(txt, "cin>>") != NULL || strstr(txt, "cout<<") != NULL || strstr(txt, "cin <<") != NULL || strstr(txt, "cout <<") != NULL)
                printf("该源程序代码语言为C++.\n");
            else if(strstr(txt, "\'\'\'") != NULL || strstr(txt, "\"\"\"") != NULL)
                printf("该源程序代码语言为Python.\n");
            else if(strstr(txt, "global") != NULL || strstr(txt, "def") != NULL || strstr(txt, "import") != NULL)
                printf("该源程序代码语言可能为Python.\n");
            else if(strstr(txt, "public") != NULL || strstr(txt, "class") != NULL || strstr(txt, "private") != NULL)
                printf("该程序源代码语言可能为C++或java语言.\n");
            else if(strstr(txt, "protected") != NULL)
                printf("该程序源代码语言可能为java语言.\n");
            free(txt);
            break;
    }
/***程序运行结束**********************************************************************************************************************/
    fflush(stdin);
    getchar();
    fclose(fp);
    free(prog);
    free(path);
    printf("是否重新运行程序？1-重新运行，0-退出程序：");
    scanf("%d", &restart);
    while(restart != 1 && restart != 0)
    {
        printf("指令错误，请重新输入：");
        scanf("%d", &restart);
    }
    if(restart == 1)
    {
        system("cls");
        goto start;
    }
    else if(restart == 0)
    {
        printf("谢谢使用！祝生活愉快！\n");
        return 0;
    }
}
