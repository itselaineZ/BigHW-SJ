/*1952339 信08 张馨月*/
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
	cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
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
	cct_setfontsize("新宋体", 36, 18);
	cct_setconsoleborder(55, 15);
	cct_setcolor(7, 5);
	cct_cls();
	cct_gotoxy(0, 6);
	cout << "请在\"属性\"菜单 - \"选项\"卡片中进行如下操作：";
	cct_gotoxy(0, 7);
	cout << "    选择\"使用旧版控制台\"";
	cct_gotoxy(0, 8);
	cout << "    取消\"快速编辑模式\"";
	cct_gotoxy(0, 9);
	cout << "    取消\"插入模式\"";
	cct_gotoxy(0, 14);
	to_be_continued();

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(18, 6);
		cout << "人格(CV向)测试";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\标题.wav"), NULL, SND_SYNC|SND_FILENAME);
		cct_gotoxy(5, 12);
		cout << "所有语音均为作者本人伪声,仅供娱乐，欢迎猜测性别:)";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\开场.wav"), NULL, SND_SYNC | SND_FILENAME);
		
		cct_gotoxy(0, 14);
		to_be_continued();
	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "以下哪一项能让你快速举出很多例子？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题1.wav"), NULL, SND_SYNC | SND_FILENAME);


		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\1答案.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(2, 8);
		cout << "A.令你快乐的事物";
		Sleep(3000);
		cct_gotoxy(16, 10);
		cout << "B.令你心动的事物";
		Sleep(3000);
		cct_gotoxy(32, 12);
		cout << "C.令你恐惧的事物";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[1] = mouse_rt();

	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 9);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "在聚会中，有好看的人上下打量你，你会？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题2.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		cct_gotoxy(2, 8);
		cout << "A.有点害羞，回避眼神";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2A.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_gotoxy(16, 10);
		cout << "B.迅速走开，不予理会";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2B.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_gotoxy(28, 12);
		cout << "C.打量回去，并附冷漠眼神";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\2C.wav"), NULL, SND_SYNC | SND_FILENAME);
		cct_setcolor(7, 5);
		
		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[2] = mouse_rt();

	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 4);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "你认为自己会同时喜欢两个人吗？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题3.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\3答案.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(8, 8);
		cout << "A.不会";
		Sleep(2000);
		cct_gotoxy(24, 10);
		cout << "B.有可能";
		Sleep(2000);
		cct_gotoxy(40, 12);
		cout << "C.会";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[3] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 2);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "以下哪种变化，你最害怕发生在自己身上？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题4.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\4答案.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(2, 8);
		cout << "A.变得胆怯，不再果断勇敢";
		Sleep(4000);
		cct_gotoxy(16, 10);
		cout << "B.变得麻木，不再能体谅别人";
		Sleep(4500);
		cct_gotoxy(24, 12);
		cout << "C.变得功利，失去对生活的热情";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[4] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 5);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "你认为恋人分手后，还可以做朋友吗？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题5.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\5答案.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(14, 8);
		cout << "A.可以，不谈感情，相处得更好";
		Sleep(5500);
		cct_gotoxy(14, 10);
		cout << "B.不可以，彼此太熟悉，做朋友会尴尬";
		Sleep(5500);
		cct_gotoxy(14, 12);
		cout << "C.看情况，可以适当帮助，不会经常联系";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[5] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 6);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "你觉得大多数人出轨的原因是？";
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\题6.wav"), NULL, SND_SYNC | SND_FILENAME);

		cct_setcolor(14, 1);
		PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\6答案.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cct_gotoxy(6, 8);
		cout << "A.是爱情吧";
		Sleep(2000);
		cct_gotoxy(24, 10);
		cout << "B.寻求刺激";
		Sleep(2000);
		cct_gotoxy(40, 12);
		cout << "C.灵魂寂寞";
		Sleep(2000);
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[6] = mouse_rt();
	}

	if (1) {
		cct_setfontsize("新宋体", 36, 18);
		cct_setconsoleborder(55, 15);
		cct_setcolor(7, 1);
		cct_cls();
		cct_gotoxy(10, 6);
		cout << "你的性向是？(你另一半的性别是？)";
		cct_gotoxy(10, 7); 
		cout << "(如果你想get到另一半的人格，那么请反向选择)";

		cct_setcolor(14, 1);
		cct_gotoxy(8, 8);
		cout << "A.男生";
		cct_gotoxy(24, 10);
		cout << "B.女生";
		cct_gotoxy(40, 12);
		cout << "C.双性向";
		cct_setcolor(7, 5);

		cct_gotoxy(0, 14);
		cout << "请用鼠标左键双击相应选项";
		ans[7] = mouse_rt();
	}

	int score = 0;
	for (int i = 1; i <= 6; ++i)
		score += ans[i];

	if (ans[7] == 3)
		ans[7] = 1;

	cct_setfontsize("新宋体", 36, 18);
	cct_setconsoleborder(55, 15);
	cct_setcolor(7, 5);
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "测试结果为：";
	cct_gotoxy(0, 5);
	cout << "人格CV：";
	cct_gotoxy(10, 2);

	if (ans[7] == 1) {//女性人格
		if (score <= 8) {
			cout << "萝莉";
			cct_gotoxy(10, 7);
			cout << "我喜欢的人，他是一个盖世英雄";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\萝莉-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "哥哥会一直陪着我吗？我不想长大";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\萝莉-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "哥哥....要抱抱";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\萝莉-3-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\萝莉-3-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 12) {
			cout << "少女";
			cct_gotoxy(10, 7);
			cout << "为什么要痛苦呢？一直微笑就好啦";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\少女-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "每一天都要元气满满！你，准备好和我一起接受挑战了吗？";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\少女-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 15) {
			cout << "少御";
			cct_gotoxy(10, 7);
			cout << "他们说，青山是否妩媚，还需看青山是谁";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\少御-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "可我摇头，我见众生皆草木，唯你，是青山。";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\少御-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "遇见你，纵使苦难，我三生有幸、甘之如饴";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\少御-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else {
			cout << "御姐";
			cct_gotoxy(10, 7);
			cout << "我是该让你们的心跳加快呢，还是，让它们停止？";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\御姐-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "他们的价值已经被榨干了";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\御姐-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "哦，你在试图抵抗我吗？看来还是不够听话呢";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\御姐-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
	}
	else {//男性人格
		if (score <= 8) {
			cout << "正太";
			cct_gotoxy(10, 7);
			cout << "姐姐不用担心我，我会照顾好自己的";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\正太-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "错的不是我，是世界";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\正太-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "差一年，一个月，一天，一个时辰，都不算一辈子";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\正太-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 12) {
			cout << "公子";
			cct_gotoxy(10, 7);
			cout << "小生不才，未得姑娘青睐，扰姑娘良久，姑娘莫怪";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\公子-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "自此所有仰慕之意止于唇齿，匿于年华，今生就此别过";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\公子-2.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else if (score <= 15) {
			cout << "青攻";
			cct_gotoxy(10, 7);
			cout << "我最偏心你，我的糖都给你";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青攻-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "我拿起刀，就不能拥抱你，我放下刀，就不能保护你";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青攻-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "我想成为你信赖的，成为你的空气，成为你的干净的水";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青攻-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
		else {
			cout << "青叔";
			cct_gotoxy(10, 7);
			cout << "以绝望挥剑，着逝者为铠";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青叔-1.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 8);
			cout << "愿我们所有的热爱得以保留";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青叔-2.wav"), NULL, SND_SYNC | SND_FILENAME);
			cct_gotoxy(10, 9);
			cout << "愿我们热爱的所有永不熄灭";
			PlaySound(TEXT(".\\a0be1a9cda7af2ce0052f7437766c61b\\青叔-3.wav"), NULL, SND_SYNC | SND_FILENAME);
		}
	}
	return 0;
}