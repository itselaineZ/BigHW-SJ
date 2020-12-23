/*1952339 信08 张馨月*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
#include "../include/class_gmw_sli.h"
#include "../include/class_gmw_cfi.h"
#include "../include/class_gmw_cbi.h"
using namespace std;

/* 定义 BLOCK_DISPLAY_INFO 数组中表示 空白的特殊值/结束的特殊值 */
#define BDI_VALUE_BLANK		0		//代表空白的特殊值
#define BDI_VALUE_END		-999		//代表结束的特殊值

/* 定义色块显示时，内部数组的int值与界面上显示图形的对应关系
   注：此结构体数组的值在测试用例中定义，随着游戏的不同而不同 */
typedef struct _block_display_info_ {
	const int   value;	//要显示的内部数组值
	const CCT_COLOR   bgcolor;	//-1表示用游戏区域背景色
	const CCT_COLOR   fgcolor;	//-1表示用游戏区域前景色
	const char* content;	//内部数组值对应的图形（如果为NULL，则直接显示内部数组的值）
} BLOCK_DISPLAY_INFO;

/* 定义描述字体/字号信息的结构体 */
#define		FONTNAME_LEN	12	//字体名称的最大长度（含尾零）
typedef struct _console_font_type_ {
	char font_type[FONTNAME_LEN];
	int  font_size_width;
	int  font_size_high;
} CONSOLE_FONT_TYPE;

/* 定义延时的种类 */
#define DELAY_OF_DRAW_FRAME		0	//画游戏主框架时的延时
#define DELAY_OF_DRAW_BLOCK		1	//画色块时的延时
#define DELAY_OF_BLOCK_MOVED		2	//色块移动时的延时

#define BLOCK_MOVED_DELAY_MS		15	//色块移动的缺省延时，单位ms（其余两个缺省为0）

/* 定义色块的四种移动方向 */
#define DOWN_TO_UP		0
#define UP_TO_DOWN		1
#define RIGHT_TO_LEFT	2
#define LEFT_TO_RIGHT	3

/* 定义描述整个窗口全部信息的结构体 */
class CONSOLE_GRAPHICS_INFO {
protected:
	CCT cct;	//这个class无数据成员（仅有两个静态成员），可以根据自己的需要放入下面的CFI/CBI/SLI/CFT中

	/* ---------------------------------------------------------------------------------------------------------------
		四个单独的类信息，两种方法：
		1、可以像下面一样定义成为 CONSOLE_GRAPHICS_INFO 的成员
		2、也可以通过继承方式成为 CONSOLE_GRAPHICS_INFO 的基类
	   ---------------------------------------------------------------------------------------------------------------
	 */
	/* 主框架信息，本处定义为成员，也可以采用继承方式 */
	CONSOLE_FRAME_INFO CFI;		//136字节

	/* 色块信息，本处定义为成员，也可以采用继承方式 */
	CONSOLE_BLOCK_INFO CBI;		//84字节

	/* 状态栏信息，本处定义为成员，也可以采用继承方式 */
	STATUS_LINE_INFO SLI;		//120字节

	/* 字体信息 */
	CONSOLE_FONT_TYPE CFT;		//20字节

	/* ---------------------------------------------------------------------------------------------------------------
		下面定义的是可通过设置函数改变的值，不准修改成员名，不准改变类型
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* 整个图形界面的上下左右需要的额外行列数 */
	int extern_up_lines;
	int extern_down_lines;
	int extern_left_cols;
	int extern_right_cols;

	/* 游戏主框架区域包含的色块的行列数 */
	int row_num;
	int col_num;

	/* 整个图形界面（含主框架、上下状态栏、行号列标、附加行列）的背景色和前景色 */
	CCT_COLOR area_bgcolor;
	CCT_COLOR area_fgcolor;

	/* 是否需要上下状态栏
	   - 注：true-需要 false-不需要
	   -    如果设置为false，则即使调用了状态新信息显示函数，也不显示内容）
	   - 和 STATUS_LINE_INFO 中的 is_top_status_line / is_lower_status_line 重复，只要是考虑到不同位置实现时的访问方便性 */
	bool top_status_line;
	bool lower_status_line;

	/* 打印主框架时是否需要行号列标 */
	bool draw_frame_with_row_no;
	bool draw_frame_with_col_no;

	/* 延时时间设置 */
	int delay_of_draw_frame;		//画外框是的延时
	int delay_of_draw_block;		//画游戏块的延时
	int delay_of_block_moved;	//游戏块移动的延时

	/* ---------------------------------------------------------------------------------------------------------------
		下面这四个值不是通过设置函数直接设置的
		1、start_x/start_y 是 整个图形界面的主框架区域的参考坐标起始位置(左上角）
			- 注：游戏主框架，除了有包含m行n列的色块的外框外，还有上状态栏（0/1行）/下状态栏（0/1行）/行号显示（0/2列）/列标显示区域（0/1行）
			-     在上述值各不相同的情况下，start_x/start_y的值是不同的
		2、total_lines/total_cols是计算各种元素后整个cmd窗口的大小
	   ---------------------------------------------------------------------------------------------------------------
	*/
	/* 主框架区域的参考坐标起始位置（左上角，不含extern） */
	int start_x;
	int start_y;

	/* 计算各种元素后整个cmd窗口的大小 */
	int total_lines;		//为了给中文输入法提示行及运行结束的提示信息留空间，要求在计算得到的结果基础上（上额外空间+上状态栏+列标显示+主区域+下状态栏）+ 4（1中文输入法提示行+3预留空行）
	int total_cols;

	/* ---------------------------------------------------------------------------------------------------------------
		下面允许添加你认为需要的值，这些值不能通过设置函数直接设置，只是为了方便程序中调用(不需要每次重复计算)
		说明：因为引入了 lib_class_gmw.lib，为了保持两者的结构体一致，设置这部分大小为固定64字节（目前是pad），
			  如果需要添加相应内容，请保持添加内容+填充字节=64字节
				例如：int data1;
					 int data2;
					 char pad[56];
	   ---------------------------------------------------------------------------------------------------------------
	*/
	char pad[64];

	/* ------------------------------
		下面允许添加 内部成员 函数
	   ------------------------------ */
	bool gmw_inner_check_inarea(int x, int y)const;

public:
	/* -----------------------------------------------
		供外部访问的函数，不允许改动，也不允许再添加
	   ----------------------------------------------- */

	/* 用缺省值做一个全局初始化 */
	CONSOLE_GRAPHICS_INFO(const int row = 10, const int col = 10, const CCT_COLOR bgcolor = CCT_COLOR::black, const CCT_COLOR fgcolor = CCT_COLOR::white);

	/* 调试用 - 打印 CONSOLE_GRAPHICS_INFO 中的各成员值 */
	int gmw_print() const;

	/* 取窗口的 lines 和 cols */
	int lines() const;
	int cols() const;

	/* 设置整个窗口的某些参数 */
	int gmw_set_rowcol(const int row, const int col);
	int gmw_set_color(const CCT_COLOR bgcolor = CCT_COLOR::black, const CCT_COLOR fgcolor = CCT_COLOR::white, const bool cascade = true);
	int gmw_set_font(const char* fontname = "Terminal", const int fs_high = 16, const int fs_width = 8);
	int gmw_set_delay(const int type, const int delay_ms);
	int gmw_set_ext_rowcol(const int up_lines = 0, const int down_lines = 0, const int left_cols = 0, const int right_cols = 0);

	/* 设置整个游戏主框架的参数 */
	int gmw_set_frame_default_linetype(const int type);
	int gmw_set_frame_linetype(const char* top_left = "╔", const char* lower_left = "╚", const char* top_right = "╗",
		const char* lower_right = "╝", const char* h_normal = "═", const char* v_normal = "║", const char* h_top_separator = "╦",
		const char* h_lower_separator = "╩", const char* v_left_separator = "╠", const char* v_right_separator = "╣", const char* mid_separator = "╬");
	int gmw_set_frame_style(const int block_width = 2, const int block_high = 1, const bool separator = true);
	int gmw_set_frame_color(const CCT_COLOR bgcolor = CCT_COLOR(-1), const CCT_COLOR fgcolor = CCT_COLOR(-1));

	/* 设置每个色块的参数 */
	int gmw_set_block_default_linetype(const int def_type);
	int gmw_set_block_linetype(const char* top_left = "╔", const char* lower_left = "╚", const char* top_right = "╗",
		const char* lower_right = "╝", const char* h_normal = "═", const char* v_normal = "║");
	int gmw_set_block_border_switch(const bool on_off = false);

	/* 设置是否需要上下状态栏及颜色，分开两个函数的目的是color可能在改变整个屏幕颜色是需要级联调用 */
	int gmw_set_status_line_switch(const int type, const bool on_off = true);
	int gmw_set_status_line_color(const int type, const CCT_COLOR normal_bgcolor = CCT_COLOR(-1), const CCT_COLOR normal_fgcolor = CCT_COLOR(-1), const CCT_COLOR catchy_bgcolor = CCT_COLOR(-1), const CCT_COLOR catchy_fgcolor = CCT_COLOR(-1));

	/* 设置是否需要行号列标 */
	int gmw_set_rowno_switch(const bool on_off = false);
	int gmw_set_colno_switch(const bool on_off = false);

	/* 画游戏主框架 */
	int gmw_draw_frame() const;
	/* 在上状态栏上显示信息 */
	int gmw_top_status_line(const char* msg, const char* catchy_msg = NULL) const;
	/* 在下状态栏上显示信息 */
	int gmw_lower_status_line(const char* msg, const char* catchy_msg = NULL) const;
	/* 画一个色块 */
	int gmw_draw_block(const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi) const;
	/* 移动一个色块 */
	int gmw_move_block(const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance) const;
	/* 读键盘和鼠标 */
	CCT_KMEVENT gmw_read_keyboard_and_mouse(CCT_MOUSE& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line = true) const;

	/* 定义友元函数 */
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};	//end of class CONSOLE_GRAPHICS_INFO

