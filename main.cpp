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
    for (size_t i = 0; i < strlen(kv); i++)
    {
        if (kv[i] == '=')
        {
            num++;
        }
    }
    if (num == 1)
    {
        return 1;
    }
    return 0;
}

// 从一个“key=value"字符串中找出key和value并返回，若字符串不含“=”或含多个“=”则返回NULL,同时去除字符串后面的\n
char **format_kv(char *str)
{
    int i = strlen(str);
    while (str[i - 1] == '\n')
    {
        str[i] = 0;
        i--;
    }
    if (is_kv(str))
    {
        char **key_value = (char **)malloc(2 * sizeof(char));
        key_value[0] = strtok(str, "=");
        key_value[1] = strtok(NULL, "=");
        return key_value;
    }
    return NULL;
}

// 添加一个key-value
void add_kv(char *optarg)
{
    // printf("optarg:%s\n", optarg);
    // printf("is_kv:%d\n", is_kv(optarg));
    if (is_kv(optarg))
    {
        FILE *kv_file = fopen(kv_filename, "a");
        fputs(optarg, kv_file);
        fputs("\n", kv_file);
        fclose(kv_file);
    }
    else
    {
        printf("Error!Key-value format is \"key=value\"!\n");
    }
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
// 输入一个key,查询一个key-value
void query_ky(char *key)
{
    FILE *kv_file;
    if (kv_file = fopen(kv_filename, "r"))
    {
        printf("Error!Can't read %s\n", kv_filename);
        return;
    }
    char buffer[4096];
    while (!feof(kv_file))
    {
        fgets(buffer, 4096, kv_file);
    }
    fclose(kv_file);
}
// 返回帮助信息
void help()
{
    char help_str[] = " \
    -a add a key-value\n \
        key-value format is \"key=value\"\
    -c change a key-value\n \
        input a key-value which key has exsited in file,\
        then this action will update this key's value \
    -d delete a key-valu\n \
        input a key delete a value\
    -q query a key-value\n \
        input a key ,return this key's value\
    -h show help information\n";
    printf("%s", &help_str);
}
int main(int argc, char *argv[])
{
    int res;
    while ((res = getopt(argc, argv, "a:c:d:f:q:h")) != -1)
    {
        switch (res)
        {
            // add a key-value
        case 'a':
            add_kv(optarg);
            break;
        case 'h':
            help();
            break;
        default:
            break;
        }
    }
    return 0;
}
