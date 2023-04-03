cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 17)

execute_process(COMMAND bash -c "cd ${CMAKE_SOURCE_DIR} && curl -R -O http://www.lua.org/ftp/lua-5.4.4.tar.gz && tar zxf lua-5.4.4.tar.gz && cd lua-5.4.4 && make")
add_executable(test main.cpp)
include_directories(lua-5.4.4/src)
link_directories(lua-5.4.4/src)
#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
target_link_libraries(test -L${CMAKE_SOURCE_DIR}/lua-5.4.4/src/ -llua)
configure_file(main.lua main.lua COPYONLY)
