cmake_minimum_required(VERSION 3.24.1)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
    controller/controller.hpp
    db/sqlite3_client.hpp
    web/dto/user_dto.hpp
    web/dto/page_dto.hpp
    web/dto/status_dto.hpp
    service/user_service.cpp
    web/app_component.hpp
)

set(VCPKG_INCLUDE_DIR ${VCPKG_DIR}/include)
set(VCPKG_LIB_DIR ${VCPKG_DIR}/lib)
set(OATPP_DIR ${VCPKG_INCLUDE_DIR}/oatpp-1.3.0)
set(OATPP_INCLUDE_DIR ${OATPP_DIR}/oatpp/)
set(OATPP_SQLITE_INCLUDE_DIR ${OATPP_DIR}/oatpp-sqlite/)
set(OATPP_SWAGGER_INCLUDE_DIR ${OATPP_DIR}/oatpp-swagger/)
set(OATPP_LIB_DIR ${VCPKG_LIB_DIR}/oatpp-1.3.0/)
set(FMT_INCLUDE_DIR ${VCPKG__LIB_DIR}/include/fmt)

add_definitions(
    -DSERVER_NAME="localhost"
    -DSERVER_ADDRESS="http://localhost"
    -DSERVER_PORT=11002
    -DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res"
    -DDATABASE_FILE="${CMAKE_SOURCE_DIR}/db/local.db"
    -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"    
    -DDEVELOPER_NAME="BLIPShare"
    -DDEVELOPER_URL="https://www.blipshare.com"
)

add_library(data_service_lib SHARED main.cpp)

target_compile_options(data_service_lib
    PRIVATE
    -g -Wall -Wconversion -Wsign-conversion -Wsign-compare
)

target_include_directories(data_service_lib
    PUBLIC
    ${FMT_INCLUDE_DIR}
    ${OATPP_INCLUDE_DIR}
    ${OATPP_SQLITE_INCLUDE_DIR}
    ${OATPP_SWAGGER_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${VCPKG_INCLUDE_DIR}
)

add_executable(data_service main ${SOURCE_FILES})

target_link_libraries(data_service LINK_PUBLIC data_service_lib)

target_link_directories(data_service
    PRIVATE
    ${OATPP_LIB_DIR}
    ${VCPKG_LIB_DIR})

target_link_libraries(data_service
    PUBLIC
    fmt
    oatpp::oatpp
    oatpp::oatpp-sqlite
    oatpp::oatpp-swagger
    Threads::Threads
)

# DEPLOYMENT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/deploy")

set_target_properties(data_service PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/deploy
)

# Copy the Swagger files
file(COPY 
    ${OATPP_BASE_DIR}/bin/oatpp-swagger/res
    DESTINATION
    ${CMAKE_SOURCE_DIR}/deploy
)