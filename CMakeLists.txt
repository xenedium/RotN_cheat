cmake_minimum_required(VERSION 3.19)
project(Bloodstained_RotN_extcheats)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(Bloodstained_RotN_extcheats main.cpp elevations.cpp)