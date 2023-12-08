cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME backend)

file(GLOB_RECURSE TARGET_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/backend/*.hpp
)

file(GLOB_RECURSE TARGET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${TARGET_NAME} STATIC ${TARGET_SRC} ${TARGET_HEADERS})
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/thirdparty/rapidjson/include/)

target_include_directories(${TARGET_NAME} PUBLIC
    include/backend
    include
    ${RAPIDJSON_INCLUDE_DIR}
)

target_link_libraries(${TARGET_NAME} PUBLIC
    ast
    utils
)
