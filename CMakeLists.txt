cmake_minimum_required(VERSION 3.21)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${Python3_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${Python3_LIBRARIES}
        )

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${Python3_RUNTIME_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.dll ${OUTPUT_DIR})
endif()

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/python_modules/ ${OUTPUT_DIR}/python_modules)