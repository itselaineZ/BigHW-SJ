//1851573 ¼Æ1°à Àî²©Óî
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

//void hdc_draw_pikapika(const int head_x,const int head_y)
void hdc_draw_catoon_1851573(const int head_x, const int head_y)
{
	hdc_cls();
	//±³¾°
	hdc_circle(head_x, head_y+70, 300, 1, 2, RGB(164, 255, 248));
	//µ××ù
	hdc_ellipse(head_x+10, head_y + 230, 230, 100, 0, 1, 2, RGB(209, 172, 91));
	//Î²°Í
	hdc_rectangle(head_x + 100, head_y + 190, 100, 30, -20, 1, 2, RGB(252, 228, 130));
	hdc_rectangle(head_x + 179, head_y + 190, 50, 30, 230, 1, 2, RGB(252, 228, 130));
	hdc_rectangle(head_x + 135, head_y + 130, 90, 30, -30, 1, 2, RGB(252, 228, 130));
	hdc_triangle(head_x + 135, head_y + 130, head_x + 206, head_y + 80, head_x + 216, head_y + 90, 1, 2, RGB(252, 228, 130));
	hdc_rectangle(head_x + 165, head_y + 110, 95, 50, 240, 1, 2, RGB(252, 228, 130));
	hdc_rectangle(head_x + 100, head_y , 140, 70, -30, 1, 2, RGB(252, 228, 130));
	hdc_triangle(head_x + 140, head_y+50, head_x + 260, head_y-10, head_x + 270, head_y+10, 1, 2, RGB(252, 228, 130));
	hdc_triangle(head_x + 266, head_y + 13, head_x + 222, head_y - 72, head_x + 273, head_y -100, 1, 2, RGB(252, 228, 130));

	//×ó¶ú¶äÈý½Ç
	hdc_triangle(head_x - 120, head_y - 190, head_x - 113, head_y - 50, head_x - 60, head_y - 105, 1, 2, RGB(252, 228, 130));
	//×ó¶ú¶äÁ½²à»¡
	hdc_arc(head_x + 191, head_y - 120, 200 + 110, 254, 282, 16, RGB(252, 228, 130));
//	hdc_arc(head_x + 182, head_y - 120, 200 + 110, 254, 282, 2, RGB(0, 0, 0));
	hdc_arc(head_x - 312, head_y + 42, 300, 43, 60, 16, RGB(252, 228, 130));
//	hdc_arc(head_x - 304, head_y + 38, 300, 43, 60, 2, RGB(0, 0, 0));

	//Õû¸öÍ·µÄÔ²
	hdc_circle(head_x, head_y, 120, 1, 2, RGB(252, 228, 130));
//	hdc_circle(head_x, head_y, 120, 0, 2,RGB(0,0,0));
	//×ó±ßµÄà½à½Èâ
	hdc_circle(head_x - 95, head_y + 20, 33, 1, 2, RGB(252, 228, 130));
	//ÓÒ¶ú¶äÈý½Ç
	hdc_triangle(head_x + 175, head_y - 155, head_x + 80, head_y - 40, head_x + 40, head_y - 100, 1, 2, RGB(252, 228, 130));
	//ÓÒ¶ú¶äÁ½²à»¡
	hdc_arc(head_x + 190, head_y+50, 200, -42, -5, 15, RGB(252, 228, 130));
	hdc_arc(head_x-65, head_y - 271, 270, 117, 148, 16, RGB(252, 228, 130));
	//ÓÒ¶ú¶äºÚÉ«
	hdc_arc(head_x + 190, head_y + 50, 200, -19, -5, 15, RGB(0, 0, 0));
	hdc_arc(head_x - 65, head_y - 271, 270, 117, 131, 16, RGB(0, 0, 0));
	hdc_arc(head_x+56, head_y - 98, 80, 60, 94, 15, RGB(0, 0, 0));
	hdc_triangle(head_x + 175, head_y - 155, head_x + 130, head_y - 140, head_x + 140, head_y - 100, 1, 2, RGB(0, 0, 0));

	//×ó¶ú¶äºÚÉ«
	hdc_arc(head_x + 191, head_y - 120, 200 + 110, 272, 282, 16, RGB(0, 0, 0));
	hdc_arc(head_x - 312, head_y + 42, 300, 43, 48, 16, RGB(0, 0, 0));
	hdc_arc(head_x + 30, head_y - 20, 180, 305, 320, 16, RGB(0, 0, 0));
	hdc_triangle(head_x - 115, head_y - 190, head_x - 120, head_y - 140, head_x - 100, head_y - 160, 1, 2, RGB(0, 0, 0));
	//ÓÒÑÛ¾¦
	hdc_circle(head_x + 50, head_y - 13, 20, 1, 2, RGB(83, 16, 0));
	//ÓÒÑÛÇò
	hdc_circle(head_x + 56, head_y - 21, 8, 1, 2, RGB(237, 224, 218));
	//ÓÒÈùºì
	hdc_circle(head_x + 90, head_y +20, 20, 1, 2, RGB(254, 84, 51));
	//×óÑÛ¾¦
	hdc_ellipse(head_x - 70, head_y - 13, 18, 15, 90, 1, 4, RGB(83, 16, 0));
	//×óÑÛÖé
	hdc_ellipse(head_x - 65, head_y - 20, 6, 5, 93, 1, 2, RGB(237, 224, 218));
	//±Ç×Ó
	hdc_line(head_x - 28, head_y + 10, head_x - 23, head_y + 10, 4, RGB(163, 124, 59));
	//×ó²àµÄÈùºì
	hdc_ellipse(head_x - 115, head_y + 23, 16, 12, 73, 1, 4, RGB(254, 84, 51));
	//Æ¨¹É
	hdc_circle(head_x - 70, head_y + 205, 60, 1, 2, RGB(252, 228, 130));
	hdc_ellipse(head_x + 90, head_y + 180, 80, 60, 75, 1, 2, RGB(252, 228, 130));
	hdc_ellipse(head_x + 90, head_y + 180, 80, 60, 75, 0, 2,RGB(0,0,0));

	hdc_rectangle(head_x - 100, head_y + 166, 150, 100, -10, 1, 2, RGB(252, 228, 130));
	hdc_rectangle(head_x + 100, head_y + 261, 150, 100, 184, 1, 2, RGB(252, 228, 130));
	//×ó½Å
	hdc_ellipse(head_x - 100, head_y + 245, 30, 18, -60, 1, 2, RGB(252, 228, 130));
	hdc_ellipse(head_x - 100, head_y + 245, 30, 18, -60, 0, 3, RGB(0, 0, 0));
	hdc_line(head_x - 87, head_y + 217, head_x - 91, head_y + 221, 2);
	hdc_line(head_x - 82, head_y + 222, head_x - 86, head_y + 226, 2);
	//ÓÒ½Å
	hdc_ellipse(head_x + 100, head_y + 245, 30, 18,60, 1, 2, RGB(252, 228, 130));
	hdc_ellipse(head_x + 100, head_y + 245, 30, 18, 60, 0, 2, RGB(0, 0, 0));
	hdc_line(head_x + 87, head_y + 217, head_x + 91, head_y + 221, 2);
	hdc_line(head_x + 80, head_y + 222, head_x + 84, head_y + 226, 2);
	//×óÊÖ
	hdc_ellipse(head_x - 120, head_y + 150, 16, 14, 60, 1, 3, RGB(252, 228, 130));
	hdc_ellipse(head_x - 120, head_y + 150, 16, 14, 60, 0, 2, RGB(0, 0, 0));
	//ÓÒÊÖ
	hdc_ellipse(head_x + 105, head_y + 130, 40, 30, -60, 1, 2, RGB(252, 228, 130));
	hdc_ellipse(head_x + 105, head_y + 130, 43, 32, -60, 0, 2, RGB(0, 0, 0));
	//Î÷¹Ï


	hdc_arc(head_x - 10, head_y + 48, 145, 92, 190, 15, RGB(100, 91, 26));
//	hdc_triangle(head_x , head_y + 200 ,head_x + 65, head_y + 170, head_x + 60, head_y + 187, 1, 2, RGB(100, 91, 26));
	hdc_arc(head_x - 13, head_y + 1045, 1000, -8, 8, 15, RGB(251, 90, 80));

	hdc_sector(head_x - 15, head_y + 52, 145, 90, 270, 1, 2, RGB(251, 90, 80));
	hdc_arc(head_x - 15, head_y + 45, 145, 93, 267,13, RGB(255, 147, 109));
	hdc_point(head_x - 120, head_y + 75, 10, RGB(140, 83, 55));
	hdc_point(head_x - 100, head_y + 120, 10, RGB(140, 83, 55));
	hdc_point(head_x - 74, head_y + 93, 10, RGB(140, 83, 55));
	hdc_point(head_x - 60, head_y + 140, 10, RGB(140, 83, 55));
	hdc_point(head_x - 20, head_y + 120, 10, RGB(140, 83, 55));
	hdc_point(head_x + 20, head_y + 150, 10, RGB(140, 83, 55));
	hdc_point(head_x , head_y + 77, 10, RGB(140, 83, 55));
	hdc_point(head_x+40, head_y + 100, 10, RGB(140, 83, 55));
	hdc_point(head_x + 80, head_y + 93, 10, RGB(140, 83, 55));
	//ÓÒ×ì´½
	hdc_arc(head_x - 30, head_y + 26, 15, 130, 230, 3, RGB(163, 124, 59));
	//×ó×ì´½
	hdc_arc(head_x - 9, head_y + 26, 15, 130, 230, 3, RGB(163, 124, 59));
	//×óÊÖÖ¸
	hdc_ellipse(head_x - 116, head_y + 158, 6, 3, 150, 1, 3, RGB(252, 228, 130));
//	hdc_ellipse(head_x - 120, head_y + 150, 16, 14, 60, 0, 2, RGB(0, 0, 0));
	hdc_ellipse(head_x - 122, head_y + 153, 6, 3, 120, 1, 3, RGB(252, 228, 130));
	hdc_ellipse(head_x - 130, head_y + 146, 4, 3, 120, 1, 3, RGB(252, 228, 130));
	//ÓÒÊÖÖ¸
	hdc_ellipse(head_x + 94, head_y + 164, 6, 3, 20, 1, 4, RGB(252, 228, 130));
	hdc_ellipse(head_x + 102, head_y + 154, 6, 3, 20, 1, 4, RGB(252, 228, 130));
	hdc_ellipse(head_x + 110, head_y + 145, 6, 3, 20, 1, 4, RGB(252, 228, 130));

	return;
}