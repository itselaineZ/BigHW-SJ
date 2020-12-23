#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int get_next_num(const bool new_seed, const unsigned int seed)
{
    if (new_seed)
        srand(seed);

    return rand() % 10;
}

int main()
{
    int i;

    /* ����10����������Ե�ǰʱ��Ϊ���ӣ� */
    cout << get_next_num(true, (unsigned int)time(0)) << ' ';
    for (i=1; i<10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    Sleep(1000);//��ʱ1�룬��֤��һ��time(0)��ͬ

    /* ����10����������Ե�ǰʱ��Ϊ���ӣ� */
    cout << get_next_num(true, (unsigned int)time(0)) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    /* ����10�����������12345Ϊ���ӣ� */
    cout << get_next_num(true, 12345) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    /* ����10�����������12345Ϊ���ӣ�- �͵������10��һ�� - ˵����ֻҪ���Ӳ��䣬α��������оͲ��� */
    cout << get_next_num(true, 12345) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    return 0;
}
