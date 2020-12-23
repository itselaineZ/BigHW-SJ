/*1952339 ��08 ��ܰ��*/
#pragma once
#include <iostream>
#include <Windows.h>
#include "../include/class_cct.h"
using namespace std;

/* �洢��Ϸ����ܱ߿���Ϣ���ַ�����ĳ��ȣ���β�㣩
   ע�����ַ����������ָ���ԭ����Ϊ�˽������Դ������ļ��ж� */
#define CFI_LEN		3

/* ����������Ϸ���������Ľṹ�� */
class CONSOLE_FRAME_INFO {
protected:
	/* ---------------------------------------------------------------------------------------------------------------
		���涨����ǿ�ͨ�����ú����ı��ֵ����׼�޸ĳ�Ա������׼�ı�����
	   ---------------------------------------------------------------------------------------------------------------
	 */

	/* ������Ϸ���������ĸ����Ԫ�ص���״
	�X �T �h �T �[
	�U          �U
	�c �T �� �T �f
	�U          �U
	�^ �T �k �T �a */
	char top_left[CFI_LEN];			// "�X"
	char lower_left[CFI_LEN];		// "�^"
	char top_right[CFI_LEN];			// "�["
	char lower_right[CFI_LEN];		// "�a"
	char h_normal[CFI_LEN];			// "�T"	//Horizontal
	char v_normal[CFI_LEN];			// "�U"	//Vertical
	char h_top_separator[CFI_LEN];	// "�h"
	char h_lower_separator[CFI_LEN];	// "�k"
	char v_left_separator[CFI_LEN];	// "�c"
	char v_right_separator[CFI_LEN];	// "�f"
	char mid_separator[CFI_LEN];		// "��"

	char pad1[3];	//����ֽڣ�Ϊ�˴���36�ֽ�

	/* ��Ϸ���������ı���ɫ��ǰ��ɫ */
	CCT_COLOR bgcolor;
	CCT_COLOR fgcolor;

	/* ÿ��ɫ��Ŀ�Ⱥ͸߶�(ע�⣺��ȱ�����2�ı���) */
	int block_width;
	int block_high;

	/* ɫ��֮���Ƿ���Ҫ�ָ��� */
	bool separator;
	char pad2[3];	//����ֽڣ�Ϊ�˴���56�ֽ�

	/* ---------------------------------------------------------------------------------------------------------------
		1�������⼸��ֵ�� lib_class_gmw.lib ��Ҫ�õ������Ա����Щֵ�����ڲ�����õ��ģ�����ֱ������ֵ
		2����������ʱ����Բ��ã����ǲ�׼ɾ�������� lib_class_gmw.lib �еĺ�������ʱ���ܳ���
		3��ÿ��ɫ��ĸ��ӵĿ�Ⱥ͸߶�(�зָ����Ƿֱ�Ϊ2/1)����separator�������
	   ---------------------------------------------------------------------------------------------------------------
	*/
	int block_width_ext;
	int block_high_ext;

	/* ÿ��/ÿ�к��ָ��ߵ��ܿ�ȣ��ɿ��/�߶�+�ָ��߼������ */
	int bwidth;
	int bhigh;

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

	int setcolor(const CCT_COLOR bg_color = CCT_COLOR::invalid, const CCT_COLOR fg_color = CCT_COLOR::invalid);

	/* ��Ԫ������ CONSOLE_GRAPHICS_INFO ���ʱ���˽�г�Ա�����Բ�Ҫ */
	friend class CONSOLE_GRAPHICS_INFO;
	friend void to_be_continued(const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
	friend void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO& bgi);
};

