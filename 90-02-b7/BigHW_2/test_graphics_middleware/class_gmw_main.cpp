/*1952339 ��08 ��ܰ��*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/class_cct.h"
#include "../include/class_gmw.h"
using namespace std;

/* --------------------------------------------------------------------------------------------------------------------------

	˵����1����cpp�ļ��� test_graphics_middleware Ŀ¼�£�test_lib_graphics_middleware Ŀ¼���޴��ļ���������Ŀ�ǹ��õ�
	      2������Ҫ�����ǣ�ʵ�� test_graphics_middleware ��Ŀ�е� class_gmw_sli.cpp /class_gmw_cfi.cpp /class_gmw_cbi.cpp /class_gmw.cpp��
		    ʹ test_graphics_middleware ��Ŀ�����н���� test_lib_graphics_middleware ��Ŀһ��
		 3���κζԱ��ļ����޸ģ���Ҫʹ test_graphics_middleware �� test_lib_graphics_middleware ������Ŀ��ͨ��

   --------------------------------------------------------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ������������Ϣ
  ���������
  �� �� ֵ��
  ˵    ����1������ CONSOLE_GRAPHICS_INFO �ṹ����λ����״̬��(x,y)��(0,y+2)λ��
		   2��Ϊ�˼�ʵ�֣�ֱ������Ϊ��Ԫ�����ʵ��ʱ����������֯��ʽ�����磺SLI���ǳ�Ա����Ϊ�̳У��������޸ı�������ʵ�ֲ��֡����������βα�׼�䡿��
***************************************************************************/
void to_be_continued(const char *prompt, const CONSOLE_GRAPHICS_INFO &bgi)
{
	CCT cct;
	cct.setcolor(bgi.area_bgcolor, bgi.area_fgcolor); //�ָ���ʼ��ɫ

	cct.gotoxy(0, bgi.SLI.lower_start_y + 2);//����赽ָ��λ��
	cout << setw(bgi.cols() - 1) << ' '; //���ÿո�������У�����ϴδ�ӡ���ݹ�������δȫ��������Ӷ���ʾ�ң������ǣ�Ҳ����Ҫ����

	cct.gotoxy(0, bgi.SLI.lower_start_y + 2);//����赽ָ��λ��

	if (prompt)
		cout << prompt << "�����س�������...   ";
	else
		cout << "���س�������...   ";

	while (_getch() != '\r')
		;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ������������Ϣ
  ���������
  �� �� ֵ��
  ˵    ����1������ CONSOLE_GRAPHICS_INFO �ṹ����λ����״̬��(x,y)��(0,y+2)λ��
		   2��Ϊ�˼�ʵ�֣�ֱ������Ϊ��Ԫ�����ʵ��ʱ����������֯��ʽ�����磺SLI���ǳ�Ա����Ϊ�̳У��������޸ı�������ʵ�ֲ��֡����������βα�׼�䡿��
***************************************************************************/
void to_be_continued(const char *game_name, const char *prompt, const CONSOLE_GRAPHICS_INFO &bgi)
{
	CCT cct;
	cct.setcolor(bgi.area_bgcolor, bgi.area_fgcolor); //�ָ���ʼ��ɫ

	cct.gotoxy(0, bgi.SLI.lower_start_y + 2);//����赽ָ��λ��
	cout << setw(bgi.cols() - 1) << ' '; //���ÿո�������У�����ϴδ�ӡ���ݹ�������δȫ��������Ӷ���ʾ�ң������ǣ�Ҳ����Ҫ����

	cct.gotoxy(0, bgi.SLI.lower_start_y + 2);//����赽ָ��λ��
	cout << game_name << '-' << (bgi.CFI.separator ? "��" : "��") << "�ָ���-" << prompt << "�����س�������...";

	while (_getch() != '\r')
		;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_by_fixed(void)
{
	CCT cct;
	CONSOLE_GRAPHICS_INFO MyCGI; //����һ��CGI����
	char temp[256];

	/* ������ʼ�����������������ڴ˻����������޸Ĳ������ã��������Ԥ��ֵ
		��Ϸ��������ܣ�Ϊ10*10�����ָ��ߣ�ÿ��ɫ��Ĵ�СΪ2��*1�У�ɫ�鲻���߿�
		���ڱ���ɫ�ڣ�ǰ��ɫ��
		����Ϊ����8*16
		���߿�ɫ��ʱ����ʱ��ɫ���ƶ�ʱ��ʱ3ms
		�������Ҹ�������ȫ��Ϊ0
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����
		����ʾ�к�
		����ʾ�б�
		��Ϸ����Ϊ˫�߿򣬴��ָ��ߣ�ɫ���СΪ2�����2��=1�����֣�*1���߶�1�У�����ɫͬ����
		ɫ��Ϊ˫���ߣ���ɫ��δ�꣩		*/
	if (1) {
		/* ��ʾ��ʼ���Ŀ�� */
		MyCGI.gmw_draw_frame();

		/* ��״̬����ʾ���� */
		sprintf(temp, "����1 - ���ڴ�С��%d�� %d��", MyCGI.lines(), MyCGI.cols());
		MyCGI.gmw_top_status_line(temp);

		/* ��״̬����ʾ���� */
		MyCGI.gmw_lower_status_line("����End����", "���ؽ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

		to_be_continued("����1���", MyCGI);
	}

	if (1) {
		/* Ϊ�˼򻯣������������ȷ�ԣ����б�֤ */
		cct.cls();
		int sel;
		cout << "����2�ȽϺ�ʱ���Ƿ����[0/1] : ";
		cin >> sel;
		if (sel == 1) {
			const int row = 6, col = 7;
			/* �ڳ�ʼ����ܵĻ������޸ģ�
				��Ϸ�����С
				��������
				������ɫ
				�����ֺ�
				ÿ����Ϸ��Ĵ�С
				��ʾ�к�
				��ʾ�б�
				������ʱ	*/
			MyCGI.gmw_set_rowcol(row, col);					//��Ϸ����6*7
			MyCGI.gmw_set_ext_rowcol(3, 4, 10, 20);				//���ö�������
			MyCGI.gmw_set_color(CCT_COLOR::blue, CCT_COLOR::hgreen);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
			MyCGI.gmw_set_font("������", 16, 0);				//TrueType���壨�����壩��Ȳ���Ҫ������������
			MyCGI.gmw_set_frame_style(6, 3, true);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
			MyCGI.gmw_set_frame_default_linetype(2);			//���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
			MyCGI.gmw_set_rowno_switch(true);					//��ʾ�к�
			MyCGI.gmw_set_colno_switch(true);					//��ʾ�б�
			MyCGI.gmw_set_delay(DELAY_OF_DRAW_FRAME, 200);		//���߿����ʱ
			MyCGI.gmw_set_block_border_switch(true);			//����ɫ����ҪС�߿�

			/* ��ʾ��� */
			MyCGI.gmw_draw_frame();

			/* ��״̬����ʾ���� */
			sprintf(temp, "����2 - ���ڴ�С��%d�� %d��", MyCGI.lines(), MyCGI.cols());
			MyCGI.gmw_top_status_line(temp);

			/* ���������ɫ�� */
			{
				const BLOCK_DISPLAY_INFO bdi[] = {
					{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},						//0����ʾ���ÿո���伴��
					{1,  CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},				//�����������1������ʾ������
					{2,  CCT_COLOR::hblue, CCT_COLOR::hyellow, "��"},	//�����������2������ʾ˫�߿�����
					{3,  CCT_COLOR::hcyan, CCT_COLOR::green, "��"},		//�����������3������ʾ��
					{4,  CCT_COLOR::hred, CCT_COLOR::invalid, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
					{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
				};
				MyCGI.gmw_set_delay(DELAY_OF_DRAW_BLOCK, 200);		//��ɫ�����ʱ
				int i, j;
				for (i = 0; i < row; i++)
					for (j = 0; j < col; j++)
						MyCGI.gmw_draw_block(i, j, (i*row + j) % 5, bdi);
			}

			/* ��״̬����ʾ���� */
			MyCGI.gmw_lower_status_line("����Quit����", "��ʾ������"); //ֻ�Ǹ�����ʾ���ѣ�������������Quit����������Ҫ�����뼰�ж�

			to_be_continued("����2���", MyCGI);
		}
	}

	if (1) {
		cct.cls();
		/* ����������ϼ����޸ģ�
			��Ϸ�����С
			�����ֺ�
			������ɫ
			ÿ����Ϸ��Ĵ�С
			����ʾ�к�
			��ʾ�б�
			�ر���״̬��
			��ʱΪ0	*/
		MyCGI.gmw_set_rowcol(9, 12);								//��Ϸ����9*12
		MyCGI.gmw_set_font("������", 20, 0);						//TrueType���壨�����壩��Ȳ���Ҫ������������
		MyCGI.gmw_set_color();										//�ָ�ȱʡɫ������
		MyCGI.gmw_set_frame_style(4, 2, true);						//ÿ��ɫ��������4��*�߶�2�У�Ҫ�ָ���
		MyCGI.gmw_set_rowno_switch(false);							//����ʾ�к�
		MyCGI.gmw_set_colno_switch(true);							//��ʾ�б�
		MyCGI.gmw_set_status_line_switch(TOP_STATUS_LINE, false);	//�ر���״̬��
		MyCGI.gmw_set_delay(DELAY_OF_DRAW_FRAME, 0);				//��Ҫ��ʱ
//		gmw_set_frame_linetype(&MyCGI, "�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p");		//д������ֻ��Ϊ�˶�����������ò���
		MyCGI.gmw_set_frame_linetype("��", "��", "��", "ϵ", "�T", "�U", "��", "��", "��", "��", "��");	//�Զ�����Ԫ��
		MyCGI.gmw_set_block_border_switch();							//����ɫ�鲻��ҪС�߿�

		/* ��ʾ��� */
		MyCGI.gmw_draw_frame();

		/* ��״̬����ʾ���� */
		sprintf(temp, "����3 - ���ڴ�С��%d�� %d��", MyCGI.lines(), MyCGI.cols());
		MyCGI.gmw_top_status_line(temp);

		/* ��״̬����ʾ���� */
		MyCGI.gmw_lower_status_line("����Quit����", "��ʾ������"); //ֻ�Ǹ�����ʾ���ѣ�������������Quit����������Ҫ�����뼰�ж�

		to_be_continued("����3���", MyCGI);
	}

	if (1) {
		cct.cls();
		/* ����������ϼ����޸ģ�
			��Ϸ�����С���صس������к��б�����ɱ�ʾ��Χ���۲�����Ƿ���*��**��
			�������о�Ϊ0
			�����ֺ�
			������ɫ
			ÿ����Ϸ��Ĵ�С
			����ʾ�к�
			��ʾ�б�
			������״̬��
			�ر���״̬��		*/
		MyCGI.gmw_set_rowcol(55, 60);							//��Ϸ����55*102���صز����к��б��ӡ�Ƿ���ȷ
		MyCGI.gmw_set_ext_rowcol(0, 0, 0, 0);					//���ö�������
		MyCGI.gmw_set_font("������", 12, 0);					//TrueType���壨�����壩��Ȳ���Ҫ������������
		MyCGI.gmw_set_color(CCT_COLOR::cyan, CCT_COLOR::hwhite);			//�޸Ĵ�����ɫ(�������޸���Ϸ��������״̬����
		MyCGI.gmw_set_frame_style(2, 1, false);					//ÿ��ɫ��������2��*�߶�1�У���Ҫ�ָ���
		MyCGI.gmw_set_rowno_switch(true);						//�����к���ʾ
		MyCGI.gmw_set_colno_switch(true);						//�����б���ʾ
		MyCGI.gmw_set_status_line_switch(TOP_STATUS_LINE);		//������״̬��
		MyCGI.gmw_set_status_line_color(TOP_STATUS_LINE, CCT_COLOR::hyellow, CCT_COLOR::blue, CCT_COLOR::hred, CCT_COLOR::blue);		//������״̬����ɫ
		MyCGI.gmw_set_status_line_switch(LOWER_STATUS_LINE);	//������״̬��
		MyCGI.gmw_set_status_line_color(LOWER_STATUS_LINE, CCT_COLOR::hyellow, CCT_COLOR::hgreen, CCT_COLOR::hred, CCT_COLOR::hgreen);		//������״̬����ɫ

		/* ��ʾ��� */
		MyCGI.gmw_draw_frame();

		/* ��״̬����ʾ���� */
		sprintf(temp, "����4 - ���ڴ�С��%d�� %d��", MyCGI.lines(), MyCGI.cols());
		MyCGI.gmw_top_status_line(temp);

		/* ��״̬����ʾ����(���п�����) */
		MyCGI.gmw_lower_status_line("����Q����", "��ʾ������"); //ֻ�Ǹ�����ʾ���ѣ�������������Q����������Ҫ�����뼰�ж�

		to_be_continued("����4���", MyCGI);
	}

	if (1) {
		cct.cls();
		/* ����������ϼ����޸ģ�
			��Ϸ�����С
			���Ҷ����о�Ϊ3
			������ɫ
			�����ֺ�
			����ʾ�к�
			��ʾ�б�
			������״̬��
			�ر���״̬��		*/
		MyCGI.gmw_set_rowcol(5, 5);								//��Ϸ����5*5
		MyCGI.gmw_set_ext_rowcol(0, 0, 3, 3);						//���ö�������
		MyCGI.gmw_set_color(CCT_COLOR::cyan, CCT_COLOR::hpink);				//�����޸���ɫ����ʾ����״̬����ɫ���䣩
		MyCGI.gmw_set_font("������", 24, 0);						//TrueType���壨�����壩��Ȳ���Ҫ������������
		MyCGI.gmw_set_frame_style(3, 2, false);						//ÿ��ɫ��������3��*�߶�2�У���Ҫ�ָ��ߣ�3���Ϊ4��
		MyCGI.gmw_set_frame_default_linetype(1);					//���Ԫ�ػָ�Ϊ˫��
		MyCGI.gmw_set_colno_switch();								//�����б���ʾ
		MyCGI.gmw_set_status_line_switch(TOP_STATUS_LINE, false);	//�ر���״̬��
		MyCGI.gmw_set_status_line_color(TOP_STATUS_LINE);			//������״̬����ɫΪȱʡ(��Ȼ����ʾ)
		MyCGI.gmw_set_status_line_switch(LOWER_STATUS_LINE);		//������״̬��
		MyCGI.gmw_set_status_line_color(LOWER_STATUS_LINE);		//������״̬����ɫΪȱʡ

		/* ��ʾ��� */
		MyCGI.gmw_draw_frame();

		/* ��״̬����ʾ���� */
		sprintf(temp, "����5 - ���ڴ�С��%d�� %d��", MyCGI.lines(), MyCGI.cols());
		MyCGI.gmw_top_status_line(temp);

		/* ��״̬����ʾ����(�ر���ʾ��������ʾ���ܻ��ң�Ҫ������������ѣ����ⲻ�ڴ����ϣ� */
		MyCGI.gmw_lower_status_line("����Hello����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������Hello����������Ҫ�����뼰�ж�

		to_be_continued("����5���", MyCGI);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_by_input(void)
{
	/* �ָ���ʼ��ɫ������ */
	CCT cct;
	cct.setfontsize("��������", 16, 8);
	cct.setcolor();
	cct.setconsoleborder(120, 35);
	cct.cls();

	/* Ϊ�˼򻯣������������ȷ�ԣ����б�֤ */
	int sel;
	cout << "�Ƿ������ѡ����[0/1] : ";
	cin >> sel;
	if (sel != 1)
		return;

	CONSOLE_GRAPHICS_INFO TestCGI; //����һ��CGI����(Ҳ������)
	char temp[256];

	cout << endl;
	cout << "����Ϊ��֤��Ϸ���������ֵ��ɫ���С��Ԥ�����С�״̬������������ò�Ҫ����cmd���ڵĿ����ô�С" << endl;
	cout << "��Ϊ���ó��굼�µ���ʾ�ң��������" << endl;
	cout << endl;

	/* ����Ϊ�˼򻯣��������������ȷ�ԣ����б�֤ */
	if (1) {
		int row, col;
		cout << "������Ϸɫ�������[1..55] : ";
		cin >> row;
		cout << "������Ϸɫ�������[1..102] : ";
		cin >> col;
		TestCGI.gmw_set_rowcol(row, col);	//���row,col��ֵ���󣬱������޷ָ��ߣ�����cmd���ڻ���
	}

	if (1) {
		int ext_up_line, ext_down_line, ext_left_cols, ext_right_cols;
		cout << "������Ϸ������ϲ�Ԥ������[0..10] : ";
		cin >> ext_up_line;
		cout << "������Ϸ������²�Ԥ������[0..10] : ";
		cin >> ext_down_line;
		cout << "������Ϸ��������Ԥ������[0..20] : ";
		cin >> ext_left_cols;
		cout << "������Ϸ������ұ�Ԥ������[0..20] : ";
		cin >> ext_right_cols;
		TestCGI.gmw_set_ext_rowcol(ext_up_line, ext_down_line, ext_left_cols, ext_right_cols);
	}

	if (1) {
		int bg_color, fg_color;
		cout << "���봰�ڱ���ɫ[0..15] : ";
		cin >> bg_color;
		cout << "���봰��ǰ��ɫ[0..15] : ";
		cin >> fg_color;
		TestCGI.gmw_set_color(static_cast<CCT_COLOR>(bg_color), static_cast<CCT_COLOR>(fg_color));
	}

	if (1) {
		int font_num, font_high, font_width;
		cout << "��������[0:���� 1:������] : ";
		cin >> font_num;
		cout << "��������߶�[1..36] : ";
		cin >> font_high;
		cout << "����������[1..36] : ";
		cin >> font_width;
		if (font_num == 1)
			TestCGI.gmw_set_font("������", font_high, font_width);
		else
			TestCGI.gmw_set_font("Terminal", font_high, font_width);
	}

	if (1) {
		int draw_border_delay;
		cout << "���뻭�߿���ʱ[0..1000 ��λ:ms] : ";
		cin >> draw_border_delay;
		TestCGI.gmw_set_delay(DELAY_OF_DRAW_FRAME, draw_border_delay);
	}

	if (1) {
		int top_status_line, top_normal_bgcolor, top_normal_fgcolor, top_catchy_bgcolor, top_catchy_fgcolor;
		cout << "�Ƿ���Ҫ��״̬��[0/1] : ";
		cin >> top_status_line;
		if (top_status_line) {
			cout << "������״̬�������ı�����ɫ[-1..16��-1��ʾ�ô��ڱ���ɫ] : ";
			cin >> top_normal_bgcolor;
			cout << "������״̬�������ı�ǰ��ɫ[-1..16��-1��ʾ�ô���ǰ��ɫ] : ";
			cin >> top_normal_fgcolor;
			cout << "������״̬����Ŀ�ı�����ɫ[-1..16��-1��ʾ�ô��ڱ���ɫ] : ";
			cin >> top_catchy_bgcolor;
			cout << "������״̬����Ŀ�ı�����ɫ[-1..16��-1��ʾ��ȱʡ����] : ";
			cin >> top_catchy_fgcolor;
			TestCGI.gmw_set_status_line_switch(TOP_STATUS_LINE);
			TestCGI.gmw_set_status_line_color(TOP_STATUS_LINE, static_cast<CCT_COLOR>(top_normal_bgcolor), static_cast<CCT_COLOR>(top_normal_fgcolor), static_cast<CCT_COLOR>(top_catchy_bgcolor), static_cast<CCT_COLOR>(top_catchy_fgcolor));
		}
		else
			TestCGI.gmw_set_status_line_switch(TOP_STATUS_LINE, false);
	}

	if (1) {
		int lower_status_line, lower_normal_bgcolor, lower_normal_fgcolor, lower_catchy_bgcolor, lower_catchy_fgcolor;
		cout << "�Ƿ���Ҫ��״̬��[0/1] : ";
		cin >> lower_status_line;
		if (lower_status_line) {
			cout << "������״̬�������ı�����ɫ[-1..16��-1��ʾ�ô��ڱ���ɫ] : ";
			cin >> lower_normal_bgcolor;
			cout << "������״̬�������ı�ǰ��ɫ[-1..16��-1��ʾ�ô���ǰ��ɫ] : ";
			cin >> lower_normal_fgcolor;
			cout << "������״̬����Ŀ�ı�����ɫ[-1..16��-1��ʾ�ô��ڱ���ɫ] : ";
			cin >> lower_catchy_bgcolor;
			cout << "������״̬����Ŀ�ı�����ɫ[-1..16��-1��ʾ��ȱʡ����] : ";
			cin >> lower_catchy_fgcolor;
			TestCGI.gmw_set_status_line_switch(LOWER_STATUS_LINE);
			TestCGI.gmw_set_status_line_color(LOWER_STATUS_LINE, static_cast<CCT_COLOR>(lower_normal_bgcolor), static_cast<CCT_COLOR>(lower_normal_fgcolor), static_cast<CCT_COLOR>(lower_catchy_bgcolor), static_cast<CCT_COLOR>(lower_catchy_fgcolor));
		}
		else
			TestCGI.gmw_set_status_line_switch(LOWER_STATUS_LINE, false);
	}

	if (1) {
		int rowno, colno;
		cout << "�����Ƿ���Ҫ�к�[0/1] : ";
		cin >> rowno;
		cout << "�����Ƿ���Ҫ�б�[0/1] : ";
		cin >> colno;
		TestCGI.gmw_set_rowno_switch(rowno);
		TestCGI.gmw_set_colno_switch(colno);

		int def_linetype;
		cout << "����߿�����[1-ȫ˫�� 2-ȫ���� 3-��˫���� 4-�ᵥ��˫] : ";
		cin >> def_linetype;
		TestCGI.gmw_set_block_default_linetype(def_linetype);
	}

	if (1) {
		int width, high, separator;
		cout << "������Ϸɫ��Ŀ��[ż��2..32] : ";
		cin >> width;
		cout << "������Ϸɫ��ĸ߶�[1..10] : ";
		cin >> high;
		cout << "�����Ƿ���Ҫ�ָ���[0/1] : ";
		cin >> separator;
		TestCGI.gmw_set_frame_style(width, high, separator);
	}

	if (1) {
		int border_bg_color, border_fg_color;
		cout << "������Ϸ������ɫ[-1..16��-1��ʾ�ô��ڱ���ɫ] : ";
		cin >> border_bg_color;
		cout << "������Ϸ��ǰ��ɫ[-1..16��-1��ʾ�ô���ǰ��ɫ] : ";
		cin >> border_fg_color;
		TestCGI.gmw_set_frame_color(static_cast<CCT_COLOR>(border_bg_color), static_cast<CCT_COLOR>(border_bg_color));
	}

	/* ��ʾ��ʼ���Ŀ�� */
	TestCGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "��ѡ���� - ���ڴ�С��%d�� %d��", TestCGI.lines(), TestCGI.cols());
	TestCGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	TestCGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	to_be_continued("��ѡ�������", TestCGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_step_of_color_linez(CONSOLE_GRAPHICS_INFO &ColorLinez_CGI)
{
	const char *gname = "ColorLinez";
	const int row = 8, col = 8;

	/* Ԥ��һ�����飬1-7��ʾ7�ֲ�ͬ��ɫ����0��ʾ�� */
	int cl[row][col] = {
		{0, 0, 0, 0, 4, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 0, 0, 0, 7, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 6},
		{0, 1, 0, 0, 0, 5, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	/* ����1-7�������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý�������+ѡ�С���Ϣ����һ�������еķ���
				1-7��ʾ������11-17��ʾѡ��
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ
			  3���� test_magic_ball ����������һ�ַ�ʽ��ʾɫ��Ĳ�ͬ״̬�����Զ��� */
	const BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //0����ʾ���ÿո���伴��
		{1,  CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},	//����״̬����1����Ӧ�Ĳ���
		{2,  CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{3,  CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{4,  CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{5,  CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{6,  CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{7,  CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{11, CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},//ѡ��״̬����1����Ӧ�Ĳ���ͼ��
		{12, CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{13, CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{14, CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{15, CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{16, CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{17, CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	const int BDI_NORMAL = 0, BDI_SELECTED = 10;
	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	ColorLinez_CGI.gmw_set_rowcol(row, col);

	/* ��ʾ��� */
	ColorLinez_CGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, ColorLinez_CGI.lines(), ColorLinez_CGI.cols());
	ColorLinez_CGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	ColorLinez_CGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			ColorLinez_CGI.gmw_draw_block(i, j, BDI_NORMAL + cl[i][j], bdi);
		}
	to_be_continued(gname, "��ʼ�����", ColorLinez_CGI);

	/* �����/���̲����ݷ���ֵ������Ӧ�Ķ���
	   ע��1������Լ������Ҽ��˳��������ʾ<�У���>��ʵ����Ϸ�У�Ҫ���ݷ��ص����н���ĳ�ֶ������ҳ���ͬ�����ѡ��������ȣ�
           2������Լ�����س��˳���������ʾ������Ϣ��ʵ����Ϸ�У�Ҫ���ݷ��ص����н���ĳ�ֶ������ҳ���ͬ�����ѡ��������ȣ�
           3��ʵ����Ϸ��ӦдΪ���� */
	{
		ColorLinez_CGI.gmw_top_status_line("���Լ���/��꣬�Ҽ�/�س��˳�");

		int loop = 1;
		CCT_MOUSE maction;
		int old_mrow, old_mcol, mrow = -1, mcol = -1;
		int keycode1, keycode2;
		CCT_KMEVENT ret;

		while (loop) {
			old_mrow = mrow;
			old_mcol = mcol;
			ret = ColorLinez_CGI.gmw_read_keyboard_and_mouse(maction, mrow, mcol, keycode1, keycode2);

			if (ret == CCT_KMEVENT::mouse) {
				if (maction == CCT_MOUSE::only_moved) {
					/* ��ʱ��mrow��mcol�϶����ղŲ�ͬ */

					/* ��һ��ɫ��仯��color_linez��������λ�ö���ɫ�飬�˴�ֱ����3���棩����ͬ��Ϸ�˴���ͬ�������Ǹ���ʾ */

					/* ԭɫ��������ʾ */
					if (old_mrow >= 0 && old_mcol >= 0)
						ColorLinez_CGI.gmw_draw_block(old_mrow, old_mcol, BDI_NORMAL + cl[old_mrow][old_mcol], bdi);

					/* ��ɫ�����ԣ���Ϊ��������ɫ�鶼��ֵ���˴���3����� */
					ColorLinez_CGI.gmw_draw_block(mrow, mcol, BDI_SELECTED + 3, bdi);
				}
				else if (maction == CCT_MOUSE::right_button_click) {
					/* ��״̬����ʾ���� */
					ColorLinez_CGI.gmw_lower_status_line("[�����Ҽ�]", NULL);
					loop = 0;
				}
				else {
					sprintf(temp, "[�������] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					ColorLinez_CGI.gmw_lower_status_line(temp);
					loop = 0;
				}
			}
			else { //CCT_KEYBOARD_EVENT - ������뺬��ȥ�� cmd_console_tools.cpp
				switch (keycode1) {
					case 0x0D:
						/* ��״̬����ʾ���� */
						ColorLinez_CGI.gmw_lower_status_line("[�����س���]", NULL);
						loop = 0;
						break;
					case static_cast<int>(CCT_KEYCODE::arrow_pre): //224
						switch (static_cast<CCT_KEYCODE>(keycode2)) {
							case CCT_KEYCODE::arrow_up:
								/* ��״̬����ʾ���� */
								ColorLinez_CGI.gmw_lower_status_line("[�����ϼ�ͷ]", NULL);
								break;
							case CCT_KEYCODE::arrow_down:
								/* ��״̬����ʾ���� */
								ColorLinez_CGI.gmw_lower_status_line("[�����¼�ͷ]", NULL);
								break;
							case CCT_KEYCODE::arrow_left:
								/* ��״̬����ʾ���� */
								ColorLinez_CGI.gmw_lower_status_line("[�������ͷ]", NULL);
								break;
							case CCT_KEYCODE::arrow_right:
								/* ��״̬����ʾ���� */
								ColorLinez_CGI.gmw_lower_status_line("[�����Ҽ�ͷ]", NULL);
								break;
						}
						break;
					default:
						sprintf(temp, "[��������] %d/%d", keycode1, keycode2);
						ColorLinez_CGI.gmw_lower_status_line(temp);
						break;
				}//end of switch
			}//end of else
		}//end of while

		/* ��״̬���ָ�ԭ����Ϣ */
		sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, ColorLinez_CGI.lines(), ColorLinez_CGI.cols());
		ColorLinez_CGI.gmw_top_status_line(temp);

		to_be_continued(gname, "�������������", ColorLinez_CGI);
	}

	/* �����е�һ������ʾΪ��ѡ��״̬�� - ע��������ѡ��һ����ʵ����Ϸ�и������/���̶�����ȷ��ĳ���� */
	ColorLinez_CGI.gmw_draw_block(2, 2, BDI_SELECTED + cl[2][2], bdi);
	to_be_continued(gname, "ѡ��1��", ColorLinez_CGI);

	/* �ƶ�ĳ����
	   ע��1��������ѡ��һ����ʵ����Ϸ�и������/���̶�����ȷ��ĳ����
		   2����������ѡ�˽���Ϊֹ��ʵ����Ϸ�и������/���̶�����ȷ���ƶ�����λ��
		   3��������δ�޸��ڲ������ֵ��ʵ����Ϸ�п�����Ҫ�޸� */
	ColorLinez_CGI.gmw_set_delay(DELAY_OF_BLOCK_MOVED, 200); //�����ƶ���ʱ
	ColorLinez_CGI.gmw_move_block(2, 2, BDI_SELECTED + cl[2][2], 0, bdi, UP_TO_DOWN, 3);
	/* Ϊ�˺����ƶ������������ֵ */
	cl[2 + 3][2] = cl[2][2];
	cl[2][2] = 0;
	to_be_continued(gname, "�����ƶ�3��", ColorLinez_CGI);

	ColorLinez_CGI.gmw_move_block(5, 2, BDI_SELECTED + cl[5][2], 0, bdi, LEFT_TO_RIGHT, 2);
	/* Ϊ�˺����ƶ������������ֵ */
	cl[5][2 + 2] = cl[5][2];
	cl[5][2] = 0;
	to_be_continued(gname, "�����ƶ�2��", ColorLinez_CGI);

	ColorLinez_CGI.gmw_move_block(5, 4, BDI_SELECTED + cl[5][4], 0, bdi, DOWN_TO_UP, 3);
	/* Ϊ�˺����ƶ������������ֵ */
	cl[5 - 3][4] = cl[5][4];
	cl[5][4] = 0;
	to_be_continued(gname, "�����ƶ�3��", ColorLinez_CGI);

	ColorLinez_CGI.gmw_move_block(2, 4, BDI_SELECTED + cl[2][4], 0, bdi, RIGHT_TO_LEFT, 2);
	/* Ϊ�˺����ƶ������������ֵ */
	cl[2][4 - 2] = cl[2][4];
	cl[2][4] = 0;
	to_be_continued(gname, "�����ƶ�2��", ColorLinez_CGI);

	/* �����е�һ����������
	   ע��1��������ѡ��һ����ʵ����Ϸ��һ������5����
		   2���޶�����ʽ
		   3��δ�޸��ڲ������ֵ   */
	ColorLinez_CGI.gmw_draw_block(2, 2, 0, bdi);
	to_be_continued(gname, "����1��", ColorLinez_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_color_linez(void)
{
	CONSOLE_GRAPHICS_INFO ColorLinez_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
//	ColorLinez_CGI.gmw_set_ext_rowcol(3, 2, 10, 10);						//ע�������ø������򣬿��ܵ���to_be_continued��ӡΪ���У�������δ��������ͬ��
	ColorLinez_CGI.gmw_set_color(CCT_COLOR::black, CCT_COLOR::hwhite);			//����������ɫ
	ColorLinez_CGI.gmw_set_font("������", 32);							//����
//	ColorLinez_CGI.gmw_set_frame_style();									//��Ϸ��������ÿ��ɫ���2��1���зָ���
	ColorLinez_CGI.gmw_set_frame_default_linetype(2);					//��Ϸ���������ͣ�����
	ColorLinez_CGI.gmw_set_frame_color(CCT_COLOR::hwhite, CCT_COLOR::black);		//��Ϸ��������ɫ
//	ColorLinez_CGI.gmw_set_block_border_switch();							//ÿ����Ϸɫ��/������Ҫ�߿�
//	ColorLinez_CGI.gmw_set_status_line_switch(TOP_STATUS_LINE);				//��Ҫ��״̬��
//	ColorLinez_CGI.gmw_set_status_line_switch(LOWER_STATUS_LINE);			//��Ҫ��״̬��
	ColorLinez_CGI.gmw_set_rowno_switch(true);							//��ʾ�к�
	ColorLinez_CGI.gmw_set_colno_switch(true);							//��ʾ�б�
	ColorLinez_CGI.gmw_set_delay(DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS * 3);//�Ӵ���ʱ

	test_step_of_color_linez(ColorLinez_CGI);

	/* ��Ϊ�޷ָ��ߣ�����һ�� */
	ColorLinez_CGI.gmw_set_frame_style(2, 1, false);					//��Ϸ��������ÿ��ɫ���2��1���޷ָ���
	ColorLinez_CGI.gmw_set_ext_rowcol(3, 2, 10, 10);					//����������2��3����10��10
	ColorLinez_CGI.gmw_set_frame_default_linetype(1);					//��Ϸ���������ͣ�˫��

	test_step_of_color_linez(ColorLinez_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_step_of_magic_ball(CONSOLE_GRAPHICS_INFO &MagicBall_CGI)
{
	const char *gname = "MagicBall";
	const int row = 7, col = 7;

	/* Ԥ��һ������ */
	int mb[row][col] = {
		{1, 2, 3, 4, 5, 6, 7},
		{2, 3, 4, 5, 6, 8, 1},
		{7, 6, 9, 4, 3, 2, 1},
		{8, 4, 9, 6, 7, 1, 2},
		{4, 5, 6, 7, 3, 1, 2},
		{5, 7, 5, 8, 3, 2, 4},
		{6, 2, 3, 4, 1, 6, 7},
	};

	/* ����1-9�������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý������� + ѡ�� + ��ʾ������ + ��ը����Ϣ�����ĸ������еķ���
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ
			 3���� test_color_linez ����������һ�ַ�ʽ��ʾɫ��Ĳ�ͬ״̬�����Զ��� */

	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //0����ʾ���ÿո���伴��
		{1, CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},
		{2, CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{3, CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{4, CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{5, CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{6, CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{7, CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{8, CCT_COLOR::cyan, CCT_COLOR::invalid, "��"},
		{9, CCT_COLOR::white, CCT_COLOR::invalid, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //�հ�
		{1, CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},
		{2, CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{3, CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{4, CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{5, CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{6, CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{7, CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{8, CCT_COLOR::cyan, CCT_COLOR::invalid, "��"},
		{9, CCT_COLOR::white, CCT_COLOR::invalid, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���������ʾ״̬�� */
	const BLOCK_DISPLAY_INFO bdi_prompt[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //�հ�
		{1, CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},
		{2, CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{3, CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{4, CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{5, CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{6, CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{7, CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{8, CCT_COLOR::cyan, CCT_COLOR::invalid, "��"},
		{9, CCT_COLOR::white, CCT_COLOR::invalid, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���ը/����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_exploded[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //�հ�
		{1, CCT_COLOR::hblack, CCT_COLOR::invalid, "��"},
		{2, CCT_COLOR::yellow, CCT_COLOR::invalid, "��"},
		{3, CCT_COLOR::hgreen, CCT_COLOR::invalid, "��"},
		{4, CCT_COLOR::hcyan, CCT_COLOR::invalid, "��"},
		{5, CCT_COLOR::hred, CCT_COLOR::invalid, "��"},
		{6, CCT_COLOR::hpink, CCT_COLOR::invalid, "��"},
		{7, CCT_COLOR::hyellow, CCT_COLOR::invalid, "��"},
		{8, CCT_COLOR::cyan, CCT_COLOR::invalid, "��"},
		{9, CCT_COLOR::white, CCT_COLOR::invalid, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	MagicBall_CGI.gmw_set_rowcol(row, col);

	/* ��ʾ��� */
	MagicBall_CGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, MagicBall_CGI.lines(), MagicBall_CGI.cols());
	MagicBall_CGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	MagicBall_CGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			MagicBall_CGI.gmw_draw_block(i, j, mb[i][j], bdi_normal);
		}
	to_be_continued(gname, "��ʼ�����", MagicBall_CGI);

	/* �����е���������ʾΪ��������״̬��ʾ�� - ע��������ѡ��������ʵ����Ϸ�а�Ҫ������Һ���ʾ */
	MagicBall_CGI.gmw_draw_block(2, 2, mb[2][2], bdi_prompt);
	MagicBall_CGI.gmw_draw_block(2, 3, mb[2][3], bdi_prompt);
	MagicBall_CGI.gmw_draw_block(2, 4, mb[2][4], bdi_prompt);
	to_be_continued(gname, "��3��������Ϊ��������ʾ", MagicBall_CGI);

	/* �����е���������ʾΪ��ѡ��״̬�� - ע��������ѡ��������ʵ����Ϸ�а�Ҫ������Һ���ʾ
	   �������н���ʾѡ��״̬��δ�޸��ڲ������ֵ */
	MagicBall_CGI.gmw_draw_block(2, 2, mb[2][2], bdi_selected);
	MagicBall_CGI.gmw_draw_block(2, 3, mb[2][3], bdi_selected);
	MagicBall_CGI.gmw_draw_block(2, 4, mb[2][4], bdi_selected);
	to_be_continued(gname, "��3��������Ϊѡ��", MagicBall_CGI);

	/* �����е�������������������ʽ - ��ը+�հס��� - ע��������ѡ��������ʵ����Ϸ�а�Ҫ������Һ���ʾ
	   �������н���ʱ����������δ�޸��ڲ������ֵ */
	for (int k = 0; k < 5; k++) {
		MagicBall_CGI.gmw_draw_block(2, 2, mb[2][2], bdi_exploded);
		MagicBall_CGI.gmw_draw_block(2, 3, mb[2][3], bdi_exploded);
		MagicBall_CGI.gmw_draw_block(2, 4, mb[2][4], bdi_exploded);
		Sleep(50);
		MagicBall_CGI.gmw_draw_block(2, 2, 0, bdi_normal); //0�ǿհ�
		MagicBall_CGI.gmw_draw_block(2, 3, 0, bdi_normal);
		MagicBall_CGI.gmw_draw_block(2, 4, 0, bdi_normal);
		Sleep(50);
	}
	to_be_continued(gname, "��3��������(����)", MagicBall_CGI);

	/* ���ϲ�����������������Ϸ�������
	   ע��1��δ�޸��ڲ������ֵ
		   2��δʹ��ѭ����ֱ��д�˶�ֵ */
	MagicBall_CGI.gmw_move_block(1, 2, mb[1][2], 0, bdi_normal, UP_TO_DOWN, 1);
	MagicBall_CGI.gmw_move_block(1, 3, mb[1][3], 0, bdi_normal, UP_TO_DOWN, 1);
	MagicBall_CGI.gmw_move_block(1, 4, mb[1][4], 0, bdi_normal, UP_TO_DOWN, 1);
	MagicBall_CGI.gmw_move_block(0, 2, mb[0][2], 0, bdi_normal, UP_TO_DOWN, 1);
	MagicBall_CGI.gmw_move_block(0, 3, mb[0][3], 0, bdi_normal, UP_TO_DOWN, 1);
	MagicBall_CGI.gmw_move_block(0, 4, mb[0][4], 0, bdi_normal, UP_TO_DOWN, 1);
	to_be_continued(gname, "�Ϸ�������", MagicBall_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_magic_ball(void)
{
	CONSOLE_GRAPHICS_INFO MagicBall_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
	MagicBall_CGI.gmw_set_ext_rowcol(0, 0, 0, 30);						//�ұ���30��
	MagicBall_CGI.gmw_set_color(CCT_COLOR::black, CCT_COLOR::hwhite);			//����������ɫ
	MagicBall_CGI.gmw_set_font("������", 36);							//����
//	MagicBall_CGI.gmw_set_frame_style();									//��Ϸ��������ÿ��ɫ���2��1���зָ���
	MagicBall_CGI.gmw_set_frame_default_linetype(4);					//��Ϸ���������ͣ��ᵥ��˫
	MagicBall_CGI.gmw_set_frame_color(CCT_COLOR::hwhite, CCT_COLOR::black);		//��Ϸ��������ɫ
	MagicBall_CGI.gmw_set_rowno_switch(true);							//��ʾ�к�
	MagicBall_CGI.gmw_set_colno_switch(false);							//����ʾ�б�
	MagicBall_CGI.gmw_set_status_line_switch(TOP_STATUS_LINE, false);	//����Ҫ��״̬��
	MagicBall_CGI.gmw_set_status_line_switch(LOWER_STATUS_LINE, true);	//��Ҫ��״̬��

	test_step_of_magic_ball(MagicBall_CGI);

	/* ��Ϊ�޷ָ��ߣ�����һ�� */
	MagicBall_CGI.gmw_set_frame_style(2, 1, false);						//��Ϸ��������ÿ��ɫ���2��1���޷ָ���
	MagicBall_CGI.gmw_set_ext_rowcol(2, 3, 20, 20);						//��2��3����20��20
	MagicBall_CGI.gmw_set_rowno_switch(false);							//����ʾ�к�
	MagicBall_CGI.gmw_set_colno_switch(true);							//��ʾ�б�
	MagicBall_CGI.gmw_set_status_line_switch(TOP_STATUS_LINE, true);	//��Ҫ��״̬��
	MagicBall_CGI.gmw_set_status_line_switch(LOWER_STATUS_LINE, false);	//����Ҫ��״̬��

	test_step_of_magic_ball(MagicBall_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_step_of_2048(CONSOLE_GRAPHICS_INFO &G2048_CGI)
{
	const char *gname = "2048";
	const int row = 6, col = 5;

	/* Ԥ��һ������ */
	int g2048[row][col] = {
		{0, 0, 0, 0, 0},
		{0, 2, 0, 0, 0},
		{0, 0, 0, 4, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 2, 0, 0, 0},
	};
	int g2048_full[row][col] = {
		{8192, 128, 131072, 256, 512},
		{8, 2, 4096, 1024, 65536},
		{16, 1024, 4, 4, 8192},
		{64, 1024, 512, 256, 4096},
		{2048, 32, 16384, 128, 2048},
		{2, 8, 64, 32768, 16},
	};

	/* ����2 ~ 131072 �������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý������� + ��ǰ + ��ǰ�������Ϣ�������������еķ���
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},  //0����ʾ���ÿո���伴��
		{2, CCT_COLOR::hyellow, CCT_COLOR::black, NULL},
		{4, CCT_COLOR::hred, CCT_COLOR::black, NULL},
		{8, CCT_COLOR::green, CCT_COLOR::black, NULL},
		{16, CCT_COLOR::red, CCT_COLOR::black, NULL},
		{32, CCT_COLOR::hgreen, CCT_COLOR::black, NULL},
		{64, CCT_COLOR::hyellow, CCT_COLOR::black, NULL},
		{128, CCT_COLOR::hred, CCT_COLOR::black, NULL},
		{256, CCT_COLOR::hwhite, CCT_COLOR::black, NULL},
		{512, CCT_COLOR::hblack, CCT_COLOR::black, NULL},
		{1024, CCT_COLOR::hpink, CCT_COLOR::black, NULL},
		{2048, CCT_COLOR::white, CCT_COLOR::black, NULL},
		{4096, CCT_COLOR::yellow, CCT_COLOR::black, NULL},
		{8192, CCT_COLOR::pink, CCT_COLOR::black, NULL},
		{16384, CCT_COLOR::hblue, CCT_COLOR::black, NULL},
		{32768, CCT_COLOR::hcyan, CCT_COLOR::black, NULL},
		{65536, CCT_COLOR::hgreen, CCT_COLOR::black, NULL},
		{131072, CCT_COLOR::hpink, CCT_COLOR::black, NULL},  //������ģ������Լ�����
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};

	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	G2048_CGI.gmw_set_rowcol(row, col);

	/* ��ʾ��� */
	G2048_CGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, G2048_CGI.lines(), G2048_CGI.cols());
	G2048_CGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	G2048_CGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			G2048_CGI.gmw_draw_block(i, j, g2048_full[i][j], bdi_normal);
		}

	to_be_continued(gname, "ȫ��ֵ��ʾ���", G2048_CGI);

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			G2048_CGI.gmw_draw_block(i, j, g2048[i][j], bdi_normal);
		}
	to_be_continued(gname, "��ʼ�����", G2048_CGI);

	/* �ƶ�ĳ����
	   ע��1��������ѡ��һ�����֣�ʵ����Ϸ�и��ݼ��̶�����ȷ��ĳ��ɫ��
		   2����������ѡ�˽���λ�ã�ʵ����Ϸ�и��ݼ�ͷ�������ƶ�����0Ϊֹ */
	G2048_CGI.gmw_move_block(2, 3, g2048[2][3], 0, bdi_normal, UP_TO_DOWN, 2);
	/* Ϊ�˺����ƶ������������ֵ */
	g2048[2 + 2][3] = g2048[2][3];
	g2048[2][3] = 0;
	to_be_continued(gname, "�����ƶ�2��", G2048_CGI);

	G2048_CGI.gmw_move_block(4, 3, g2048[4][3], 0, bdi_normal, RIGHT_TO_LEFT, 3);
	/* Ϊ�˺����ƶ������������ֵ */
	g2048[4][3 - 3] = g2048[4][3];
	g2048[4][3] = 0;
	to_be_continued(gname, "�����ƶ�3��", G2048_CGI);

	G2048_CGI.gmw_move_block(4, 0, g2048[4][0], 0, bdi_normal, DOWN_TO_UP, 2);
	/* Ϊ�˺����ƶ������������ֵ */
	g2048[4 - 2][0] = g2048[4][0];
	g2048[4][0] = 0;
	to_be_continued(gname, "�����ƶ�2��", G2048_CGI);

	G2048_CGI.gmw_move_block(2, 0, g2048[2][0], 0, bdi_normal, LEFT_TO_RIGHT, 3);
	/* Ϊ�˺����ƶ������������ֵ */
	g2048[2][0 + 3] = g2048[2][0];
	g2048[2][0] = 0;
	to_be_continued(gname, "�����ƶ�3��", G2048_CGI);

	/* ģ��һ�����µĺϲ�
	   ע��1����������ͬ���ֺϲ�����ʾ������δ��
		   2��δ�޸������ֵ */
	G2048_CGI.gmw_move_block(1, 1, g2048[1][1], 0, bdi_normal, DOWN_TO_UP, 1);
	G2048_CGI.gmw_move_block(5, 1, g2048[5][1], 0, bdi_normal, DOWN_TO_UP, 5); //�ƶ���(0,1)���غ�λ��
	//�ƶ����غ�λ�ú��������ֵ���ɫ�ػ�(0,1)
	G2048_CGI.gmw_draw_block(0, 1, g2048[1][1] + g2048[5][1], bdi_normal); //δ�޸������ֵ��ֱ���úͽ�����ʾ

	G2048_CGI.gmw_move_block(2, 3, g2048[2][3], 0, bdi_normal, DOWN_TO_UP, 2);
	to_be_continued(gname, "���һ�����Ϻϲ�", G2048_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_2048(void)
{
	CONSOLE_GRAPHICS_INFO G2048_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
	G2048_CGI.gmw_set_color(CCT_COLOR::black, CCT_COLOR::white);			//����������ɫ
	G2048_CGI.gmw_set_font("������", 16);						//����
	G2048_CGI.gmw_set_frame_style(10, 5, true);					//��Ϸ��������ÿ��ɫ���10��5���зָ��ߡ�����ɫ����߿򣬿��Ϊ10(�����6λ����)���߶�Ϊ5(Ϊ�˱���ɫ��Ϊ����)��
	G2048_CGI.gmw_set_frame_color(CCT_COLOR::white, CCT_COLOR::black);	//��Ϸ��������ɫ
	G2048_CGI.gmw_set_block_border_switch(true);				//Сɫ����߿�
	G2048_CGI.gmw_set_rowno_switch(true);						//��ʾ�к�
	G2048_CGI.gmw_set_colno_switch(true);						//��ʾ�б�

	test_step_of_2048(G2048_CGI);

	/* ��Ϊ�޷ָ��ߣ�����һ�� */

	G2048_CGI.gmw_set_font("Terminal", 16, 8);	//����
	G2048_CGI.gmw_set_frame_style(10, 5, false);//��Ϸ��������ÿ��ɫ���10��5���޷ָ��ߡ�����ɫ����߿򣬿��Ϊ10(�����6λ����)���߶�Ϊ5(Ϊ�˱���ɫ��Ϊ����)��
	G2048_CGI.gmw_set_ext_rowcol(2, 3, 4, 5);	//�������У���2��3����4��5
	G2048_CGI.gmw_set_rowno_switch(false);		//����ʾ�к�
	G2048_CGI.gmw_set_colno_switch(false);		//����ʾ�б�

	test_step_of_2048(G2048_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_step_of_merge_to_10(CONSOLE_GRAPHICS_INFO &Mto10_CGI)
{
	const char *gname = "�ϳ�ʮ";
	const int row = 6, col = 5;

	/* Ԥ��һ������ */
	int mto10[row][col] = {
		{1, 3, 2, 1, 1},
		{3, 1, 3, 2, 2},
		{3, 1, 1, 2, 1},
		{1, 1, 1, 2, 1},
		{2, 3, 2, 3, 3},
		{1, 2, 2, 2, 1}
	};

	/* ����1 ~ 10 �������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý������� + ��ǰ + ��ǰ�������Ϣ�������������еķ���
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},  //0����ʾ���ÿո���伴��
		{1,  CCT_COLOR::blue,   CCT_COLOR::black,  NULL},	//����1�ġ�������״̬
		{2,  CCT_COLOR::green,  CCT_COLOR::black,  NULL},
		{3,  CCT_COLOR::cyan,   CCT_COLOR::black,  NULL},
		{4,  CCT_COLOR::red,    CCT_COLOR::black,  NULL},
		{5,  CCT_COLOR::pink,   CCT_COLOR::black,  NULL},
		{6,  CCT_COLOR::hblue,  CCT_COLOR::black,  NULL},
		{7,  CCT_COLOR::hgreen, CCT_COLOR::black,  NULL},
		{8,  CCT_COLOR::hcyan,  CCT_COLOR::black,  NULL},
		{9,  CCT_COLOR::hred,   CCT_COLOR::black,  NULL},
		{10, CCT_COLOR::hpink,  CCT_COLOR::black,  NULL},	//����10�ġ�������״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},  //0����ʾ���ÿո���伴��
		{1,  CCT_COLOR::blue,   CCT_COLOR::white,  NULL},//����1�ġ���ѡ��+������״̬
		{2,  CCT_COLOR::green,  CCT_COLOR::white,  NULL},
		{3,  CCT_COLOR::cyan,   CCT_COLOR::white,  NULL},
		{4,  CCT_COLOR::red,    CCT_COLOR::white,  NULL},
		{5,  CCT_COLOR::pink,   CCT_COLOR::white,  NULL},
		{6,  CCT_COLOR::hblue,  CCT_COLOR::white,  NULL},
		{7,  CCT_COLOR::hgreen, CCT_COLOR::white,  NULL},
		{8,  CCT_COLOR::hcyan,  CCT_COLOR::white,  NULL},
		{9,  CCT_COLOR::hred,   CCT_COLOR::white,  NULL},
		{10, CCT_COLOR::hpink,  CCT_COLOR::white,  NULL},	//����10�ġ���ѡ��+������״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},  //0����ʾ���ÿո���伴��
		{1,  CCT_COLOR::blue,   CCT_COLOR::hwhite,  NULL},//����1�ġ�ѡ�С�״̬
		{2,  CCT_COLOR::green,  CCT_COLOR::hwhite,  NULL},
		{3,  CCT_COLOR::cyan,   CCT_COLOR::hwhite,  NULL},
		{4,  CCT_COLOR::red,    CCT_COLOR::hwhite,  NULL},
		{5,  CCT_COLOR::pink,   CCT_COLOR::hwhite,  NULL},
		{6,  CCT_COLOR::hblue,  CCT_COLOR::hwhite,  NULL},
		{7,  CCT_COLOR::hgreen, CCT_COLOR::hwhite,  NULL},
		{8,  CCT_COLOR::hcyan,  CCT_COLOR::hwhite,  NULL},
		{9,  CCT_COLOR::hred,   CCT_COLOR::hwhite,  NULL},
		{10, CCT_COLOR::hpink,  CCT_COLOR::hwhite,  NULL},	//����10�ġ�ѡ�С�״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};

	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	Mto10_CGI.gmw_set_rowcol(row, col);

	/* ��ʾ��� */
	Mto10_CGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, Mto10_CGI.lines(), Mto10_CGI.cols());
	Mto10_CGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	Mto10_CGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			Mto10_CGI.gmw_draw_block(i, j, mto10[i][j], bdi_normal);
		}
	to_be_continued(gname, "��ʼ�����", Mto10_CGI);

	/* ��ʾһ����ǰ�ģ������ƶ�/�����ϰ���ͷ����Ч���� - �˴����ָ��һ����ʵ����Ϸ�и��ݼ��̻����Ĳ�����ѡ�� */
	Mto10_CGI.gmw_draw_block(2, 2, mto10[2][2], bdi_related);
	to_be_continued(gname, "��ǰ��ѡ״̬", Mto10_CGI);

	/* i=0ѭ������ʾһ��ѡ��������ģ��������/�س������˴�ֱ��д�����꣬ʵ����Ϸ��Ҫ�ò��Һ��������ҵ�ǰѡ����ֵ��ͬ������������
	   i=1ѭ��������ѡ���������������ǽ�����ֵ��Ϊ0��ͨ����ʾ����ֵ�ķ�ʽ��ʾ�հ׿飬�����������ǲ�������ֵ��ֱ�ӽ�������Ϊ0��*/
	for (i = 0; i < 2; i++) {
		if (i == 1)
			mto10[2][2] = mto10[1][1] = mto10[2][1] = mto10[3][0] = mto10[3][1] = mto10[3][2] = 0; //�������ֵ

		Mto10_CGI.gmw_draw_block(2, 2, mto10[2][2], bdi_selected); //������ֵΪ0ʱ��ʾ����
		Mto10_CGI.gmw_draw_block(1, 1, mto10[1][1], bdi_related);
		Mto10_CGI.gmw_draw_block(2, 1, mto10[2][1], bdi_related);
		Mto10_CGI.gmw_draw_block(3, 0, mto10[3][0], bdi_related);
		Mto10_CGI.gmw_draw_block(3, 1, mto10[3][1], bdi_related);
		Mto10_CGI.gmw_draw_block(3, 2, mto10[3][2], bdi_related);

		if (i == 0)
			to_be_continued(gname, "��ʾ��ǰѡ�м�������", Mto10_CGI);
		else {
			/* ѡ������ʾ��ֵ */
			mto10[2][2] = 2; //�˴�ֱ��д��
			Mto10_CGI.gmw_draw_block(2, 2, mto10[2][2], bdi_normal);

			to_be_continued(gname, "������ǰѡ�м�������", Mto10_CGI);
		}
	}

	/* ���ϲ��кϲ��ģ�2,2��ɫ�����䵽��3,2�� - ����Ӧ����ɫ�������δ����ʵ�ʳ����а�����м���
	   ע��1��δ�޸��ڲ������ֵ
		   2��δʹ��ѭ����ֱ��д�˶�ֵ */
	Mto10_CGI.gmw_move_block(2, 2, mto10[2][2], 0, bdi_normal, UP_TO_DOWN, 1);
	to_be_continued(gname, "����1��ɫ�����", Mto10_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_merge_to_10(void)
{
	CONSOLE_GRAPHICS_INFO Mto10_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
	Mto10_CGI.gmw_set_color(CCT_COLOR::black, CCT_COLOR::white);
	Mto10_CGI.gmw_set_font("Terminal", 16, 8);
	Mto10_CGI.gmw_set_frame_style(6, 3, true);	//ɫ����߿򣬿��Ϊ6(�����2λ����)���߶�Ϊ3(����һ��)
	Mto10_CGI.gmw_set_frame_color(CCT_COLOR::white, CCT_COLOR::black);
	Mto10_CGI.gmw_set_block_border_switch(true);
	Mto10_CGI.gmw_set_rowno_switch(true);//��ʾ�к�
	Mto10_CGI.gmw_set_colno_switch(true);//��ʾ�б�

	test_step_of_merge_to_10(Mto10_CGI);

	/* ��Ϊ�޷ָ��ߣ�����һ�� */
	Mto10_CGI.gmw_set_font("Terminal", 20, 10);
	Mto10_CGI.gmw_set_frame_style(6, 3, false);//�޷ָ���
	Mto10_CGI.gmw_set_ext_rowcol(2, 3, 4, 5);	//�������У���2��3����4��5

	test_step_of_merge_to_10(Mto10_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_step_of_popstar(CONSOLE_GRAPHICS_INFO &PopStar_CGI)
{
	const char *gname = "PopStar";
	const int row = 8, col = 9;

	/* Ԥ��һ������ */
	int popstar[row][col] = {
		{1, 2, 1, 3, 5, 2, 5, 5, 4},
		{2, 2, 3, 4, 5, 1, 1, 2, 1},
		{1, 1, 4, 4, 5, 2, 1, 1, 1},
		{2, 2, 5, 4, 3, 3, 2, 3, 4},
		{4, 3, 5, 5, 5, 2, 5, 1, 2},
		{1, 3, 3, 2, 2, 2, 3, 3, 3},
		{5, 4, 2, 2, 3, 3, 3, 1, 2},
		{4, 2, 2, 2, 3, 2, 2, 2, 2}
	};
	int popstar_col_moved[row][col] = {
		{0, 2, 0, 0, 5, 0, 0, 0, 0},
		{0, 2, 0, 0, 5, 0, 0, 0, 0},
		{1, 1, 0, 0, 5, 0, 0, 0, 0},
		{2, 2, 5, 0, 3, 0, 0, 3, 0},
		{4, 3, 5, 0, 5, 0, 0, 1, 0},
		{1, 3, 3, 2, 2, 0, 0, 3, 0},
		{5, 4, 2, 2, 3, 0, 0, 1, 0},
		{4, 2, 2, 2, 3, 0, 0, 2, 0}
	};

	/* ����0-5�������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý������� + ��ǰ + ��ǰ�������Ϣ�������������еķ���
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ */

	 /* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{0, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //0����ʾ���ÿո���伴��
		{1, CCT_COLOR::hblue, CCT_COLOR::black, "��"},
		{2, CCT_COLOR::hgreen, CCT_COLOR::black, "��"},
		{3, CCT_COLOR::hcyan, CCT_COLOR::black, "��"},
		{4, CCT_COLOR::hred, CCT_COLOR::black, "��"},
		{5, CCT_COLOR::hpink, CCT_COLOR::black, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ���ǰѡ����״̬+ѡ�к������״̬�� */
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //�հ�
		{1, CCT_COLOR::hblue, CCT_COLOR::white, "��"},
		{2, CCT_COLOR::hgreen, CCT_COLOR::white, "��"},
		{3, CCT_COLOR::hcyan, CCT_COLOR::white, "��"},
		{4, CCT_COLOR::hred, CCT_COLOR::white, "��"},
		{5, CCT_COLOR::hpink, CCT_COLOR::white, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, "  "},  //�հ�
		{1, CCT_COLOR::hblue, CCT_COLOR::hwhite, "��"},
		{2, CCT_COLOR::hgreen, CCT_COLOR::hwhite, "��"},
		{3, CCT_COLOR::hcyan, CCT_COLOR::hwhite, "��"},
		{4, CCT_COLOR::hred, CCT_COLOR::hwhite, "��"},
		{5, CCT_COLOR::hpink, CCT_COLOR::hwhite, "��"},
		{BDI_VALUE_END, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL} //�жϽ�������Ϊ-999
	};

	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	PopStar_CGI.gmw_set_rowcol(row, col);

	/* ��ʾ��� */
	PopStar_CGI.gmw_draw_frame();

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, PopStar_CGI.lines(), PopStar_CGI.cols());
	PopStar_CGI.gmw_top_status_line(temp);

	/* ��״̬����ʾ���� */
	PopStar_CGI.gmw_lower_status_line("����End����", "���Խ�����"); //ֻ�Ǹ�����ʾ���ѣ�������������End����������Ҫ�����뼰�ж�

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			PopStar_CGI.gmw_draw_block(i, j, popstar[i][j], bdi_normal);
		}
	to_be_continued(gname, "��ʼ�����", PopStar_CGI);

	/* ��ʾһ����ǰ�ģ������ƶ�/�����ϰ���ͷ����Ч���� - �˴����ָ��һ����ʵ����Ϸ�и��ݼ��̻����Ĳ�����ѡ�� */
	PopStar_CGI.gmw_draw_block(4, 4, popstar[4][4], bdi_related);
	to_be_continued(gname, "��ǰѡ��״̬", PopStar_CGI);

	/* ��ʾһ��ѡ��������ģ��������/�س������˴�ֱ��д�����꣬ʵ����Ϸ��Ҫ�ò��Һ��������ҵ�ǰѡ����ֵ��ͬ������������ */
	PopStar_CGI.gmw_draw_block(4, 4, popstar[4][4], bdi_selected);
	PopStar_CGI.gmw_draw_block(4, 3, popstar[4][3], bdi_related);
	PopStar_CGI.gmw_draw_block(4, 2, popstar[4][2], bdi_related);
	PopStar_CGI.gmw_draw_block(3, 2, popstar[3][2], bdi_related);
	to_be_continued(gname, "��ǰѡ�м���������ʾ״̬", PopStar_CGI);

	/* ����ѡ��������� - �˴�ֱ��д������ */
	PopStar_CGI.gmw_draw_block(4, 4, 0, bdi_normal);
	PopStar_CGI.gmw_draw_block(4, 3, 0, bdi_normal);
	PopStar_CGI.gmw_draw_block(4, 2, 0, bdi_normal);
	PopStar_CGI.gmw_draw_block(3, 2, 0, bdi_normal);
	to_be_continued(gname, "����4�����", PopStar_CGI);

	/* ���ϲ��������ģ�2,2��ɫ�����䵽��4,2��
	   ע��1��δ�޸��ڲ������ֵ
		   2��δʹ��ѭ����ֱ��д�˶�ֵ */
	PopStar_CGI.gmw_move_block(2, 2, popstar[2][2], 0, bdi_normal, UP_TO_DOWN, 2);
	to_be_continued(gname, "����1��ɫ�����", PopStar_CGI);

	/* ��ʾ�����ƶ�(ӦΪ�������˴�ֱ��д) */
	{
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++) {
				PopStar_CGI.gmw_draw_block(i, j, popstar_col_moved[i][j], bdi_normal);
			}
		to_be_continued(gname, "���ƶ���ʼ�����", PopStar_CGI);

		//���дΪ��������������const���ǲ���
		const int moved_col_no = 7;
		const int distance = 2;

		for (i = row - 1; i >= 0; i--) {
			if (popstar_col_moved[i][moved_col_no] == 0)
				continue; //�հ׿鲻�ƶ�
			PopStar_CGI.gmw_move_block(i, moved_col_no, popstar_col_moved[i][moved_col_no], 0, bdi_normal, RIGHT_TO_LEFT, distance);
			//Ӧ�޸������ֵ���˴���
		}
	}
	to_be_continued(gname, "��������2�����", PopStar_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void test_popstar(void)
{
	CONSOLE_GRAPHICS_INFO PopStar_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
	PopStar_CGI.gmw_set_color(CCT_COLOR::black, CCT_COLOR::white);
	PopStar_CGI.gmw_set_font("Terminal", 16, 8);
	PopStar_CGI.gmw_set_frame_style(6, 3, true);	//ɫ����߿򣬿��Ϊ6���߶�Ϊ3
	PopStar_CGI.gmw_set_frame_color(CCT_COLOR::white, CCT_COLOR::black);
	PopStar_CGI.gmw_set_block_border_switch(true);

	test_step_of_popstar(PopStar_CGI);

	/* ��Ϊ�޷ָ��ߣ�����һ�� */
	PopStar_CGI.gmw_set_font("������", 20);
	PopStar_CGI.gmw_set_frame_style(6, 3, false);
	PopStar_CGI.gmw_set_ext_rowcol(2, 3, 4, 5);	//��2��3����4��5
	PopStar_CGI.gmw_set_rowno_switch(true);//��ʾ�к�
	PopStar_CGI.gmw_set_colno_switch(true);//��ʾ�б�

	test_step_of_popstar(PopStar_CGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	/* ��Ϊ������ lib_class_gmw.lib���˴��ȼ�鼸���ṹ��Ĵ�С�Ƿ����Ҫ�� */
	if (sizeof(STATUS_LINE_INFO) != 120) {
		cout << "STATUS_LINE_INFO ����120�ֽڣ����ʹ�� lib_class_gmw.lib �еĺ�������ܳ���" << endl;
		return -1;
	}
	if (sizeof(CONSOLE_FRAME_INFO) != 136) {
		cout << "CONSOLE_FRAME_INFO ����136�ֽڣ����ʹ�� lib_class_gmw.lib �еĺ�������ܳ���" << endl;
		return -1;
	}
	if (sizeof(CONSOLE_BLOCK_INFO) != 84) {
		cout << "CONSOLE_BLOCK_INFO ����84�ֽڣ����ʹ�� lib_class_gmw.lib �еĺ�������ܳ���" << endl;
		return -1;
	}
	if (sizeof(CONSOLE_GRAPHICS_INFO) != 492) {
		cout << "CONSOLE_GRAPHICS_INFO ����492�ֽڣ����ʹ�� lib_class_gmw.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	/* �ù̶�ֵ���Կ�� */
	test_by_fixed();

	/* �ü�������ֵ���Կ�� */
	test_by_input();

	/* �� color_linez ��������Ϸ���� */
	test_color_linez();

	/* �� magic_ball ��������Ϸ���� */
	test_magic_ball();

	/* �� 2048 ��������Ϸ���� */
	test_2048();

	/* �� �ϳ�ʮ ��������Ϸ���� */
	test_merge_to_10();

	/* �� �������� ��������Ϸ���� */
	test_popstar();

	CCT cct;
	cct.setcolor();

	system("pause");

	return 0;
}
