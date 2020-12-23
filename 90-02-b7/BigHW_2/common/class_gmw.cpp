/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <Windows.h>
#include <cstring>
//允许添加自己需要的头文件
#include "../include/class_cct.h"
#include "../include/class_gmw.h"
using namespace std;

/* --------------------------------------------------------------------------
	此处可以给出需要的静态全局变量
		1、尽可能少，最好没有
		2、静态全局只读变量/宏定义个数不限
		3、不允许外部全局变量
   --------------------------------------------------------------------------
*/

/* --------------------------------------------------------------------------
	此处可以给出需要的内部函数的实现
		1、函数名不限，建议为 gmw_inner_*
		2、个数不限
		3、如果是成员函数，必须是在private/protected中声明的函数
		4、如果是全局函数，必须是static，即仅限制在本源程序文件内部使用
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/

 /* --------------------------------------------------------------------------
	  实现下面给出的函数（函数声明不准动）
	 --------------------------------------------------------------------------
 */

/***************************************************************************
  函数名称：
  功    能：设置游戏主框架的行列数
  输入参数：const int row	：行数(错误则为0，不设上限，人为保证正确性)
		   const int col	：列数(错误则为0，不设上限，人为保证正确性)
  返 回 值：
  说    明：1、指消除类游戏的矩形区域的行列值
            2、行列的变化会导致 CONSOLE_GRAPHICS_INFO 中其它成员值的变化，要处理
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_rowcol(const int row, const int col)
{
	row_num = row < 0 ? 0 : row;
	col_num = col < 0 ? 0 : col;
	SLI.top_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.top_start_y = extern_up_lines;
	SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：const int bg_color	：前景色（缺省 CCT_COLOR::black）
		   const int fg_color	：背景色（缺省 CCT_COLOR::white）
		   const bool cascade	：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
				    前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
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
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：const char *fontname	：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high		：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width		：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与class_cct中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
            2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_font(const char *fontname, const int fs_high, const int fs_width)
{
	int h = fs_high < 0 ? 16 : fs_high;
	int w = fs_width < 0 ? 8 : fs_width;
	if (strcmp(fontname, "Terminal") == 0 || strcmp(fontname, "新宋体") == 0) {
		cct.setfontsize(fontname, h, w);
		return 1;
	}
	else 
		return -1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_delay(const int type, const int delay_ms)
{
	if (type == DELAY_OF_DRAW_FRAME)
		delay_of_draw_frame = delay_ms < 0 ? 0 : delay_ms;
	else if (type == DELAY_OF_BLOCK_MOVED)
		delay_of_draw_block = delay_ms < 0 ? 0 : delay_ms;
	else if (type == DELAY_OF_BLOCK_MOVED)
		delay_of_block_moved = delay_ms < BLOCK_MOVED_DELAY_MS ? BLOCK_MOVED_DELAY_MS : delay_ms;

	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：const int up_lines		：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines	：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols		：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols	：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致 CONSOLE_GRAPHICS_INFO 中其它成员值的变化，要处理
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
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_INFO 结构中的11种线型（缺省4种）
  输入参数：const int type	：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：提示 - CONSOLE_FRAME_INFO cfi 做成员或继承，实现方式不同
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_default_linetype(const int type)
{
	if (type == 1) {
		//╠ ╦ ╣╬ ╩
		strcpy(CFI.top_left, "╔");
		strcpy(CFI.lower_left, "╚");
		strcpy(CFI.top_right, "╗");
		strcpy(CFI.lower_right, "╝");
		strcpy(CFI.h_normal, "═");
		strcpy(CFI.v_normal, "║");
		strcpy(CFI.h_top_separator, "╦");
		strcpy(CFI.h_lower_separator, "╩");
		strcpy(CFI.v_left_separator, "╠");
		strcpy(CFI.v_right_separator, "╣");
		strcpy(CFI.mid_separator, "╬");
	}
	else if (type == 2) {
		//┌└┘┐├┤┬┴┼─│
		strcpy(CFI.top_left, "┌");
		strcpy(CFI.lower_left, "└");
		strcpy(CFI.top_right, "┐");
		strcpy(CFI.lower_right, "┘");
		strcpy(CFI.h_normal, "─");
		strcpy(CFI.v_normal, "│");
		strcpy(CFI.h_top_separator, "┬");
		strcpy(CFI.h_lower_separator, "┴");
		strcpy(CFI.v_left_separator, "├");
		strcpy(CFI.v_right_separator, "┤");
		strcpy(CFI.mid_separator, "┼");
	}
	else if (type == 3) {
		//╒╕╘╛╞╡╤╧╪═│
		strcpy(CFI.top_left, "╒");
		strcpy(CFI.lower_left, "╘");
		strcpy(CFI.top_right, "╕");
		strcpy(CFI.lower_right, "╛");
		strcpy(CFI.h_normal, "═");
		strcpy(CFI.v_normal, "│");
		strcpy(CFI.h_top_separator, "╤");
		strcpy(CFI.h_lower_separator, "╧");
		strcpy(CFI.v_left_separator, "╞");
		strcpy(CFI.v_right_separator, "╡");
		strcpy(CFI.mid_separator, "╪");
	}
	else if (type == 4) {
		//╓╖╙╜╟╢╥╨╫─║
		strcpy(CFI.top_left, "╓");
		strcpy(CFI.lower_left, "╙");
		strcpy(CFI.top_right, "╖");
		strcpy(CFI.lower_right, "╜");
		strcpy(CFI.h_normal, "─");
		strcpy(CFI.v_normal, "║");
		strcpy(CFI.h_top_separator, "╥");
		strcpy(CFI.h_lower_separator, "╨");
		strcpy(CFI.v_left_separator, "╟");
		strcpy(CFI.v_right_separator, "╢");
		strcpy(CFI.mid_separator, "╫");
	}
	if (type >= 1 && type <= 4)
		return type; //可按需变化
	else
		return -1;
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_INFO 结构中的11种线型
  输入参数：const char *...	：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
			4、提示 - CONSOLE_FRAME_INFO cfi 做成员或继承，实现方式不同
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
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_INFO 结构中的色块数量大小、是否需要分隔线等
  输入参数：const int block_width	：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
		   const int block_high	：高度（错误及缺省1）
		   const bool separator	：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致 CONSOLE_GRAPHICS_INFO 中其它成员值的变化，要处理
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
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_INFO 结构中的颜色
  输入参数：const int bg_color	：背景色（缺省 -1表示用窗口背景色）
		   const int fg_color	：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_frame_color(const CCT_COLOR bgcolor, const CCT_COLOR fgcolor)
{
	CFI.setcolor(bgcolor, fgcolor);
	return 0; //可按需变化
}
/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：const int type	：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_default_linetype(const int type)
{
	if (type == 1) {
		//╠ ╦ ╣╬ ╩
		strcpy(CBI.top_left, "╔");
		strcpy(CBI.lower_left, "╚");
		strcpy(CBI.top_right, "╗");
		strcpy(CBI.lower_right, "╝");
		strcpy(CBI.h_normal, "═");
		strcpy(CBI.v_normal, "║");
	}
	else if (type == 2) {
		//┌└┘┐├┤┬┴┼─│
		strcpy(CBI.top_left, "┌");
		strcpy(CBI.lower_left, "└");
		strcpy(CBI.top_right, "┐");
		strcpy(CBI.lower_right, "┘");
		strcpy(CBI.h_normal, "─");
		strcpy(CBI.v_normal, "│");
	}
	else if (type == 3) {
		//╒╕╘╛╞╡╤╧╪═│
		strcpy(CBI.top_left, "╒");
		strcpy(CBI.lower_left, "╘");
		strcpy(CBI.top_right, "╕");
		strcpy(CBI.lower_right, "╛");
		strcpy(CBI.h_normal, "═");
		strcpy(CBI.v_normal, "│");
	}
	else if (type == 4) {
		//╓╖╙╜╟╢╥╨╫─║
		strcpy(CBI.top_left, "╓");
		strcpy(CBI.lower_left, "╙");
		strcpy(CBI.top_right, "╖");
		strcpy(CBI.lower_right, "╜");
		strcpy(CBI.h_normal, "─");
		strcpy(CBI.v_normal, "║");
	}
	if (type >= 1 && type <= 4)
		return type;
	else 
		return -1; //可按需变化
}


/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：const char *...	：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_linetype(const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	make_linetype(CBI.top_left, top_left);
	make_linetype(CBI.lower_left, lower_left);
	make_linetype(CBI.top_right, top_right);
	make_linetype(CBI.lower_right, lower_right);
	make_linetype(CBI.h_normal, h_normal);
	make_linetype(CBI.v_normal, v_normal);
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：const bool on_off	：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_block_border_switch(const bool on_off)
{
	CBI.block_border = on_off;
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：const int type			：状态栏类型（上/下）
		   const bool on_off		：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		    2、行列的变化会导致 CONSOLE_GRAPHICS_INFO 中其它成员值的变化，要处理
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
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：const int type				：状态栏类型（上/下）
		   const int normal_bgcolor	：正常文本背景色（缺省 -1表示使用窗口背景色）
		   const int normal_fgcolor	：正常文本前景色（缺省 -1表示使用窗口前景色）
		   const int catchy_bgcolor	：醒目文本背景色（缺省 -1表示使用窗口背景色）
		   const int catchy_fgcolor	：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
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
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：const bool on_off	：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
            2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_rowno_switch(const bool on_off)
{
	draw_frame_with_row_no = on_off;
	if(on_off)
		SLI.top_start_y = extern_up_lines,
		SLI.lower_start_y = extern_up_lines + SLI.is_top_status_line + row_num * (CFI.block_high + CFI.separator) + (!CFI.separator) + 1 + draw_frame_with_row_no;

	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
            2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_set_colno_switch(const bool on_off)
{
	draw_frame_with_col_no = on_off;
	if (on_off)
		SLI.top_start_x = extern_left_cols + draw_frame_with_col_no,
		SLI.lower_start_x = extern_left_cols + draw_frame_with_col_no;
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
            2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::gmw_print() const
{
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：返回整个窗口的行数（已实现，不要动）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::lines() const
{
	return this->total_lines;
}

/***************************************************************************
  函数名称：
  功    能：返回整个窗口的列数（已实现，不要动）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CONSOLE_GRAPHICS_INFO::cols() const
{
	return this->total_cols;
}

/***************************************************************************
  函数名称：
  功    能：CONSOLE_GRAPHICS_INFO的构造函数
  输入参数：const int row			：游戏区域色块行数（缺省10）
		   const int col			：游戏区域色块列数（缺省10）
		   const CCT_COLOR bgcolor	：整个窗口背景色（缺省 CCT_COLOR::black）
		   const CCT_COLOR fgcolor	：整个窗口背景色（缺省 CT_COLOR::white）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
CONSOLE_GRAPHICS_INFO::CONSOLE_GRAPHICS_INFO(const int row, const int col, const CCT_COLOR bgcolor, const CCT_COLOR fgcolor)
{
	memset(this, 0x00, sizeof(CONSOLE_GRAPHICS_INFO)); //数据成员全部置0

	/* 设定游戏主区域的色块数量 */
	gmw_set_rowcol(row, col);

	/* 初始化整个游戏区域的颜色 */
	gmw_set_color(bgcolor, fgcolor);

	/* 初始化字体为缺省（点阵字体，8*16） */
	gmw_set_font();

	/* 设定延时 */
	gmw_set_delay(DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);

	/* 初始化上下左右辅助区域的大小为缺省（全0） */
	gmw_set_ext_rowcol();

	/* 置是否需要上下状态栏的缺省值（都要） */
	gmw_set_status_line_switch(TOP_STATUS_LINE);
	gmw_set_status_line_switch(LOWER_STATUS_LINE);
	gmw_set_status_line_color(TOP_STATUS_LINE);
	gmw_set_status_line_color(LOWER_STATUS_LINE);

	/* 置打印色块时是否需要行号列标的缺省值（不要） */
	gmw_set_rowno_switch();
	gmw_set_colno_switch();

	/* 设定游戏大边框的缺省线型（双线） */
	gmw_set_frame_linetype();
	gmw_set_frame_style();
	gmw_set_frame_color();

	/* 设定每个色块的缺省线型（双线）*/
	gmw_set_block_linetype();
	gmw_set_block_border_switch();
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：
  返 回 值：
  说    明：具体可参考demo的效果
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


	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：在上状态栏上显示信息
  输入参数：
  返 回 值：
  说    明：
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
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：在下状态栏上显示信息
  输入参数：
  返 回 值：
  说    明：
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
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
            2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
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
	return 1; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
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
	return 0; //可按需变化
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：
		   CCT_MOUSE &MAction						：如果返回 CCT_KMEVENT::mouse，则此值有效，为 only_moved/left_button_click/right_button_click 三者之一
		                                               如果返回 CCT_KMEVENT::keyboard，则此值无效
		   int &MRow								：如果返回 CCT_KMEVENT::mouse 且 MAction = only_moved/left_button_click，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_KMEVENT::mouse 且 MAction = only_moved/left_button_click，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KMEVENT::keyboard，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KMEVENT::keyboard，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
           1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
		                      得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		                      得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_KMEVENT::mouse ，MAction 为 left_button_click, MRow 为行号，MCol 为列标
		                          且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_KMEVENT::mouse ，MAction 为 right_button_click, MRow、MCol不可信
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KMEVENT::keyboard，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 class_cct.cpp 中的 read_keyboard_and_mouse 函数实现
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
						gmw_lower_status_line(NULL, "[当前光标] 位置非法");
					continue;
				}
				else if (update_lower_status_line) {
					char content[30];
					sprintf(content, "[当前光标] %d行%d列", MY, MX);
					gmw_lower_status_line(content);
				}
				cct.disable_mouse();
				return CCT_KMEVENT::mouse;
			}
			else if (MAction == CCT_MOUSE::left_button_click) {
				MRow = MY, MCol = MX;
				if (!gmw_inner_check_inarea(xx, yy)) {
					if (update_lower_status_line)
						gmw_lower_status_line(NULL, "[当前光标] 位置非法");
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
	return CCT_KMEVENT::keyboard; //可按需变化
}
