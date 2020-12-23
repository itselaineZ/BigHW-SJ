/*1952339 信08 张馨月*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <io.h>
#include <direct.h>
#include "../include/common_mybase_tool.h"
using namespace std;

const char* lst[][3] = { {"--help", NULL},
                        {"--firstline", NULL}, 
                        {"--fileformat", NULL}, 
                        {"--forbiddenkey", NULL}, 
                        {"--courseid", "number", NULL}, 
                        {"--filename", "string", NULL}, 
                        {NULL}
                        };
const char* type[] = {"Bool", "Bool", "Bool", "Bool", "String", "String", NULL};
const char* dft[] = {"false", "false", "false", "false", "/", "/", NULL};
const char* kinds[] = {"*.c", "*.cpp", "*.h", NULL};
const char* fstl_warning[] = {"首行信息不全", "首行信息过多", "未取到首行信息", "学号不匹配", "姓名不匹配", "班级不匹配", NULL};

int file_to_sstream(stringstream& sin, const char* const filename)
{
    ifstream fin(filename, ios::out | ios::binary); //必须binary方式
    if (fin.is_open() == 0)
        return -1;

    char ch;
    while (1) {
        fin.get(ch);
        if (fin.eof())
            break;
        sin << (unsigned char)ch;
    }
    fin.close();

    return 0;
}

void content_anylise(char (*infom)[20])
{
    cout << "name           type                  default          exists value            range/set\n";
    cout << "===================================================================================================================\n";
    for (int i = 0; lst[i][0]; ++i) {
        cout << setw(15) << setiosflags(ios::left) << lst[i][0];
        cout << setw(22) << type[i];
        cout << setw(17) << dft[i];
        cout << setw(7) << (infom[i][0] != 0);
        if(i >= 0 && i <= 4)
            cout << setw(17) << (infom[i][0] != 0 ? "true" : "/");
        else
            cout << setw(17) << (infom[i][0] != 0 ? infom[i] : "/");
        cout<< "/\n";
    }
 }

void usage()
{
    cout << "\nUsage: 90-02-b3-hw_check-demo.exe.exe { --firstline | --fileformat | --forbiddenkey }\n";
    cout << "                                      { --courseid cid }\n";
    cout << "                                      { --filename name / all }\n";
    cout << "                                      必选项：指定检查类型(多选一)\n";
    cout << "                                        --firstline    : 首行检查\n";
    cout << "                                        --fileformat   : 文件格式规范检查(不需要实现)\n";
    cout << "                                        --forbiddenkey : 禁用关键字检查(不需要实现)\n";
    cout << "                                      必选项：\n";
    cout << "                                        --courseid     : 课号\n";
    cout << "                                      必选项：\n";
    cout << "                                        --filename     : 文件名(all表示全部)\n\n";
    cout << "e.g.   90 - 02 - b4 - hw_check.exe --firstline --courseid 100718 --filename 3 - b1.cpp : 检查100718课程的3 - b1.cpp的首行\n";
    cout << "       90 - 02 - b4 - hw_check.exe --firstline --courseid 100718 --filename all : 检查100718课程的全部文件的首行\n";
    cout << "       90 - 02 - b4 - hw_check.exe --fileformat --courseid 100215 --filename all : 检查100215课程的全部文件的格式化\n";
}

int cmp(const char (*a)[30], const char(*b)[30]) {
    return strcmp(a[0], b[0]);
}

void pubble_sort(char (*st)[4][30], char (*ed)[4][30])
{
    char t[4][30];
    for(int i = 0; st + i < ed; ++ i)
        for(int j = 0; st + j <= ed; ++ j)
            if (cmp(*(st + i), *(st + j)) < 0)
                for (int k = 0; k < 4; ++k) {
                    strcpy_s(t[k], *(*(st+i)+k));
                    strcpy_s(*(*(st+i)+k), *(*(st+j)+k));
                    strcpy_s(*(*(st+j)+k), t[k]);
                }
}

bool check_file_kind(char *file_name)
{
    int n = strlen(file_name);
    int p;
    for (p = n - 1; file_name[p] != '.'; --p)
        ;
    for (int i = 0; kinds[i]; ++i)
        if (strcmp(kinds[i] + 1, file_name + p + 1) == 0)
            return 1;
    return 0;
}

int find_id(const char(*stu_lst)[4][30], char* courseid, char* filename)
{
    if (!str_in(courseid, filename))
        return -1;
    for (; *filename != '-' && *filename; ++filename)
        ;
    ++filename;
    for (int i = 0; stu_lst[i][0][0]; ++i)
        if (str_in(stu_lst[i][0], filename))
            return i;
    return -1;
}

bool check_line(const char *line)
{
    for (; *line != '\r' && *line != '\n'; ++line)
        if (*line != ' ' && *line != '\t')
            return 0;
    return 1;
}

void check_firstline(const char* ad, const char* name, const char(*stu_lst)[4][30], const int id)
{//首行检查

    stringstream sin;
    file_to_sstream(sin, ad);

    char a[5][50] = { 0 }, ss[100] = {0};
    bool tg[4] = { 0 };
    
    char b[200];
    sin.getline(b, 200, '\n');
    while (check_line(b))
        sin.getline(b, 200, '\n');
    int p = 0, len = 0;
    for (p = 0; b[p] != '\r'; ++p)
        ;
    len = p;
    p = 0;
    a[0][0] = b[p++];
    while (p < len && (a[0][0] == '\n' || a[0][0] == ' ' || a[0][0] == '\r' || a[0][0] == '\t'))
        a[0][0] = b[p++];
    while ((b[p] == ' ' || b[p] == '\t') && p < len)
        ++p;
    if (p >= len || a[0][0] != '/') {
        cout << fstl_warning[2] << '\n';
        return;
    }
    else {
        a[0][1] = b[p++];
        while ((b[p] == ' ' || b[p] == '\t') && p < len)
            ++p;
        if (a[0][1] != '*' && a[0][1] != '/') {
            cout << fstl_warning[2] << '\n';
            return;
        }
    }

    for (int i = 1; i < 4 && p <= len; ++i) {
        int j;
        for (j = 0; b[p] != ' ' && p <= len && b[p] != '\r' && b[p] != '\t'; ++j)
            a[i][j] = b[p++];
        a[i][j] = 0;
        while ((b[p] == ' ' || b[p] == '\t') && p < len)
            ++p;
        if (j >= len || a[i][0] == '*' || a[i][0] == '#') {
            cout << fstl_warning[0] << '\n';
            return;
        }
    }
    
    /*
    sin >> a[0][0];
    while (sin.good() && (a[0][0] == '\n' || a[0][0] == ' ' || a[0][0] == '\r'))
        sin >> a[0][0];
    if (!sin.good() || a[0][0] != '/') {
        cout << fstl_warning[2] << '\n';
        return;
    }
    else {
        sin >> a[0][1];
        if (a[0][1] != '*' && a[0][1] != '/') {
            cout << fstl_warning[2] << '\n';
            return;
        }
    }

    int delta = 0;
    for (int i = 1; i < 4; ++i) {
        sin >> a[i] + delta;
        if (!sin.good() || a[i][0] == '*' || a[i][0] == '#') {
            cout << fstl_warning[0] << '\n';
            return;
        }
    }*/

    int n = strlen(a[3]);
    if (a[3][n - 1] == '/' && a[3][n - 2] == '*')
        a[3][n - 2] = 0, a[4][0] = '*', a[4][1] = '/', a[4][2] = 0;
    else {
        //sin >> a[4];
        int i;
        for (i = 0; b[p] != ' ' && b[p] != '\r' && p <= len && b[p] != '\t'; ++i)
            a[4][i] = b[p++];
        a[4][i] = 0;
    }
    
    if (strcmp(a[0], "//") == 0 && a[4][0]) {
        cout << fstl_warning[1] << '\n';
        return;
    }
    
    if ((strcmp(a[0], "/*") == 0 && strcmp(a[4], "*/")) || (strcmp(a[0], "/*") && a[4][0])) {
        cout << fstl_warning[2] << '\n';
        return;
    }

    if (!a[1][0] || !a[2][0] || !a[3][0]) {
        cout << fstl_warning[0] << '\n';
        return;
    }

    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            if (strcmp(a[i], stu_lst[id][j]) == 0)
                tg[j] = 1;
    }
    if (!tg[0] || !tg[1] || (!tg[3] && !tg[2])) {
        if (!tg[0])
            cout << fstl_warning[3] << ' ';
        if (!tg[1])
            cout << fstl_warning[4] << ' ';
        if (!tg[3] && !tg[2])
            cout << fstl_warning[5] << ' ';
        putchar(10);
    }
    else
        cout << "通过\n";
}

void check_subdir(char* ad, const char* order, const char (*stu_lst)[4][30], const int id)
{
    int t = _chdir(ad);

    long int HANDLE, k;
    bool tg = 0;
    _finddata_t file;
    bool all = (strcmp("all", order) == 0);

    for (int i = 0; kinds[i]; ++i) {
        k = HANDLE = _findfirst(kinds[i], &file);
        while (k != -1) {
            if (all || strcmp(file.name, order) == 0) {
                cout << stu_lst[id][0] << '-' << stu_lst[id][1] << '-' << stu_lst[id][2] << " : ";
                cout << file.name << " : ";
                tg = 1;
                check_firstline(file.name, ad, stu_lst, id);
            }
            k = _findnext(HANDLE, &file);
        }
    }

    if (!tg) {
        cout << stu_lst[id][0] << '-' << stu_lst[id][1] << '-' << stu_lst[id][2] << " : ";
        cout << order << " : ";
        cout << "未提交\n";
    }

    _chdir("../");
}

int main(int argc, char *argv[])
{
    char infom[6][20] = {0};
    if (argc < 4 || !check_lst(argc, argv, lst, type, infom) || (infom[1][0] != 0) + (infom[2][0] != 0) + (infom[3][0] != 0) != 1) {
        content_anylise(infom);
        if(infom[0][0]||(!infom[4][0] && !infom[5][0]))
            usage();
        if ((infom[1][0] != 0) + (infom[2][0] != 0) + (infom[3][0] != 0) != 1)
            cout << "参数[--firstline | --fileformat | --forbiddenkey]必须指定一个且只能指定一个\n";
        return 0;
    }

    if (infom[0][0]) {
        usage();
        return 0;
    }
    if (infom[2][0]) {
        cout << "文件格式检查未实现\n";
        return 0;
    }
    if (infom[3][0]) {
        cout << "关键词禁用检查未实现\n";
        return 0;
    }

    char address[50] = "./source";
    
    if (_chdir("./source") != 0) {
        cout << "源文件错误\n";
        return -1;
    }

    stringstream sin;
    char lst_name[20];
    strcpy_s(lst_name, infom[4]);
    file_to_sstream(sin, str_aft(lst_name, ".dat"));
    int stu_num;
    char stu_lst[100][4][30] = {0};
    for (stu_num = 0; sin.good(); ++ stu_num)
        for (int j = 0; j < 4; ++j)
            sin >> stu_lst[stu_num][j];
    --stu_num;
    pubble_sort(stu_lst, stu_lst+stu_num);

    _finddata_t file;
    long int HANDLE, k;
    bool all = (strcmp(infom[5], "all") == 0);

    for (int i = 0; i < stu_num; ++i) {
        k = HANDLE = _findfirst("*.*", &file);
        strcpy_s(address, "./");
        bool tg = 0;
        while (k != -1ll) {
            int id = find_id(stu_lst, infom[4], file.name);
            if (file.attrib & _A_SUBDIR && id == i) {
                tg = 1;
                check_subdir(str_aft(address, file.name), infom[5], stu_lst, id);
                break;
            }
            k = _findnext(HANDLE, &file);
        }
        if (!tg && !all)
            cout << stu_lst[i][0] << '-' << stu_lst[i][1] << '-' << stu_lst[i][2] << " : " << infom[5] << " : 未提交\n";
        if (all)
            putchar(10);
    }

	return 0;
}