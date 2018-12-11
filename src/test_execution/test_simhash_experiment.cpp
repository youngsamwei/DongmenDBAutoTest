//
// Created by sam on 2018/12/10.
//


#include <io.h>
#include <iostream>
#include "test_simhash_experiment.h"
#include <Utils.h>
#include <simhash.h>


TestSimhashExperiment::TestSimhashExperiment(TestExecutionConfig *config) {
    this->config = config;
};

/*第一步：计算文件的simhash值*/
int TestSimhashExperiment::run_simhash() {
    struct _wfinddata_t fb;   //查找相同属性文件的存储结构体

    long handle;
    int resultone = 0;
    int noFile;            //对系统隐藏文件的处理标记

    handle = _wfindfirst((config->expDirName + L"/*").c_str(), &fb);
    //找到第一个匹配的文件
    if (handle != 0) {
        //当可以继续找到匹配的文件，继续执行
        while (0 == _wfindnext(handle, &fb)) {
            //windows下，常有个系统文件，名为“..”,对它不做处理
            noFile = wcscmp(fb.name, L"..");

            if (0 != noFile) {
                //属性值为16，则说明是文件夹，调用任务处理
                /*对每个学生作业文件夹中的c文件，计算simhash值*/
                if (fb.attrib == 16) {
                    wstring dir = config->expDirName + L"/" + fb.name;
                    wstring exp_student_name = fb.name;
                    int underline_pos = exp_student_name.find(L"_");
                    wstring sno = exp_student_name.substr(0, underline_pos);
                    wstring sname = exp_student_name.substr(underline_pos + 1, exp_student_name.length());

                    map<wstring, wstring>::iterator iter;
                    wstring slash = L"/";
                    for (iter = config->exp_files.begin(); iter != config->exp_files.end(); iter++) {
                        wstring file_name = iter->first;
                        wstring find_file = Utils::findFileNameEndWith(dir, file_name);
                        if (find_file.length() == 0) {
                            /*若没有找到需要复制的文件, 需要记录异常*/
                            break;
                        }
                        wstring file_path = dir + slash + find_file;
                        ul_int file_hash = SimHash::simhash_file(Utils::ws2s(file_path).c_str());


                        string sql_insert =
                                "insert into experiments_simhash(sno, sname, expname, filename, round, simhash) values('"
                                + Utils::ws2s(sno) + "', '"
                                + Utils::ws2s(sname) + "', '"
                                + Utils::ws2s(config->expName) + "', '"
                                + Utils::ws2s(iter->first) + "', "
                                + to_string(config->round) + ", "
                                + to_string(file_hash) + ")";

                        cout << endl << sql_insert << endl;
                        if (!config->connManager->execute_sql(sql_insert)){
                            cout<<"error in store_test_execution_result. sno: "<<Utils::ws2s(sno)<<endl<<"error message"<<config->connManager->get_error_msg()<<endl;
                        };
                    }
                }

            }
        }
        //关闭文件夹
        _findclose(handle);
    }
    return 0;
};


/*第一步：计算文件的simhash值*/
int TestSimhashExperiment::run_simhash(TestExecutionConfig *config) {
    this->config = config;
    return this->run_simhash();
};

/* 第二步：根据simhash值聚类*/
int TestSimhashExperiment::run_cluster() {
    return 0;
};