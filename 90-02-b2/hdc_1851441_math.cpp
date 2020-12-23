/* 1851441 陈江浩 计3班 */
#include <iostream>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

void hdc_draw_Mathematical_curve_1851441()
{
	hdc_cls();

	const int thickness = 1, RGB_value = 1;

	//(x^2+y^2-1)^3-x^x*y^3=0 原函数表达式
	const int center_x = 400, center_y = 400;//原点坐标

	double x, y_1, y_2;
	int start_x_1, start_x_2, start_y_1, start_y_2;
	int end_x_1 = 0 + center_x, end_x_2 = 0 + center_x, end_y_1 = 1*200 + center_y, end_y_2 = int(-1.05*200) + center_y;
	int count = 0;
	double exchange = 0;
	for (x = 0; x < 1.15; x+=0.0001)
	{
		
		for (double i = -1.0;i<1.5; i += 0.0001)
		{
			if (fabs((x*x + i * i - 1)*(x*x + i * i - 1)*(x*x + i * i - 1) - x *x*i*i*i) < 1e-6)
			{	
				if(count)
					exchange = y_1;
				y_1 = i;
				break;
			}
		}
		for (double i = 1.3; i >= -1.0; i -= 0.0001)
		{
			if (fabs((x*x + i * i - 1)*(x*x + i * i - 1)*(x*x + i * i - 1) - x * x*i*i*i) < 1e-3)
			{
				y_2 = i;
				break;
			}
		}
		count++;
		if (fabs(y_1 - y_2) < 0.03)
			y_1 = exchange;//处理未取得正确y_1坐标
		start_x_1 = end_x_1;
		start_x_2 = end_x_2;
		start_y_1 = end_y_1;
		start_y_2 = end_y_2;
		end_x_1 = int(x * 200) + center_x;
		end_x_2 = -1 * int(x * 200) + center_x;
		end_y_1 = -1*int(y_1 * 200) + center_y;
		end_y_2 = -1*int(y_2 * 200) + center_y;
		hdc_line(start_x_1, start_y_1,end_x_1 , end_y_1, thickness, RGB_value);
		hdc_line(start_x_1, start_y_2, end_x_1, end_y_2, thickness, RGB_value);
		hdc_line(start_x_2, start_y_1, end_x_2, end_y_1, thickness, RGB_value);
		hdc_line(start_x_2, start_y_2, end_x_2, end_y_2, thickness, RGB_value);
	}

}
//绘制心形线

