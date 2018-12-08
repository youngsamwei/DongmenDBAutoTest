cmake_minimum_required(VERSION 3.9)
project(DongmenDBAutoTest)

set(CMAKE_CXX_STANDARD 11)

set(INC_DIR "mysqlconnector/include")
set(LINK_DIR "mysqlconnector/lib")

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(libmysql)

#add_subdirectory(src/test_execution)

add_executable(DongmenDBAutoTest test_mysql_connector_c.cpp )
target_link_libraries(DongmenDBAutoTest libmysql )