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
    if (argc != 2) {
        cout << " run_dbscan_cluster <test_round_num> " << endl << "error exit." << endl;
        exit(0);
    }
    int r = atoi(argv[1]);
    if (r > 0) {
        test_round = r;
    } else {
        cout << "run_dbscan_cluster <test_round_num> <file_name>\n test_round_num should be a num." << endl
             << "error exit." << endl;
        exit(0);
    }

    string output_file_name = "D:/experiment_cluster_" + to_string(test_round) + ".txt";

    dbscan_cluster.DoDBSCANRecursive(test_round, 10, 1);
    dbscan_cluster.WriteToFile(test_round, output_file_name);


}