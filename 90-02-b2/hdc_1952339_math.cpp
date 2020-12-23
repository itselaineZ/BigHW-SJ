/*1952339 信08 张馨月*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include "../include/cmd_hdc_tools.h"
#include "hdc_student_works.h"
#include "../include/cmd_console_tools.h"
using namespace std;

void hdc_draw_Mathematical_curve_1952339()
{
	hdc_cls();
	const int thickness = 3;//粗细
	int x, y;
	double  thita;
	for (double t = 0.001; t <= 1.0; t += 0.001) {
		thita = 360.0 * 4.0 * t;
		x = int(250 + 40 * cos(thita) + 100 * cos(4.0 / 6.0 * thita));
		y = int(250 + 40 * sin(thita) - 60 * sin(4.0 / 6.0 * thita));
		hdc_point(x, y, thickness, RGB(0, 255, 0));
	}
	cct_setcolor();
	cct_gotoxy(0, 20);
	cout << "Rhodonea曲线\n";
}