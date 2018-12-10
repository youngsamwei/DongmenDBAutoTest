//
// Created by sam on 2018/12/10.
//

#include "dbscan/datapoint.h"
#include "dbscan/dbscan.h"

int main(int argc, char *argv[]) {

    DBSCANClusterAnalysis dbscan_cluster;
    string dbuser = "root";//mysql账号名
    string dbpasswd = "123456"; //mysql账号密码
    string dbip = "127.0.0.1";
    string dbname = "database_experiment";//数据库名
    unsigned int port = 3306;

    DataPointMysqlConnManager connManager;


//    int test_round = -1;
//    if (argc == 1) {
//        cout << " DongmenDBAutoTest <test_round_num>" << endl << "error exit." << endl;
//        exit(0);
//    }
//    int r = atoi(argv[1]);
//    if (r > 0) {
//        test_round = r;
//    } else {
//        cout << "DongmenDBAutoTest <test_round_num>  test_round_num should be a num." << endl << "error exit." << endl;
//        exit(0);
//    }

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

    string sql_select ="select sno, sname, simhash from experiments_simhash where round = 7 and filename='exp_01_04_update.c'";

    dbscan_cluster.init(&connManager, sql_select, 10, 1);        //算法初始化操作，指定半径为15，领域内最小数据点个数为3，（在程序中已指定数据维度为2）
//    connManager.close_connect();

    dbscan_cluster.DoDBSCANRecursive();                    //执行聚类算法
    dbscan_cluster.WriteToFile("D:/XYResult.txt");//写执行后的结果写入文件


    connManager.close_connect();
}