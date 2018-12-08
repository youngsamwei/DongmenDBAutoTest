cmake_minimum_required(VERSION 3.9)
project(DongmenDBAutoTest)

set(CMAKE_CXX_STANDARD 11)

#设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(MYSQL_CONNECTOR_INC_DIR "mysqlconnector/include")
set(MYSQL_CONNECTOR_LINK_DIR "mysqlconnector/lib")

include_directories(${MYSQL_CONNECTOR_INC_DIR})
link_directories(${MYSQL_CONNECTOR_LINK_DIR})
link_libraries(libmysql)

#头文件搜索目录
INCLUDE_DIRECTORIES(include)
#链接库搜索路径
LINK_DIRECTORIES(lib)

#设置被依赖的库
SET(EXTRA_LIBS mysql_connector_wrapper test_execution)

add_subdirectory(src)

AUX_SOURCE_DIRECTORY(. MAIN_SRC_LIST)
ADD_EXECUTABLE(test_mysql_connector_c ${MAIN_SRC_LIST} )
target_link_libraries(test_mysql_connector_c)
