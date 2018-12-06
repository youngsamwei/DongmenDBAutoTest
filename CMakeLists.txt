cmake_minimum_required(VERSION 3.9)
project(DongmenDBAutoTest)

set(CMAKE_CXX_STANDARD 11)

#mysql conector c
#set(MYSQL_CONNECTOR_INC_DIR "mysqlconnector/include")
#set(MYSQL_CONNECTOR_LINK_DIR "mysqlconnector/lib")

# mysql connector c++ 1.0.5
#set(MYSQL_CONNECTOR_INC_DIR "mysqlcppconn_1.0.5/include")
#set(MYSQL_CONNECTOR_LINK_DIR "mysqlcppconn_1.0.5/lib")

# mysql connector c++ 8.0.13
set(MYSQL_CONNECTOR_INC_DIR "mysqlcppconn/include/jdbc" "mysqlcppconn/include/mysqlx")
set(MYSQL_CONNECTOR_LINK_DIR "mysqlcppconn/lib64")

include_directories(${MYSQL_CONNECTOR_INC_DIR})
link_directories(${MYSQL_CONNECTOR_LINK_DIR})

#mysql conector c
#link_libraries(libmysql)

# mysql connector c++ 8.0.13
#link_libraries(mysqlcppconn-7-vs14)

# mysql connector c++ 1.0.5
#link_libraries(mysqlcppconn)

#设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#头文件搜索目录
INCLUDE_DIRECTORIES(include)
#链接库搜索路径
LINK_DIRECTORIES(lib)

# 引入 boost,
INCLUDE_DIRECTORIES(D:/boost_1_68_0)
LINK_DIRECTORIES(D:/boost_1_68_0/stage/lib)

#设置被依赖的库
SET(EXTRA_LIBS mysql_connector_wrapper test_execution)

add_subdirectory(src)

# test_mysql_main.cpp 的代码列表
AUX_SOURCE_DIRECTORY(. MAIN_SRC_LIST)
ADD_EXECUTABLE(test_mysql ${MAIN_SRC_LIST} )

#target_link_libraries(DongmenDBAutoTest libmysql )


#add_executable(test_mysql  main.cpp mysql_connector_wrapper)

