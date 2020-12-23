/*1952339 信08 张馨月*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
using namespace std;

/* 存储游戏主框架边框信息的字符数组的长度（含尾零）
   注：用字符数组而不用指针的原因是为了将来可以从配置文件中读 */
#define CFI_LEN		3

/* 定义描述游戏主框架区域的结构体 */
class CONSOLE_FRAME_INFO {
protected:
	/* ---------------------------------------------------------------------------------------------------------------
		下面定义的是可通过设置函数改变的值，不准修改成员名，不准改变类型
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* 定义游戏主框架区域的各组成元素的形状
	╔ ═ ╤ ═ ╗
	║          ║
	╟ ═ ┼ ═ ╢
	║          ║
	╚ ═ ╧ ═ ╝ */
	char top_left[CFI_LEN];			// "╔"
	char lower_left[CFI_LEN];		// "╚"
	char top_right[CFI_LEN];			// "╗"
	char lower_right[CFI_LEN];		// "╝"
	char h_normal[CFI_LEN];			// "═"	//Horizontal
	char v_normal[CFI_LEN];			// "║"	//Vertical
	char h_top_separator[CFI_LEN];	// "╤"
	char h_lower_separator[CFI_LEN];	// "╧"
	char v_left_separator[CFI_LEN];	// "╟"
	char v_right_separator[CFI_LEN];	// "╢"
	char mid_separator[CFI_LEN];		// "┼"

	char pad1[3];	//填充字节，为了凑齐36字节

	/* 游戏主框架区域的背景色和前景色 */
	CCT_COLOR bgcolor;
	CCT_COLOR fgcolor;

	/* 每个色块的宽度和高度(注意：宽度必须是2的倍数) */
	int block_width;
	int block_high;

	/* 色块之间是否需要分隔线 */
	bool separator;
	char pad2[3];	//填充字节，为了凑齐56字节

	/* ---------------------------------------------------------------------------------------------------------------
		1、下面这几个值是 lib_class_gmw.lib 需要用到的类成员，这些值都是内部计算得到的，不是直接设置值
		2、具体首先时你可以不用，但是不准删除，否则 lib_class_gmw.lib 中的函数调用时可能出错】
		3、每个色块的附加的宽度和高度(有分隔线是分别为2/1)，由separator计算而来
	   ---------------------------------------------------------------------------------------------------------------
	*/
	int block_width_ext;
	int block_high_ext;

	/* 每行/每列含分隔线的总宽度，由宽度/高度+分隔线计算而来 */
	int bwidth;
	int bhigh;

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


public:
	/* -----------------------------------------------
		1、供外部访问的函数（为了统一，修改本类数据成员的值的函数被封装在 CONSOLE_GRAPHICS_INFO 中后向外部提供
			例如：gmw_set_frame_default_linetype等，这些函数该如何实现?
		2、为了提供一定的自由发挥程序，此处不限制函数名（这些函数应该在 CONSOLE_GRAPHICS_INFO 的视线中被用到）
	   -----------------------------------------------
	*/

	int setcolor(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);

	/* 友元，方便 CONSOLE_GRAPHICS_INFO 访问本类私有成员，可以不要 */
	friend class CONSOLE_GRAPHICS_INFO;
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};

