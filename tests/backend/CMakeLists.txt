cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME "backend_test")

file(GLOB_RECURSE TARGET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${TARGET_NAME} ${TARGET_SRC})

set(RAPIDJSON_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/thirdparty/rapidjson/include/)

target_include_directories(${TARGET_NAME} 
PUBLIC
    ${CMAKE_SOURCE_DIR}/backend/include
    ${RAPIDJSON_INCLUDE_DIR}
)

target_link_libraries(${TARGET_NAME} PUBLIC
    backend
    gtest
    gtest_main
)

gtest_discover_tests(${TARGET_NAME})
