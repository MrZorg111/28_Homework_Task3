cmake_minimum_required (VERSION 3.17)

add_executable("28_Homework_Task3" main.cpp function.cpp ${MY_INCLUDE_DIR}/function.h)
target_include_directories("28_Homework_Task3" PUBLIC ${MY_INCLUDE_DIR})