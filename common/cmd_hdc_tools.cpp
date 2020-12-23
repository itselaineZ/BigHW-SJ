/* 1952339 信08 张馨月*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */
#include <cmath>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

struct vct2 {
	int x, y;
	vct2() { x = y = 0; }
	vct2(int a, int b) { x = a, y = b; }
};

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

const double pi = acos(-1);

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */
static bool in_triangle(const vct2 A, const vct2 B, const vct2 C, const vct2 P)
{
	vct2 v0 = vct2(C.x-A.x, C.y-A.y), v1 = vct2(B.x-A.x, B.y-A.y), v2 = vct2(P.x-A.x, P.y-A.y);
	double u = double(((double)v1.x*v1.x+(double)v1.y*v1.y)*((double)v2.x*v0.x+ (double)v2.y*v0.y)-((double)v1.x*v0.x+ (double)v1.y*v0.y)*((double)v2.x*v1.x+ (double)v2.y*v1.y)) / (((double)v0.x*v0.x+(double)v0.y*v0.y)*((double)v1.x*v1.x+ (double)v1.y*v1.y)-((double)v0.x*v1.x+ (double)v0.y*v1.y)*((double)v1.x*v0.x+ (double)v1.y*v0.y));
	double v = double(((double)v0.x*v0.x+(double)v0.y*v0.y)*((double)v2.x*v1.x+ (double)v2.y*v1.y)-((double)v0.x*v1.x+ (double)v0.y*v1.y)*((double)v2.x*v0.x+ (double)v2.y*v0.y)) / (((double)v0.x*v0.x+(double)v0.y*v0.y)*((double)v1.x*v1.x+ (double)v1.y*v1.y)-((double)v0.x*v1.x+ (double)v0.y*v1.y)*((double)v1.x*v0.x+ (double)v1.y*v0.y));
	return u >= 0.0 && v >= 0.0 && u + v <= 1.0;
}

static bool in_circle(const int x, const int y, const int a, const int b, const int r)
{
	return (x - a) * (x - a) + (y - b) * (y - b) <= r * r;
}

static int chacheng(const vct2 a, const vct2 b)
{
	return a.x * b.y - a.y * b.x;
}

static bool check_between(const vct2 a, const vct2 b, const vct2 x)
{
	return chacheng(x, a) * chacheng(b, x) >= 0;
}

/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
            const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
    /* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
            const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	//hdc_cls();
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int old_x1 = INT_MAX, old_y1 = INT_MAX;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	int lx = x - tn, rx = x + tn, dy = y - tn, uy = y + tn;
	for (int xx = max(lx, 0); xx <= rx; xx ++)
		for (int yy = max(dy, 0); yy <= uy; yy ++)
			if (in_circle(xx, yy, x, y, tn))
				hdc_base_point(xx, yy);
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_point函数的组合(除hdc_line外，具体见说明)
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：画线段
  输入参数：const int x1		：起点的x
            const int y1		：起点的y
			const int x2		：终点的x
			const int y2		：终点的y
			const int thickness	：线段的粗细（有缺省值）
			const int RGB_value	：线段的颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	if (abs(x1 - x2) > abs(y1 - y2)) {
		int lx, rx, y;
		if (x1 < x2)
			lx = x1, rx = x2, y = y1;
		else
			lx = x2, rx = x1, y = y2;
		for (int x = max(lx, 0); x <= rx; ++x)
			hdc_point(x, y + int(((double)y1 - y2) / ((double)x1 - x2) * ((double)x - lx)), thickness, RGB_value);
	}
	else {
		int dy, uy, x;
		if (y1 < y2)
			dy = y1, uy = y2, x = x1;
		else
			dy = y2, uy = y1, x = x2;
		for (int y = max(dy, 0); y <= uy; ++y)
			hdc_point(x + int(((double)x1 - x2) / ((double)y1 - y2) * ((double)y - dy)), y, thickness, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
            const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	if (!filled)
		return;
	int lx, rx, dy, uy;
	lx = min(x1, min(x2, x3));
	rx = max(x1, max(x2, x3));
	dy = min(y1, min(y2, y3));
	uy = max(y1, max(y2, y3));
	vct2 A = vct2(x1, y1), B = vct2(x2, y2), C = vct2(x3, y3);
	for (int x = max(lx, 0); x <= rx; x += thickness)
		for (int y = max(dy, 0); y <= uy; y += thickness)
			if (in_triangle(A, B, C, vct2(x, y)))
				hdc_point(x, y, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
            const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int x1 = left_up_x;
	int y1 = left_up_y;
	int x2 = int(x1 + width * cos(rotation_angles / 180.0 * pi));
	int y2 = int(y1 + width * sin(rotation_angles / 180.0 * pi));
	int x3 = int(x2 - high * sin(rotation_angles / 180.0 * pi));
	int y3 = int(y2 + high * cos(rotation_angles / 180.0 * pi));
	int x4 = int(x1 - high * sin(rotation_angles / 180.0 * pi));
	int y4 = int(y1 + high * cos(rotation_angles / 180.0 * pi));

	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x4, y4, thickness, RGB_value);
	hdc_line(x4, y4, x1, y1, thickness, RGB_value);
	if (!filled)
		return;
	hdc_triangle(x1, y1, x2, y2, x3, y3, 1, thickness, RGB_value);
	hdc_triangle(x1, y1, x4, y4, x3, y3, 1, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
            const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int end = (angle_end - angle_begin) > 360 ? 360 + angle_begin : angle_end;
	if (end < angle_begin)
		end += 360;
	for (int i = angle_begin; i <= end; ++i)
		hdc_point(int(point_x + radius * sin(i / 180.0 * pi)), int(point_y - radius * cos(i / 180.0 * pi)), thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	if (angle_end - angle_begin % 360 == 0)
		hdc_circle(point_x, point_y, radius, filled, thickness, RGB_value);
	else {
		int x1 = int(point_x + radius * sin(angle_begin / 180.0 * pi)), y1 = int(point_y - radius * cos(angle_begin / 180.0 * pi));
		int x2 = int(point_x + radius * sin(angle_end / 180.0 * pi)), y2 = int(point_y - radius * cos(angle_end / 180.0 * pi));
		hdc_line(point_x, point_y, x1, y1, thickness, RGB_value);
		hdc_line(point_x, point_y, x2, y2, thickness, RGB_value);
		hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);
		if (!filled)
			return;
		for (int r = 1; r <= radius; r += thickness)
			hdc_arc(point_x, point_y, r, angle_begin, angle_end, thickness, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	hdc_arc(point_x, point_y, radius, 0, 360, thickness, RGB_value);
	if (!filled)
		return;
	int lx = point_x-radius, rx = point_x+radius, dy = point_y-radius, uy = point_y+radius;
	for (int x = max(lx, 0); x <= rx; x += thickness)
		for (int y = max(dy, 0); y <= uy; y += thickness)
			if (in_circle(x, y, point_x, point_y, radius))
				hdc_point(x, y, thickness, RGB_value);

}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//hdc_cls();

	int px1, py1, px2, py2, d;
	int lx = point_x - radius_a, rx = point_x + radius_a, dy = point_y - radius_b, uy = point_y + radius_b;
	for (int x = lx; x <= rx; x += thickness) {
		int y = int(radius_b * sqrt(1.0 - (double(x) - point_x) * (double(x) - point_x) / radius_a / radius_a));
		d = (int)sqrt((x - point_x) * (x - point_x) + (y - point_y) * (y - point_y));
		px1 = int((x - point_x) * cos(rotation_angles / 180.0 * pi) - y * sin(rotation_angles / 180.0 * pi) + point_x);
		py1 = int(y * cos(rotation_angles / 180.0 * pi) + (double(x) - point_x) * sin(rotation_angles / 180.0 * pi) + point_y);
		px2 = int((x - point_x) * cos(rotation_angles / 180.0 * pi) + y * sin(rotation_angles / 180.0 * pi) + point_x);
		py2 = int(-y * cos(rotation_angles / 180.0 * pi) + (double(x) - point_x) * sin(rotation_angles / 180.0 * pi) + point_y);
		hdc_point(px1, py1, thickness, RGB_value);
		hdc_point(px2, py2, thickness, RGB_value);
		if (filled)
			hdc_line(px1, py1, px2, py2, thickness, RGB_value);
	}

	for (int y = dy; y <= uy; y += thickness) {
		int x = int(radius_a * sqrt(1.0 - (double(y)-point_y) * (double(y)-point_y) / radius_b / radius_b));
		d = (int)sqrt((x - point_x) * (x - point_x) + (y - point_y) * (y - point_y));
		px1 = int(x * cos(rotation_angles / 180.0 * pi) - (double(y) - point_y) * sin(rotation_angles / 180.0 * pi) + point_x);
		py1 = int((y - point_y) * cos(rotation_angles / 180.0 * pi) + x * sin(rotation_angles / 180.0 * pi) + point_y);
		px2 = int(-x * cos(rotation_angles / 180.0 * pi) - (double(y) - point_y) * sin(rotation_angles / 180.0 * pi) + point_x);
		py2 = int((y - point_y) * cos(rotation_angles / 180.0 * pi) - x * sin(rotation_angles / 180.0 * pi) + point_y);
		hdc_point(px1, py1, thickness, RGB_value);
		hdc_point(px2, py2, thickness, RGB_value);
	}
}

#endif !HDC_SERIES_BY_TEACHER
