//
// Created by sam on 2018/12/11.
//

#ifndef DONGMENDBAUTOTEST_MONITOR_TEST_CASES_EXECUTION_H
#define DONGMENDBAUTOTEST_MONITOR_TEST_CASES_EXECUTION_H
#include <ctime>
#include <io.h>
#include <cstring>
#include "test_execution.h"
#include <afxres.h>
#include <iostream>
#include <assert.h>
#include <tlhelp32.h>
#include <unistd.h>

/*监控执行测试用例的exe程序是否出现异常导致程序无法终止。
 * 参数：
 * exe_file_name ：被监控的进程名称
 * timeout：超时阈值，以秒为单位*/
void monitor_test_cases_execution(string exe_file_name, int timeout, int &recieving_chars_count);

void find_process_and_kill(const char *strFilename) ;

#endif //DONGMENDBAUTOTEST_MONITOR_TEST_CASES_EXECUTION_H
