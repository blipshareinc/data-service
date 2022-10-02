cmake_minimum_required(VERSION 3.24.1)
project(DataService VERSION 1.0.0 LANGUAGES CXX C)

set(LIB /usr/local/lib64)

find_package(SQLite3)
#find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(fmt REQUIRED)
find_package(Threads REQUIRED)
find_package(oatpp 1.3.0 CONFIG REQUIRED)
find_package(oatpp-sqlite 1.3.0 CONFIG REQUIRED)
find_package(oatpp-swagger 1.3.0 CONFIG REQUIRED)

add_subdirectory(src)
