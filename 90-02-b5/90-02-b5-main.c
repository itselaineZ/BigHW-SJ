#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../include/cmd_c_cfgtools.h"

union cfg_value {
	int    ivalue;
	double dvalue;
	char   svalue[128];
	char   cvalue;
	void* value;
};

struct cfg_item {
	const char* cfg_item_name;
	enum ITEM_TYPE  cfg_item_type;
	union cfg_value cfg_item_value;
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void to_be_continued(const char* prompt)
{
	if (prompt)
		printf("%s�����س�������...", prompt);
	else
		printf("���س�������...");

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;
	printf("\n");
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���Ϊcfg_item�к��й����壬������ֻ�ܳ�ʼ����һ�����ú�����ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void set_item(struct cfg_item* item)
{
	item[0].cfg_item_value.ivalue = 123;
	item[1].cfg_item_value.dvalue = 123.45;
	strcpy(item[2].cfg_item_value.svalue, "Hello");
	item[3].cfg_item_value.cvalue = 'Y';
	//	item[4].cfg_item_value.ivalue = 0;
	item[5].cfg_item_value.ivalue = 99999;
	//	item[6].cfg_item_value.ivalue = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int test_readconfig_c(const char* cfgname, const char** group_name, struct cfg_item* item)
{
	FILE* fp;
	int ret, i, j;
	char tmp[256];

	/* ��һ��ģ�⣬��������� */
	if (1) {
		remove(cfgname); //ɾ���ļ�

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				printf("����[%s]ʧ��.\n", group_name[i]);
			else
				printf("����[%s]�ɹ�.\n", group_name[i]);
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8������", cfgname);
		to_be_continued(tmp);
	}

	/* �ڶ���ģ�⣬ÿ����������� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* ˵����item_add�ĵ�3��������void*����˲���ʲô���ͣ�������union��һ����Ա�ĵ�ַ����������Ա��ַ */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					printf("����[%s]/%s ʧ��.\n", group_name[i], tmp);
				else
					printf("����[%s]/%s �ɹ�.\n", group_name[i], tmp);
			}
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ�8�������6��������", cfgname);
		to_be_continued(tmp);
	}

	/* ������ģ�⣬ɾ���鼰�� */
	if (1) {
		sprintf(tmp, "��������ļ�%s����[������3]�������ɷݣ�������2-������B�������ɷݣ��Һ����ֵ���Ͳ�ͬ", cfgname);
		to_be_continued(tmp);

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		printf("ɾ��[������3]��%d��\n", group_del(fp, "������3"));
		printf("ɾ��[������5]��%d��\n", group_del(fp, "������5"));

		printf("ɾ��<������2-������B>��%d��\n", item_del(fp, "������2", "������2-������B"));

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲�[������3]/[������5]/<������2-������B>�Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ���Ĵ�ģ�⣬�޸��� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';

		/* �Ѵ�������� */
		item_update(fp, "������4", "������4-������B", &a, TYPE_INT);
		item_update(fp, "������1", "������1-������D", "helloworld", TYPE_STRING);
		item_update(fp, "������8", "������8-������E", &b, TYPE_DOUBLE);
		item_update(fp, "������6", "������6-������F", NULL, TYPE_NULL);
		item_update(fp, "������7", "������7-������C", &c, TYPE_CHARACTER);

		/* ����������� */
		item_update(fp, "������6", "������6-������U", NULL, TYPE_NULL);
		item_update(fp, "������7", "������7-������V", &c, TYPE_CHARACTER);
		item_update(fp, "������7", "������6-������W", NULL, TYPE_NULL);
		item_update(fp, "������4", "������4-������X", &a, TYPE_INT);
		item_update(fp, "������1", "������1-������Y", "helloworld", TYPE_STRING);
		item_update(fp, "������8", "������8-������Z", &b, TYPE_DOUBLE);

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲����������Ƿ����޸�", cfgname);
		to_be_continued(tmp);
	}

	/* �����ģ�⣬�� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDONLY);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* �Ѵ�������� */
		if (item_get_value(fp, "������4", "������4-������B", &a, TYPE_INT) > 0)
			printf("[������4]/������4-������B=%d\n", a);
		if (item_get_value(fp, "������1", "������1-������F", &a, TYPE_INT) > 0)
			printf("[������1]/������1-������F=%d\n", a);
		if (item_get_value(fp, "������6", "������6-������D", &c, TYPE_CHARACTER) > 0)
			printf("[������6]/������6-������D=%c\n", c);
		if (item_get_value(fp, "������8", "������8-������C", s, TYPE_STRING) > 0)
			printf("[������8]/������8-������C=%s\n", s);
		if (item_get_value(fp, "������7", "������7-������E", NULL, TYPE_NULL) > 0)
			printf("[������7]/������7-������E=<NULL>\n");
		if (item_get_value(fp, "������6", "������6-������B", &b, TYPE_DOUBLE) > 0)
			printf("[������6]/������6-������B=%f\n", b);
		if (item_get_value(fp, "������1", "������100", NULL, TYPE_NULL) > 0)
			printf("[������1]/������100=<NULL>\n");
		else
			printf("[������1]/������100 ������\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	const char* cfgname = "c1.cfg";
	const char* group_name[] = {
		"������1",
		"������2",
		"������3",
		"������4",
		"������5",
		"������6",
		"������7",
		"������8",
		NULL
	};

	struct cfg_item item[] =
	{
		{ "������A", TYPE_INT, 0 },		//������union�ĳ�ʼ����ֻ�ܳ�ʼ����һ��Ԫ��
		{ "������B", TYPE_DOUBLE, 0 },
		{ "������C", TYPE_STRING, 0 },
		{ "������D", TYPE_CHARACTER, 0 },
		{ "������E", TYPE_NULL, 0 },
		{ "������F", TYPE_INT, 0 },
		{ NULL,     TYPE_NULL, 0 }
	};
	set_item(item); //��union����ֵ

	test_readconfig_c(cfgname, group_name, item);

	return 0;
}