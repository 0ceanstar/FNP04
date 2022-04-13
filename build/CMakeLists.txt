cmake_minimum_required (VERSION 3.22)
# 这里写项目名字
project (Elgamal)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
# 源代码的路径
link_directories("/usr/local/lib" "../src")
# 将源代码添加到此项目的可执行文件，第一个参数为可执行文件的名字
add_executable (main "../main.cpp" "../src/Elgamal.cpp" "../src/Poly.cpp" "../src/thres_Elgamal.cpp" )
# 需要引入的库文件，第一个参数需要与上行保持一致
target_link_libraries(main "gmp")
# 库文件路径
include_directories("/usr/local/include" "../include")

