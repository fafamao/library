cmake_minimum_required(VERSION 3.10)

project(concurrency)


include_directories(inc)
add_library(concurrency STATIC actor.cpp safe_queue.cpp)
set_target_properties(concurrency PROPERTIES LIBRARY_OUTPUT_DIRECTORY /home/baobo/repo/practice_cpp/out)
target_include_directories(concurrency PUBLIC ../inc)