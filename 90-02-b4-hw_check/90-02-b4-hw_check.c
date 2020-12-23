/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "../include/common_mybase_tool_c.h"

const char* lst[][3] = { {"--help", NULL},
                        {"--firstline", NULL},
                        {"--fileformat", NULL},
                        {"--forbiddenkey", NULL},
                        {"--courseid", "number", NULL},
                        {"--filename", "string", NULL},
                        {NULL}
};
const char* type[] = { "Bool", "Bool", "Bool", "Bool", "String", "String", NULL };
const char* dft[] = { "false", "false", "false", "false", "/", "/", NULL };
const char* kinds[] = { "*.c", "*.cpp", "*.h", NULL };
const char* fstl_warning[] = { "首行信息不全", "首行信息过多", "未取到首行信息", "学号不匹配", "姓名不匹配", "班级不匹配", NULL };

int file_to_buf(char* buf, const char* const filename)
{
    FILE* fin;

    fin = fopen(filename, "rb"); //必须binary方式
    if (fin == NULL)
        return -1;

    char ch, * p = buf;
    while (1) {
        ch = fgetc(fin);
        if (feof(fin))
            break;
        *p++ = ch;
    }
    *p = '\0';
    fclose(fin);

    return strlen(buf); //返回字符串长度，在源程序文件不考虑含\0的情况下，就是文件的长度
}

void content_anylise(char(*infom)[20])
{
    printf("name           type                  default          exists value            range/set\n");
    printf("===================================================================================================================\n");
    int i = 0;
    while (lst[i][0]) {
        printf("%-15s", lst[i][0]);
        printf("%-22s", type[i]);
        printf("%-17s", dft[i]);
        printf("%-7d", (infom[i][0] != 0));
        if (i >= 0 && i <= 4)
            printf("%-17s", (infom[i][0] != 0 ? "true" : "/"));
        else
            printf("%-17s", (infom[i][0] != 0 ? infom[i] : "/"));
        printf("/\n");
        ++i;
    }
}

void usage()
{
    printf("\nUsage: 90-02-b3-hw_check-demo.exe.exe { --firstline | --fileformat | --forbiddenkey }\n");
    printf("                                      { --courseid cid }\n");
    printf("                                      { --filename name / all }\n");
    printf("                                      必选项：指定检查类型(多选一)\n");
    printf("                                        --firstline    : 首行检查\n");
    printf("                                        --fileformat   : 文件格式规范检查(不需要实现)\n");
    printf("                                        --forbiddenkey : 禁用关键字检查(不需要实现)\n");
    printf("                                      必选项：\n");
    printf("                                        --courseid     : 课号\n");
    printf("                                      必选项：\n");
    printf("                                        --filename     : 文件名(all表示全部)\n\n");
    printf("e.g.   90 - 02 - b3 - hw_check - demo.exe.exe --firstline --courseid 100718 --filename 3 - b1.cpp : 检查100718课程的3 - b1.cpp的首行\n");
    printf("       90 - 02 - b3 - hw_check - demo.exe.exe --firstline --courseid 100718 --filename all : 检查100718课程的全部文件的首行\n");
    printf("       90 - 02 - b3 - hw_check - demo.exe.exe --fileformat --courseid 100215 --filename all : 检查100215课程的全部文件的格式化\n");
}

int cmp(char(*a)[30], char(*b)[30]) {
    return strcmp(a[0], b[0]);
}

void pubble_sort(char(*st)[4][30], char(*ed)[4][30])
{
    char t[4][30];
    int i = 0;
    while (st + i < ed) {
        int j = 0;
        while (st + j <= ed) {
            if (cmp(*(st + i), *(st + j)) < 0) {
                int k = 0;
                while (k < 4) {
                    strcpy(t[k], *(*(st + i) + k));
                    strcpy(*(*(st + i) + k), *(*(st + j) + k));
                    strcpy(*(*(st + j) + k), t[k]);
                    ++k;
                }
            }
            ++j;
        }
        ++i;
    }
}

int check_file_kind(char* file_name)
{
    int n = strlen(file_name);
    int p = n - 1;
    while (file_name[p] != '.')
        --p;
    int i = 0;
    while (kinds[i]) {
        if (strcmp(kinds[i] + 1, file_name + p + 1) == 0)
            return 1;
        ++i;
    }
    return 0;
}

int find_id(char(*stu_lst)[4][30], char* courseid, char* filename)
{
    if (!str_in(courseid, filename))
        return -1;
    while (*filename != '-' && *filename)
        ++filename;
    ++filename;
    int i = 0;
    while (stu_lst[i][0][0]) {
        if (str_in(stu_lst[i][0], filename))
            return i;
        ++i;
    }
    return -1;
}

int check_line(const char* line)
{
    while (*line != '\r' && *line != '\n') {
        if (*line != ' ' && *line != '\t')
            return 0;
        ++line;
    }
    return 1;
}

void check_firstline(const char* ad, const char* name, char(*stu_lst)[4][30], const int id)
{//首行检查
    char In[5000];
    char* sin = In;
    file_to_buf(sin, ad);

    char a[5][50], ss[100];
    int tg[4];
    memset(a, 0, sizeof a);
    memset(ss, 0, sizeof ss);
    memset(tg, 0, sizeof tg);

    char b[200];
    sin += s_gets(sin, b);
    while (check_line(b))
        sin += s_gets(sin, b);
    int p = 0, len = 0;
    while (b[p] != '\r')
        ++p;
    len = p;
    p = 0;
    a[0][0] = b[p++];
    while (p < len && (a[0][0] == '\n' || a[0][0] == ' ' || a[0][0] == '\r' || a[0][0] == '\t'))
        a[0][0] = b[p++];
    while ((b[p] == ' ' || b[p] == '\t') && p < len)
        ++p;
    if (p >= len || a[0][0] != '/') {
        printf("%s\n", fstl_warning[2]);
        return;
    }
    else {
        a[0][1] = b[p++];
        while ((b[p] == ' ' || b[p] == '\t') && p < len)
            ++p;
        if (a[0][1] != '*' && a[0][1] != '/') {
            printf("%s\n", fstl_warning[2]);
            return;
        }
    }

    int i = 1;
    while (i < 4 && p <= len) {
        int j = 0;
        while (b[p] != ' ' && p <= len && b[p] != '\r' && b[p] != '\t')
            a[i][j] = b[p++], ++j;
        a[i][j] = 0;
        while ((b[p] == ' ' || b[p] == '\t') && p < len)
            ++p;
        if (j >= len || a[i][0] == '*' || a[i][0] == '#') {
            printf("%s\n", fstl_warning[0]);
            return;
        }
        ++i;
    }

    int n = strlen(a[3]);
    if (a[3][n - 1] == '/' && a[3][n - 2] == '*')
        a[3][n - 2] = 0, a[4][0] = '*', a[4][1] = '/', a[4][2] = 0;
    else {
        //sin >> a[4];
        int i = 0;
        while (b[p] != ' ' && b[p] != '\r' && p <= len && b[p] != '\t')
            a[4][i] = b[p++], ++i;
        a[4][i] = 0;
    }

    if (strcmp(a[0], "//") == 0 && a[4][0]) {
        printf("%s\n", fstl_warning[1]);
        return;
    }

    if ((strcmp(a[0], "/*") == 0 && strcmp(a[4], "*/")) || (strcmp(a[0], "/*") && a[4][0])) {
        printf("%s\n", fstl_warning[2]);
        return;
    }

    if (!a[1][0] || !a[2][0] || !a[3][0]) {
        printf("%s\n", fstl_warning[0]);
        return;
    }

    i = 1;
    while (i < 4) {
        int j = 0;
        while (j < 4) {
            if (strcmp(a[i], stu_lst[id][j]) == 0)
                tg[j] = 1;
            ++j;
        }
        ++i;
    }
    if (!tg[0] || !tg[1] || (!tg[3] && !tg[2])) {
        if (!tg[0])
            printf("%s ", fstl_warning[3]);
        if (!tg[1])
            printf("%s ", fstl_warning[4]);
        if (!tg[3] && !tg[2])
            printf("%s ", fstl_warning[5]);
        putchar(10);
    }
    else
        puts("通过");
}

void check_subdir(char* ad, const char* order, char(*stu_lst)[4][30], const int id)
{
    DIR* dir = opendir(ad);
    chdir(ad);

    struct dirent* entry;
    int tg = 0;
    int all = (strcmp("all", order) == 0);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (all || strcmp(entry->d_name, order) == 0) {
            struct stat st;
            stat(entry->d_name, &st);
            if (S_ISDIR(st.st_mode))
                continue;
            else {
                printf("%s-%s-%s : ", stu_lst[id][0], stu_lst[id][1], stu_lst[id][2]);
                printf("%s : ", entry->d_name);
                tg = 1;
                check_firstline(entry->d_name, ad, stu_lst, id);
            }
        }
    }

    if (!tg) {
        printf("%s-%s-%s : ", stu_lst[id][0], stu_lst[id][1], stu_lst[id][2]);
        printf("%s : ", order);
        puts("未提交");
    }

    closedir(dir);
    chdir("..");
}

int main(int argc, char* argv[])
{
    char infom[6][20];
    memset(infom, 0, sizeof infom);
    if (argc < 4 || !check_lst(argc, argv, lst, type, infom, NULL) || (infom[1][0] != 0) + (infom[2][0] != 0) + (infom[3][0] != 0) != 1) {
        content_anylise(infom);
        if (infom[0][0] || (!infom[4][0] && !infom[5][0]))
            usage();
        if ((infom[1][0] != 0) + (infom[2][0] != 0) + (infom[3][0] != 0) != 1)
            printf("参数[--firstline | --fileformat | --forbiddenkey]必须指定一个且只能指定一个\n");
        return 0;
    }

    if (infom[0][0]) {
        usage();
        return 0;
    }
    if (infom[2][0]) {
        printf("文件格式检查未实现\n");
        return 0;
    }
    if (infom[3][0]) {
        printf("关键词禁用检查未实现\n");
        return 0;
    }

    char address[50] = "./source";

    if (chdir("./source") != 0) {
        printf("源文件错误\n");
        return -1;
    }

    char In[5000];
    char* sin = In;
    char lst_name[20];
    strcpy(lst_name, infom[4]);
    file_to_buf(sin, str_aft_str(lst_name, ".dat"));
    int stu_num = 0;
    char stu_lst[500][4][30];
    memset(stu_lst, 0, sizeof stu_lst);
    int rt = 1;
    while (sin && *sin) {
        int j = 0;
        while (j < 4) {
            sin += (rt = s_getstr(sin, stu_lst[stu_num][j]));
            ++j;
        }
        ++stu_num;
    }
    --stu_num;
    chdir("..");
    pubble_sort(stu_lst, stu_lst + stu_num);

    int all = (strcmp(infom[5], "all") == 0);
    int i = 0;
    while (i < stu_num) {
        DIR* dir = opendir("./source");
        struct dirent* entry;
        int tg = 0;
        strcpy(address, "./");
        chdir("./source");
        while ((entry = readdir(dir)) != NULL) {
            int id = find_id(stu_lst, infom[4], entry->d_name);
            if (id != i)
                continue;
            struct stat st;
            stat(entry->d_name, &st);
            if (S_ISDIR(st.st_mode)) {
                tg = 1;
                check_subdir(str_aft_str(address, entry->d_name), infom[5], stu_lst, id);
                break;
            }
        }
        if (!tg && !all)
            printf("%s-%s-%s : %s : 未提交\n", stu_lst[i][0], stu_lst[i][1], stu_lst[i][2], infom[5]);
        if (all)
            putchar(10);
        chdir("..");
        ++i;
    }

    return 0;
}
