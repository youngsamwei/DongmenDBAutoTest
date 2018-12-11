//
// Created by sam on 2018/11/3.
//

#ifndef DONGMENDB_TEST_EXECUTION_H
#define DONGMENDB_TEST_EXECUTION_H

#include <cstddef>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <thread>
#include "test_execution_config.h"

using namespace std;

class TestExecution {

    TestExecutionConfig *config;
    wstring project_name = L"dongmendb";
    wstring cmake_build_type = L" -DCMAKE_BUILD_TYPE=Debug ";
    wstring cmake_files = L"-G \"CodeBlocks - MinGW Makefiles\" ";
    wstring cmake_build_dir = L"cmake-build-debug";
    wstring cmd_build  = L" --build ";
    wstring cmd_target_clean = L" --target clean -- -j 2 ";
    wstring cmd_target = L" --target ";
    wstring cmake_others_parameters = L" -- -j 2";
    wstring cmake_exe = L"cmake.exe ";
    const int SIZE_RAND_STR_LEN = 32; //生成32 + 1位C Style字符串
    const char *CCH = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";


public:

    TestExecution(TestExecutionConfig *config);
    /*执行实验测试
     * 参数：实验名称，编译目标，实验作业所在文件夹
     * exp_dir_name 指向一个学生的一个实验任务
     * 输出到output_dir
     * 输出文件名命名规则：1)以输入exp_dir_name中最后的文件夹名称作为文件前缀，
     *  再加步骤名称，再加步骤结果，形如201501030413_毛锟_cmake_build_passed，
     *  201501030413_毛锟_test_cases_execution_passed
     * 2)文件内容是每个阶段的命令输出。
     *
     * */
    int run(wstring exp_dir_name);

    /*执行实验测试
     * exp_dir_name 指向多个学生的实验任务，每个学生一个文件夹
     * */
    int batchrun();

    int batchrun(TestExecutionConfig *config);

protected:
    /*初始化输出文件夹*/
    int init_output_dir(wstring ouput_dir);

    /*初始化dongmendb文件夹*/
    int init_dongmendb(wstring work_dir, wstring dir_name);

    /*清理工作文件夹中产生的文件*/
    int clear_dongmendb(wstring work_dir, wstring dir_name);

    /*复制dongmendb的源代码到目标文件夹*/
    int copy_dongmendb(wstring from_dir_name, wstring dest_dir_name);

    /*从实验作业文件夹复制文件到目标文件夹*/
    int copy_exp_to_dongmendb(wstring exp_dir_name, wstring dest_dir_name,
                              std::map<wstring, wstring> exp_files, ofstream& out);

    int copy_exp_to_dongmendb(wstring exp_dir_name, wstring dest_dir_name,
                              std::map<wstring, wstring> exp_files);

    int cmd_cmake_refresh(wstring output_dir, wstring build_dir_name);
    /*在cmd中执行命令，清理cmake产生的文件*/
    int cmd_cmake_clean(wstring build_dir_name);

    /*在cmd中执行命令，build代码*/
    int cmd_cmake_build(wstring build_dir_name, wstring exp_target, ofstream& out);
    int cmd_cmake_build(wstring build_dir_name, wstring exp_target);

    /*在cmd中执行命令，运行exe目标文件*/
    int cmd_exp_target(wstring bin_dir, wstring exp_target, ofstream& out, string contents);
    int cmd_exp_target(wstring bin_dir, wstring exp_target, string contents);

    /*获取测试结果*/
    int cmd_get_test_result();

    /*保存执行结果：学号，姓名，实验名称，第几次测试，测试结果，测试日期时间*/
    int store_test_execution_result(string sno, string sname, string expname, int round, string result);

    /*更新测试结果*/
    int update_test_execution_result(string sno, string sname, string expname, int round, string result);


private:
    /*产生指定长度的随机字符串, 默认长度32*/
    char *rand_str(size_t len);
    char *rand_str();

    /*执行cmd命令，并将执行结果写入result*/
    int executeCMD(wstring cmd, ofstream& xout);

    int executeCMD(wstring cmd);
    /*检查命令的输出中是否包含contents指定的内容*/
    int executeCMD(wstring cmd, ofstream& xout, string contents);
    int executeCMD(wstring cmd, string contents);



    /*利用接收到的字符数作为监控标识，
     * recieving_chars_count < 0 表示测试用例程序没有开始工作；
     * recieving_chars_count > 0 表示正在工作
     * 若>0时且超过10秒recieving_chars_count不改变，则认为出现异常，应该被终止。*/
public:
    int recieving_chars_count = -1;
    /* 若monitor_stop_flag > 0 则认为应该终止监控线程 */
    int monitor_stop_flag = 0;
};

#endif //DONGMENDB_TEST_EXECUTION_H
