//
// Created by sam on 2018/12/10.
//

#include "dbscan/datapoint.h"
#include "dbscan/dbscan.h"

int main(int argc, char *argv[]) {

    string dbip = "127.0.0.1";
    string dbuser = "root";//mysql账号名
    string dbpasswd = "123456"; //mysql账号密码

    string dbname = "database_experiment";//数据库名
    unsigned int port = 3306;

    DBSCANClusterAnalysis dbscan_cluster(dbip, dbuser, dbpasswd, dbname);

    int test_round = -1;
    string file_name = "";
    if (argc != 3) {
        cout << " run_dbscan_cluster <test_round_num> <file_name>" << endl << "error exit." << endl;
        exit(0);
    }
    int r = atoi(argv[1]);
    if (r > 0) {
        test_round = r;
        file_name = argv[2];
    } else {
        cout << "run_dbscan_cluster <test_round_num> <file_name>\n test_round_num should be a num." << endl
             << "error exit." << endl;
        exit(0);
    }

    string sql_select = "select sno, sname, simhash from experiments_simhash where round = " + to_string(test_round) +
                        " and filename='" + file_name + "'";

    dbscan_cluster.initDataPoints(sql_select, 10, 1);        //算法初始化操作，指定半径为10，领域内最小数据点个数为1，（在程序中已指定数据维度为1）

    string output_file_name = "D:/experiment_cluster_" + to_string(test_round) + ".txt";
    dbscan_cluster.DoDBSCANRecursive();                    //执行聚类算法
    dbscan_cluster.WriteToMysql(test_round, file_name);    //将聚类结果写入数据库
    dbscan_cluster.WriteToFile(test_round, output_file_name);


}