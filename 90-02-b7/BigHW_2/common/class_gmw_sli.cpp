/*1952339 ��08 ��ܰ��*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <Windows.h>
//��������Լ���Ҫ��ͷ�ļ�
#include "../include/class_cct.h"
#include "../include/class_gmw_sli.h"
using namespace std;

/* --------------------------------------------------------------------------
	�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ���
		1���������٣����û��
		2����̬ȫ��ֻ������/�궨���������
		3���������ⲿȫ�ֱ���
   --------------------------------------------------------------------------
*/

/* --------------------------------------------------------------------------
	�˴����Ը�����Ҫ���ڲ�������ʵ��
		1�����������ޣ�����Ϊ sli_inner_*
		2����������
		3������ǳ�Ա��������������private/protected�������ĺ���
		4�������ȫ�ֺ�����������static�����������ڱ�Դ�����ļ��ڲ�ʹ��
   --------------------------------------------------------------------------
*/

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/

/* --------------------------------------------------------------------------
	 �˴����Ը�����Ҫ�Ĺ���������ʵ��
		 1�����������ޣ�����Ϊ sli_*
		 2����������
		 3������ǳ�Ա��������������public�������ĺ���
		 4���������ⲿȫ�ֺ���
	--------------------------------------------------------------------------
*/

int STATUS_LINE_INFO::setcolor_top_normal(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->top_normal_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->top_normal_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_top_catchy(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->top_catchy_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->top_catchy_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_lower_normal(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->lower_normal_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->lower_normal_fgcolor = fg_color;
	return 1;
}
int STATUS_LINE_INFO::setcolor_lower_catchy(const CCT_COLOR bg_color, const CCT_COLOR fg_color)
{
	if (bg_color != CCT_COLOR::invalid)
		this->lower_catchy_bgcolor = bg_color;
	if (fg_color != CCT_COLOR::invalid)
		this->lower_catchy_fgcolor = fg_color;
	return 1;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
