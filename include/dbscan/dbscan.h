//
// Created by sam on 2018/12/10.
//

#ifndef DONGMENDBAUTOTEST_DBSCAN_H
#define DONGMENDBAUTOTEST_DBSCAN_H

#include <vector>
#include <iostream>
#include <cmath>
#include "mysqlconn_manager.h"
#include "dbscan/datapoint.h"

using namespace std;

//聚类分析类型
class DBSCANClusterAnalysis : public MySQLConnManager{
private:
    vector<DataPoint> dadaSets;        //数据集合
    unsigned int dimNum;            //维度
    double radius;                    //半径
    unsigned int dataNum;            //数据数量
    unsigned int minPTs;            //邻域最小数据个数

    double GetDistance(DataPoint &dp1, DataPoint &dp2);                    //距离函数
    void SetArrivalPoints(DataPoint &dp);                                //设置数据点的领域点列表
    void KeyPointCluster(unsigned long i, unsigned long clusterId);    //对数据点领域内的点执行聚类操作
public:

    DBSCANClusterAnalysis(string dbip, string dbuser, string dbpasswd, string dbname) ;                   //默认构造函数
    ~DBSCANClusterAnalysis();

    bool initDataPoints(string &sql_select, double radius, int minPTs);

    bool DoDBSCANRecursive();            //DBSCAN递归算法
    bool WriteToOStream(const string fileName, ofstream &of1);    //将聚类结果写入文件
    bool WriteToFile(const int round, const string outputFileName);
    bool WriteToMysql(int test_round, string file_name);//将聚类结果写入数据库

    int getDataPoints(const string &sql_select, vector<DataPoint> *dataSets);
};

#endif //DONGMENDBAUTOTEST_DBSCAN_H
