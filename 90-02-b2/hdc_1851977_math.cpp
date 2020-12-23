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

static const double PI = 3.14159;
/* 绘制一个星形线 */
void hdc_draw_Astroid(const int point_x, const int point_y, const int a, const int thickness, const int RGB_value)
{
	cct_gotoxy(0, 0);
	cout << "一条星形线blingbling" << endl;
	for (double count = 0; count <= 360; count += 0.1)
		hdc_point((int)(point_x + a * cos(count*PI / 180)*cos(count*PI / 180)*cos(count*PI / 180)), (int)(point_y + a * sin(count*PI / 180)*sin(count*PI / 180)*sin(count*PI / 180)), thickness, RGB_value);
}

void hdc_draw_Mathematical_curve_1851977()
{
	hdc_cls();
	hdc_draw_Astroid(430, 350, 100, 5, RGB(117, 241, 164));
	hdc_draw_Astroid(430, 350, 120, 5, RGB(251, 237, 107));
	hdc_draw_Astroid(430, 350, 140, 5, RGB(245, 157, 113));
	hdc_draw_Astroid(430, 350, 160, 5, RGB(108, 125, 250));
	hdc_draw_Astroid(430, 350, 180, 5, RGB(117, 241, 164));
	hdc_draw_Astroid(430, 350, 200, 5, RGB(251, 237, 107));
	hdc_draw_Astroid(430, 350, 220, 5, RGB(245, 157, 113));
	hdc_draw_Astroid(430, 350, 240, 5, RGB(108, 125, 250));
	hdc_draw_Astroid(430, 350, 260, 5, RGB(117, 241, 164));
	hdc_draw_Astroid(430, 350, 280, 5, RGB(251, 237, 107));
	hdc_draw_Astroid(430, 350, 300, 5, RGB(245, 157, 113));
	hdc_draw_Astroid(430, 350, 320, 5, RGB(108, 125, 250));
}
