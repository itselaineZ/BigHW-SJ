#pragma once

//#include <Windows.h>

/* ������ɫ���ú궨��ȡ�����֣�������䣩 */
enum class CCT_COLOR {
	invalid = -1, //CONSOLE_GRAPHICS_INFO�е�-1���ر���루�ʣ������Ϊ��ʼ��ƿ��ǲ���ȫ�����´˴�������ֵ���Ƿ��Ӱ�쵽ԭ�г��򣿣�
	black = 0, //��
	blue,	//��
	green,	//��
	cyan,	//��
	red,		//��
	pink,	//��
	yellow,	//��
	white,	//��
	hblack,	//����
	hblue,	//����
	hgreen,	//����
	hcyan,	//����
	hred,	//����
	hpink,	//����
	hyellow,	//����
	hwhite	//����
};

/* ���������̲������� */
enum class CCT_KMEVENT {
	mouse = 0,
	keyboard
};

/* �����ĸ������ */
enum class CCT_KEYCODE {
	kb_escape = 27,
	kb_space = 32,
	arrow_pre = 0xe0,		//��ͷ����ǰ׺���루224��
	arrow_up = 72,
	arrow_down = 80,
	arrow_left = 75,
	arrow_right = 77
};

/* �������Ĳ��� */
enum class CCT_MOUSE {
	no_action = 	0x0000,	//��������
	only_moved = 0x0001,	//����ƶ�
	left_button_click = 0x0002,	//�������
	left_button_doubleclick = 0x0004,	//˫�����
	right_button_click = 0x0008,	//�����Ҽ�
	right_button_doubleclick = 0x0010,	//˫���Ҽ�
	leftright_button_click = 0x0020,	//ͬʱ�������Ҽ�
	wheel_click = 0x0040,	//���ֱ�����
	wheel_moved_up = 0x0080,	//���������ƶ�
	wheel_moved_down = 0x0100	//���������ƶ�
};

/* ���������̬ */
enum class CCT_CURSOR {
	full = 0,	//�����ʾ��ȫ��ɫ��
	half,		//�����ʾ�����ɫ��
	normal,		//�����ʾ�����ߣ�ȱʡΪ�˷�ʽ��
	invisible	//��겻��ʾ
};

/* cmd_console_tools�µĺ������� */
class CCT {
protected:
	static const HANDLE __hout;
	static const HANDLE __hin;

public:
	/* ��������ɫ���á�������á��ַ�/�ַ�����ʾ */
	void cls(void) const;
	void setcolor(const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white) const;
	void getcolor(int& bg_color, int& fg_color) const;
	void gotoxy(const int X, const int Y) const;
	void getxy(int& x, int& y) const;
	void setcursor(const CCT_CURSOR options) const;
	void showch(const int X, const int Y, const char ch, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, const int rpt = 1) const;
	void showstr(const int X, const int Y, const char* str, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, int rpt = 1, int max_len = -1) const;
	void showint(const int X, const int Y, const int num, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, const int rpt = 1) const;

	/* �봰�ڴ�С�йصĺ��� */
	void setconsoleborder(int set_cols, int set_lines, int set_buffer_cols = -1, int set_buffer_lines = -1) const;
	void getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines) const;

	/* �б������йصĺ��� */
	void getconsoletitle(char* title, int maxbuflen) const;
	void setconsoletitle(const char* title) const;

	/* ���������йصĺ��� */
	void enable_mouse(void) const;
	void disable_mouse(void) const;
	CCT_KMEVENT read_keyboard_and_mouse(int& MX, int& MY, CCT_MOUSE& MAction, int& keycode1, int& keycode2) const;

	/* �����弰�ֺ������йصĺ��� */
	int  getfontinfo(void) const;
	void setconsolefont(const int font_no) const;
	void setfontsize(const char* fontname, const int high, const int width = 0) const;
};

