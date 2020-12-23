/*1952339 信08 张馨月*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
using namespace std;

/* 定义状态栏信息 */
#define TOP_STATUS_LINE			0	//上状态栏，位置固定在游戏主框架区域的最上方（如果有列标，则在列标之上）
#define LOWER_STATUS_LINE		1   //上状态栏，位置固定在游戏主框架区域的最下方

/* 定义描述状态栏信息的结构体 */
class STATUS_LINE_INFO {
protected:
	/* ---------------------------------------------------------------------------------------------------------------
		下面定义的是可通过设置函数改变的值，不准修改成员名，不准改变类型
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* 是否有上下状态栏 */
	bool is_top_status_line;
	bool is_lower_status_line;

	char pad1[2];	//填充字节，为了凑齐4字节

	/* 上状态栏的位置（左侧坐标） */
	int top_start_x;
	int top_start_y;

	/* 上状态栏正常信息配色 */
	CCT_COLOR top_normal_bgcolor;
	CCT_COLOR top_normal_fgcolor;

	/* 上状态栏醒目信息配色 */
	CCT_COLOR top_catchy_bgcolor;
	CCT_COLOR top_catchy_fgcolor;

	/* 下状态栏的位置（左侧坐标） */
	int lower_start_x;
	int lower_start_y;

	/* 下状态栏正常信息配色 */
	CCT_COLOR lower_normal_bgcolor;
	CCT_COLOR lower_normal_fgcolor;

	/* 下状态栏醒目信息配色 */
	CCT_COLOR lower_catchy_bgcolor;
	CCT_COLOR lower_catchy_fgcolor;

	/* ---------------------------------------------------------------------------------------------------------------
		1、下面这个值是 lib_class_gmw.lib 需要用到的类成员，这些值都是内部计算得到的，不是直接设置值
		2、具体首先时你可以不用，但是不准删除，否则 lib_class_gmw.lib 中的函数调用时可能出错】
	   ---------------------------------------------------------------------------------------------------------------
	*/

	 /* 状态栏所占的宽度（该值由计算得到，是游戏区域的宽度，不包括扩展区域，信息超过宽度则截断） */
	int width;

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
	int setcolor_top_normal(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_top_catchy(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_lower_normal(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_lower_catchy(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	/* 友元，方便 CONSOLE_GRAPHICS_INFO 访问本类私有成员，可以不要 */
	friend class CONSOLE_GRAPHICS_INFO;
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};

