cmake_minimum_required(VERSION 3.9)
project(DongmenDBAutoTest)

set(CMAKE_CXX_STANDARD 11)

#set(INC_DIR "C:/Program Files/MySQL/MySQL Connector C 6.1/include")
#set(LINK_DIR "C:/Program Files/MySQL/MySQL Connector C 6.1/lib" "C:/Program Files/MySQL/MySQL Connector C 6.1/lib/vs14")


set(INC_DIR "mysqlconnector/include")
set(LINK_DIR "mysqlconnector/lib" "mysqlconnector/lib/vs12")


include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(libmysql)
#link_libraries(mysqlclient)

add_subdirectory(src/test_execution)

add_executable(mysqltest main.cpp )
#target_link_libraries(mysqltest libmysql )