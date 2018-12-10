
aux_source_directory(dbscan DIR_SRCS_dbscan)
ADD_LIBRARY(dbscan ${DIR_SRCS_dbscan})

aux_source_directory(mysql_connector_manager DIR_SRCS_mysql_connector_wrapper)
ADD_LIBRARY(mysql_connector_manager ${DIR_SRCS_mysql_connector_wrapper})

aux_source_directory(simhash DIR_SRCS_simhash)
ADD_LIBRARY(simhash ${DIR_SRCS_simhash})

aux_source_directory(test_execution DIR_SRCS_test_execution)
ADD_LIBRARY(test_execution ${DIR_SRCS_test_execution})

aux_source_directory(utils DIR_SRCS_utils)
ADD_LIBRARY(utils ${DIR_SRCS_utils})

#TARGET_LINK_LIBRARIES(mysql_connector_manager test_execution)

ADD_EXECUTABLE(DongmenDBAutoTest test_execution_main.cpp)
TARGET_LINK_LIBRARIES(DongmenDBAutoTest  utils test_execution mysql_connector_manager)

ADD_EXECUTABLE(run_simhash_experiment run_simhash_experiment.cpp)
TARGET_LINK_LIBRARIES(run_simhash_experiment  utils test_execution mysql_connector_manager simhash)

ADD_EXECUTABLE(run_dbscan_cluster run_dbscan_cluster.cpp)
TARGET_LINK_LIBRARIES(run_dbscan_cluster  utils mysql_connector_manager dbscan)