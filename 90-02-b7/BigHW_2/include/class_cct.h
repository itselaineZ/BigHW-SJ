#pragma once

//#include <Windows.h>

/* 定义颜色（用宏定义取代数字，方便记忆） */
enum class CCT_COLOR {
	invalid = -1, //CONSOLE_GRAPHICS_INFO中的-1而特别加入（问：如果因为初始设计考虑不周全，导致此处加入新值，是否会影响到原有程序？）
	black = 0, //黑
	blue,	//蓝
	green,	//绿
	cyan,	//青
	red,		//红
	pink,	//粉
	yellow,	//黄
	white,	//白
	hblack,	//亮黑
	hblue,	//亮蓝
	hgreen,	//亮绿
	hcyan,	//亮青
	hred,	//亮红
	hpink,	//亮粉
	hyellow,	//亮黄
	hwhite	//亮白
};

/* 定义鼠标键盘操作类型 */
enum class CCT_KMEVENT {
	mouse = 0,
	keyboard
};

/* 定义四个方向键 */
enum class CCT_KEYCODE {
	kb_escape = 27,
	kb_space = 32,
	arrow_pre = 0xe0,		//箭头键的前缀键码（224）
	arrow_up = 72,
	arrow_down = 80,
	arrow_left = 75,
	arrow_right = 77
};

/* 定义鼠标的操作 */
enum class CCT_MOUSE {
	no_action = 	0x0000,	//无鼠标操作
	only_moved = 0x0001,	//鼠标移动
	left_button_click = 0x0002,	//按下左键
	left_button_doubleclick = 0x0004,	//双击左键
	right_button_click = 0x0008,	//按下右键
	right_button_doubleclick = 0x0010,	//双击右键
	leftright_button_click = 0x0020,	//同时按下左右键
	wheel_click = 0x0040,	//滚轮被按下
	wheel_moved_up = 0x0080,	//滚轮向上移动
	wheel_moved_down = 0x0100	//滚轮向下移动
};

/* 定义光标的形态 */
enum class CCT_CURSOR {
	full = 0,	//光标显示，全高色块
	half,		//光标显示，半高色块
	normal,		//光标显示，横线（缺省为此方式）
	invisible	//光标不显示
};

/* cmd_console_tools下的函数声明 */
class CCT {
protected:
	static const HANDLE __hout;
	static const HANDLE __hin;

public:
	/* 清屏、颜色设置、光标设置、字符/字符串显示 */
	void cls(void) const;
	void setcolor(const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white) const;
	void getcolor(int& bg_color, int& fg_color) const;
	void gotoxy(const int X, const int Y) const;
	void getxy(int& x, int& y) const;
	void setcursor(const CCT_CURSOR options) const;
	void showch(const int X, const int Y, const char ch, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, const int rpt = 1) const;
	void showstr(const int X, const int Y, const char* str, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, int rpt = 1, int max_len = -1) const;
	void showint(const int X, const int Y, const int num, const CCT_COLOR bg_color = CCT_COLOR::black, const CCT_COLOR fg_color = CCT_COLOR::white, const int rpt = 1) const;

	/* 与窗口大小有关的函数 */
	void setconsoleborder(int set_cols, int set_lines, int set_buffer_cols = -1, int set_buffer_lines = -1) const;
	void getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines) const;

	/* 有标题栏有关的函数 */
	void getconsoletitle(char* title, int maxbuflen) const;
	void setconsoletitle(const char* title) const;

	/* 与鼠标操作有关的函数 */
	void enable_mouse(void) const;
	void disable_mouse(void) const;
	CCT_KMEVENT read_keyboard_and_mouse(int& MX, int& MY, CCT_MOUSE& MAction, int& keycode1, int& keycode2) const;

	/* 与字体及字号设置有关的函数 */
	int  getfontinfo(void) const;
	void setconsolefont(const int font_no) const;
	void setfontsize(const char* fontname, const int high, const int width = 0) const;
};

