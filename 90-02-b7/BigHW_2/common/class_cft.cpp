/*1952339 ��08 ��ܰ��*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/class_cft.h"
#include "../include/common_mybase_tool.h"
using namespace std;

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ������ʵ�֣���Ҫ��
   ***************************************************************************/
CFT::CFT()
{
	filename = "";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
***************************************************************************/
CFT::~CFT()
{
	if (fp.is_open())
		fp.close();
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::open(const char* cfgname, int opt)
{
	filename = cfgname;
	if (opt == OPEN_OPT_RDONLY) {
		this->fp.open(cfgname, fstream::in | fstream::binary);
		if (this->fp.is_open() == NULL)
			return 0;
	}
	else {
		this->fp.open(cfgname, ios::in | ios::out | ios::binary);
		if (this->fp.is_open() == NULL) {
			ofstream pp(cfgname, ios::out | ios::binary);
			pp.close();
			this->fp.open(cfgname, fstream::out | fstream::in | fstream::binary);
		}
	}
	if (this->fp.is_open() == NULL)
		return 0;
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void CFT::close()
{
	this->fp.close();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����C++17����filesystem::resize_fileֱ�ӿ����޸��ļ���С��֮ǰ�İ汾��
				   ��˱����������þɷ���
			��ʵ�֣���Ҫ��
***************************************************************************/
int CFT::file_resize(int newsize)
{
	/* �����С�Ǹ�����ֱ�ӷ���-1 */
	if (newsize < 0)
		return -1;

	if (!fp.good())
		fp.clear();

	/* ȡfp��ǰָ��λ�� */
	int now_pos = int(fp.tellg());

	/* ���ȣ�C++��ʽ�ر� */
	this->close();

	/* ��Σ�C��ʽ�򿪲��ı��ļ���С */
	FILE* fp_cstyle;
	fp_cstyle = fopen(filename.c_str(), "rb+"); //rw��ʽ��
	if (fp_cstyle) {
		_chsize(_fileno(fp_cstyle), newsize);
		fclose(fp_cstyle);
	}
	else
		cout << "open [" << filename << "] for resize failed" << endl;

	/* �ٴΣ�C++��ʽ���´� */
	fp.open(filename, fstream::in | fstream::out | fstream::binary);
	if (fp.is_open() == 0) {
		cout << "reopen [" << filename << "] after resize failed" << endl;
		return -1;
	}

	/* �ļ�ָ���ƶ���ԭλ�� */
	fp.seekg(now_pos < newsize ? now_pos : newsize, fstream::beg);

	return 0;
}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�protected��
   ---------------------------------------------------------------- */
static char find_first(const char* p)
{
	int i;
	for (i = 0; *(p + i) && (*(p + i) == ' ' || *(p + i) == '\t'); ++i)
		;
	return *(p + i);
}

static int make_group_name(char* aim, const char* src)
{
	aim[0] = '[';
	strcpy(aim + 1, src);
	int len = strlen(aim);
	aim[len] = ']';
	aim[len + 1] = '\r';
	aim[len + 2] = '\n';
	aim[len + 3] = 0;
	len += 3;
	return len;
}

static bool str_first_seg_end(const char* str)
{
	int i;
	for (i = 0; str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'); ++i)
		;
	for (; str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n' && str[i] != '='; ++i)
		;
	return str[i] == ' ' || str[i] == '\t' || str[i] == '=';
}

int CFT::file_length()
{
	int file_len, now_pos;

	/* ȡfp��ǰָ��λ�� */
	now_pos = int(this->fp.tellg());

	/* ���ļ�ָ���ƶ�����󣬴�ʱtellp�Ľ�������ļ���С */
	fp.seekp(0, fstream::end);
	file_len = int(fp.tellg());

	/* ָ���ƶ��غ�������ǰ��ԭλ�� */
	fp.seekp(now_pos, fstream::beg);

	return file_len;
}

void CFT::group_find(const char* group_name)
{
	char str[150];
	while (fp.eof() == 0 && fp.good()) {
		//fp.read(str, 150);
		fp.getline(str, 150);
		int t = int(fp.tellp());
		if (find_first(str) == '[') {
			int i;
			for (i = 0; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;//ȥ��[
			if (str_in(group_name, str + i)) {
				int n = strlen(str);
				fp.seekp(-(int)strlen(str) - 1, fstream::cur);
				return;
			}
		}
	}
	return;
}

void CFT::newsize_move_add(const int delta_len)
{
	int ll = file_length();
	file_resize(file_length() + delta_len);

	int now_pos = int(fp.tellp());
	fp.seekp(-delta_len - 1, fstream::end);
	char c;
	int t = int(fp.tellg());
	ll = file_length();
	while (t > now_pos) {
		fp.read(&c, 1);
		fp.seekp(delta_len - 1, fstream::cur);
		fp.write(&c, 1);
		fp.seekp(-2 - delta_len, fstream::cur);
		t = int(fp.tellp());
	}
	fp.read(&c, 1);
	fp.seekg(delta_len - 1, fstream::cur);
	fp.write(&c, 1);
	fp.clear();
}

void CFT::newsize_move_del(const int delta_len)
{
	//fseek(fp, delta_len, SEEK_CUR);
	int t = int(fp.tellg()), sz = file_length();
	char c;
	do {
		fp.read(&c, 1);
		if (fp.eof())
			break;
		t = int(fp.tellg());
		fp.seekp(-delta_len - 1, fstream::cur);
		fp.write(&c, sizeof(char));
		fp.seekp(delta_len, fstream::cur);
		t = int(fp.tellg());
	} while (!fp.eof() && t < sz);
	if (fp.eof())
		fp.clear();
	file_resize(file_length() - delta_len);
}

int CFT::item_add_opt(const char* group_name, const char* item_name, const char* content)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int sz = file_length();

	if (group_name == NULL) {
		do {
			fp.getline(str, 150);
			while (find_first(str) == '#')
				fp.getline(str, 150);
			if (str_in(item_name, str) && str_first_seg_end(str))
				return 0;
		} while (int(fp.tellg()) < sz && !fp.eof());
		if (fp.eof())
			fp.clear();
		int len_content = strlen(content);
		fp.seekg(0, fstream::end);
		fp.write(content, len_content);//ֱ��ĩβ���
		return 1;

	}
	else {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}

		fp.getline(str, 150);
		int len = strlen(str);
		int delta_len = strlen(content);
		int tt = int(fp.tellp());

		if (int(fp.tellp()) == sz || fp.eof()) {
			fp.clear();
			fp.seekp(0, fstream::end);
			fp.write(content, delta_len);
			return 1;
		}

		do {
			fp.getline(str, 150);
			while (find_first(str) == '#')
				fp.getline(str, 150);
			if (str_in(item_name, str) && str_first_seg_end(str))
				return 0;
		} while (find_first(str) != '[' && int(fp.tellg()) < sz && !fp.eof());

		if (!fp.good()) {
			fp.clear();
			fp.seekp(0, fstream::end);
		}

		if (find_first(str) == '[') {
			int ll = strlen(str);
			fp.seekp(-ll - 1, fstream::cur);
		}
		int t = int(fp.tellg());
		newsize_move_add(delta_len);
		fp.seekg(t, fstream::beg);
		fp.write(content, delta_len);
		return 1;
	}
}

int CFT::item_update_opt(const char* group_name, const char* item_name, const char* content)
{
	fp.clear();
	fp.seekp(0, fstream::beg);
	char str[150];
	int n = 0, t;
	int len_item = strlen(item_name);
	int len_content = strlen(content);
	int sz = file_length();

	if (group_name == NULL) {
		do {
			int t = int(fp.tellp());
			fp.getline(str, 150);
			while (find_first(str) == '#')
				fp.getline(str, 150);
			if (str_in(item_name, str) && str_first_seg_end(str)) {
				if (n == 0) {
					int ll = strlen(str) + 1;
					newsize_move_del(ll);
					fp.seekp(t, fstream::beg);
					newsize_move_add(len_content);
					fp.seekp(t, fstream::beg);
					fp.write(content, len_content);
				}
				else {
					int ll = strlen(str) + 1;
					newsize_move_del(ll);
					fp.seekp(t, fstream::beg);
				}
				++n;
			}
			sz = file_length();
		} while (int(fp.tellg()) < sz && !fp.eof());

		if (n == 0) {
			fp.seekp(0, fstream::end);
			fp.write(content, len_content);
			n = 1;
		}

		return n;
	}
	else {
		group_find(group_name);
		if (fp.eof())
			return 0;

		fp.getline(str, 150);
		int len = strlen(str);
		if (int(fp.tellg()) == sz || fp.eof()) {
			fp.clear();
			fp.seekp(0, fstream::end);
			fp.write(content, len_content);
			return 1;
		}

		do {
			int t = int(fp.tellp());
			fp.getline(str, 150);
			while (find_first(str) == '#')
				fp.getline(str, 150);
			if (str_in(item_name, str) && str_first_seg_end(str)) {
				if (n == 0) {
					int ll = strlen(str);
					newsize_move_del(ll + 1);
					fp.seekp(t, fstream::beg);
					newsize_move_add(len_content);
					fp.seekp(t, fstream::beg);
					fp.write(content, len_content);
				}
				else {
					int ll = strlen(str);
					newsize_move_del(ll + 1);
					fp.seekp(t, fstream::beg);
				}
				++n;
			}
			sz = file_length();
		} while (find_first(str) != '[' && int(fp.tellp()) < sz && !fp.eof());

		if (n == 0) {
			if (find_first(str) == '[') {
				int ll = strlen(str);
				fp.seekp(-ll - 1, fstream::cur);
			}
			t = int(fp.tellp());
			newsize_move_add(len_content);
			fp.seekp(t, fstream::beg);
			fp.write(content, len_content);
			n = 1;
		}
		return n;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
  ��	���ӳɹ�����1�����򷵻�0
  ��	���[test]���Ѵ��ڣ������ظ����ӣ�ֱ�ӷ���0����
  ��	�����������ļ������
 ***************************************************************************/
int CFT::group_add(const char* group_name)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char aim[150];
	int len = make_group_name(aim, group_name);

	group_find(group_name);
	if (this->fp.eof() == 0)
		return 0;
	fp.clear();
	fp.seekp(0, fstream::end);
	fp.write(aim, strlen(aim));
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
  ��	ɾ���ɹ�����n(ɾ���������)�����򷵻�0
  ��	���[test]�鲻���ڣ�ֱ�ӷ���0����
  ��	���[test]���ظ����ڣ����磺�ֹ��޸�ʹ����ͬ��������Ҫɾ������ͬ���鲢����2
***************************************************************************/
int CFT::group_del(const char* group_name)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	int delta_len = 0, n = 0;

	if (group_name)
		group_find(group_name);
	if (fp.eof() || !group_name) {
		fp.clear();
		return 0;
	}

	char str[150];
	int t = int(fp.tellp());
	fp.getline(str, 150);
	int len = strlen(str);

	while (this->fp.eof() == 0) {
		delta_len = 0;
		int ll = len;
		int tt = int(fp.tellp());
		do {
			delta_len += ll + 1;
			fp.getline(str, 150);
			ll = strlen(str);
			tt = int(fp.tellp());
		} while (find_first(str) != '[' && !fp.eof());
		if (fp.eof()) {
			fp.clear();
			fp.seekp(0, fstream::end);
			newsize_move_del(delta_len);
		}
		else {
			fp.seekp(-ll - 1, fstream::cur);
			newsize_move_del(delta_len);
		}
		++n;

		this->fp.seekp(0, fstream::beg);
		group_find(group_name);
		tt = int(fp.tellp());
		if (fp.eof()) {
			fp.clear();
			break;
		}
		fp.getline(str, 150);
		len = strlen(str);
	}
	return n;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const int item_value)
{
	char content[150];
	sprintf(content, "%s=%d\r\n", item_name, item_value);

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const double item_value)
{
	char content[150];
	sprintf(content, "%s=%lf\r\n", item_name, item_value);

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const char* item_value)
{
	char content[150];
	sprintf(content, "%s=%s\r\n", item_name, item_value);

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const string& item_value)
{
	char content[150];
	sprintf(content, "%s=%s\r\n", item_name, item_value.c_str());

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const char item_value)
{
	char content[150];
	sprintf(content, "%s=%c\r\n", item_name, item_value);

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name)
{
	char content[150];
	sprintf(content, "%s=\r\n", item_name);

	return item_add_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
  ��	ɾ���ɹ�����1�����򷵻�0
  ��	���[test]�鲻���ڣ�ֱ�ӷ���0����
  ��	���[test]����ڣ���Ҫɾ����"��ʼֵ"����ڣ���ֱ�ӷ���0����
  ��	���[test]����ڣ���Ҫɾ����"��ʼֵ"���ظ����ڣ����磺�ֹ��޸�ʹ���ڶ��"��ʼֵ"������ɾ����������ͬ�������1��ע�⣺����ɾ���������ͬ���
  ��	�������ΪNULL������item_del(fp, NULL, "��ʼֵ");���ʾ�ڼ������ļ���ɾ������ͬ����
***************************************************************************/
int CFT::item_del(const char* group_name, const char* item_name)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	int n = 0;
	char str[150];
	int len_item = strlen(item_name);
	int delta_len = 0;
	int sz = file_length();

	if (group_name == NULL) {
		while (int(fp.tellg()) < sz && !fp.eof()) {
			int t = int(fp.tellp());
			fp.getline(str, 150);
			while (find_first(str) == '#') {
				t = int(fp.tellp());
				fp.getline(str, 150);
			}
			if (str_in(item_name, str) && str_first_seg_end(str)) {
				++n;
				int ll = strlen(str);
				newsize_move_del(ll + 1);
				fp.seekp(t, fstream::beg);
				sz = file_length();
			}
		}
		return n;
	}
	else {
		group_find(group_name);
		if (fp.eof())
			return 0;

		fp.getline(str, 150);
		int len = strlen(str);

		do {
			int t = int(fp.tellp());
			fp.getline(str, 150);
			while (find_first(str) == '#') {
				t = int(fp.tellp());
				fp.getline(str, 150);
			}
			if (str_in(item_name, str) && str_first_seg_end(str)) {
				++n;
				int ll = strlen(str);
				newsize_move_del(ll + 1);
				fp.seekp(t, fstream::beg);
				sz = file_length();
			}
		} while (find_first(str) != '[' && int(fp.tellg()) < sz && !fp.eof());
	}
	return n;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const int item_value)
{
	char content[150];
	sprintf(content, "%s=%d\r\n", item_name, item_value);

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const double item_value)
{
	char content[150];
	sprintf(content, "%s=%lf\r\n", item_name, item_value);

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const char* item_value)
{
	char content[150];
	sprintf(content, "%s=%s\r\n", item_name, item_value);

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const string& item_value)
{
	char content[150];
	sprintf(content, "%s=%s\r\n", item_name, item_value.c_str());

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const char item_value)
{
	char content[150];
	sprintf(content, "%s=%c\r\n", item_name, item_value);

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name)
{
	char content[150];
	sprintf(content, "%s=\r\n", item_name);

	return item_update_opt(group_name, item_name, content);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, int& item_value)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			int rt = 0, i;
			for (i = 0; str[i] && str[i] != '='; ++i)
				;
			if (!str[i])
				return 0;
			++i;
			for (; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			int tg = 1;
			if (str[i] == '-') {
				tg = -1, ++i;
				if (str[i] < '0' || str[i] > '9')
					return 0;
			}
			else if (!str[i] || str[i] < '0' || str[i] > '9')
				return 0;
			for (; str[i] >= '0' && str[i] <= '9'; ++i)
				rt = rt * 10 + str[i] - 48;
			item_value = rt*tg;
			return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, double& item_value)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			double rt = 0.0;
			int i;
			for (i = 0; str[i] && str[i] != '='; ++i)
				;
			if (!str[i])
				return 0;
			++i;
			for (; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (!str[i] || str[i] < '0' || str[i] > '9')
				return 0;
			for (; str[i] && str[i] >= '0' && str[i] <= '9'; ++i)
				rt = rt * 10 + str[i] - 48;
			if (str[i] != '.')
				return 0;
			++i;
			if (str[i] < '0' || str[i] > '9')
				return 0;
			for (double j = 0.1; str[i] >= '0' && str[i] <= '9'; ++i, j /= 10.0)
				rt += (str[i] - 48) * j;
			item_value = rt;
			return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, char* item_value)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			int i = len_item;
			for (; str[i] && str[i] != '='; ++i)
				;
			if (!str[i])
				return 0;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (!str[i])
				return 0;
			int j;
			for (j = 0; str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'; ++i, ++j)
				*(item_value + j) = str[i];
			*(item_value + j) = 0;
			return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, string& item_value)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			int i = len_item;
			char rt[200];
			for (; str[i] && str[i] != '='; ++i)
				;
			if (!str[i])
				return 0;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (!str[i])
				return 0;
			int j;
			for (j = 0; str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'; ++i, ++j)
				*(rt + j) = str[i];
			*(rt + j) = 0;
			item_value = rt;
			return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, char& item_value)
{
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			int i = len_item;
			for (; str[i] != '=' && str[i]; ++i)
				;
			if (!str[i])
				return 0;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (!str[i])
				return 0;
			item_value = str[i];
			return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name)
{
	fp.clear();
	fp.seekg(0, fstream::beg);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	if (group_name) {
		group_find(group_name);
		if (fp.eof()) {
			fp.clear();
			return 0;
		}
		fp.getline(str, 150);
		int len = strlen(str);
	}

	do {
		fp.getline(str, 150);
		while (find_first(str) == '#')
			fp.getline(str, 150);
		if (str_in(item_name, str) && str_first_seg_end(str)) {
			int i = len_item;
			for (; str[i] && str[i] != '='; ++i)
				;
			if (!str[i])
				return 0;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (!str[i] || str[i] == '\n' || str[i] == '\r')
				return 0;
			else
				return 1;
		}
	} while (find_first(str) != '[' && !fp.eof());
	return 0;
}
