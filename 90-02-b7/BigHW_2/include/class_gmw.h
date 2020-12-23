/*1952339 ��08 ��ܰ��*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
#include "../include/class_gmw_sli.h"
#include "../include/class_gmw_cfi.h"
#include "../include/class_gmw_cbi.h"
using namespace std;

/* ���� BLOCK_DISPLAY_INFO �����б�ʾ �հ׵�����ֵ/����������ֵ */
#define BDI_VALUE_BLANK		0		//����հ׵�����ֵ
#define BDI_VALUE_END		-999		//�������������ֵ

/* ����ɫ����ʾʱ���ڲ������intֵ���������ʾͼ�εĶ�Ӧ��ϵ
   ע���˽ṹ�������ֵ�ڲ��������ж��壬������Ϸ�Ĳ�ͬ����ͬ */
typedef struct _block_display_info_ {
	const int   value;	//Ҫ��ʾ���ڲ�����ֵ
	const CCT_COLOR   bgcolor;	//-1��ʾ����Ϸ���򱳾�ɫ
	const CCT_COLOR   fgcolor;	//-1��ʾ����Ϸ����ǰ��ɫ
	const char* content;	//�ڲ�����ֵ��Ӧ��ͼ�Σ����ΪNULL����ֱ����ʾ�ڲ������ֵ��
} BLOCK_DISPLAY_INFO;

/* ������������/�ֺ���Ϣ�Ľṹ�� */
#define		FONTNAME_LEN	12	//�������Ƶ���󳤶ȣ���β�㣩
typedef struct _console_font_type_ {
	char font_type[FONTNAME_LEN];
	int  font_size_width;
	int  font_size_high;
} CONSOLE_FONT_TYPE;

/* ������ʱ������ */
#define DELAY_OF_DRAW_FRAME		0	//����Ϸ�����ʱ����ʱ
#define DELAY_OF_DRAW_BLOCK		1	//��ɫ��ʱ����ʱ
#define DELAY_OF_BLOCK_MOVED		2	//ɫ���ƶ�ʱ����ʱ

#define BLOCK_MOVED_DELAY_MS		15	//ɫ���ƶ���ȱʡ��ʱ����λms����������ȱʡΪ0��

/* ����ɫ��������ƶ����� */
#define DOWN_TO_UP		0
#define UP_TO_DOWN		1
#define RIGHT_TO_LEFT	2
#define LEFT_TO_RIGHT	3

/* ����������������ȫ����Ϣ�Ľṹ�� */
class CONSOLE_GRAPHICS_INFO {
protected:
	CCT cct;	//���class�����ݳ�Ա������������̬��Ա�������Ը����Լ�����Ҫ���������CFI/CBI/SLI/CFT��

	/* ---------------------------------------------------------------------------------------------------------------
		�ĸ�����������Ϣ�����ַ�����
		1������������һ�������Ϊ CONSOLE_GRAPHICS_INFO �ĳ�Ա
		2��Ҳ����ͨ���̳з�ʽ��Ϊ CONSOLE_GRAPHICS_INFO �Ļ���
	   ---------------------------------------------------------------------------------------------------------------
	 */
	/* �������Ϣ����������Ϊ��Ա��Ҳ���Բ��ü̳з�ʽ */
	CONSOLE_FRAME_INFO CFI;		//136�ֽ�

	/* ɫ����Ϣ����������Ϊ��Ա��Ҳ���Բ��ü̳з�ʽ */
	CONSOLE_BLOCK_INFO CBI;		//84�ֽ�

	/* ״̬����Ϣ����������Ϊ��Ա��Ҳ���Բ��ü̳з�ʽ */
	STATUS_LINE_INFO SLI;		//120�ֽ�

	/* ������Ϣ */
	CONSOLE_FONT_TYPE CFT;		//20�ֽ�

	/* ---------------------------------------------------------------------------------------------------------------
		���涨����ǿ�ͨ�����ú����ı��ֵ����׼�޸ĳ�Ա������׼�ı�����
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* ����ͼ�ν��������������Ҫ�Ķ��������� */
	int extern_up_lines;
	int extern_down_lines;
	int extern_left_cols;
	int extern_right_cols;

	/* ��Ϸ��������������ɫ��������� */
	int row_num;
	int col_num;

	/* ����ͼ�ν��棨������ܡ�����״̬�����к��бꡢ�������У��ı���ɫ��ǰ��ɫ */
	CCT_COLOR area_bgcolor;
	CCT_COLOR area_fgcolor;

	/* �Ƿ���Ҫ����״̬��
	   - ע��true-��Ҫ false-����Ҫ
	   -    �������Ϊfalse����ʹ������״̬����Ϣ��ʾ������Ҳ����ʾ���ݣ�
	   - �� STATUS_LINE_INFO �е� is_top_status_line / is_lower_status_line �ظ���ֻҪ�ǿ��ǵ���ͬλ��ʵ��ʱ�ķ��ʷ����� */
	bool top_status_line;
	bool lower_status_line;

	/* ��ӡ�����ʱ�Ƿ���Ҫ�к��б� */
	bool draw_frame_with_row_no;
	bool draw_frame_with_col_no;

	/* ��ʱʱ������ */
	int delay_of_draw_frame;		//������ǵ���ʱ
	int delay_of_draw_block;		//����Ϸ�����ʱ
	int delay_of_block_moved;	//��Ϸ���ƶ�����ʱ

	/* ---------------------------------------------------------------------------------------------------------------
		�������ĸ�ֵ����ͨ�����ú���ֱ�����õ�
		1��start_x/start_y �� ����ͼ�ν�������������Ĳο�������ʼλ��(���Ͻǣ�
			- ע����Ϸ����ܣ������а���m��n�е�ɫ�������⣬������״̬����0/1�У�/��״̬����0/1�У�/�к���ʾ��0/2�У�/�б���ʾ����0/1�У�
			-     ������ֵ������ͬ������£�start_x/start_y��ֵ�ǲ�ͬ��
		2��total_lines/total_cols�Ǽ������Ԫ�غ�����cmd���ڵĴ�С
	   ---------------------------------------------------------------------------------------------------------------
	*/
	/* ���������Ĳο�������ʼλ�ã����Ͻǣ�����extern�� */
	int start_x;
	int start_y;

	/* �������Ԫ�غ�����cmd���ڵĴ�С */
	int total_lines;		//Ϊ�˸��������뷨��ʾ�м����н�������ʾ��Ϣ���ռ䣬Ҫ���ڼ���õ��Ľ�������ϣ��϶���ռ�+��״̬��+�б���ʾ+������+��״̬����+ 4��1�������뷨��ʾ��+3Ԥ�����У�
	int total_cols;

	/* ---------------------------------------------------------------------------------------------------------------
		���������������Ϊ��Ҫ��ֵ����Щֵ����ͨ�����ú���ֱ�����ã�ֻ��Ϊ�˷�������е���(����Ҫÿ���ظ�����)
		˵������Ϊ������ lib_class_gmw.lib��Ϊ�˱������ߵĽṹ��һ�£������ⲿ�ִ�СΪ�̶�64�ֽڣ�Ŀǰ��pad����
			  �����Ҫ�����Ӧ���ݣ��뱣���������+����ֽ�=64�ֽ�
				���磺int data1;
					 int data2;
					 char pad[56];
	   ---------------------------------------------------------------------------------------------------------------
	*/
	char pad[64];

	/* ------------------------------
		����������� �ڲ���Ա ����
	   ------------------------------ */
	bool gmw_inner_check_inarea(int x, int y)const;

public:
	/* -----------------------------------------------
		���ⲿ���ʵĺ�����������Ķ���Ҳ�����������
	   ----------------------------------------------- */

	/* ��ȱʡֵ��һ��ȫ�ֳ�ʼ�� */
	CONSOLE_GRAPHICS_INFO(const int row = 10, const int col = 10, const CCT_COLOR bgcolor = CCT_COLOR::black, const CCT_COLOR fgcolor = CCT_COLOR::white);

	/* ������ - ��ӡ CONSOLE_GRAPHICS_INFO �еĸ���Աֵ */
	int gmw_print() const;

	/* ȡ���ڵ� lines �� cols */
	int lines() const;
	int cols() const;

	/* �����������ڵ�ĳЩ���� */
	int gmw_set_rowcol(const int row, const int col);
	int gmw_set_color(const CCT_COLOR bgcolor = CCT_COLOR::black, const CCT_COLOR fgcolor = CCT_COLOR::white, const bool cascade = true);
	int gmw_set_font(const char* fontname = "Terminal", const int fs_high = 16, const int fs_width = 8);
	int gmw_set_delay(const int type, const int delay_ms);
	int gmw_set_ext_rowcol(const int up_lines = 0, const int down_lines = 0, const int left_cols = 0, const int right_cols = 0);

	/* ����������Ϸ����ܵĲ��� */
	int gmw_set_frame_default_linetype(const int type);
	int gmw_set_frame_linetype(const char* top_left = "�X", const char* lower_left = "�^", const char* top_right = "�[",
		const char* lower_right = "�a", const char* h_normal = "�T", const char* v_normal = "�U", const char* h_top_separator = "�j",
		const char* h_lower_separator = "�m", const char* v_left_separator = "�d", const char* v_right_separator = "�g", const char* mid_separator = "�p");
	int gmw_set_frame_style(const int block_width = 2, const int block_high = 1, const bool separator = true);
	int gmw_set_frame_color(const CCT_COLOR bgcolor = CCT_COLOR(-1), const CCT_COLOR fgcolor = CCT_COLOR(-1));

	/* ����ÿ��ɫ��Ĳ��� */
	int gmw_set_block_default_linetype(const int def_type);
	int gmw_set_block_linetype(const char* top_left = "�X", const char* lower_left = "�^", const char* top_right = "�[",
		const char* lower_right = "�a", const char* h_normal = "�T", const char* v_normal = "�U");
	int gmw_set_block_border_switch(const bool on_off = false);

	/* �����Ƿ���Ҫ����״̬������ɫ���ֿ�����������Ŀ����color�����ڸı�������Ļ��ɫ����Ҫ�������� */
	int gmw_set_status_line_switch(const int type, const bool on_off = true);
	int gmw_set_status_line_color(const int type, const CCT_COLOR normal_bgcolor = CCT_COLOR(-1), const CCT_COLOR normal_fgcolor = CCT_COLOR(-1), const CCT_COLOR catchy_bgcolor = CCT_COLOR(-1), const CCT_COLOR catchy_fgcolor = CCT_COLOR(-1));

	/* �����Ƿ���Ҫ�к��б� */
	int gmw_set_rowno_switch(const bool on_off = false);
	int gmw_set_colno_switch(const bool on_off = false);

	/* ����Ϸ����� */
	int gmw_draw_frame() const;
	/* ����״̬������ʾ��Ϣ */
	int gmw_top_status_line(const char* msg, const char* catchy_msg = NULL) const;
	/* ����״̬������ʾ��Ϣ */
	int gmw_lower_status_line(const char* msg, const char* catchy_msg = NULL) const;
	/* ��һ��ɫ�� */
	int gmw_draw_block(const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi) const;
	/* �ƶ�һ��ɫ�� */
	int gmw_move_block(const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance) const;
	/* �����̺���� */
	CCT_KMEVENT gmw_read_keyboard_and_mouse(CCT_MOUSE& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line = true) const;

	/* ������Ԫ���� */
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};	//end of class CONSOLE_GRAPHICS_INFO

