cmake_minimum_required (VERSION 3.25.2 FATAL_ERROR)

project(UsersSql)

set(CMAKE_CXX_STANDARD 17)

set (SQLLIB "C:/Dev/libraries/MySQL Server 8.0/lib/mysqlcppconn-static.lib")
set (HEADER "C:/Dev/libraries/MySQL Server 8.0/include")
set (MAIN "src/main.cpp")

include_directories(${HEADER})

add_executable (SqlApp ${MAIN})

target_link_libraries(SqlApp PRIVATE ${SQLLIB})