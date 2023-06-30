# 设置cmake最小版本
cmake_minimum_required(VERSION 3.0)
# 设置项目名称
project(simple_kye-value_pair_storage)
# 设置C++标准11
set(CMAKE_CXX_STANDARD 11)
# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/)
# 生成可执行文件
add_executable(main main.cpp)
# 链接readline动态库
TARGET_LINK_LIBRARIES(main readline.so)
