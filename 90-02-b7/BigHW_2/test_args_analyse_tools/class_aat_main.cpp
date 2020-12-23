/*1952339 信08 张馨月*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "../include/class_aat.h"

/* 三个宏定义只准打开一个，否则编译报错 */
#define BASE_TEST		//基本测试
//#define QQ_RECORD_TEST	//QQ聊天记录分析测试
//#define HW_CHECK_TEST	//作业检查测试

#ifdef BASE_TEST
/***************************************************************************
  函数名称：
  功    能：基本测试
  输入参数：
  返 回 值：
  说    明：命令行格式要求：先--开始的可变参数，顺序任意，最后是指定的固定参数
***************************************************************************/
int main(int argc, char* argv[])
{
    string hashtype[] = { "md5","sha1","sha224","sha256","sha384","sha512","all", "" };	//结尾必须是""
    int intset[] = { 11,22,33,123,345,INVALID_INT_VALUE_OF_SET }; 				//结尾必须是INVALID_INT_VALUE_OF_SET

    AAT args[] = {
        AAT("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
        AAT("--bool",      ST_EXTARGS_TYPE::boolean, 0, true),

		AAT("--intdef",    ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535),
        AAT("--interr",    ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535),	//参数12345可为任何值，无意义
#if 0	
		/* 减轻工作量，不考虑多个相同参数的处理 --mintdef 34 --mintdef 56 */
		AAT("--mintdef",   ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535, true),
        AAT("--minterr",   ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535, true),	//参数12345可为任何值，无意义
#endif

		AAT("--intsetdef", ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset),		//参数2代表default为set中的第[2]个值，即33，如果此值超范围，缺省0
        AAT("--intseterr", ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset),		//参数2无意义，不用
#if 0	
		/* 减轻工作量，不考虑多个相同参数的处理 */
		AAT("--mintsetdef",ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset, true),	//参数2代表default为set中的第[2]个值，即33，如果此值超范围，缺省0
        AAT("--mintseterr",ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset, true),	//参数2无意义，不用
#endif

		AAT("--str1",      ST_EXTARGS_TYPE::str,                  1, string("")),		//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
        AAT("--str2",      ST_EXTARGS_TYPE::str,                  1, string("Hello")),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
#if 0	
		/* 减轻工作量，不考虑多个相同参数的处理 */
		AAT("--mstr1",     ST_EXTARGS_TYPE::str,                  1, string(""), true),		//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
        AAT("--mstr2",     ST_EXTARGS_TYPE::str,                  1, string("Hello"), true),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
#endif

		AAT("--strsetdef", ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype),		//参数3代表default为set中的第[3]个值，即sha256，如果此值超范围，缺省0
        AAT("--strseterr", ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype),		//参数3无意义，不用
#if 0	
		/* 减轻工作量，不考虑多个相同参数的处理 */
		AAT("--mstrsetdef",ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype, true),		//参数3代表default为set中的第[3]个值，即sha256，如果此值超范围，缺省0
        AAT("--mstrseterr",ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype, true),		//参数3无意义，不用
#endif

		AAT("--ipdef",     ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230")),
        AAT("--iperr",     ST_EXTARGS_TYPE::ipaddr_with_error,       1, string("")),			//缺省是0.0.0.0
#if 0	
		/* 减轻工作量，不考虑多个相同参数的处理 */
		AAT("--mipdef",    ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230"), true),
        AAT("--miperr",    ST_EXTARGS_TYPE::ipaddr_with_error,       1, string(""), true),
#endif
		AAT()  //最后一个，用于结束
    };

	int need_fixed_args = 1;	//试试改为0
    int cur_argc;

    /* 最后一个参数：1-表示除选项参数外，还需要其它参数
                  0-表示除选项参数外，不需要其它参数 */
    if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
        //错误信息在函数中已打印
        return -1;
    }

    args_analyse_print(args);

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}

		/* 此处应该处理要求的固定参数，本例中简单打印即可 */
		cout << "还有" << argc - cur_argc << "个固定参数" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	cout << endl << "请认真观察打印输出中，对应项的exist是否为1，值是否为预期" << endl << endl;

    return 0;
}

#if 0
// 测试用例

./test_optargs --help

./test_optargs --bool

./test_optargs --intdef 123
./test_optargs --intdef 123 --intdef 456
./test_optargs --intdef -12
./test_optargs --intdef 654321

./test_optargs --interr 123
./test_optargs --interr 123 --interr 456	//报错
./test_optargs --interr -12
./test_optargs --interr 654321

#if 0	/* 减轻工作量，不考虑多个相同参数的处理 */
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

#if 0	/* 减轻工作量，不考虑多个相同参数的处理 */
./test_optargs --mintsetdef 11 --mintsetdef 22
./test_optargs --mintsetdef 11 --mintsetdef 12
./test_optargs --mintsetdef 11 --mintsetdef 22 --mintsetdef 11

./test_optargs --mintseterr 11 --mintseterr 22
./test_optargs --mintseterr 11 --mintseterr 12
./test_optargs --mintseterr 11 --mintseterr 22 --mintseterr 11
#endif

./test_optargs --str1 hello
./test_optargs --str1 hello --str1 horse	//报错

./test_optargs --str2 hello
./test_optargs --str2 hello --str2 horse	//报错

#if 0	/* 减轻工作量，不考虑多个相同参数的处理 */
./test_optargs --mstr1 hello --mstr1 horse
./test_optargs --mstr1 hello --mstr1 horse --mstr1 hello

./test_optargs --mstr2 hello --mstr2 horse
./test_optargs --mstr2 hello --mstr2 horse --mstr2 horse
#endif

./test_optargs --strsetdef md5
./test_optargs --strsetdef md4
./test_optargs --strsetdef md5 --strsetdef sha1	//报错

./test_optargs --strseterr md5
./test_optargs --strseterr md4
./test_optargs --strseterr md5 --strseterr sha1	//报错

#if 0	/* 减轻工作量，不考虑多个相同参数的处理 */
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
./test_optargs --ipdef 1.1.1.1 --ipdef 2.2.2.2	//报错

#if 0
./test_optargs --mipdef 1.1.1.1
./test_optargs --mipdef 1.1.1.1234
./test_optargs --mipdef 1.1.1.1 --mipdef 2.2.2.2
./test_optargs --miperr 1.1.1.1 --miperr 2.2.2.2345
#endif

//上面各测试项的任意组合：
#endif

#endif BASE_TEST

#ifdef QQ_RECORD_TEST
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：具体略，实际使用时，放入另一个cpp更合理
 ***************************************************************************/
int read_qq_record(const char *qq_record_filename, const char *stulist_filename, 
							const time_t begin_time, const time_t end_time,
								const char *stuno, const char *const key, 
									const bool only_zero, const bool more_than_zero)
{
	cout << "参数分析完毕，开始进行QQ聊天记录分析..." << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " { --stulist | --qq_record | --begin | --end | {--stuno} | {--only_zero} }" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--stulist filename   : 学生列表文件名(缺省:stulist.txt)" << endl;
	cout << setw(wopt) << ' ' << "--qq_record filename : 导出的聊天记录文件名(缺省:2019-高程.txt)" << endl;
	cout << setw(wopt) << ' ' << "--begin timestr      : 起始时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)" << endl;
	cout << setw(wopt) << ' ' << "--end timestr        : 结束时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)" << endl;
	cout << setw(wopt) << ' ' << "注：未检查时间串正确性" << endl;
	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--stuno stuno        : 指定某个学生(无此选项则全部学生)" << endl;
	cout << setw(wopt) << ' ' << "--only_zero          : 仅显示0发言学生(指定--stuno时本项无效)" << endl;
	cout << setw(wopt) << ' ' << "--more_than_zero     : 仅显示有发言学生(指定--stuno时本项无效，且与--only_zero互斥)" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\"" << endl;
	cout << setw(wkey) << "                               : 统计\"2019-高程.txt\"中在stulist.txt列表中的学生在2020.3.5 10:00~11:50间的发言数量" << endl;
	cout << "      " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero" << endl;
	cout << setw(wkey) << "                               : 统计\"2019-高程.txt\"中在stulist.txt列表中的学生在2020.3.5 10:00~11:50间0发言数量" << endl;
	cout << "      " << procname << " --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234" << endl;
	cout << setw(wkey) << "                               : 统计\"2019-高程.txt\"中在stulist.txt列表中的学生1951234在2020.3.5 10:00~11:50间的发言数量" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\"                 : 统计2020.3.5 10:00~11:50间所有学生的发言数量" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero     : 统计2020.3.5 10:00~11:50间所有0发言的学生" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --more_than_zero: 统计2020.3.5 10:00~11:50间所有有发言的学生" << endl;
	cout << "      " << procname << " --stulist list1.txt --qq_record 2019-高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234 : 统计2020.3.5 10:00~11:50间1951234的发言数量" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "请在cmd下加参数运行." << endl << endl;
		system("pause");
	}
}

/* enum的顺序要和args的排列顺序保持一致 */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_STULIST_FNAME, OPT_ARGS_QQ_RECORD_FNAME, OPT_ARGS_BEGIN_TIME, OPT_ARGS_END_TIME, OPT_ARGS_STUNO, OPT_ARGS_ONLY_ZERO, OPT_ARGS_MORE_THAN_ZERO, OPT_ARGS_KEY };

/***************************************************************************
  函数名称：
  功    能：从QQ群聊记录中统计出勤情况的main函数
  输入参数：
  返 回 值：
  说    明：为了简化，此处略去了--begin / --end的时间检查机制
***************************************************************************/
int main(int argc, char** argv)
{
	AAT args[] = {
		AAT("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--stulist", ST_EXTARGS_TYPE::str, 1, string("stulist.txt")),
		AAT("--qq_record", ST_EXTARGS_TYPE::str, 1, string("2019-高程.txt")),
		AAT("--begin", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--end", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--stuno", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT("--only_zero", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--more_than_zero", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--key", ST_EXTARGS_TYPE::str, 1, string("")),
		AAT()  //最后一个，用于结束
	};

	int need_fixed_args = 0;	//试试改为1
	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	args_analyse_print(args);

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}

		/* 此处应该处理要求的固定参数，本例中简单打印即可 */
		cout << "还有" << argc - cur_argc << "个固定参数" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		usage(argv[0], argc);
		return -1; //执行完成直接退出
	}

#if 0	//如果不希望 --stulist 和 --qq_record 有缺省值，则打开此条件编译
	if (args[OPT_ARGS_STULIST_FNAME].existed() == 0) {
		cout << "必须指定[" << args[OPT_ARGS_STULIST_FNAME].get_name() << "]学生名单文件" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_QQ_RECORD_FNAME].existed() == 0) {
		cout << "必须指定[" << args[OPT_ARGS_QQ_RECORD_FNAME].get_name() << "]QQ日志文件" << endl;
		usage(argv[0], argc);
		return -1;
	}
#endif

	if (args[OPT_ARGS_STUNO].existed() + args[OPT_ARGS_ONLY_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "指定[" << args[OPT_ARGS_STUNO].get_name() << "]参数则[" << args[OPT_ARGS_ONLY_ZERO].get_name() << "]参数无效" << endl;
		return -1;
	}

	if (args[OPT_ARGS_STUNO].existed() + args[OPT_ARGS_MORE_THAN_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "指定[" << args[OPT_ARGS_STUNO].get_name() << "]参数则[" << args[OPT_ARGS_MORE_THAN_ZERO].get_name() << "]参数无效" << endl;
		return -1;
	}

	if (args[OPT_ARGS_ONLY_ZERO].existed() + args[OPT_ARGS_MORE_THAN_ZERO].existed() == 2) {
		usage(argv[0], argc);
		cout << "参数[" << args[OPT_ARGS_ONLY_ZERO].get_name() << "/" << args[OPT_ARGS_MORE_THAN_ZERO].get_name() << "]互斥" << endl;
		return -1;
	}

	if (args[OPT_ARGS_BEGIN_TIME].existed() == 0) {
		usage(argv[0], argc);
		cout << "必须指定[" << args[OPT_ARGS_BEGIN_TIME].get_name() << "]起始时间" << endl;
		return -1;
	}

	if (args[OPT_ARGS_END_TIME].existed() == 0) {
		usage(argv[0], argc);
		cout << "必须指定[" << args[OPT_ARGS_END_TIME].get_name() << "]结束时间" << endl;
		return -1;
	}

#if 0
	/* 此处进行--begin和--end的时间分析：
	     1、判断时间串是否合法
	     2、判断起始时间是否小于结束时间
	   此处略 */
	string begin_time = args[OPT_ARGS_BEGIN_TIME].get_string();
	time_t btime = st_str2time(begin_time.c_str());
	if (btime < 0) {
		usage(argv[0], argc);
		cout << "[" << args[OPT_ARGS_BEGIN_TIME].get_name() << "]的格式错误" << endl;
		return -1;
	}

	string end_time = args[OPT_ARGS_END_TIME].get_string();
	time_t etime = st_str2time(end_time.c_str());
	if (etime < 0) {
		usage(argv[0], argc);
		cout << "[" << args[OPT_ARGS_END_TIME].get_name() << "]的格式错误" << endl;
		return -1;
	}

	if (btime > etime) {
		usage(argv[0], argc);
		cout << "起始时间[" << begin_time << "]晚于结束时间[" << end_time << "]" << endl;
		return -1;
	}
#else
	time_t btime = 1, etime = 2;
#endif

	/* 参数分析完毕，进入聊天记录的读取和处理部分（略）*/
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：具体略，实际使用时，放入另一个cpp更合理
 ***************************************************************************/
int check_fristline(const string& cno, const string& filename)
{
	cout << "开始进行源程序文件首行检查..." << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
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

	cout << setw(wkey) << ' ' << "必选项：指定检查类型(多选一)" << endl;
	cout << setw(wopt) << ' ' << "--firstline    : 首行检查" << endl;
	cout << setw(wopt) << ' ' << "--fileformat   : 文件格式规范检查(不需要实现)" << endl;
	cout << setw(wopt) << ' ' << "--forbiddenkey : 禁用关键字检查(不需要实现)" << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--courseid     : 课号" << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--filename     : 文件名(all表示全部)" << endl;
	cout << endl;

	cout << "e.g.   " << procname << " --firstline --courseid 100718 --filename 3-b1.cpp  : 检查100718课程的3-b1.cpp的首行" << endl;
	cout << "       " << procname << " --firstline --courseid 100718 --filename all       : 检查100718课程的全部文件的首行" << endl;
	cout << "       " << procname << " --fileformat --courseid 100215 --filename all      : 检查100215课程的全部文件的格式化" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "请在cmd下加参数运行." << endl << endl;
		system("pause");
	}
}

/* enum的顺序要和args的排列顺序保持一致 */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_FIRSTLINE, OPT_ARGS_FILEFORMAT, OPT_ARGS_FORBIDDEN_KEY, OPT_ARGS_COURSEID, OPT_ARGS_FILENAME };

/***************************************************************************
  函数名称：
  功    能：作业检查的main函数
  输入参数：
  返 回 值：
  说    明：
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
		AAT()  //最后一个，用于结束
	};

	int need_fixed_args = 0;	//试试改为1
	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse(argc, argv, args, need_fixed_args)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	args_analyse_print(args);

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}

		/* 此处应该处理要求的固定参数，本例中简单打印即可 */
		cout << "还有" << argc - cur_argc << "个固定参数" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

		/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		usage(argv[0], argc);
		return -1; //执行完成直接退出
	}

	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_FILEFORMAT].existed() + args[OPT_ARGS_FORBIDDEN_KEY].existed() != 1) {
		usage(argv[0], argc);
		cout << "参数[" << args[OPT_ARGS_FIRSTLINE].get_name() << "|" << args[OPT_ARGS_FILEFORMAT].get_name() << "|" << args[OPT_ARGS_FORBIDDEN_KEY].get_name() << "]必须指定一个且只能指定一个" << endl;
		return -1;
	}

	if (args[OPT_ARGS_COURSEID].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_COURSEID].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_FILENAME].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_FILENAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	if (args[OPT_ARGS_FIRSTLINE].existed()) {
		string cno = args[OPT_ARGS_COURSEID].get_string();
		string filename = args[OPT_ARGS_FILENAME].get_string();

		check_fristline(cno, filename);
	}
	else if (args[OPT_ARGS_FILEFORMAT].existed()) {
		cout << "文件格式检查未实现" << endl;
	}
	else if (args[OPT_ARGS_FORBIDDEN_KEY].existed()) {
		cout << "禁用关键字检查未实现" << endl;
	}

	return 0;
}

#endif //HW_CHECK_TEST