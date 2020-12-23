/*1952339 ��08 ��ܰ��*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <Windows.h>
#include <cstring>
//��������Լ���Ҫ��ͷ�ļ�
#include "../include/class_cct.h"
#include "../include/class_gmw.h"
using namespace std;

/* --------------------------------------------------------------------------
	�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ���
		1���������٣����û��
		2����̬ȫ��ֻ������/�궨���������
		3���������ⲿȫ�ֱ���
   --------------------------------------------------------------------------
*/

/* --------------------------------------------------------------------------
	�˴����Ը�����Ҫ���ڲ�������ʵ��
		1�����������ޣ�����Ϊ gmw_inner_*
		2����������
		3������ǳ�Ա��������������private/protected�������ĺ���
		4�������ȫ�ֺ�����������static�����������ڱ�Դ�����ļ��ڲ�ʹ��
   --------------------------------------------------------------------------
*/

static void make_linetype(char* aim, const char* source)
{
	if (source == NULL)
		strcpy(aim, "  ");
	else if (strlen(source) > 2)
		aim[0] = *source,
		aim[1] = *(source + 1),
		aim[2] = 0;
	else if (strlen(source) == 1)
		aim[0] = *source,
		aim[1] = *(source + 1),
		aim[2] = 0;
	else
		strcpy(aim, source);
}

bool CONSOLE_GRAPHICS_INFO::gmw_inner_check_inarea(int x, int y)const
{
	int right_x = col_num * (CFI.block_width + CFI.separator) * 2;
	int lower_y = row_num * (CFI.block_high + CFI.separator);
	if (!x || !y || x >= right_x || y >= lower_y)
		return 0;
	else
		x -= 2, --y;
	int unit_x = (CFI.block_width + CFI.separator) * 2 + 1;
	int unit_y = CFI.block_high + CFI.separator + 1;
	x %= unit_x;
	y %= unit_y;
	if (CFI.separator)
		return x >= 0 && x <= (CFI.block_width - 1) * 2 && y >= 0 && y <= CFI.block_high - 1;
	else
		return 1;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/

 /* --------------------------------------------------------------------------
	  ʵ����������ĺ���������������׼����
	 --------------------------------------------------------------------------
 */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ����ܵ�������
  ���������const int row	������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
		   const int col	������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
  �� �� ֵ��
  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
            2�����еı仯�ᵼ�� CONSOLE_GRAPHICS_INFO ��������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_rowcol(const int row, const int col)
{
	row_num = row < 0 ? 0 : row;
	col_num = col < 0 ? 0 : col;
	SLI.top_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.top_start_y = extern_up_lines;
	SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������const int bg_color	��ǰ��ɫ��ȱʡ CCT_COLOR::black��
		   const int fg_color	������ɫ��ȱʡ CCT_COLOR::white��
		   const bool cascade	���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
				    ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_color(const CCT_COLOR bgcolor, const CCT_COLOR fgcolor, const bool cascade)
{
	area_bgcolor = bgcolor;
	area_fgcolor = fgcolor;
	if (SLI.top_catchy_fgcolor == CCT_COLOR::black)
		SLI.top_catchy_fgcolor = CCT_COLOR::white;
	if (SLI.lower_catchy_fgcolor == CCT_COLOR::black)
		SLI.lower_catchy_fgcolor = CCT_COLOR::white;
	if (cascade) {
		CFI.setcolor(bgcolor, fgcolor);
		SLI.setcolor_top_normal(bgcolor, fgcolor);
		SLI.setcolor_top_catchy(bgcolor);
		SLI.setcolor_lower_normal(bgcolor, fgcolor);
		SLI.setcolor_lower_catchy(bgcolor);
	}
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������const char *fontname	���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high		������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width		������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����class_cct�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
            2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_font(const char *fontname, const int fs_high, const int fs_width)
{
	int h = fs_high < 0 ? 16 : fs_high;
	int w = fs_width < 0 ? 8 : fs_width;
	if (strcmp(fontname, "Terminal") == 0 || strcmp(fontname, "������") == 0) {
		cct.setfontsize(fontname, h, w);
		return 1;
	}
	else 
		return -1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_delay(const int type, const int delay_ms)
{
	if (type == DELAY_OF_DRAW_FRAME)
		delay_of_draw_frame = delay_ms < 0 ? 0 : delay_ms;
	else if (type == DELAY_OF_BLOCK_MOVED)
		delay_of_draw_block = delay_ms < 0 ? 0 : delay_ms;
	else if (type == DELAY_OF_BLOCK_MOVED)
		delay_of_block_moved = delay_ms < BLOCK_MOVED_DELAY_MS ? BLOCK_MOVED_DELAY_MS : delay_ms;

	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�const int up_lines		���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines	���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols		����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols	���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ�� CONSOLE_GRAPHICS_INFO ��������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_ext_rowcol(const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	extern_up_lines = up_lines < 0 ? 0 : up_lines;
	extern_down_lines = down_lines < 0 ? 0 : down_lines;
	extern_left_cols = left_cols < 0 ? 0 : left_cols;
	extern_right_cols = right_cols < 0 ? 0 : right_cols;
	SLI.top_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.top_start_y = extern_up_lines;
	SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_INFO �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������const int type	��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ������ʾ - CONSOLE_FRAME_INFO cfi ����Ա��̳У�ʵ�ַ�ʽ��ͬ
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_default_linetype(const int type)
{
	if (type == 1) {
		//�d �j �g�p �m
		strcpy(CFI.top_left, "�X");
		strcpy(CFI.lower_left, "�^");
		strcpy(CFI.top_right, "�[");
		strcpy(CFI.lower_right, "�a");
		strcpy(CFI.h_normal, "�T");
		strcpy(CFI.v_normal, "�U");
		strcpy(CFI.h_top_separator, "�j");
		strcpy(CFI.h_lower_separator, "�m");
		strcpy(CFI.v_left_separator, "�d");
		strcpy(CFI.v_right_separator, "�g");
		strcpy(CFI.mid_separator, "�p");
	}
	else if (type == 2) {
		//�����������ȩЩة੤��
		strcpy(CFI.top_left, "��");
		strcpy(CFI.lower_left, "��");
		strcpy(CFI.top_right, "��");
		strcpy(CFI.lower_right, "��");
		strcpy(CFI.h_normal, "��");
		strcpy(CFI.v_normal, "��");
		strcpy(CFI.h_top_separator, "��");
		strcpy(CFI.h_lower_separator, "��");
		strcpy(CFI.v_left_separator, "��");
		strcpy(CFI.v_right_separator, "��");
		strcpy(CFI.mid_separator, "��");
	}
	else if (type == 3) {
		//�V�Y�\�_�b�e�h�k�n�T��
		strcpy(CFI.top_left, "�V");
		strcpy(CFI.lower_left, "�\");
		strcpy(CFI.top_right, "�Y");
		strcpy(CFI.lower_right, "�_");
		strcpy(CFI.h_normal, "�T");
		strcpy(CFI.v_normal, "��");
		strcpy(CFI.h_top_separator, "�h");
		strcpy(CFI.h_lower_separator, "�k");
		strcpy(CFI.v_left_separator, "�b");
		strcpy(CFI.v_right_separator, "�e");
		strcpy(CFI.mid_separator, "�n");
	}
	else if (type == 4) {
		//�W�Z�]�`�c�f�i�l�o���U
		strcpy(CFI.top_left, "�W");
		strcpy(CFI.lower_left, "�]");
		strcpy(CFI.top_right, "�Z");
		strcpy(CFI.lower_right, "�`");
		strcpy(CFI.h_normal, "��");
		strcpy(CFI.v_normal, "�U");
		strcpy(CFI.h_top_separator, "�i");
		strcpy(CFI.h_lower_separator, "�l");
		strcpy(CFI.v_left_separator, "�c");
		strcpy(CFI.v_right_separator, "�f");
		strcpy(CFI.mid_separator, "�o");
	}
	if (type >= 1 && type <= 4)
		return type; //�ɰ���仯
	else
		return -1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_INFO �ṹ�е�11������
  ���������const char *...	����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
			4����ʾ - CONSOLE_FRAME_INFO cfi ����Ա��̳У�ʵ�ַ�ʽ��ͬ
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_linetype(const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	make_linetype(CFI.top_left, top_left);
	make_linetype(CFI.lower_left, lower_left);
	make_linetype(CFI.top_right, top_right);
	make_linetype(CFI.lower_right, lower_right);
	make_linetype(CFI.h_normal, h_normal);
	make_linetype(CFI.v_normal, v_normal);
	make_linetype(CFI.h_top_separator, h_top_separator);
	make_linetype(CFI.h_lower_separator, h_lower_separator);
	make_linetype(CFI.v_left_separator, v_left_separator);
	make_linetype(CFI.v_right_separator, v_right_separator);
	make_linetype(CFI.mid_separator, mid_separator);
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_INFO �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ���������const int block_width	����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
		   const int block_high	���߶ȣ�����ȱʡ1��
		   const bool separator	���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ�� CONSOLE_GRAPHICS_INFO ��������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_style(const int block_width, const int block_high, const bool separator)
{
	CFI.block_high = block_high < 0 ? 1 : block_high;
	CFI.block_width = block_width < 0 ? 2 : (block_width & 1 ? block_width + 1 : block_width);
	CFI.separator = separator;
	SLI.top_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.top_start_y = extern_up_lines;
	SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_INFO �ṹ�е���ɫ
  ���������const int bg_color	������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
		   const int fg_color	��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_color(const CCT_COLOR bgcolor, const CCT_COLOR fgcolor)
{
	CFI.setcolor(bgcolor, fgcolor);
	return 0; //�ɰ���仯
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������const int type	��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_default_linetype(const int type)
{
	if (type == 1) {
		//�d �j �g�p �m
		strcpy(CBI.top_left, "�X");
		strcpy(CBI.lower_left, "�^");
		strcpy(CBI.top_right, "�[");
		strcpy(CBI.lower_right, "�a");
		strcpy(CBI.h_normal, "�T");
		strcpy(CBI.v_normal, "�U");
	}
	else if (type == 2) {
		//�����������ȩЩة੤��
		strcpy(CBI.top_left, "��");
		strcpy(CBI.lower_left, "��");
		strcpy(CBI.top_right, "��");
		strcpy(CBI.lower_right, "��");
		strcpy(CBI.h_normal, "��");
		strcpy(CBI.v_normal, "��");
	}
	else if (type == 3) {
		//�V�Y�\�_�b�e�h�k�n�T��
		strcpy(CBI.top_left, "�V");
		strcpy(CBI.lower_left, "�\");
		strcpy(CBI.top_right, "�Y");
		strcpy(CBI.lower_right, "�_");
		strcpy(CBI.h_normal, "�T");
		strcpy(CBI.v_normal, "��");
	}
	else if (type == 4) {
		//�W�Z�]�`�c�f�i�l�o���U
		strcpy(CBI.top_left, "�W");
		strcpy(CBI.lower_left, "�]");
		strcpy(CBI.top_right, "�Z");
		strcpy(CBI.lower_right, "�`");
		strcpy(CBI.h_normal, "��");
		strcpy(CBI.v_normal, "�U");
	}
	if (type >= 1 && type <= 4)
		return type;
	else 
		return -1; //�ɰ���仯
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������const char *...	����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_linetype(const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	make_linetype(CBI.top_left, top_left);
	make_linetype(CBI.lower_left, lower_left);
	make_linetype(CBI.top_right, top_right);
	make_linetype(CBI.lower_right, lower_right);
	make_linetype(CBI.h_normal, h_normal);
	make_linetype(CBI.v_normal, v_normal);
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������const bool on_off	��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_border_switch(const bool on_off)
{
	CBI.block_border = on_off;
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������const int type			��״̬�����ͣ���/�£�
		   const bool on_off		��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		    2�����еı仯�ᵼ�� CONSOLE_GRAPHICS_INFO ��������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_status_line_switch(const int type, const bool on_off)
{
	if (type == TOP_STATUS_LINE) {
		SLI.is_top_status_line = top_status_line = on_off;
		if (on_off)
			SLI.top_start_x = extern_left_cols + draw_frame_with_col_no,
			SLI.top_start_y = extern_up_lines;
	}
	else if (type == LOWER_STATUS_LINE) {
		SLI.is_lower_status_line = lower_status_line = on_off;
		if (on_off) 
			SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no,
			SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;
	}
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������const int type				��״̬�����ͣ���/�£�
		   const int normal_bgcolor	�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
		   const int normal_fgcolor	�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
		   const int catchy_bgcolor	����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
		   const int catchy_fgcolor	����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_status_line_color(const int type, const CCT_COLOR normal_bgcolor, const CCT_COLOR normal_fgcolor, const CCT_COLOR catchy_bgcolor, const CCT_COLOR catchy_fgcolor)
{
	if (type == TOP_STATUS_LINE) {
		int bg, fg;
		cct.getcolor(bg, fg);
		if (normal_bgcolor != CCT_COLOR::invalid)
			bg = int(normal_bgcolor);
		if (normal_fgcolor != CCT_COLOR::invalid)
			fg = int(normal_fgcolor);
		SLI.setcolor_top_normal((CCT_COLOR)bg, (CCT_COLOR)fg);
		cct.getcolor(bg, fg);
		if (catchy_bgcolor != CCT_COLOR::invalid)
			bg = int(catchy_bgcolor);
		if (normal_fgcolor != CCT_COLOR::invalid)
			fg = int(catchy_fgcolor);
		SLI.setcolor_top_normal((CCT_COLOR)bg, (CCT_COLOR)fg);
		return 1;
	}
	else if (type == LOWER_STATUS_LINE) {
		int bg, fg;
		cct.getcolor(bg, fg);
		if (normal_bgcolor != CCT_COLOR::invalid)
			bg = int(normal_bgcolor);
		if (normal_fgcolor != CCT_COLOR::invalid)
			fg = int(normal_fgcolor);
		SLI.setcolor_lower_normal((CCT_COLOR)bg, (CCT_COLOR)fg);
		cct.getcolor(bg, fg);
		if (catchy_bgcolor != CCT_COLOR::invalid)
			bg = int(catchy_bgcolor);
		if (normal_fgcolor != CCT_COLOR::invalid)
			fg = int(catchy_fgcolor);
		SLI.setcolor_lower_normal((CCT_COLOR)bg, (CCT_COLOR)fg);
		return 2;
	}
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������const bool on_off	��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_rowno_switch(const bool on_off)
{
	draw_frame_with_row_no = on_off;
	if(on_off)
		SLI.top_start_y = extern_up_lines,
		SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;

	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_colno_switch(const bool on_off)
{
	draw_frame_with_col_no = on_off;
	if (on_off)
		SLI.top_start_x = extern_left_cols + draw_frame_with_col_no,
		SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
            2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_print() const
{
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڵ���������ʵ�֣���Ҫ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::lines() const
{
	return this->total_lines;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڵ���������ʵ�֣���Ҫ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::cols() const
{
	return this->total_cols;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�CONSOLE_GRAPHICS_INFO�Ĺ��캯��
  ���������const int row			����Ϸ����ɫ��������ȱʡ10��
		   const int col			����Ϸ����ɫ��������ȱʡ10��
		   const CCT_COLOR bgcolor	���������ڱ���ɫ��ȱʡ CCT_COLOR::black��
		   const CCT_COLOR fgcolor	���������ڱ���ɫ��ȱʡ CT_COLOR::white��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
CONSOLE_GRAPHICS_INFO::CONSOLE_GRAPHICS_INFO(const int row, const int col, const CCT_COLOR bgcolor, const CCT_COLOR fgcolor)
{
	memset(this, 0x00, sizeof(CONSOLE_GRAPHICS_INFO)); //���ݳ�Աȫ����0

	/* �趨��Ϸ�������ɫ������ */
	gmw_set_rowcol(row, col);

	/* ��ʼ��������Ϸ�������ɫ */
	gmw_set_color(bgcolor, fgcolor);

	/* ��ʼ������Ϊȱʡ���������壬8*16�� */
	gmw_set_font();

	/* �趨��ʱ */
	gmw_set_delay(DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);

	/* ��ʼ���������Ҹ�������Ĵ�СΪȱʡ��ȫ0�� */
	gmw_set_ext_rowcol();

	/* ���Ƿ���Ҫ����״̬����ȱʡֵ����Ҫ�� */
	gmw_set_status_line_switch(TOP_STATUS_LINE);
	gmw_set_status_line_switch(LOWER_STATUS_LINE);
	gmw_set_status_line_color(TOP_STATUS_LINE);
	gmw_set_status_line_color(LOWER_STATUS_LINE);

	/* �ô�ӡɫ��ʱ�Ƿ���Ҫ�к��б��ȱʡֵ����Ҫ�� */
	gmw_set_rowno_switch();
	gmw_set_colno_switch();

	/* �趨��Ϸ��߿��ȱʡ���ͣ�˫�ߣ� */
	gmw_set_frame_linetype();
	gmw_set_frame_style();
	gmw_set_frame_color();

	/* �趨ÿ��ɫ���ȱʡ���ͣ�˫�ߣ�*/
	gmw_set_block_linetype();
	gmw_set_block_border_switch();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_draw_frame() const
{
	cct.cls();
	cct.setcolor(area_bgcolor, area_fgcolor);

	int row = start_y + top_status_line + extern_up_lines + draw_frame_with_row_no;
	int col = start_x + extern_left_cols + draw_frame_with_col_no;
	int cc = col_num * CFI.block_width * 2 + (col_num - 1) * CFI.separator * 2;
	int rr = row_num * CFI.block_high + row_num * CFI.separator;

	cct.gotoxy(col, row);

	if (draw_frame_with_row_no) {
		int y = row, unit = CFI.block_high & 1 ? CFI.block_high/2+1 : CFI.block_high/2;
		for (int i = 0; i < row_num && i < 24; ++i) {
			cct.showch(col - 1, y + unit, 'A'+i, CFI.bgcolor, CFI.fgcolor);
			y += CFI.block_high + CFI.separator;
			Sleep(delay_of_draw_frame);
		}
		for (int i = 24; i < row_num; ++i) {
			cct.showch(col - 1, y + unit, '*', CFI.bgcolor, CFI.fgcolor);
			y += CFI.block_high + CFI.separator;
			Sleep(delay_of_draw_frame);
		}
	}
	if (draw_frame_with_col_no) {
		int x = col, unit = CFI.block_width;
		for (int j = 0; j < col_num && j < 10; ++j) {
			cct.showch(x + unit, row - 1, '0' + j, CFI.bgcolor, CFI.fgcolor);
			x += (CFI.block_width + CFI.separator) * 2;
			Sleep(delay_of_draw_frame);
		}
		for (int j = 10; j < col_num; ++j) {
			cct.showch(x + unit, row - 1, '*', CFI.bgcolor, CFI.fgcolor);
			x += (CFI.block_width + CFI.separator) * 2;
			Sleep(delay_of_draw_frame);
		}
	}


	cct.showstr(col, row, CFI.top_left, CFI.bgcolor, CFI.fgcolor);
	for (int j = 2; j <= cc; ) {
		for(int k = 1; k <= CFI.block_width; ++k, j += 2)
			cct.showstr(col + j, row, CFI.h_normal, CFI.bgcolor, CFI.fgcolor),
			Sleep(delay_of_draw_frame);
		if (CFI.separator)
			cct.showstr(col + j, row, CFI.h_top_separator, CFI.bgcolor, CFI.fgcolor),
			j += 2;
	}
	cct.showstr(col + cc + 2, row, CFI.top_right, CFI.bgcolor, CFI.fgcolor);

	for (int i = 1; i <= rr; ) {
		for (int k = 1; k <= CFI.block_high; ++k, ++i) {
			cct.showstr(col, row + i, CFI.v_normal, CFI.bgcolor, CFI.fgcolor);
			cct.showstr(col + cc + 2, row + i, CFI.v_normal, CFI.bgcolor, CFI.fgcolor);
			Sleep(delay_of_draw_frame);
			for (int t = CFI.block_width * 2 + 2; t <= cc && CFI.separator; t += CFI.block_width * 2 + 2)
				cct.showstr(col + t, row + i, CFI.v_normal, CFI.bgcolor, CFI.fgcolor),
				Sleep(delay_of_draw_frame);;
		}
		if (CFI.separator) {
			cct.showstr(col, row + i, CFI.v_left_separator, CFI.bgcolor, CFI.fgcolor);
			cct.showstr(col + cc + 2, row + i, CFI.v_right_separator, CFI.bgcolor, CFI.fgcolor);
			cct.showstr(col + 2, row + i, CFI.h_normal, CFI.bgcolor, CFI.fgcolor, CFI.block_width*col_num+col_num-1);
			Sleep(delay_of_draw_frame);
			for (int k = CFI.block_width * 2 + 2; k <= cc; k += CFI.block_width*2 + 2)
				cct.showstr(col + k, row + i, CFI.mid_separator, CFI.bgcolor, CFI.fgcolor),
				Sleep(delay_of_draw_frame);
			++i; 
		}
	}

	if (!CFI.separator) {
		++rr;
		for (int k = 2; k <= cc; k += 2)
			cct.showstr(col + k, row + rr, CFI.h_normal, CFI.bgcolor, CFI.fgcolor),
			Sleep(delay_of_draw_frame);
	}

	for (int k = CFI.block_width * 2 + 2; k <= cc && CFI.separator; k += CFI.block_width * 2 + 2)
		cct.showstr(col + k, row + rr, CFI.h_lower_separator, CFI.bgcolor, CFI.fgcolor),
		Sleep(delay_of_draw_frame);
	cct.showstr(col, row + rr, CFI.lower_left, CFI.bgcolor, CFI.fgcolor);
	cct.showstr(col + cc + 2, row + rr, CFI.lower_right, CFI.bgcolor, CFI.fgcolor);
	Sleep(delay_of_draw_frame);


	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬������ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_top_status_line(const char* msg, const char* catchy_msg) const
{
	if (!SLI.is_top_status_line)
		return 0;
	int x = SLI.top_start_x, y = SLI.top_start_y;
	cct.gotoxy(x, y);
	if (catchy_msg)
		cct.showstr(x, y, catchy_msg, SLI.top_catchy_bgcolor, SLI.top_catchy_fgcolor);
	cct.getxy(x, y);
	if (msg)
		cct.showstr(x, y, msg, SLI.top_normal_bgcolor, SLI.top_normal_fgcolor);
	cct.setcolor();
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬������ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_lower_status_line(const char* msg, const char* catchy_msg) const
{
	if (!SLI.is_lower_status_line)
		return 0;
	int x = SLI.lower_start_x, y = SLI.lower_start_y;
	cct.gotoxy(x, y);
	if (catchy_msg)
		cct.showstr(x, y, catchy_msg, SLI.lower_catchy_bgcolor, SLI.lower_catchy_fgcolor);
	cct.getxy(x, y);
	if (msg)
		cct.showstr(x, y, msg, SLI.lower_normal_bgcolor, SLI.lower_normal_fgcolor);
	cct.setcolor();
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
            2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_draw_block(const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi) const
{
	if (bdi == NULL)
		return 0;
	int cc = col_no * CFI.block_width * 2 + extern_left_cols + CFI.separator * col_no * 2 + 2 + draw_frame_with_col_no;
	int rr = row_no * CFI.block_high + extern_up_lines + CFI.separator * row_no + 1 + SLI.is_top_status_line + draw_frame_with_row_no;
	cct.gotoxy(cc, rr);
	CCT_COLOR bgcolor, fgcolor;

	for (const BLOCK_DISPLAY_INFO* p = bdi; p && p->value != BDI_VALUE_END; ++p)
		if (p->value == bdi_value) {
			if (p->value == BDI_VALUE_BLANK) {
				bgcolor = CFI.bgcolor;
				fgcolor = CFI.fgcolor;
			}
			else {
				bgcolor = (p->bgcolor == CCT_COLOR::invalid ? CFI.bgcolor : p->bgcolor);
				fgcolor = (p->fgcolor == CCT_COLOR::invalid ? CFI.fgcolor : p->fgcolor);
			}

			if (CBI.block_border) {
				cct.showstr(cc, rr, CBI.top_left, bgcolor, fgcolor);
				for (int k = 1; k < CFI.block_width - 1; k++)
					cct.showstr(cc + k * (CBI_LEN - 1), rr, CBI.h_normal, bgcolor, fgcolor);
				cct.showstr(cc + (CFI.block_width - 1) * (CBI_LEN - 1), rr, CBI.top_right, bgcolor, fgcolor);

				for (int k = 1; k < CFI.block_high - 1; ++k) {
					cct.showstr(cc, rr + k, CBI.v_normal, bgcolor, fgcolor);
					cct.showstr(cc + (CFI.block_width - 1) * (CBI_LEN - 1), rr + k, CBI.v_normal, bgcolor, fgcolor);
				}

				cct.showstr(cc, rr + CFI.block_high - 1, CBI.lower_left, bgcolor, fgcolor);
				for (int k = 1; k < CFI.block_width - 1; k++)
					cct.showstr(cc + k * (CBI_LEN - 1), rr + CFI.block_high - 1, CBI.h_normal, bgcolor, fgcolor);
				cct.showstr(cc + (CFI.block_width - 1) * (CBI_LEN - 1), rr + CFI.block_high - 1, CBI.lower_right, bgcolor, fgcolor);
			}
			char content[20];
			if (p->content)
				strcpy(content, p->content);
			else
				sprintf(content, "%d", p->value);

			int dt_y = CFI.block_high - 1 - 2 * CBI.block_border;
			if (CFI.block_high != 1)
				dt_y >>= 1;
			int width = (CFI.block_width - CBI.block_border * 2) * 2;
			for (int i = 0; i < dt_y; ++i)
				for (int j = 0; j < width; ++j)
					cct.showch(cc + CBI.block_border * (CBI_LEN - 1) + j, rr + CBI.block_border + i, ' ', bgcolor, fgcolor);

			int len = strlen(content);
			if (len < CFI.block_width * 2 - 4 * CBI.block_border) {
				int delta = CFI.block_width * 2 - 4 * CBI.block_border - len;
				delta >>= 1;
				for (int k = 0; k < delta; ++k)
					cct.showch(cc + CBI.block_border * (CBI_LEN - 1) + k, rr + CBI.block_border + dt_y, ' ', bgcolor, fgcolor);
				cct.showstr(cc + CBI.block_border * (CBI_LEN - 1) + delta, rr + CBI.block_border + dt_y, content, bgcolor, fgcolor);

				int aft = CFI.block_width * 2 - 4 * CBI.block_border - len - delta;
				for (int k = 0; k < aft; ++k)
					cct.showch(cc + CBI.block_border * (CBI_LEN - 1) + delta + len + k, rr + CBI.block_border + dt_y, ' ', bgcolor, fgcolor);
			}
			else
				cct.showstr(cc + CBI.block_border * (CBI_LEN - 1), rr + CBI.block_border + dt_y, content, bgcolor, fgcolor);

			for (int i = dt_y + 1; i < CFI.block_high - CBI.block_border * 2 && CFI.block_high != 1; ++i)
				for (int j = 0; j < width; ++j)
					cct.showch(cc + CBI.block_border * (CBI_LEN - 1) + j, rr + CBI.block_border + i, ' ', bgcolor, fgcolor);

			break;
		}
	Sleep(delay_of_draw_block);
	return 1; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ������
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_move_block(const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance) const
{
	cct.gotoxy(col_no, row_no);
	int cc = 0, rr = 0;
	if (direction == UP_TO_DOWN)
		cc = 0, rr = 1;
	else if (direction == DOWN_TO_UP)
		cc = 0, rr = -1;
	else if (direction == LEFT_TO_RIGHT)
		cc = 1, rr = 0;
	else if (direction == RIGHT_TO_LEFT)
		cc = -1, rr = 0;
	for (int i = 1; i <= distance; ++i) {
		gmw_draw_block(row_no+rr*(i-1), col_no+cc*(i-1), BDI_VALUE_BLANK, bdi);
		gmw_draw_block(row_no+rr*i, col_no+cc*i, bdi_value, bdi);
		Sleep(delay_of_block_moved);
	}
	return 0; //�ɰ���仯
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������
		   CCT_MOUSE &MAction						��������� CCT_KMEVENT::mouse�����ֵ��Ч��Ϊ only_moved/left_button_click/right_button_click ����֮һ
		                                               ������� CCT_KMEVENT::keyboard�����ֵ��Ч
		   int &MRow								��������� CCT_KMEVENT::mouse �� MAction = only_moved/left_button_click�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_KMEVENT::mouse �� MAction = only_moved/left_button_click�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KMEVENT::keyboard�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KMEVENT::keyboard�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
           1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
		                      �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		                      �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_KMEVENT::mouse ��MAction Ϊ left_button_click, MRow Ϊ�кţ�MCol Ϊ�б�
		                          �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_KMEVENT::mouse ��MAction Ϊ right_button_click, MRow��MCol������
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KMEVENT::keyboard��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ class_cct.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
CCT_KMEVENT CONSOLE_GRAPHICS_INFO::gmw_read_keyboard_and_mouse(CCT_MOUSE&MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line) const
{
	cct.enable_mouse();
	int MX, MY, k1, k2;
	while (1) {
		CCT_KMEVENT rt = cct.read_keyboard_and_mouse(MX, MY, MAction, k1, k2);
		if (rt == CCT_KMEVENT::mouse) {
			int xx = MX - extern_left_cols - draw_frame_with_col_no;
			int yy = MY - extern_up_lines - draw_frame_with_row_no - SLI.is_top_status_line;
			if (MAction == CCT_MOUSE::only_moved) {
				if (MX == MCol && MY == MRow)
					continue;
				if (!gmw_inner_check_inarea(xx, yy)) {
					if (update_lower_status_line)
						gmw_lower_status_line(NULL, "[��ǰ���] λ�÷Ƿ�");
					continue;
				}
				else if (update_lower_status_line) {
					char content[30];
					sprintf(content, "[��ǰ���] %d��%d��", MY, MX);
					gmw_lower_status_line(content);
				}
				cct.disable_mouse();
				return CCT_KMEVENT::mouse;
			}
			else if (MAction == CCT_MOUSE::left_button_click) {
				MRow = MY, MCol = MX;
				if (!gmw_inner_check_inarea(xx, yy)) {
					if (update_lower_status_line)
						gmw_lower_status_line(NULL, "[��ǰ���] λ�÷Ƿ�");
					continue;
				}
				cct.disable_mouse();
				return CCT_KMEVENT::mouse;
			}
			else if (MAction == CCT_MOUSE::right_button_click) {
				cct.disable_mouse();
				return CCT_KMEVENT::mouse;
			}
		}
		else if(rt == CCT_KMEVENT::keyboard){
			KeyCode1 = k1, KeyCode2 = k2;
			cct.disable_mouse();
			return CCT_KMEVENT::keyboard;
		}
	}
	cct.disable_mouse();
	return CCT_KMEVENT::keyboard; //�ɰ���仯
}
