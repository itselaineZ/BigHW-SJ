/* 1851977 计算机3班 李家麟 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

//const int Minions_Blue = RGB(80, 151, 204);
const int Minions_Blue = RGB(29, 118, 162);
//const int Minions_Yellow = RGB(235, 235, 49);
const int Minions_Yellow = RGB(249, 217, 70);
const int Minions_Black = RGB(0, 0, 0);
const int Minions_White = RGB(255, 255, 255);

const int base_x = 300;
const int base_y = 700;

static void Minions_body()
{
	hdc_sector(base_x + 140, base_y - 189, 90, 120, 150, true, 5, Minions_Yellow);
	hdc_sector(base_x + 50, base_y - 189, 90, 210, 240, true, 5, Minions_Yellow);
	hdc_triangle(base_x + 50, base_y - 189, base_x + 50, base_y - 114, base_x + 5, base_y - 114, true, 5, Minions_Yellow);
	hdc_triangle(base_x + 140, base_y - 189, base_x + 140, base_y - 114, base_x + 185, base_y - 114, true, 5, Minions_Yellow);
	hdc_rectangle(base_x + 50, base_y - 189, 90, 70, 0, true, 5, Minions_Yellow);
	hdc_rectangle(base_x - 30, base_y - 390, 246, 249, 0, true, 5, Minions_Yellow);
	//hdc_sector(base_x + 93, base_y - 390, 123, -90, 90, true, 5, Minions_Yellow);
	hdc_sector(base_x + 94, base_y - 363, 125, -80, 80, true, 5, Minions_Yellow);
	hdc_arc(base_x + 140, base_y - 189, 90, 120, 150, 5, Minions_Black);
	/* 水平 */
	hdc_line(base_x + 5, base_y - 114, base_x + 185, base_y - 114, 5, Minions_Black);
	hdc_arc(base_x + 50, base_y - 189, 90, 210, 240, 5, Minions_Black);
	/* 竖直 */
	hdc_line(base_x - 30, base_y - 141, base_x - 30, base_y - 390, 5, Minions_Black);
	hdc_line(base_x +216, base_y - 141, base_x +216, base_y - 390, 5, Minions_Black);
	//hdc_arc(base_x + 93, base_y - 390, 123, -90, 90, 5, Minions_Black);
	hdc_arc(base_x + 94, base_y - 363, 125, -80, 80, 5, Minions_Black);

}
static void Minions_eyes()
{
	hdc_rectangle(base_x - 30, base_y - 390, 41, 40, 0, true, 5, Minions_Black);
	hdc_circle(base_x + 52, base_y - 370, 41, true, 5, Minions_White);
	hdc_circle(base_x + 52, base_y - 370, 20, true, 5, Minions_Black);
	hdc_circle(base_x + 57, base_y - 373, 8, true, 5, Minions_White);
	hdc_circle(base_x + 52, base_y - 370, 41, false, 5, Minions_Black);
	hdc_circle(base_x + 52, base_y - 370, 20, false, 5, Minions_Black);
	//hdc_circle(base_x + 57, base_y - 373, 8, false, 5, Minions_Black);
	hdc_rectangle(base_x + 175, base_y - 390, 41, 40, 0, true, 5, Minions_Black);
	hdc_circle(base_x + 136, base_y - 370, 41, true, 5, Minions_White);
	hdc_circle(base_x + 136, base_y - 370, 20, true, 5, Minions_Black);
	hdc_circle(base_x + 141, base_y - 373, 8, true, 5, Minions_White);
	hdc_circle(base_x + 136, base_y - 370, 41, false, 5, Minions_Black);
	hdc_circle(base_x + 136, base_y - 370, 20, false, 5, Minions_Black);
	//hdc_circle(base_x + 141, base_y - 373, 8, false, 5, Minions_Black);
}
static void Minions_mouth()
{
	hdc_sector(base_x + 93, base_y - 310, 38, 90, 270, true, 5, Minions_White);
	hdc_sector(base_x + 93, base_y - 310, 40, 90, 270, false, 5, Minions_Black);
}
static void Minions_cloth()
{
	/* 填充中央牛仔裤 */
	hdc_rectangle(base_x - 3, base_y - 243, 192, 128, 0, true, 5, Minions_Blue);
	hdc_rectangle(base_x - 30, base_y - 189, 246, 44, 0, true, 5, Minions_Blue);
	hdc_sector(base_x - 30, base_y - 189, 26, 90, 180, true, 5, Minions_Blue);
	hdc_sector(base_x + 216, base_y - 189, 27, 180, 270, true, 5, Minions_Blue);
	hdc_sector(base_x + 140, base_y - 189, 90, 120, 150, true, 5, Minions_Blue);
	hdc_sector(base_x + 50, base_y - 189, 90, 210, 240, true, 5, Minions_Blue);
	
	/* 画中央牛仔裤 */
	//hdc_rectangle(base_x - 3, base_y - 243, 192, 54, 0, false, 5, Minions_Black);
	hdc_line(base_x - 3, base_y - 243, base_x + 189, base_y - 243, 5, Minions_Black);
	hdc_line(base_x - 3, base_y - 243, base_x - 3, base_y - 189, 5, Minions_Black);
	hdc_line(base_x + 189, base_y - 243, base_x + 189, base_y - 189, 5, Minions_Black);
	hdc_arc(base_x - 30, base_y - 189, 27, 90, 180, 5, Minions_Black);
	hdc_arc(base_x + 216, base_y - 189, 27, 180, 270, 5, Minions_Black);
	hdc_line(base_x - 30, base_y - 189, base_x - 3, base_y - 189, 5, Minions_Black);
	hdc_line(base_x + 216, base_y - 189, base_x + 189, base_y - 189, 5, Minions_Black);

	/* 填充左右两边牛仔吊带 */
		//左侧吊带
	hdc_triangle(base_x - 30, base_y - 280, base_x - 30, base_y - 260, base_x - 20, base_y - 270, true, 5, Minions_Blue);
	hdc_rectangle(base_x - 2, base_y - 233, 38, 14, 225, true, 5, Minions_Blue);
		//右侧吊带
	hdc_triangle(base_x + 216, base_y - 282, base_x + 216, base_y - 260, base_x + 206, base_y - 270, true, 5, Minions_Blue);
	hdc_rectangle(base_x + 179, base_y - 245, 38, 14, -45, true, 5, Minions_Blue);

	/* 左侧两条平行线 */
	hdc_line(base_x - 30, base_y - 280, base_x + 7, base_y - 243, 5, Minions_Black);
	hdc_line(base_x - 30, base_y - 260, base_x - 3, base_y - 233, 5, Minions_Black);
	/* 连接两条平行线 */
	hdc_line(base_x + 7, base_y - 243, base_x - 3, base_y - 233, 5, Minions_Black);
	/* 点点 */
	hdc_point(base_x - 3, base_y - 243, 10, Minions_Black);
	/* 右侧两条平行线 */
	hdc_line(base_x + 216, base_y - 282, base_x + 179, base_y - 245, 5, Minions_Black);
	hdc_line(base_x + 216, base_y - 260, base_x + 189, base_y - 233, 5, Minions_Black);
	/* 连接两条平行线 */
	hdc_line(base_x + 179, base_y - 243, base_x + 189, base_y - 233, 5, Minions_Black);
	/* 点点 */
	hdc_point(base_x + 189, base_y - 243, 10, Minions_Black);
	/* 画中间的口袋 */
	hdc_line(base_x + 53, base_y - 213, base_x + 133, base_y - 213, 5, Minions_Black);
	hdc_line(base_x + 53, base_y - 213, base_x + 53, base_y - 193, 5, Minions_Black);
	hdc_line(base_x + 133, base_y - 213, base_x + 133, base_y - 193, 5, Minions_Black);
	hdc_arc(base_x + 94, base_y - 193, 40, 90, 270, 5, Minions_Black);
	/* 画竖线 */
	hdc_line(base_x + 93, base_y - 114, base_x + 93, base_y - 129, 5, Minions_Black);
	//hdc_sector(base_x + 93, base_y - 310, 40, 90, 270, false, 5, Minions_Black);
}
static void Minions_feet()
{
	/* 左边一只脚 */
	hdc_sector(base_x + 40, base_y - 50, 40, -90, 0, true, 5, Minions_Black);
	hdc_rectangle(base_x + 40, base_y - 110, 40, 60, 0, true, 5, Minions_Black);
	/* 右边一只脚 */
	hdc_sector(base_x + 160, base_y - 50, 40, 0, 90, true, 5, Minions_Black);
	hdc_rectangle(base_x + 120, base_y - 110, 40, 60, 0, true, 5, Minions_Black);
}
static void Minions_hand()
{
	/* 左手 */
	hdc_sector(base_x + 7, base_y - 233, 52, 180, 360, true, 5, Minions_Yellow);
	hdc_sector(base_x + 7, base_y - 233, 41, 180, 360, true, 5, Minions_White);
	hdc_arc(base_x + 7, base_y - 233, 52, 180, 360, 5, Minions_Black);
	hdc_arc(base_x + 7, base_y - 233, 41, 180, 360, 5, Minions_Black);
	//hdc_arc(base_x - 30, base_y - 213, 20, 180, 360, 5, Minions_Black);
	/* 右手 */
	hdc_sector(base_x + 179, base_y - 233, 52, 0, 180, true, 5, Minions_Yellow);
	hdc_sector(base_x + 179, base_y - 233, 41, 0, 180, true, 5, Minions_White);
	hdc_arc(base_x + 182, base_y - 233, 52, 0, 180, 5, Minions_Black);
	hdc_arc(base_x + 182, base_y - 233, 41, 0, 180, 5, Minions_Black);
}
static void Minions_body_line()
{
	hdc_arc(base_x + 140, base_y - 189, 90, 120, 150, 5, Minions_Black);
	/* 水平 */
	hdc_line(base_x + 5, base_y - 114, base_x + 185, base_y - 114, 5, Minions_Black);
	hdc_arc(base_x + 50, base_y - 189, 90, 210, 240, 5, Minions_Black);
	/* 竖直 */
	hdc_line(base_x - 30, base_y - 141, base_x - 30, base_y - 390, 5, Minions_Black);
	hdc_line(base_x + 216, base_y - 141, base_x + 216, base_y - 390, 5, Minions_Black);
	//hdc_arc(base_x + 93, base_y - 390, 123, -90, 90, 5, Minions_Black);
	hdc_arc(base_x + 94, base_y - 363, 125, -80, 80, 5, Minions_Black);
}
//void hdc_draw_Minions(const int base_x, const int base_y)
void hdc_draw_catoon_1851977(const int base_x, const int base_y)
{
	hdc_cls();
	cct_gotoxy(0, 0);
	cout << "程序猿的小黄人当然没有头发" << endl;
	Minions_hand();
	Minions_body();
	Minions_eyes();
	Minions_mouth();
	Minions_cloth();
	Minions_feet();
	Minions_body_line();
}
