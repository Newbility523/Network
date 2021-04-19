cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_COMPLIER /bin/gcc.exe)
set(CMAKE_CXX_COMPLIE /usr/bin/g++)

project(server)


include(CTest)
enable_testing()

add_executable(server main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
