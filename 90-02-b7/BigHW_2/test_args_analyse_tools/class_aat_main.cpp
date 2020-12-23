/*1952339 ��08 ��ܰ��*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "../include/class_aat.h"

/* �����궨��ֻ׼��һ����������뱨�� */
#define BASE_TEST		//��������
//#define QQ_RECORD_TEST	//QQ�����¼��������
//#define HW_CHECK_TEST	//��ҵ������

#ifdef BASE_TEST
/***************************************************************************
  �������ƣ�
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ���������и�ʽҪ����--��ʼ�Ŀɱ������˳�����⣬�����ָ���Ĺ̶�����
***************************************************************************/
int main(int argc, char* argv[])
{
    string hashtype[] = { "md5","sha1","sha224","sha256","sha384","sha512","all", "" };	//��β������""
    int intset[] = { 11,22,33,123,345,INVALID_INT_VALUE_OF_SET }; 				//��β������INVALID_INT_VALUE_OF_SET

    AAT args[] = {
        AAT("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
        AAT("--bool",      ST_EXTARGS_TYPE::boolean, 0, true),

		AAT("--intdef",    ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535),
        AAT("--interr",    ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535),	//����12345��Ϊ�κ�ֵ��������
#if 0	
		/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� --mintdef 34 --mintdef 56 */
		AAT("--mintdef",   ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535, true),
        AAT("--minterr",   ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535, true),	//����12345��Ϊ�κ�ֵ��������
#endif

		AAT("--intsetdef", ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset),		//����2����defaultΪset�еĵ�[2]��ֵ����33�������ֵ����Χ��ȱʡ0
        AAT("--intseterr", ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset),		//����2�����壬����
#if 0	
		/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
		AAT("--mintsetdef",ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset, true),	//����2����defaultΪset�еĵ�[2]��ֵ����33�������ֵ����Χ��ȱʡ0
        AAT("--mintseterr",ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset, true),	//����2�����壬����
#endif

		AAT("--str1",      ST_EXTARGS_TYPE::str,                  1, string("")),		//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
        AAT("--str2",      ST_EXTARGS_TYPE::str,                  1, string("Hello")),	//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
#if 0	
		/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
		AAT("--mstr1",     ST_EXTARGS_TYPE::str,                  1, string(""), true),		//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
        AAT("--mstr2",     ST_EXTARGS_TYPE::str,                  1, string("Hello"), true),	//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
#endif

		AAT("--strsetdef", ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype),		//����3����defaultΪset�еĵ�[3]��ֵ����sha256�������ֵ����Χ��ȱʡ0
        AAT("--strseterr", ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype),		//����3�����壬����
#if 0	
		/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
		AAT("--mstrsetdef",ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype, true),		//����3����defaultΪset�еĵ�[3]��ֵ����sha256�������ֵ����Χ��ȱʡ0
        AAT("--mstrseterr",ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype, true),		//����3�����壬����
#endif

		AAT("--ipdef",     ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230")),
        AAT("--iperr",     ST_EXTARGS_TYPE::ipaddr_with_error,       1, string("")),			//ȱʡ��0.0.0.0
#if 0	
		/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
		AAT("--mipdef",    ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230"), true),
        AAT("--miperr",    ST_EXTARGS_TYPE::ipaddr_with_error,       1, string(""), true),
#endif
		AAT()  //���һ�������ڽ���
    };

	int need_fixed_args = 1;	//���Ը�Ϊ0
    int cur_argc;

    /* ���һ��������1-��ʾ��ѡ������⣬����Ҫ��������
                  0-��ʾ��ѡ������⣬����Ҫ�������� */
    if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
        //������Ϣ�ں������Ѵ�ӡ
        return -1;
    }

    args_analyse_print(args);

	/* ����������ɺ�Ĵ����� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "ָ����Ҫ�̶���������δ����" << endl;
			return -1;
		}

		/* �˴�Ӧ�ô���Ҫ��Ĺ̶������������м򵥴�ӡ���� */
		cout << "����" << argc - cur_argc << "���̶�����" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	cout << endl << "������۲��ӡ����У���Ӧ���exist�Ƿ�Ϊ1��ֵ�Ƿ�ΪԤ��" << endl << endl;

    return 0;
}

#if 0
// ��������

./test_optargs --help

./test_optargs --bool

./test_optargs --intdef 123
./test_optargs --intdef 123 --intdef 456
./test_optargs --intdef -12
./test_optargs --intdef 654321

./test_optargs --interr 123
./test_optargs --interr 123 --interr 456	//����
./test_optargs --interr -12
./test_optargs --interr 654321

#if 0	/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
./test_optargs --mintdef 12 --mintdef 34 --mintdef 56
./test_optargs --mintdef 12 --mintdef 34 --mintdef 12
./test_optargs --mintdef 12 --mintdef 34 --mintdef 568888

./test_optargs --minterr 12 --minterr 34 --minterr 56
./test_optargs --minterr 12 --minterr 34 --minterr 12
./test_optargs --minterr 12 --minterr 34 --minterr 568888
#endif

./test_optargs --intsetdef 11
./test_optargs --intsetdef 12
./test_optargs --intsetdef 11 --intsetdef 22

./test_optargs --intseterr 11
./test_optargs --intseterr 12
./test_optargs --intseterr 11 --intseterr 22

#if 0	/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
./test_optargs --mintsetdef 11 --mintsetdef 22
./test_optargs --mintsetdef 11 --mintsetdef 12
./test_optargs --mintsetdef 11 --mintsetdef 22 --mintsetdef 11

./test_optargs --mintseterr 11 --mintseterr 22
./test_optargs --mintseterr 11 --mintseterr 12
./test_optargs --mintseterr 11 --mintseterr 22 --mintseterr 11
#endif

./test_optargs --str1 hello
./test_optargs --str1 hello --str1 horse	//����

./test_optargs --str2 hello
./test_optargs --str2 hello --str2 horse	//����

#if 0	/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
./test_optargs --mstr1 hello --mstr1 horse
./test_optargs --mstr1 hello --mstr1 horse --mstr1 hello

./test_optargs --mstr2 hello --mstr2 horse
./test_optargs --mstr2 hello --mstr2 horse --mstr2 horse
#endif

./test_optargs --strsetdef md5
./test_optargs --strsetdef md4
./test_optargs --strsetdef md5 --strsetdef sha1	//����

./test_optargs --strseterr md5
./test_optargs --strseterr md4
./test_optargs --strseterr md5 --strseterr sha1	//����

#if 0	/* ���Ṥ�����������Ƕ����ͬ�����Ĵ��� */
./test_optargs --mstrsetdef md5
./test_optargs --mstrsetdef sha
./test_optargs --mstrsetdef md5 --mstrsetdef sha1
./test_optargs --mstrsetdef md5 --mstrsetdef sha
./test_optargs --mstrsetdef md5 --mstrsetdef sha --mstrsetdef sha384

./test_optargs --mstrseterr md5
./test_optargs --mstrseterr sha
./test_optargs --mstrseterr md5 --mstrseterr sha1
./test_optargs --mstrseterr md5 --mstrseterr sha
./test_optargs --mstrseterr md5 --mstrseterr sha384 --mstrseterr sha
#endif

./test_optargs --ipdef 1.1.1.1
./test_optargs --iperr 1.1.1.1234
./test_optargs --ipdef 1.1.1.1 --ipdef 2.2.2.2	//����

#if 0
./test_optargs --mipdef 1.1.1.1
./test_optargs --mipdef 1.1.1.1234
./test_optargs --mipdef 1.1.1.1 --mipdef 2.2.2.2
./test_optargs --miperr 1.1.1.1 --miperr 2.2.2.2345
#endif

//������������������ϣ�
#endif

#endif BASE_TEST

#ifdef QQ_RECORD_TEST
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������ԣ�ʵ��ʹ��ʱ��������һ��cpp������
 ***************************************************************************/
int read_qq_record(const char *qq_record_filename, const char *stulist_filename, 
							const time_t begin_time, const time_t end_time,
								const char *stuno, const char *const key, 
									const bool only_zero, const bool more_than_zero)
{
	cout << "����������ϣ���ʼ����QQ�����¼����..." << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " { --stulist | --qq_record | --begin | --end | {--stuno} | {--only_zero} }" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--stulist filename   : ѧ���б��ļ���(ȱʡ:stulist.txt)" << endl;
	cout << setw(wopt) << ' ' << "--qq_record filename : �����������¼�ļ���(ȱʡ:2019-�߳�.txt)" << endl;
	cout << setw(wopt) << ' ' << "--begin timestr      : ��ʼʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)" << endl;
	cout << setw(wopt) << ' ' << "--end timestr        : ����ʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)" << endl;
	cout << setw(wopt) << ' ' << "ע��δ���ʱ�䴮��ȷ��" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--stuno stuno        : ָ��ĳ��ѧ��(�޴�ѡ����ȫ��ѧ��)" << endl;
	cout << setw(wopt) << ' ' << "--only_zero          : ����ʾ0����ѧ��(ָ��--stunoʱ������Ч)" << endl;
	cout << setw(wopt) << ' ' << "--more_than_zero     : ����ʾ�з���ѧ��(ָ��--stunoʱ������Ч������--only_zero����)" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\"" << endl;
	cout << setw(wkey) << "                               : ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ����2020.3.5 10:00~11:50��ķ�������" << endl;
	cout << "      " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero" << endl;
	cout << setw(wkey) << "                               : ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ����2020.3.5 10:00~11:50��0��������" << endl;
	cout << "      " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234" << endl;
	cout << setw(wkey) << "                               : ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ��1951234��2020.3.5 10:00~11:50��ķ�������" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-�߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\"                 : ͳ��2020.3.5 10:00~11:50������ѧ���ķ�������" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-�߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero     : ͳ��2020.3.5 10:00~11:50������0���Ե�ѧ��" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-�߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --more_than_zero: ͳ��2020.3.5 10:00~11:50�������з��Ե�ѧ��" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-�߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234 : ͳ��2020.3.5 10:00~11:50��1951234�ķ�������" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "����cmd�¼Ӳ�������." << endl << endl;
		system("pause");
	}
}

/* enum��˳��Ҫ��args������˳�򱣳�һ�� */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_STULIST_FNAME, OPT_ARGS_QQ_RECORD_FNAME, OPT_ARGS_BEGIN_TIME, OPT_ARGS_END_TIME, OPT_ARGS_STUNO, OPT_ARGS_ONLY_ZERO, OPT_ARGS_MORE_THAN_ZERO, OPT_ARGS_KEY };

/***************************************************************************
  �������ƣ�
  ��    �ܣ���QQȺ�ļ�¼��ͳ�Ƴ��������main����
  ���������
  �� �� ֵ��
  ˵    ����Ϊ�˼򻯣��˴���ȥ��--begin / --end��ʱ�������
***************************************************************************/
int main(int argc, char** argv)
{
	AAT args[] = {
		AAT("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--stulist", ST_EXTARGS_TYPE::str, 1, string("stulist.txt")),
		AAT("--qq_record", ST_EXTARGS_TYPE::str, 1, string("2019-�߳�.txt")),
		AAT("--begin", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--end", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--stuno", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--only_zero", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--more_than_zero", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--key", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT()  //���һ�������ڽ���
	};

	int need_fixed_args = 0;	//���Ը�Ϊ1
	int cur_argc, ret = 0;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	args_analyse_print(args);

	/* ����������ɺ�Ĵ����� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "ָ����Ҫ�̶���������δ����" << endl;
			return -1;
		}

		/* �˴�Ӧ�ô���Ҫ��Ĺ̶������������м򵥴�ӡ���� */
		cout << "����" << argc - cur_argc << "���̶�����" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	/* ��help�����⴦�� */
	if (args[OPT_ARGS_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		usage(argv[0], argc);
		return -1; //ִ�����ֱ���˳�
	}

#if 0	//�����ϣ�� --stulist �� --qq_record ��ȱʡֵ����򿪴���������
	if (args[OPT_ARGS_STULIST_FNAME].existed() == 0) {
		cout << "����ָ��[" << args[OPT_ARGS_STULIST_FNAME].get_name() << "]ѧ�������ļ�" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_QQ_RECORD_FNAME].existed() == 0) {
		cout << "����ָ��[" << args[OPT_ARGS_QQ_RECORD_FNAME].get_name() << "]QQ��־�ļ�" << endl;
		usage(argv[0], argc);
		return -1;
	}
#endif

	if (args[OPT_ARGS_STUNO].existed() + args[OPT_ARGS_ONLY_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "ָ��[" << args[OPT_ARGS_STUNO].get_name() << "]������[" << args[OPT_ARGS_ONLY_ZERO].get_name() << "]������Ч" << endl;
		return -1;
	}

	if (args[OPT_ARGS_STUNO].existed() + args[OPT_ARGS_MORE_THAN_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "ָ��[" << args[OPT_ARGS_STUNO].get_name() << "]������[" << args[OPT_ARGS_MORE_THAN_ZERO].get_name() << "]������Ч" << endl;
		return -1;
	}

	if (args[OPT_ARGS_ONLY_ZERO].existed() + args[OPT_ARGS_MORE_THAN_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "����[" << args[OPT_ARGS_ONLY_ZERO].get_name() << "/" << args[OPT_ARGS_MORE_THAN_ZERO].get_name() << "]����" << endl;
		return -1;
	}

	if (args[OPT_ARGS_BEGIN_TIME].existed() == 0) {
		usage(argv[0], argc);
		cout << "����ָ��[" << args[OPT_ARGS_BEGIN_TIME].get_name() << "]��ʼʱ��" << endl;
		return -1;
	}

	if (args[OPT_ARGS_END_TIME].existed() == 0) {
		usage(argv[0], argc);
		cout << "����ָ��[" << args[OPT_ARGS_END_TIME].get_name() << "]����ʱ��" << endl;
		return -1;
	}

#if 0
	/* �˴�����--begin��--end��ʱ�������
	     1���ж�ʱ�䴮�Ƿ�Ϸ�
	     2���ж���ʼʱ���Ƿ�С�ڽ���ʱ��
	   �˴��� */
	string begin_time = args[OPT_ARGS_BEGIN_TIME].get_string();
	time_t btime = st_str2time(begin_time.c_str());
	if (btime < 0) {
		usage(argv[0], argc);
		cout << "[" << args[OPT_ARGS_BEGIN_TIME].get_name() << "]�ĸ�ʽ����" << endl;
		return -1;
	}

	string end_time = args[OPT_ARGS_END_TIME].get_string();
	time_t etime = st_str2time(end_time.c_str());
	if (etime < 0) {
		usage(argv[0], argc);
		cout << "[" << args[OPT_ARGS_END_TIME].get_name() << "]�ĸ�ʽ����" << endl;
		return -1;
	}

	if (btime > etime) {
		usage(argv[0], argc);
		cout << "��ʼʱ��[" << begin_time << "]���ڽ���ʱ��[" << end_time << "]" << endl;
		return -1;
	}
#else
	time_t btime = 1, etime = 2;
#endif

	/* ����������ϣ����������¼�Ķ�ȡ�ʹ����֣��ԣ�*/
	string stulist_fname = args[OPT_ARGS_STULIST_FNAME].get_string();
	string qq_record_fname = args[OPT_ARGS_QQ_RECORD_FNAME].get_string();
	string stuno = args[OPT_ARGS_STUNO].get_string();
	string key = args[OPT_ARGS_KEY].get_string();
	const bool only_zero = args[OPT_ARGS_ONLY_ZERO].existed();
	const bool more_than_zero = args[OPT_ARGS_MORE_THAN_ZERO].existed();

	read_qq_record(qq_record_fname.c_str(), stulist_fname.c_str(), btime, etime, stuno.c_str(), key.c_str(), only_zero, more_than_zero);

	return 0;
}
#endif //QQ_RECORD_TEST

#ifdef HW_CHECK_TEST
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������ԣ�ʵ��ʹ��ʱ��������һ��cpp������
 ***************************************************************************/
int check_fristline(const string& cno, const string& filename)
{
	cout << "��ʼ����Դ�����ļ����м��..." << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " { --firstline | --fileformat | --forbiddenkey }" << endl;
	cout << setw(wkey) << ' ' << "{ --courseid cid }" << endl;
	cout << setw(wkey) << ' ' << "{ --filename name/all }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���������(��ѡһ)" << endl;
	cout << setw(wopt) << ' ' << "--firstline    : ���м��" << endl;
	cout << setw(wopt) << ' ' << "--fileformat   : �ļ���ʽ�淶���(����Ҫʵ��)" << endl;
	cout << setw(wopt) << ' ' << "--forbiddenkey : ���ùؼ��ּ��(����Ҫʵ��)" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--courseid     : �κ�" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--filename     : �ļ���(all��ʾȫ��)" << endl;
	cout << endl;

	cout << "e.g.   " << procname << " --firstline --courseid 100718 --filename 3-b1.cpp  : ���100718�γ̵�3-b1.cpp������" << endl;
	cout << "       " << procname << " --firstline --courseid 100718 --filename all       : ���100718�γ̵�ȫ���ļ�������" << endl;
	cout << "       " << procname << " --fileformat --courseid 100215 --filename all      : ���100215�γ̵�ȫ���ļ��ĸ�ʽ��" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "����cmd�¼Ӳ�������." << endl << endl;
		system("pause");
	}
}

/* enum��˳��Ҫ��args������˳�򱣳�һ�� */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_FIRSTLINE, OPT_ARGS_FILEFORMAT, OPT_ARGS_FORBIDDEN_KEY, OPT_ARGS_COURSEID, OPT_ARGS_FILENAME };

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ҵ����main����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	AAT args[] = {
		AAT("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--firstline", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--fileformat", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--forbiddenkey", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--courseid", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--filename", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT()  //���һ�������ڽ���
	};

	int need_fixed_args = 0;	//���Ը�Ϊ1
	int cur_argc, ret = 0;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	args_analyse_print(args);

	/* ����������ɺ�Ĵ����� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "ָ����Ҫ�̶���������δ����" << endl;
			return -1;
		}

		/* �˴�Ӧ�ô���Ҫ��Ĺ̶������������м򵥴�ӡ���� */
		cout << "����" << argc - cur_argc << "���̶�����" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

		/* ��help�����⴦�� */
	if (args[OPT_ARGS_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		usage(argv[0], argc);
		return -1; //ִ�����ֱ���˳�
	}

	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_FILEFORMAT].existed() + args[OPT_ARGS_FORBIDDEN_KEY].existed() != 1) {
		usage(argv[0], argc);
		cout << "����[" << args[OPT_ARGS_FIRSTLINE].get_name() << "|" << args[OPT_ARGS_FILEFORMAT].get_name() << "|" << args[OPT_ARGS_FORBIDDEN_KEY].get_name() << "]����ָ��һ����ֻ��ָ��һ��" << endl;
		return -1;
	}

	if (args[OPT_ARGS_COURSEID].existed() == 0) {
		cout << "����ָ������[" << args[OPT_ARGS_COURSEID].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_FILENAME].existed() == 0) {
		cout << "����ָ������[" << args[OPT_ARGS_FILENAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_FIRSTLINE].existed()) {
		string cno = args[OPT_ARGS_COURSEID].get_string();
		string filename = args[OPT_ARGS_FILENAME].get_string();

		check_fristline(cno, filename);
	}
	else if (args[OPT_ARGS_FILEFORMAT].existed()) {
		cout << "�ļ���ʽ���δʵ��" << endl;
	}
	else if (args[OPT_ARGS_FORBIDDEN_KEY].existed()) {
		cout << "���ùؼ��ּ��δʵ��" << endl;
	}

	return 0;
}

#endif //HW_CHECK_TEST