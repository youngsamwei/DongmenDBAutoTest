//
// Created by sam on 2018/12/10.
//

#include "dbscan/datapoint_mysqlconn_manager.h"

int DataPointMysqlConnManager::getDataPoints(const string &sql_select, vector<DataPoint> *dataSets) {

    if (!this->execute_sql(sql_select))
        return 1;

    MYSQL_RES *res = this->store_result();
    if (NULL == res) {
        mysql_free_result(res);
        return 1;
    }

    MYSQL_ROW row;
    unsigned long i = 0;
    while (row = mysql_fetch_row(res)) {
        DataPoint tempDP(row[0], row[1]);
        double tempDimData[DIME_NUM];
        tempDimData[0] = atof(row[2]);

        tempDP.SetDimension(tempDimData);

        tempDP.SetDpId(i);                    //将数据点对象ID设置为i
        tempDP.SetVisited(false);            //数据点对象isVisited设置为false
        tempDP.SetClusterId(-1);            //设置默认簇ID为-1
        dataSets->push_back(tempDP);
        i++;
    }

    mysql_free_result(res);
    return 0;
};