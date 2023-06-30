#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
            str[i - 1] = 0;
            i--;
        }
        while (str[0] == 0)
        {
            int len = strlen(str);
            for (size_t i = 0; i < len; i++)
            {
                str[i] = str[i + 1];
            }
            str[len - 1] = 0;
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
        char *str = fgets(buffer, 4096, kv_file);
        char **key_value = format_kv(str);
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
    if (key_value)
    {
        if (!query_ky(key_value[0]))
        {
            FILE *kv_file = fopen(kv_filename, "a");
            fputs(key_value[0], kv_file);
            fputs("=", kv_file);
            fputs(key_value[1], kv_file);
            fputs("\n", kv_file);
            fclose(kv_file);
            printf("Add key-value success!\n");
        }
        else
        {
            printf("The key maybe has existed in the file!\n");
        }
    }
    else
    {
        printf("Error!Key-value format is \"key=value\"!\n");
    }
    free(str);
    return;
}
// 删除一个key-value
void del_kv(char *key)
{
    char *value = query_ky(key);

    if (value == NULL)
    {
        printf("Error! The key is not existed!\n");
        return;
    }
    else
    {
        printf("%s=%s\n", key, value);
    }

    int len = strlen(kv_filename);
    char *tmp_filename = (char *)malloc(len + 4);
    strcpy(tmp_filename, kv_filename);
    strcat(tmp_filename, ".tmp");
    FILE *kv_file = fopen(kv_filename, "r");
    FILE *tmp_file = fopen(tmp_filename, "w");

    if (kv_file == NULL)
    {
        printf("Error! Can\'t open %s!", kv_filename);
        return;
    }
    if (tmp_file == NULL)
    {
        printf("Error! Can\'t open %s!", tmp_filename);
        return;
    }
    char buffer[4096];
    while (!feof(kv_file))
    {
        char *str = fgets(buffer, 4096, kv_file);
        if (NULL == str)
        {
            break;
        }
        int len = strlen(str);
        char *tmp_str = (char *)malloc(len);
        strcpy(tmp_str, str);
        char **key_value = format_kv(tmp_str);

        if (key_value != NULL && strcmp(key, key_value[0]) != 0)
        {

            fputs(str, tmp_file);
        }
        free(tmp_str);
    }
    fclose(tmp_file);
    fclose(kv_file);
    remove(kv_filename);
    rename(tmp_filename, kv_filename);
    free(tmp_filename);

    printf("Delete success!\n");
}

// 返回帮助信息
void help()
{
    char help_str[] = "\
    -a add a key-value\n\
        key-value format is \"key=value\"\n\
    -c enter the cmd mode\n\
        \"add key=value\" add a key-value pair\n\
        \"query key\" query a key-value pari\n\
        \"del key\" delete a key-value\n\
        \"exit\" exit the cmd mode\n\
    -d delete a key-valu\n \
        input a key delete a value\n\
    -q query a key-value\n\
        input a key ,return this key's value\n\
    -h show help information\n";
    printf("%s", &help_str);
}

void cmd_mode()
{
    char *line;
    while ((line = readline("kv_operate >")) != NULL)
    {
        if (strcmp(line, "exit") == 0)
        {
            break;
        }
        if (strstr(line, "add") == line)
        {
            strtok(line, " ");
            char *kv_str = strtok(NULL, " ");
            add_kv(kv_str);
        }
        else if (strstr(line, "del") == line)
        {
            strtok(line, " ");
            char *kv_str = strtok(NULL, " ");
            del_kv(kv_str);
        }
        else if (strstr(line, "query") == line)
        {
            strtok(line, " ");
            char *key = strtok(NULL, " ");
            char *res = query_ky(key);
            if (res != NULL)
            {
                printf("%s=%s\n", key, res);
            }
            else
            {
                printf("Error!Can\'t find the value of key \"%s\"!\n", key);
            }
        }
        else if (strstr(line, "help") == line)
        {
            help();
        }
        else
        {
            printf("Unkonw command!Please use \"help\" check help info!\n");
        }
        add_history(line);
        free(line);
    }
}
int main(int argc, char *argv[])
{
    int res;
    while ((res = getopt(argc, argv, "a:cd:q:h")) != -1)
    {
        switch (res)
        {
            // add a key-value
        case 'a':
            add_kv(optarg);
            break;
            // change a key-value
        case 'd':
            del_kv(optarg);
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
        case 'c':
            cmd_mode();
            break;
        }
    }
    return 0;
}
