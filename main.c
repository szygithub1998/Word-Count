#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
/***�������***********************************************************************************************/
    int  i,m,n,on_off;      //ѭ������i����������m��n�����ر���on_off
    int  c,w,l,k,d,z,h,f; //�ַ��������������������С������С�ע���С����С���������
    FILE *fp;             //�ļ�ָ��
    char *str;            //�������fscanf��fgets�������ַ�ָ��
    char ch;              //�������fgetc�������ַ�
    char *prog,type,*path;//�﷨ģʽ�ַ��������ַ�ָ�롪�����ڽ����û�����
    char *txt;            //����ָ�롪�����ڶ�ȡ�������ºʹ����ָ��
    int  restart;         //�������г�������˳�����
/***���г��򣬴��ļ�*************************************************************************************/
    start:                //����ʼѭ��
    prog = (char*)malloc(sizeof(char) * 20);
    if(!prog)
    {
        printf("��̬�ռ�����ʧ�ܣ�\n");
        exit(1);
    }
    path = (char*)malloc(sizeof(char) * 100);
    if(!path)
    {
        printf("��̬�ռ�����ʧ�ܣ�\n");
        exit(1);
    }

    printf("[wc.exe] [-x] [file.c]\n");
    scanf("%s -%c %s", prog, &type, path);

    while(strcmp(prog, "wc.exe") != 0)
    {
        printf("δ�ҵ����޷�����%s�����������룺", prog);
        for(i = 0; i <= 19; i++)
            prog[i] = '\0';
        for(i = 0; i <= 99; i++)
            path[i] = '\0';
        scanf("%s -%c %s", prog, &type, path);
    }
    //printf("%s -%c %s", prog, type, path);

    while(type!='c' && type!='w' && type!='l' && type!='s' && type!='h' && type!='k' && type!='d' && type!='z' && type!='f')
    {
        printf("����wc.exe�Ĳ���ָ�������������������ָ�");
        scanf("%c", &type);
    }

    fp = fopen(path, "r");
    while(fp == NULL)
    {
        printf("�ļ���ʧ�ܣ������������ļ�·�������·���µ��ļ�����");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
/***ִ��ָ��**************************************************************************************************************************/
    switch(type)
    {
        case 'c':
            c = 0;
            while(!feof(fp))
            {
                c++;
                fgetc(fp);
            }
            printf("�ļ�%s�е��ַ���Ϊ��%d\n", path, c);
            break;

        case 'w': /*�ɽ����Ƶ�Ӧ��Ӣ������*/
            w = 0;
            str = (char*)malloc(sizeof(char) * 30);
            if(!str)
            {
                printf("��̬�ռ�����ʧ�ܣ�\n");
                exit(1);
            }
            while(!feof(fp))
            {
                w++;
                fscanf(fp, "%s", str);
            }
            printf("�ļ�%s�еĴ���Ϊ��%d\n", path, w);
            free(str);
            break;

        case 'l': /*�ɽ����Ƶ�Ӧ��Դ�������*/
            l = 0;
            str = (char*)malloc(sizeof(char) * 1000);
            if(!str)
            {
                printf("��̬�ռ�����ʧ�ܣ�\n");
                exit(1);
            }
            while(!feof(fp))                             /*�д��Ľ�����Ϊʶ��\n\r*/
            {
                l++;
                fgets(str, 1000, fp);
            }
            printf("�ļ�%s�е�����Ϊ��%d\n", path, l);
            free(str);
            break;

        case 's':
            /*��δ���ƣ������ڴ�*/
            break;

        case 'k':
            k = 0;
            m = 0;//������������¼ÿ�зǿհ��ַ���Ŀ
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
            printf("�ļ�%s�еĿ�����Ϊ��%d\n", path, k);
            ch = '\0';
            break;

        case 'd':
            d = 0;
            m = 0;     //�ַ�'/'ǰ��ķǿհ��ַ���������Ч�ǿհ��ַ���
            on_off = 1;//���ر���������δ����'/'ʱ����j����
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
                    on_off = 0;//�ַ�'/'����ע�ͣ�ֹͣ������Ч�ǿհ��ַ���j
                }
            }
            printf("�ļ�%s�еĴ�������Ϊ��%d\n", path, d);
            ch = '\0';
            break;

        case 'z':        /*�д����ƣ�����h�����ٴ���������ͬʱ����kdz*/
            z = 0;
            m = 0;//��Ч�ǿհ��ַ���
            n = 0;//�����ַ�'/'
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
            printf("�ļ�%s�е�ע������Ϊ��%d\n", path, z);
            ch = '\0';
            break;

        case 'f':/*��Ӧ������������Դ������룬��ģ����������Դ�������*/
            i = 0;
            txt = (char*)malloc(sizeof(char) * 10000);
            if(!txt)
            {
                printf("��̬�ռ�����ʧ�ܣ�\n");
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
                    printf("��Դ�����������ΪC++.\n");
                else if(strstr(txt, "<stdio.h>") != NULL || strstr(txt, "<stdlib.h>") != NULL)
                    printf("��Դ�����������ΪC����.\n");
            }
            else if(strstr(txt, "#!/usr/bin/") != NULL)
            {
                printf("��Դ�����������ΪPython.\n");
            }
            else if(strstr(txt, "public class") != NULL)
            {
                printf("��Դ�����������ΪJava����.\n");
            }
            else if(strstr(txt, "<!DOCTYPE html>") != NULL)
            {
                printf("��Դ�����������ΪHTML����.\n");
            }
            else if(strstr(txt, "printf(") != NULL || strstr(txt, "scanf(") != NULL)
                printf("��Դ�����������ΪC����.\n");
            else if(strstr(txt, "cin>>") != NULL || strstr(txt, "cout<<") != NULL || strstr(txt, "cin <<") != NULL || strstr(txt, "cout <<") != NULL)
                printf("��Դ�����������ΪC++.\n");
            else if(strstr(txt, "\'\'\'") != NULL || strstr(txt, "\"\"\"") != NULL)
                printf("��Դ�����������ΪPython.\n");
            else if(strstr(txt, "global") != NULL || strstr(txt, "def") != NULL || strstr(txt, "import") != NULL)
                printf("��Դ����������Կ���ΪPython.\n");
            else if(strstr(txt, "public") != NULL || strstr(txt, "class") != NULL || strstr(txt, "private") != NULL)
                printf("�ó���Դ�������Կ���ΪC++��java����.\n");
            else if(strstr(txt, "protected") != NULL)
                printf("�ó���Դ�������Կ���Ϊjava����.\n");
            free(txt);
            break;
    }
/***�������н���**********************************************************************************************************************/
    fflush(stdin);
    getchar();
    fclose(fp);
    free(prog);
    free(path);
    printf("�Ƿ��������г���1-�������У�0-�˳�����");
    scanf("%d", &restart);
    while(restart != 1 && restart != 0)
    {
        printf("ָ��������������룺");
        scanf("%d", &restart);
    }
    if(restart == 1)
    {
        system("cls");
        goto start;
    }
    else if(restart == 0)
    {
        printf("ллʹ�ã�ף������죡\n");
        return 0;
    }
}
