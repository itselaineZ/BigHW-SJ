/*1952339 信08 张馨月*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
using namespace std;

/* 存储色块边框信息的字符数组的长度（含尾零）
   注：用字符数组而不用指针的原因是为了将来可以从配置文件中读 */
#define CBI_LEN					3

/* 定义描述色块信息的结构体 */
class  CONSOLE_BLOCK_INFO {
protected:
	/* ---------------------------------------------------------------------------------------------------------------
		下面定义的是可通过设置函数改变的值，不准修改成员名，不准改变类型
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* 定义小边框的各组成元素的形状
	╔ ═ ╗
	║    ║
	╚ ═ ╝ */
	char top_left[CBI_LEN];			// "╔"
	char lower_left[CBI_LEN];		// "╚"
	char top_right[CBI_LEN];			// "╗"
	char lower_right[CBI_LEN];		// "╝"
	char h_normal[CBI_LEN];			// "═"	//Horizontal
	char v_normal[CBI_LEN];			// "║"	//Vertical

	bool block_border;				//色块是否需要边框
	bool pad1;						//填充字节，为了凑齐20字节

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
			例如：gmw_set_status_line_switch/color等，这些函数该如何实现?
		2、为了提供一定的自由发挥程序，此处不限制函数名（这些函数应该在 CONSOLE_GRAPHICS_INFO 的视线中被用到）
	   -----------------------------------------------
	*/

	/* 友元，方便 CONSOLE_GRAPHICS_INFO 访问本类私有成员，可以不要 */
	friend class CONSOLE_GRAPHICS_INFO;
};

