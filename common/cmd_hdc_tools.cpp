/* 1952339 ��08 ��ܰ��*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */
#include <cmath>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

struct vct2 {
	int x, y;
	vct2() { x = y = 0; }
	vct2(int a, int b) { x = a, y = b; }
};

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

const double pi = acos(-1);

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */

/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */
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

/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
            const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
    /* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
            const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
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
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

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
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_point���������(��hdc_line�⣬�����˵��)
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����߶�
  ���������const int x1		������x
            const int y1		������y
			const int x2		���յ��x
			const int y2		���յ��y
			const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			const int RGB_value	���߶ε���ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
            const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
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
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
            const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
            const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
