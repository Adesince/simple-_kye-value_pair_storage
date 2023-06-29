#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// 存储key-value文件的名称
char kv_filename[] = "key_value.txt";
// 判断kv是否合规
int is_kv(char *kv)
{
    int num = 0;
    if (NULL == kv || strlen(kv) == 0)
    {
        return 0;
    }
    int len = strlen(kv);
    for (size_t i = 0; i < len; i++)
    {
        if (kv[i] == '=')
        {
            num++;
        }
    }
    if (num == 1 && kv[0] != '=' && kv[len - 1] != '=')
    {
        return 1;
    }
    return 0;
}

// 从一个“key=value"字符串中找出key和value并返回，若字符串不含“=”或含多个“=”则返回NULL,同时去除字符串后面的\n
char **format_kv(char *str)
{
    if (is_kv(str))
    {
        int i = strlen(str);
        while (str[i - 1] == '\n' || str[i - 1] == '\r')
        {
            str[i - 1] = '\0';
            i--;
        }
        char **key_value = (char **)malloc(2 * sizeof(char));
        key_value[0] = strtok(str, "=");
        key_value[1] = strtok(NULL, "=");
        return key_value;
    }
    return NULL;
}

// 输入一个key,查询一个key-value
char *query_ky(char *mykey)
{
    // 异常处理
    if (NULL == mykey || strlen(mykey) == 0)
    {
        printf("The length of the key must be greater than 1!\n");
        return NULL;
    }
    // 读取文件
    FILE *kv_file;
    kv_file = fopen(kv_filename, "r");
    if (kv_file == NULL)
    {
        printf("Error!Can't read %s\n", kv_filename);
        return NULL;
    }
    char buffer[4096];
    while (!feof(kv_file))
    {
        char *str;
        str = fgets(buffer, 4096, kv_file);
        char **key_value;
        // 将读取的每行转为key-value
        key_value = format_kv(str);
        if ((NULL != key_value) && (strcmp(key_value[0], mykey) == 0))
        {
            return key_value[1];
        }
    }
    fclose(kv_file);
    return NULL;
}

// 添加一个key-value
void add_kv(char *optarg)
{
    int len = strlen(optarg);
    char *str;
    str = (char *)malloc(len);
    strcpy(str, optarg);
    char **key_value;
    key_value = format_kv(str);
    if (key_value && !query_ky(key_value[0]))
    {
        FILE *kv_file = fopen(kv_filename, "a");
        fputs(key_value[0], kv_file);
        fputs("=", kv_file);
        fputs(key_value[1], kv_file);
        fputs("\n", kv_file);
        fclose(kv_file);
    }
    else
    {
        printf("\
Error!Key-value format is \"key=value\"!\n\
The key maybe has existed in the file!\n");
    }
    free(str);
    return;
}
// 更改一个key-value
void change_kv()
{
}
// 删除一个key-value
void del_kv()
{
}

// 返回帮助信息
void help()
{
    char help_str[] = " \
    -a add a key-value\n \
        key-value format is \"key=value\"\n \
    -c change a key-value\n \
        input a key-value which key has exsited in file,\n \
        then this action will update this key's value \n \
    -d delete a key-valu\n \
        input a key delete a value\n \
    -q query a key-value\n \
        input a key ,return this key's value\n \
    -h show help information\n";
    printf("%s", &help_str);
}
int main(int argc, char *argv[])
{
    int res;
    while ((res = getopt(argc, argv, "a:c:d:q:h")) != -1)
    {
        switch (res)
        {
            // add a key-value
        case 'a':
            add_kv(optarg);
            break;
            // change a key-value
        case 'c':
            break;
            // delete a key-value
        case 'd':
            break;
            // query a key-value
        case 'q':
            char *res;
            res = query_ky(optarg);
            if (res != NULL)
            {
                printf("%s=%s\n", optarg, res);
            }
            else
            {
                printf("Error!Can\'t find the value of key \"%s\"!\n", optarg);
            }
            break;
            // show help information
        case 'h':
            help();
            break;
        default:
            break;
        }
    }
    return 0;
}
