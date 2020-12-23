//1851573 计1班 李博宇
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

void hdc_draw_Mathematical_curve(const double x, const double y, const double length)
{
	//	hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
	hdc_triangle(int(x), int(y), int(x + length), int(y), int(x + length * 0.5), int(y - length * 0.5 * sqrt(3)));
	if (length <= 10) {
		return;
	}
	else {
		double le = length / 2;
		hdc_draw_Mathematical_curve(x, y, le);
		hdc_draw_Mathematical_curve(x + le, y, le);
		hdc_draw_Mathematical_curve(x + le / 2, y - le / 2 * sqrt(3), le);
	}
	return;
}

void hdc_draw_Mathematical_curve_1851573()
{
	hdc_cls();
	hdc_draw_Mathematical_curve(100, 600, 600);//三角形左下角的坐标
}
