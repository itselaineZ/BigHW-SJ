/* 1851441 陈江浩 计3班 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"
/* 允许添加需要的头文件 */
using namespace std;


const int COLOR_BODY = RGB(255, 196, 142);
const int COLOR_HAT = RGB(254, 121, 128);
const int COLOR_KUZI = RGB(93, 66, 65);
const int COLOR_HORN = RGB(190, 157, 114);

void hdc_draw_background(const int x_nose, const int y_nose)
{
	
	hdc_square(x_nose - 250, y_nose - 250, 500, 0, 1, 1, RGB(255, 255, 255));
}

void hdc_draw_hat(const int x_nose, const int y_nose)
{
	
	hdc_ellipse(x_nose, y_nose - 130, 80, 20, 0, 1, 1, COLOR_HAT);
	hdc_ellipse(x_nose, y_nose - 130, 80, 20, 0, 0, 1, 1);//帽子上沿的椭圆形线条
	hdc_rectangle(x_nose-80, y_nose-130, 160, 80,0,1, 1, COLOR_HAT);
	hdc_line(x_nose-80, y_nose - 130, x_nose - 80, y_nose - 50, 1,1);
	hdc_line(x_nose + 80, y_nose - 130, x_nose + 80, y_nose - 50, 1, 1);//边缘线
	hdc_rectangle(x_nose - 10, y_nose - 100,40, 10, 45, 1, 1, RGB(255, 255, 255));
	hdc_rectangle(x_nose - 15, y_nose - 72, 40, 10, 315, 1, 1, RGB(255, 255, 255));//白色的×
	hdc_ellipse(x_nose, y_nose - 20, 120, 50, 0, 1, 1, COLOR_HAT);
	hdc_ellipse(x_nose, y_nose - 20, 120, 50, 0, 0, 1,1);
	hdc_ellipse(x_nose, y_nose , 120, 50, 0, 1, 1, COLOR_HAT);
	hdc_ellipse(x_nose, y_nose, 120, 50, 0, 0, 1, 1);//帽檐
	hdc_line(x_nose - 120, y_nose - 20, x_nose - 120, y_nose, 1, 1);
	hdc_line(x_nose+120 , y_nose - 20, x_nose +120, y_nose, 1, 1);//边缘线
}
//绘制帽子

void hdc_draw_face(const int x_nose, const int y_nose)
{
	hdc_sector(x_nose, y_nose + 75, 110, -45, 45, 1, 1, COLOR_BODY);
	hdc_arc(x_nose, y_nose + 75, 110, -45, 45, 1,1);
	hdc_sector(x_nose, y_nose + 75-int(110/sqrt(2)), int(110/ sqrt(2)), 90, -90, 1, 1, COLOR_BODY);//脸庞绘制
	
	hdc_line(x_nose - 40, y_nose - 20, x_nose - 25, y_nose - 15, 1, 1);
	hdc_line(x_nose + 40, y_nose - 20, x_nose + 25, y_nose - 15, 1, 1);//两条眉毛
	hdc_circle(x_nose-40, y_nose+5, 15,  1, 1, RGB(255,255,255));
	hdc_circle(x_nose - 40, y_nose + 5, 10, 1, 1, 1);
	hdc_circle(x_nose + 40, y_nose + 5, 15, 1, 1, RGB(255, 255, 255));
	hdc_circle(x_nose + 40, y_nose + 5, 10, 1, 1, 1);//两颗眼珠子
	hdc_point( x_nose, y_nose+20,17, RGB(0,0,255));//蓝鼻子
	hdc_line(x_nose , y_nose + 28, x_nose, y_nose +43, 1, 1);
	hdc_arc(x_nose - 10, y_nose + 26, 20, 150, -150, 1, 1);
	hdc_arc(x_nose + 10, y_nose + 26, 20, 150, -150, 1, 1);//嘴巴
}
//绘制脸

void hdc_draw_body(const int x_nose, const int y_nose)
{
	hdc_rectangle(x_nose - 25, y_nose + 70, 50, 50, 0, 1, 1, COLOR_BODY);
	hdc_triangle(x_nose - 25, y_nose + 70, x_nose - 25, y_nose + 120, x_nose - 40, y_nose + 120, 1, 1, COLOR_BODY);
	hdc_triangle(x_nose + 25, y_nose + 70, x_nose + 25, y_nose + 120, x_nose + 40, y_nose + 120, 1, 1, COLOR_BODY);
	hdc_arc(x_nose, y_nose + 75 - int(110 / sqrt(2)), int(110 / sqrt(2)), 90, -90, 1, 1);//边框线
	hdc_line(x_nose - 25, y_nose + 70, x_nose - 40, y_nose + 120, 1, 1);
	hdc_line(x_nose + 25, y_nose + 70, x_nose + 40, y_nose + 120, 1, 1);
	hdc_sector(x_nose , y_nose + 120, 40, 90, -90, 1,1, COLOR_KUZI);
	
}
//绘制身体

void hdc_draw_hand_left(const int x_nose, const int y_nose)
{
	hdc_rectangle(x_nose + 25, y_nose + 75, 30, 5, 30, 1, 1, COLOR_BODY);//手臂
	hdc_sector(x_nose+60, y_nose + 85, 17, 45, -15, 1, 1, RGB(93, 66, 65));
	hdc_sector(x_nose + 60, y_nose + 85, 17, 105, -75, 1, 1,COLOR_BODY);//蹄子
	hdc_sector(x_nose + 60, y_nose + 85, 17, 45, -15, 0, 1,1);
	hdc_line(x_nose + 25, y_nose + 70, x_nose + 40, y_nose + 120, 1, 1);
}
//绘制左手

void hdc_draw_hand_right(const int x_nose, const int y_nose)
{
	hdc_rectangle(x_nose - 25, y_nose + 75, 30, 5, 150, 1, 1, COLOR_BODY);
	hdc_sector(x_nose - 60, y_nose + 85, 17, 15, -45, 1, 1, RGB(93, 66, 65));
	hdc_sector(x_nose - 60, y_nose + 85, 17, 75, -105, 1, 1, COLOR_BODY);
	hdc_sector(x_nose - 60, y_nose + 85, 17, 15, -45, 0, 1, 1);
	hdc_line(x_nose - 25, y_nose + 70, x_nose - 40, y_nose + 120, 1, 1);
}
//绘制右手

void hdc_draw_leg(const int x_nose, const int y_nose)
{
	hdc_rectangle(x_nose - 20, y_nose + 163, 3, 17, -15, 1, 1, COLOR_BODY);
	hdc_rectangle(x_nose - 25, y_nose + 155, 10, 7, 0, 1, 1, COLOR_KUZI);
	hdc_rectangle(x_nose + 17, y_nose + 163, 3, 17, 15, 1, 1, COLOR_BODY);
	hdc_rectangle(x_nose + 15, y_nose + 155, 10, 7, 0, 1, 1, COLOR_KUZI);//腿
	hdc_sector(x_nose-25, y_nose + 180, 10, -90, 90, 1, 1, COLOR_KUZI);
	hdc_sector(x_nose + 25, y_nose + 180, 10, -90, 90, 1, 1, COLOR_KUZI);//小jiojio

}
//绘制腿

void hdc_draw_horn(const int x_nose, const int y_nose)
{
	int i = 1;
	while(1)
	{
		hdc_sector(x_nose - 80 * i, y_nose - 120, 60, 90 * ((i == 1) + 1), 90 * ((i == 1) + 2), 1, 1, COLOR_HORN);
		hdc_sector(x_nose - 80*i, y_nose - 120, 60, 90 * ((i == 1) + 1), 90 * ((i == 1) + 2), 0, 1, 1);//大扇形

		hdc_sector(x_nose - 125*i, y_nose - 120, 15, -90, 90, 1, 1, COLOR_HORN);
		hdc_arc(x_nose - 125 * i, y_nose - 120, 15, -90, 90, 1, 1);
		hdc_line(x_nose - 110 * i, y_nose - 120, x_nose - 110 * i, y_nose - 100, 1);
		hdc_arc(x_nose - 80 * i, y_nose - 100, 30, (255-i*15) * i,(255+i*15) * i, 1, 1);//第一个小扇形
		
		hdc_sector(x_nose - 100 * i, y_nose - 120, 10, -90, 90, 1, 1, COLOR_HORN);
		hdc_arc(x_nose - 100 * i, y_nose - 120, 10, -90, 90, 1, 1);
		hdc_line(x_nose - 90 * i, y_nose - 120, x_nose - 90 * i, y_nose - 85, 1);
		hdc_arc(x_nose - 70 * i, y_nose - 85, 20, (245-i*25) * i,(245+i*25) * i, 1, 1);//第二个小扇形
		
		if (i == -1)
			break;
		i = -1;
	}
}
//绘制犄角

void hdc_draw_sakura(const int x_nose, const int y_nose)
{
	;
}
//绘制樱花
//void hdc_draw_Chopper(const int x_nose,const int y_nose )
void hdc_draw_catoon_1851441(const int x_nose, const int y_nose)
{
	hdc_cls();

	cout << "私はトニ一トニ一 チョッバ";
	hdc_draw_background(x_nose, y_nose);//背景
	hdc_draw_horn(x_nose, y_nose);//犄角
	hdc_draw_hat(x_nose, y_nose);//帽子
	hdc_draw_face(x_nose, y_nose);//脸
	hdc_draw_body(x_nose, y_nose);//身体
	hdc_draw_hand_left(x_nose, y_nose);
	hdc_draw_hand_right(x_nose, y_nose);//左右手 本来想画的不一样 然后发现太麻烦了
	hdc_draw_leg(x_nose, y_nose);//双腿

}
//绘制托尼托尼乔巴
