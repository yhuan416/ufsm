cmake_minimum_required(VERSION 3.5)

project(ufsm)

add_library(ufsm src/ufsm.c)
target_include_directories(ufsm PUBLIC include) 

add_executable(ufsm_test test/main.c)
target_link_libraries(ufsm_test ufsm)
