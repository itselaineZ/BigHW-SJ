/*1952339 ��08 ��ܰ��*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<time.h>
#pragma comment(lib,"winmm.lib")
#define md5 a0be1a9cda7af2ce0052f7437766c61b
#include"../include/cmd_console_tools.h"
using namespace std;

void cct_setconsolefont(const int font_no);

static void to_be_continued()
{
	cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;
	cout << endl;

	return;
}

int mouse_rt()
{
	int X = 0, Y = 0;
	int loop = 1;
	int ret, maction;
	int keycode1, keycode2;

	cct_enable_mouse();

	while (loop) {
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
			if (Y == 8) {

				cct_disable_mouse();
				return 1;
			}
			else if (Y == 10) {

				cct_disable_mouse();
				return 2;
			}
			else if (Y == 12) {

				cct_disable_mouse();
				return 3;
			}
		}
	}
	return -1;
}

int main()
{
	int ans[10];

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setfontsize("������", 36, 18);
	cct_setconsoleborder(55, 15);
	cct_setcolor(7, 5);
	cct_cls();
	cct_gotoxy(0, 6);
	cout << "����\"����\"�˵� - \"ѡ��\"��Ƭ�н������²�����";
	cct_gotoxy(0, 7);
	cout << "    ѡ��\"ʹ�þɰ����̨\"";
	cct_gotoxy(0, 8);
	cout << "    ȡ��\"���ٱ༭ģʽ\"";
	cct_gotoxy(0, 9);
	cout << "    ȡ��\"����ģʽ\"";
	cct_gotoxy(0, 14);
	to_be_continued();

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(18, 6);
		cout << "�˸�(CV��)����";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����.wav"), NULL, SND_SYNC|SND_FILENAME);
		cct_gotoxy(5, 12);
		cout << "����������Ϊ���߱���α��,�������֣���ӭ�²��Ա�:)";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����.wav"), NULL, SND_SYNC | SND_FILENAME);
		
		cct_gotoxy(0, 14);
		to_be_continued();
	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "������һ����������پٳ��ܶ����ӣ�";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��1.wav"), NULL, SND_SYNC | SND_FILENAME);


		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\1��.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(2, 8);
		cout << "A.������ֵ�����";
		Sleep(3000);
		cct_gotoxy(16, 10);
		cout << "B.�����Ķ�������";
		Sleep(3000);
		cct_gotoxy(32, 12);
		cout << "C.����־������";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[1] = mouse_rt();

	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 9);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "�ھۻ��У��кÿ��������´����㣬��᣿";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��2.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		cct_gotoxy(2, 8);
		cout << "A.�е㺦�ߣ��ر�����";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2A.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_gotoxy(16, 10);
		cout << "B.Ѹ���߿����������";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2B.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_gotoxy(28, 12);
		cout << "C.������ȥ��������Į����";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2C.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_setcolor(7, 5);
		
		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[2] = mouse_rt();

	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 4);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "����Ϊ�Լ���ͬʱϲ����������";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��3.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\3��.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(8, 8);
		cout << "A.����";
		Sleep(2000);
		cct_gotoxy(24, 10);
		cout << "B.�п���";
		Sleep(2000);
		cct_gotoxy(40, 12);
		cout << "C.��";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[3] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 2);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "�������ֱ仯������·������Լ����ϣ�";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��4.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\4��.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(2, 8);
		cout << "A.��õ��ӣ����ٹ����¸�";
		Sleep(4000);
		cct_gotoxy(16, 10);
		cout << "B.�����ľ�����������±���";
		Sleep(4500);
		cct_gotoxy(24, 12);
		cout << "C.��ù�����ʧȥ�����������";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[4] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "����Ϊ���˷��ֺ󣬻�������������";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��5.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\5��.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(14, 8);
		cout << "A.���ԣ���̸���飬�ദ�ø���";
		Sleep(5500);
		cct_gotoxy(14, 10);
		cout << "B.�����ԣ��˴�̫��Ϥ�������ѻ�����";
		Sleep(5500);
		cct_gotoxy(14, 12);
		cout << "C.������������ʵ����������ᾭ����ϵ";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[5] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 6);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "����ô�����˳����ԭ���ǣ�";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��6.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\6��.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(6, 8);
		cout << "A.�ǰ����";
		Sleep(2000);
		cct_gotoxy(24, 10);
		cout << "B.Ѱ��̼�";
		Sleep(2000);
		cct_gotoxy(40, 12);
		cout << "C.����į";
		Sleep(2000);
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[6] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("������", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 1);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "��������ǣ�(����һ����Ա��ǣ�)";
		cct_gotoxy(10, 7); 
		cout << "(�������get����һ����˸���ô�뷴��ѡ��)";

		cct_setcolor(14, 1);
		cct_gotoxy(8, 8);
		cout << "A.����";
		cct_gotoxy(24, 10);
		cout << "B.Ů��";
		cct_gotoxy(40, 12);
		cout << "C.˫����";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "����������˫����Ӧѡ��";
		ans[7] = mouse_rt();
	}

	int score = 0;
	for (int i = 1; i <= 6; ++i)
		score += ans[i];

	if (ans[7] == 3)
		ans[7] = 1;

	cct_setfontsize("������", 36, 18);
	cct_setconsoleborder(55, 15);
	cct_setcolor(7, 5);
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "���Խ��Ϊ��";
	cct_gotoxy(0, 5);
	cout << "�˸�CV��";
	cct_gotoxy(10, 2);

	if (ans[7] == 1) {//Ů���˸�
		if (score <= 8) {
			cout << "����";
			cct_gotoxy(10, 7);
			cout << "��ϲ�����ˣ�����һ������Ӣ��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "����һֱ���������Ҳ��볤��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "���....Ҫ����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-3-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-3-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 12) {
			cout << "��Ů";
			cct_gotoxy(10, 7);
			cout << "ΪʲôҪʹ���أ�һֱ΢Ц�ͺ���";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��Ů-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "ÿһ�춼ҪԪ���������㣬׼���ú���һ�������ս����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��Ů-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 15) {
			cout << "����";
			cct_gotoxy(10, 7);
			cout << "����˵����ɽ�Ƿ����ģ����迴��ɽ��˭";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "����ҡͷ���Ҽ������Բ�ľ��Ψ�㣬����ɽ��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "�����㣬��ʹ���ѣ����������ҡ���֮����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else {
			cout << "����";
			cct_gotoxy(10, 7);
			cout << "���Ǹ������ǵ������ӿ��أ����ǣ�������ֹͣ��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "���ǵļ�ֵ�Ѿ���ե����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "Ŷ��������ͼ�ֿ����𣿿������ǲ���������";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
	}
	else {//�����˸�
		if (score <= 8) {
			cout << "��̫";
			cct_gotoxy(10, 7);
			cout << "��㲻�õ����ң��һ��չ˺��Լ���";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��̫-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "��Ĳ����ң�������";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��̫-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "��һ�꣬һ���£�һ�죬һ��ʱ����������һ����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\��̫-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 12) {
			cout << "����";
			cct_gotoxy(10, 7);
			cout << "С�����ţ�δ�ù����������Ź������ã�����Ī��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "�Դ�������Ľ֮��ֹ�ڴ��ݣ������껪�������ʹ˱��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 15) {
			cout << "�๥";
			cct_gotoxy(10, 7);
			cout << "����ƫ���㣬�ҵ��Ƕ�����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\�๥-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "�����𵶣��Ͳ���ӵ���㣬�ҷ��µ����Ͳ��ܱ�����";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\�๥-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "�����Ϊ�������ģ���Ϊ��Ŀ�������Ϊ��ĸɾ���ˮ";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\�๥-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else {
			cout << "����";
			cct_gotoxy(10, 7);
			cout << "�Ծ����ӽ���������Ϊ��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "Ը�������е��Ȱ����Ա���";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "Ը�����Ȱ�����������Ϩ��";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\����-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
	}
	return 0;
}