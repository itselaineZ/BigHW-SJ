/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <Windows.h>
//允许添加自己需要的头文件
#include "../include/class_cct.h"
#include "../include/class_gmw_sli.h"
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
		1、函数名不限，建议为 sli_inner_*
		2、个数不限
		3、如果是成员函数，必须是在private/protected中声明的函数
		4、如果是全局函数，必须是static，即仅限制在本源程序文件内部使用
   --------------------------------------------------------------------------
*/

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/

/* --------------------------------------------------------------------------
	 此处可以给出需要的公共函数的实现
		 1、函数名不限，建议为 sli_*
		 2、个数不限
		 3、如果是成员函数，必须是在public中声明的函数
		 4、不允许外部全局函数
	--------------------------------------------------------------------------
*/

int STATUS_LINE_INFO::setcolor_top_normal(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->top_normal_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->top_normal_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_top_catchy(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->top_catchy_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->top_catchy_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_lower_normal(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->lower_normal_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->lower_normal_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_lower_catchy(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->lower_catchy_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->lower_catchy_fgcolor = fg_color;
	return 1;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
