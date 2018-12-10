

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
TARGET_LINK_LIBRARIES(DongmenDBAutoTest test_execution mysql_connector_manager utils)