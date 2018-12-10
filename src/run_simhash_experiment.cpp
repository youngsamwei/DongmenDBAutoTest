//
// Created by sam on 2018/11/4.
//

#include <iostream>
#include <Utils.h>
#include <test_simhash_experiment.h>
#include "test_execution.h"

int main(int argc, char *argv[]) {
    locale::global(locale(""));
    string dbuser = "root";//mysql账号名
    string dbpasswd = "123456"; //mysql账号密码
    string dbip = "127.0.0.1";
    string dbname = "database_experiment";//数据库名
    unsigned int port = 3306;

    MySQLConnManager connManager;


    int test_round = -1;
    if (argc == 1) {
        cout << " DongmenDBAutoTest <test_round_num>" << endl << "error exit." << endl;
        exit(0);
    }
    int r = atoi(argv[1]);
    if (r > 0) {
        test_round = r;
    } else {
        cout << "DongmenDBAutoTest <test_round_num>  test_round_num should be a num." << endl << "error exit." << endl;
        exit(0);
    }

    connManager.init(dbip, dbuser, dbpasswd, dbname);
    if (connManager.reconnect()) {
        if (!connManager.select_db(dbname)) {
            cout << "Select successfully the database: " << dbname << endl;
        } else {
            cout << "select database error: " << connManager.get_error_msg() << endl;
        }
    } else {
        cout << "error: " << connManager.get_error_msg() << endl;

        exit(0);
    }

    /*实验2的实验设置*/
    wstring experiment_2_expDirName = Utils::FormatWString(L"F:/云班课作业 2018/计算机16-1，2，3-数据库系统-课程设计_实验2_实现u_第%i次",
                                                           test_round);
    TestExecutionConfig experiment_config_2(L"experiment_2",
                                            L"exp_01_04_update_test",
                                            experiment_2_expDirName,
                                            L"云班课作业",
                                            L"F:/dongmendb",
                                            L"E:/CLion_workspace/DongmenDB",
                                            L"F:/dongmendb_output_exp_2",
                                            test_round, &connManager,
                                            OUTPUT_CONSOLE);
    experiment_config_2.exp_files[L"exp_01_04_update.c"] = L"/src_experiment/exp_01_stmt_parser/exp_01_04_update.c";
    experiment_config_2.exp_files[L"exp_07_05_update.c"] = L"/src_experiment/exp_07_physical_operate/exp_07_05_update.c";

    /*实验3的实验设置*/
    wstring experiment_3_expDirName = Utils::FormatWString(L"F:/云班课作业 2018/计算机16-1，2，3-数据库系统-课程设计_实验3_实现D_第%i次",
                                                           test_round);
    TestExecutionConfig experiment_config_3(L"experiment_3",
                                            L"exp_01_05_delete_test",
                                            experiment_3_expDirName,
                                            L"云班课作业",
                                            L"F:/dongmendb",
                                            L"E:/CLion_workspace/DongmenDB",
                                            L"F:/dongmendb_output_exp_3",
                                            test_round, &connManager,
                                            OUTPUT_CONSOLE);
    experiment_config_3.exp_files[L"exp_01_05_delete.c"] = L"/src_experiment/exp_01_stmt_parser/exp_01_05_delete.c";
    experiment_config_3.exp_files[L"exp_07_06_delete.c"] = L"/src_experiment/exp_07_physical_operate/exp_07_06_delete.c";

    TestSimhashExperiment tse(&experiment_config_2);
//    te.run(exp_name, exp_target, exp_dir_name, exp_files, work_dir, dongmendb_src_dir, output_dir);
    tse.run_simhash(&experiment_config_2);

    tse.run_simhash(&experiment_config_3);

    connManager.close_connect();
}

