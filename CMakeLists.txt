cmake_minimum_required(VERSION 3.9)
project(DongmenDBAutoTest)

set(CMAKE_CXX_STANDARD 11)

#设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 引入 boost,
INCLUDE_DIRECTORIES(D:/boost_1_68_0_mingw-win64-x86_64-8.1.0)
LINK_DIRECTORIES(D:/boost_1_68_0_mingw-win64-x86_64-8.1.0/stage/lib)

#INCLUDE_DIRECTORIES(D:/boost_1_68_0-mingw-win64-i686)
#LINK_DIRECTORIES(D:/boost_1_68_0-mingw-win64-i686/stage/lib)

#INCLUDE_DIRECTORIES(D:/boost_1_68_0-msvc-14.1-64)
#LINK_DIRECTORIES(D:/boost_1_68_0-msvc-14.1-64/lib64-msvc-14.1)


#INCLUDE_DIRECTORIES(D:/boost_1_57_0-msvc-11.0-32/)
#LINK_DIRECTORIES(D:/boost_1_57_0-msvc-11.0-32/lib32-msvc-11.0)

#mysql conector c
#set(MYSQL_CONNECTOR_INC_DIR "mysqlconnector/include")
#set(MYSQL_CONNECTOR_LINK_DIR "mysqlconnector/lib")

# mysql connector c++ 1.0.5
# 无论与 1.68-msvc还是1.57-msvc均不能成功编译 error: conflicting declaration 'typedef char int8_t'
#set(MYSQL_CONNECTOR_INC_DIR "mysqlcppconn_1.0.5/include")
#set(MYSQL_CONNECTOR_LINK_DIR "mysqlcppconn_1.0.5/lib")

# mysql connector c++ 1.1.11
set(MYSQL_CONNECTOR_INC_DIR "C:/Program Files/MySQL/MySQL Connector C++ 1.1.11/include")
set(MYSQL_CONNECTOR_LINK_DIR "C:/Program Files/MySQL/MySQL Connector C++ 1.1.11/lib/opt/")

# 1.1.9 无论与 1.68-msvc还是1.57-msvc均能成功编译,但执行时 During startup program exited with code 0xc000007b.
#set(MYSQL_CONNECTOR_INC_DIR "F:/mysql_connector_cpp/mysql-connector-c++-noinstall-1.1.9-win32/include")
#set(MYSQL_CONNECTOR_LINK_DIR "F:/mysql_connector_cpp/mysql-connector-c++-noinstall-1.1.9-win32/lib")

# mysql connector c++ 8.0.13-win32
# 无论与 1.68-msvc还是1.57-msvc均不能成功编译 error: expected constructor, destructor, or type conversion before '(' token
#set(MYSQL_CONNECTOR_INC_DIR "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-win32/include/jdbc" )
#set(MYSQL_CONNECTOR_INC_DIR ${MYSQL_CONNECTOR_INC_DIR} "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-win32/include/mysqlx" )
#set(MYSQL_CONNECTOR_LINK_DIR "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-win32/lib")

# mysql-connector-c++-8.0.13-winx64
#
#set(MYSQL_CONNECTOR_INC_DIR "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-winx64/include/jdbc" )
#set(MYSQL_CONNECTOR_INC_DIR ${MYSQL_CONNECTOR_INC_DIR} "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-winx64/include/mysqlx" )
#set(MYSQL_CONNECTOR_LINK_DIR "F:/mysql_connector_cpp/mysql-connector-c++-8.0.13-winx64/lib")

include_directories(${MYSQL_CONNECTOR_INC_DIR})
link_directories(${MYSQL_CONNECTOR_LINK_DIR})

#mysql 5.5 include and libs
#INCLUDE_DIRECTORIES("C:/Program Files/MySQL/MySQL Server 5.5/include")
LINK_DIRECTORIES("C:/Program Files/MySQL/MySQL Server 5.5/lib")


#mysql conector c
#link_libraries(libmysql)

# mysql connector c++ 8.0.13
#link_libraries(mysqlcppconn8-1-vs14)
#link_libraries(libeay32)
#link_libraries(ssleay32)

link_libraries(libmysql)

# mysql connector c++ 1.0.5
#link_libraries(mysqlcppconn)

# mysql connector c++ 1.1.11
link_libraries(mysqlcppconn)

#头文件搜索目录
INCLUDE_DIRECTORIES(include)
#链接库搜索路径
LINK_DIRECTORIES(lib)


#设置被依赖的库
SET(EXTRA_LIBS mysql_connector_wrapper test_execution)

add_subdirectory(src)

# test_mysql_main.cpp 的代码列表
AUX_SOURCE_DIRECTORY(. MAIN_SRC_LIST)
ADD_EXECUTABLE(test_mysql_connector_cpp ${MAIN_SRC_LIST} )
target_link_libraries(test_mysql_connector_cpp mysql_connector_wrapper  libmysql mysqlcppconn)

#target_link_libraries(DongmenDBAutoTest libmysql )


#add_executable(test_mysql  main.cpp mysql_connector_wrapper)

