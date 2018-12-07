//
// Created by sam on 2018/11/4.
//

#include <iostream>
#include "test_execution.h"

int main(int argc, char *argv[]) {
    locale::global(locale(""));

    /*实验2的实验设置*/
    TestExecutionConfig experiment_config_2(L"experiment_2",
                                            L"exp_01_04_update_test",
                                            L"F:\\云班课作业 2018\\计算机16-1，2，3-数据库系统-课程设计_实验2_实现u_第六次/",
                                            L"云班课作业",
                                            L"F:/dongmendb",
                                            L"E:/CLion_workspace/DongmenDB",
                                            L"F:\\dongmendb_output_exp_2");
    experiment_config_2.exp_files[L"exp_01_04_update.c"] = L"/src_experiment/exp_01_stmt_parser/exp_01_04_update.c";
    experiment_config_2.exp_files[L"exp_07_05_update.c"] = L"/src_experiment/exp_07_physical_operate/exp_07_05_update.c";


    /*实验3的实验设置*/
    TestExecutionConfig experiment_config_3(L"experiment_3",
                                            L"exp_01_05_delete_test",
                                            L"F:\\云班课作业 2018\\计算机16-1，2，3-数据库系统-课程设计_实验3_实现D_第六次/",
                                            L"云班课作业",
                                            L"F:/dongmendb",
                                            L"E:/CLion_workspace/DongmenDB",
                                            L"F:\\dongmendb_output_exp_3");
    experiment_config_3.exp_files[L"exp_01_05_delete.c"] = L"/src_experiment/exp_01_stmt_parser/exp_01_05_delete.c";
    experiment_config_3.exp_files[L"exp_07_06_delete.c"] = L"/src_experiment/exp_07_physical_operate/exp_07_06_delete.c";


    TestExecution te;
//    te.run(exp_name, exp_target, exp_dir_name, exp_files, work_dir, dongmendb_src_dir, output_dir);
    te.batchrun(experiment_config_2);

    te.batchrun(experiment_config_3);
}

