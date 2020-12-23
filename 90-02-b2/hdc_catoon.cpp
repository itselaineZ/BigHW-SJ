/*1952339 信08 张馨月*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include "../include/cmd_hdc_tools.h"
using namespace std;

const double pi = acos(-1);

static void hdc_ellipse_half(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int px1, py1, px2, py2, d;
	int lx = point_x - radius_a, rx = point_x + radius_a, dy = point_y - radius_b, uy = point_y + radius_b;
	for (int y = dy; y <= point_y-10; y += thickness) {
		int x = int(radius_a * sqrt(1.0 - (double(y) - point_y) * (double(y) - point_y) / radius_b / radius_b));
		d = (int)sqrt((x - point_x) * (x - point_x) + (y - point_y) * (y - point_y));
		px1 = int(x * cos(rotation_angles / 180.0 * pi) - (double(y) - point_y) * sin(rotation_angles / 180.0 * pi) + point_x);
		py1 = int((y - point_y) * cos(rotation_angles / 180.0 * pi) + x * sin(rotation_angles / 180.0 * pi) + point_y);
		px2 = int(-x * cos(rotation_angles / 180.0 * pi) - (double(y) - point_y) * sin(rotation_angles / 180.0 * pi) + point_x);
		py2 = int((y - point_y) * cos(rotation_angles / 180.0 * pi) - x * sin(rotation_angles / 180.0 * pi) + point_y);
		hdc_point(px1, py1, thickness, RGB_value);
		hdc_point(px2, py2, thickness, RGB_value);
		if(filled)
			hdc_line(px1, py1, px2, py2, thickness, RGB_value);
	}
}

void hdc_draw_catoon_1952339(const int base_x, const int base_y)
{
	//位置最好为 (300, 200)
	hdc_cls();

	//头
	hdc_ellipse(base_x, base_y, 60, 50, 0, 1, 2, RGB(255, 255, 255));
	hdc_ellipse(base_x, base_y, 60, 50, 0, 0, 1, RGB(0, 0, 0));
	hdc_ellipse_half(base_x, base_y, 60, 50, 0, 1, 2, RGB(0, 204, 255));
	hdc_line(base_x - 65, base_y + 10, base_x, base_y - 60, 10, RGB(0, 204, 255));
	hdc_line(base_x + 65, base_y + 10, base_x, base_y - 60, 10, RGB(0, 204, 255));
	hdc_ellipse(base_x, base_y - 40, 100, 30, 0, 1, 2, RGB(153, 102, 255));
	hdc_ellipse(base_x, base_y - 40, 100, 30, 0, 0, 2, RGB(112, 41, 255));
	hdc_rectangle(base_x - 50, base_y - 95, 100, 50, 0, 1, 2, RGB(153, 102, 255));
	hdc_rectangle(base_x - 50, base_y - 95, 100, 50, 0, 0, 2, RGB(112, 41, 255));

	//辫子
	for (int i = 5; i <= 75; i += 10) {
		hdc_circle(base_x - 60 - i, base_y + 10 + i/5, 6, 1, 2, RGB(0, 204, 255));
		hdc_circle(base_x - 60 - i, base_y + 10 + i/5, 6, 0, 1, RGB(51, 51, 255));
		hdc_circle(base_x + 60 + i, base_y + 10 + i/5, 6, 1, 2, RGB(0, 204, 255));
		hdc_circle(base_x + 60 + i, base_y + 10 + i/5, 6, 0, 1, RGB(51, 51, 255));
	}
	hdc_triangle(base_x - 60 - 80, base_y + 10 + 15, base_x - 85 - 80, base_y + 20 + 15, base_x - 85 - 80, base_y + 0 + 15, 1, 2, RGB(0, 204, 255));
	hdc_triangle(base_x + 60 + 80, base_y + 10 + 15, base_x + 85 + 80, base_y + 20 + 15, base_x + 85 + 80, base_y + 0 + 15, 1, 2, RGB(0, 204, 255));
	hdc_triangle(base_x - 60 - 80, base_y + 10 + 15, base_x - 85 - 80, base_y + 20 + 15, base_x - 85 - 80, base_y + 0 + 15, 0, 1, RGB(51, 51, 255));
	hdc_triangle(base_x + 60 + 80, base_y + 10 + 15, base_x + 85 + 80, base_y + 20 + 15, base_x + 85 + 80, base_y + 0 + 15, 0, 1, RGB(51, 51, 255));

	//五官
	hdc_ellipse(base_x - 25, base_y + 5, 5, 10, 0, 1, 2, RGB(0, 0, 0));
	hdc_ellipse(base_x + 25, base_y + 5, 5, 10, 0, 1, 2, RGB(0, 0, 0));
	hdc_ellipse(base_x - 25, base_y + 5, 1, 1, 0, 1, 2, RGB(255, 255, 255));
	hdc_ellipse(base_x + 25, base_y + 5, 1, 1, 0, 1, 2, RGB(255, 255, 255));
	hdc_line(base_x - 2, base_y + 25, base_x + 2, base_y + 25, 1, RGB(0, 0, 0));

	//脖子
	hdc_rectangle(base_x - 3, base_y + 45, 6, 25, 0, 1, 2, RGB(255, 255, 255));
	hdc_line(base_x-5, base_y+50, base_x+5, base_y+50, 1, RGB(0, 0, 0));

	//手
	hdc_circle(base_x - 60 - 60, base_y + 85, 10, 1, 2, RGB(255, 255, 255));
	hdc_circle(base_x - 60 - 60, base_y + 85, 10, 0, 1, RGB(0, 0, 0));
	hdc_circle(base_x - 60 - 52, base_y + 74, 2, 1, 2, RGB(255, 255, 255));
	hdc_circle(base_x + 60 + 60, base_y + 85, 10, 1, 2, RGB(255, 255, 255));
	hdc_circle(base_x + 60 + 60, base_y + 85, 10, 0, 1, RGB(0, 0, 0));
	hdc_circle(base_x + 60 + 52, base_y + 74, 2, 1, 2, RGB(255, 255, 255));

	//衣服
	hdc_rectangle(base_x - 60 - 50, base_y + 75, 220, 20, 0, 1, 2, RGB(255, 153, 255));
	hdc_line(base_x - 60 - 48, base_y + 90, base_x - 30, base_y + 110, 5, RGB(255, 153, 255));
	hdc_line(base_x + 60 + 48, base_y + 90, base_x + 30, base_y + 110, 5, RGB(255, 153, 255));
	hdc_line(base_x - 50, base_y + 100, base_x + 50, base_y + 100, 7, RGB(255, 153, 255));
	hdc_rectangle(base_x - 35, base_y + 110, 70, 60, 0, 1, 2, RGB(255, 153, 255));
	hdc_line(base_x - 30, base_y + 110, base_x - 40, base_y + 165, 7, RGB(255, 153, 255));
	hdc_line(base_x + 30, base_y + 110, base_x + 40, base_y + 165, 7, RGB(255, 153, 255));
	hdc_line(base_x - 60 - 50, base_y + 75, base_x - 60 - 50, base_y + 95, 1, RGB(0, 0, 0));
	hdc_line(base_x + 60 + 50, base_y + 75, base_x + 60 + 50, base_y + 95, 1, RGB(0, 0, 0));

	//领带
	hdc_rectangle(base_x - 10, base_y + 70, 12, 10, 45, 1, 2, RGB(255, 204, 255));
	hdc_rectangle(base_x - 10, base_y + 70, 12, 10, 45, 0, 1, RGB(0, 0, 0));
	hdc_rectangle(base_x, base_y + 78, 12, 10, -45, 1, 2, RGB(255, 204, 255));
	hdc_rectangle(base_x, base_y + 78, 12, 10, -45, 0, 1, RGB(0, 0, 0));
	hdc_triangle(base_x, base_y + 78, base_x - 5, base_y + 135, base_x + 7, base_y + 150, 1, 2, RGB(255, 204, 255));
	hdc_triangle(base_x, base_y + 78, base_x - 5, base_y + 135, base_x + 7, base_y + 150, 0, 1, RGB(0, 0, 0));
	hdc_circle(base_x, base_y + 88, 4, 1, 2, RGB(255, 204, 255));
	hdc_circle(base_x, base_y + 88, 4, 0, 1, RGB(0, 0, 0));

	cct_setcolor();
	cct_gotoxy(0, 25);
}