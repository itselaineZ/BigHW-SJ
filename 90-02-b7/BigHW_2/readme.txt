90-02-final：本学期最后一个大作业

commom：公共文件
	注意：class_aat.cpp - 部分给出，需要自行补充完整
	      class_cct.cpp - 已给出完整实现（供阅读参考）
	      class_cft.cpp - 部分给出，需要自行补充完整
              class_gmw.cpp     - 部分给出，需要自行补充完整
              class_gmw_cbi.cpp - 部分给出，需要自行补充完整
              class_gmw_cfi.cpp - 部分给出，需要自行补充完整
              class_gmw_sli.cpp - 部分给出，需要自行补充完整


include：公共头文件
	注意：class_aat.h - 部分给出，需要自行补充完整
	      class_cct.h - 已给出完整定义（供阅读参考）
	      class_cft.h - 部分给出，需要自行补充完整
              class_gmw.h     - 部分给出，需要自行补充完整
              class_gmw_cbi.h - 部分给出，需要自行补充完整
              class_gmw_cfi.h - 部分给出，需要自行补充完整
              class_gmw_sli.h - 部分给出，需要自行补充完整

lib：存放老师提供 lib_class_gmw.lib 和 lib_class_gmw.pdb 公共库文件，供 test_lib_graphics_middleware 调用
	注意：不准删除

test_args_analyse_tools：
	注意：测试主函数是 class_aat_main.cpp（有三个条件编译选项，根据需要打开任意一个即可）
              class_aat的实现在 common/class_aat.cpp 中（不完整，需要自行补充完整）

test_cfgfile_tools：
	注意：测试主函数是 class_cft_main.cpp
              class_cft的实现在 common/class_cft.cpp 中（不完整，需要自行补充完整）

test_cmd_console_tools：
	注意：测试主函数是 class_cct_main.cpp
              class_cct的实现在 commonb/class_cct.cpp 中 （本项目已实现，供阅读参考）

test_graphics_middleware：
	注意：测试主函数是 class_gmw_main.cpp
              class_gmw 及 class_gmw_** 的实现在 commonb/class_gmw.cpp及class_gmw_**.cpp 中（不完整，需要自行补充完整）

test_lib_graphics_middleware：用于测试老师提供的class_gmw实现的测试项目
	注意：测试主函数是 test_graphics_middleware/class_gmw_main.cpp，即与你的class_gmw实现共用测试用例
              class_gmw 及 class_gmw_** 的实现在 lib/lib_class_gmw.lib中（静态链接库，无源程序文件）

