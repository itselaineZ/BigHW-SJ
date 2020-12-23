/*1952339 ��08 ��ܰ��*/
#pragma once

#include <string>
using namespace std;

#define INVALID_INT_VALUE_OF_SET	0x7FFFFFFF

/*  args    extargs_num extargs_type  extargs_fun             extargs_defvalue;
	--help  0           NULL          NULL                    NULL
	--limit 1           INT           char * ת int ����      min/max/def
	--limit 1           INT           char * ת int ����      min/max/��default�����ش�
	--limit 1           INT           char * ת int ����      12/23/35�����е�һ�������ش�
	--user  1           string        char * ת string ����   def
	--user  1           string        char * ת string ����   "abc"/"def"/"xyz"�����е�һ��
	--ip    1           IPADDR        char * ת ipaddr ����   NULL
*/

/* ������ֲ������� */
enum class ST_EXTARGS_TYPE {
	null = 0,				//�������޲γ�ʼ��
	boolean,				//����Ҫ����0/1����ʾ�Ƿ���ڣ����磺--help
	int_with_default,		//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ�����ȱʡֵ
	int_with_error,			//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ��򷵻ش���
	int_with_set_default,	//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	int_with_set_error,		//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	str,					//���Ӳ���Ϊ�ַ���
	str_with_set_default,	//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	str_with_set_error,		//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	ipaddr_with_default,	//���Ӳ���ΪIP��ַ����ȱʡֵ������һ��u_int32
	ipaddr_with_error,		//���Ӳ���ΪIP��ַ����ȱʡֵ�����ش���
#if 0
	/* ���Ṥ������������ʱ���� */
	date_with_default,			//���Ӳ���Ϊ�����ͣ���ʽΪ"yyyy-mm-dd"����ȱʡֵ
	date_with_error,			//���Ӳ���Ϊ�����ͣ���ʽΪ"yyyy-mm-dd"����ȱʡֵ
	date_with_set_default,		//���Ӳ���Ϊ�����ͣ���ʽΪ"yyyy-mm-dd"��ֻ������һ��������Ԫ�صļ���["1980-1-2"/"1990-3-12"/"2020-4-14"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	date_with_set_error,		//���Ӳ���Ϊ�����ͣ���ʽΪ"yyyy-mm-dd"��ֻ������һ��������Ԫ�صļ���["1980-1-2"/"1990-3-12"/"2020-4-14"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	time_with_default,			//���Ӳ���Ϊʱ���ͣ���ʽΪ"hh:mm:ss"����ȱʡֵ
	time_with_error,			//���Ӳ���Ϊʱ���ͣ���ʽΪ"hh:mm:ss"����ȱʡֵ
	time_with_set_default,		//���Ӳ���Ϊʱ���ͣ���ʽΪ"hh:mm:ss"��ֻ������һ��������Ԫ�صļ���["01:02:03"/"09:34:23"/"22:00:00"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	time_with_set_error,		//���Ӳ���Ϊʱ���ͣ���ʽΪ"hh:mm:ss"��ֻ������һ��������Ԫ�صļ���["01:02:03"/"09:34:23"/"22:00:00"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	datetime_with_default,		//���Ӳ���Ϊ����ʱ���ͣ���ʽΪ"yyyy-mm-dd hh:mm:ss"����ȱʡֵ
	datetime_with_error,		//���Ӳ���Ϊ����ʱ���ͣ���ʽΪ"yyyy-mm-dd hh:mm:ss"����ȱʡֵ
	datetime_with_set_default,	//���Ӳ���Ϊ����ʱ���ͣ���ʽΪ"yyyy-mm-dd hh:mm:ss"��ֻ������һ��������Ԫ�صļ���["1900-01-01 01:02:03"/"1990-03-12 09:34:23"/"2020-4-14 22:00:00"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	datetime_with_set_error,	//���Ӳ���Ϊ����ʱ���ͣ���ʽΪ"yyyy-mm-dd hh:mm:ss"��ֻ������һ��������Ԫ�صļ���["1900-01-01 01:02:03"/"1990-03-12 09:34:23"/"2020-4-14 22:00:00"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
#endif
	tmax					//���ֵ�����Ƴ���
};

/* ---------------------------------------------------------------
	 �������������Ҫ�Ķ���
	 constȫ�ֱ���/staticȫ�ֱ���(����)/define/class/struct/enum/enum class/union��
   ---------------------------------------------------------------- */



/* ---------------------------------------------------------------
	   class AAT�Ķ��壬���в��ֲ�Ҫ��������protected����������Ҫ�Ķ���
   ---------------------------------------------------------------- */
class AAT {
protected:
	/* ��Щ��ʼ����ֵ�Ͳ�Ӧ���ٱ� */
	string				args_name;		//�������ƣ������� "--help��ʽ"
	ST_EXTARGS_TYPE		extargs_type;	//�������Ķ������������
	int					extargs_num;	//��������ĸ�����0-1��������δ����

	bool extargs_bool_default;	//bool�Ͷ��������ȱʡֵ��default��

	int  extargs_int_default;	//int�Ͷ��������ȱʡֵ��default��
	int  extargs_int_min;		//int�Ͷ����������Сֵ��min��
	int  extargs_int_max;		//int�Ͷ�����������ֵ��max��
	int* extargs_int_set;		//int�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	string  extargs_string_default;	//string�Ͷ��������ȱʡֵ(��ipaddr)
	string* extargs_string_set;		//string�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	unsigned int   extargs_ipaddr_default;		//IP��ַȱʡֵ

	/* ������Щ�Ǳ��� */
	int    args_existed;				//�������Ƿ���ֹ�����ֹ��ͬ���� -n ** -n ** �ظ����֣�
	int    extargs_int_value;			//int�Ͷ������������ֵ
	string extargs_string_value;		//string�Ͷ������������ֵ
	unsigned int extargs_ipaddr_value;	//IP��ַ�������������ֵ��IP��ַ���ڲ��洢Ϊ����ʽ���ַ�����ʽ��Ҫת����

	/* ---------------------------------------------------------------
		 �������������Ҫ�Ķ��壨�ڲ��ã�
	   ---------------------------------------------------------------- */

public:
	AAT();
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def);

	/* ���Ṥ������ʡȥ��ͬ�����Ĵ������ĸ����캯�������������Ϊtrue����� */
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max, const bool mutli_args = false);
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set, const bool mutli_args = false);
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const string def, const bool mutli_args = false); //ע��date/time/datetimeҲƥ��˹��캯�����ԣ�
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set, const bool mutli_args = false);//ע��date/time/datetime��set��ʽҲƥ��˹��캯�����ԣ�

	~AAT();

	/* ��ȡ���� */
	const string get_name() const;			//����ĳ����������ƣ����� "--help"��
	const int    existed() const;			//�ж�ĳ�������Ƿ����
	const int    get_int() const;			//����ĳ�������ֵ��int�ͣ�
	const string get_string() const;		//����ĳ�������ֵ��string�ͣ�
	const unsigned int get_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ��������u_int32�͵� 0x7f000001��
	const string get_str_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ���������ַ�����ʽ��"127.0.0.1"��

#if 0
	/* ���Ṥ������ʡȥ��ͬ�����Ĵ��� */

	/* ���Ṥ������ʡȥ����/ʱ���͵Ĵ��� */
#endif

	friend int args_analyse(const int argc, const char* const *const argv, AAT* const args, const int follow_up_args);
	friend int args_analyse_print(const AAT *const args);

	/* ---------------------------------------------------------------
		 ���������������Ҫ�Ķ��壨���ⲻ���֣�
	   ---------------------------------------------------------------- */
};

int args_analyse(const int argc, const char* const *const argv, AAT* const args, const int follow_up_args);
int args_analyse_print(const AAT* const args);

