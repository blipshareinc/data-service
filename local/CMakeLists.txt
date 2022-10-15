cmake_minimum_required(VERSION 3.24.1)
project(DataService VERSION 1.0.0 LANGUAGES CXX C)

set(LIB /usr/local/lib64)

find_package(SQLite3)

option(ARM32V7 "Architecture is ARM32v7" OFF)

if(ARM32V7)
    message("Building for Arm32v7 architecture...")
    find_package(oatpp 1.3.0 CONFIG REQUIRED)
    find_package(oatpp-sqlite 1.3.0 CONFIG REQUIRED)
    find_package(oatpp-swagger 1.3.0 CONFIG REQUIRED)
else()
    message("Building for Arch64 architecture...")
    set(VCPKG_DIR /vcpkg/installed/x64-linux)
    find_package(unofficial-sqlite3 CONFIG REQUIRED)
    find_package(oatpp 1.3.0 CONFIG PATHS ${VCPKG_DIR} REQUIRED)
    find_package(oatpp-sqlite 1.3.0 CONFIG PATHS ${VCPKG_DIR} REQUIRED)
    find_package(oatpp-swagger 1.3.0 CONFIG PATHS ${VCPKG_DIR} REQUIRED)
endif()

find_package(fmt REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src)
