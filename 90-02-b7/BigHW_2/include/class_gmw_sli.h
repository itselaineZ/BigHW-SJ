/*1952339 ��08 ��ܰ��*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
using namespace std;

/* ����״̬����Ϣ */
#define TOP_STATUS_LINE			0	//��״̬����λ�ù̶�����Ϸ�������������Ϸ���������б꣬�����б�֮�ϣ�
#define LOWER_STATUS_LINE		1   //��״̬����λ�ù̶�����Ϸ�������������·�

/* ��������״̬����Ϣ�Ľṹ�� */
class STATUS_LINE_INFO {
protected:
	/* ---------------------------------------------------------------------------------------------------------------
		���涨����ǿ�ͨ�����ú����ı��ֵ����׼�޸ĳ�Ա������׼�ı�����
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* �Ƿ�������״̬�� */
	bool is_top_status_line;
	bool is_lower_status_line;

	char pad1[2];	//����ֽڣ�Ϊ�˴���4�ֽ�

	/* ��״̬����λ�ã�������꣩ */
	int top_start_x;
	int top_start_y;

	/* ��״̬��������Ϣ��ɫ */
	CCT_COLOR top_normal_bgcolor;
	CCT_COLOR top_normal_fgcolor;

	/* ��״̬����Ŀ��Ϣ��ɫ */
	CCT_COLOR top_catchy_bgcolor;
	CCT_COLOR top_catchy_fgcolor;

	/* ��״̬����λ�ã�������꣩ */
	int lower_start_x;
	int lower_start_y;

	/* ��״̬��������Ϣ��ɫ */
	CCT_COLOR lower_normal_bgcolor;
	CCT_COLOR lower_normal_fgcolor;

	/* ��״̬����Ŀ��Ϣ��ɫ */
	CCT_COLOR lower_catchy_bgcolor;
	CCT_COLOR lower_catchy_fgcolor;

	/* ---------------------------------------------------------------------------------------------------------------
		1���������ֵ�� lib_class_gmw.lib ��Ҫ�õ������Ա����Щֵ�����ڲ�����õ��ģ�����ֱ������ֵ
		2����������ʱ����Բ��ã����ǲ�׼ɾ�������� lib_class_gmw.lib �еĺ�������ʱ���ܳ���
	   ---------------------------------------------------------------------------------------------------------------
	*/

	 /* ״̬����ռ�Ŀ�ȣ���ֵ�ɼ���õ�������Ϸ����Ŀ�ȣ���������չ������Ϣ���������ضϣ� */
	int width;

	/* ---------------------------------------------------------------------------------------------------------------
		���������������Ϊ��Ҫ��ֵ����Щֵ����ͨ�����ú���ֱ�����ã�ֻ��Ϊ�˷�������е���(����Ҫÿ���ظ�����)
		˵������Ϊ������ lib_class_gmw.lib��Ϊ�˱������ߵĽṹ��һ�£������ⲿ�ִ�СΪ�̶�64�ֽڣ�Ŀǰ��pad����
			  �����Ҫ�����Ӧ���ݣ��뱣���������+����ֽ�=64�ֽ�
				���磺int data1;
					 int data2;
					 char pad[56];
	   ---------------------------------------------------------------------------------------------------------------
	*/
	char pad[64];

	/* ------------------------------
		����������� �ڲ���Ա ����
	   ------------------------------ */

public:

	/* -----------------------------------------------
		1�����ⲿ���ʵĺ�����Ϊ��ͳһ���޸ı������ݳ�Ա��ֵ�ĺ�������װ�� CONSOLE_GRAPHICS_INFO �к����ⲿ�ṩ
			���磺gmw_set_frame_default_linetype�ȣ���Щ���������ʵ��?
		2��Ϊ���ṩһ�������ɷ��ӳ��򣬴˴������ƺ���������Щ����Ӧ���� CONSOLE_GRAPHICS_INFO �������б��õ���
	   -----------------------------------------------
	*/
	int setcolor_top_normal(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_top_catchy(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_lower_normal(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	int setcolor_lower_catchy(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);
	/* ��Ԫ������ CONSOLE_GRAPHICS_INFO ���ʱ���˽�г�Ա�����Բ�Ҫ */
	friend class CONSOLE_GRAPHICS_INFO;
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};

