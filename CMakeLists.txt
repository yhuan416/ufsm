cmake_minimum_required(VERSION 3.5)

project(ufsm)

option(UFSM_BUILD_STATIC "Build static library" ON)
option(UFSM_BUILD_SHARED "Build shared library" ON)
option(UFSM_BUILD_TESTS "Build tests" OFF)

set(ufsm_version v1.0.0)

set(ufsm_name ufsm)
set(ufsm_src src/ufsm.c)
set(ufsm_include_dir include)

# ufsm static library
if (UFSM_BUILD_STATIC)
    add_library(${ufsm_name} ${ufsm_src})
    target_include_directories(${ufsm_name} PUBLIC ${ufsm_include_dir})

    install(TARGETS ${ufsm_name} DESTINATION lib)
endif()

# ufsm shared library
if (UFSM_BUILD_SHARED)
    set(ufsm_shared_name ${ufsm_name}_shared)

    add_library(${ufsm_shared_name} SHARED ${ufsm_src})
    target_include_directories(${ufsm_shared_name} PUBLIC ${ufsm_include_dir})

    set_target_properties(${ufsm_shared_name} PROPERTIES OUTPUT_NAME ${ufsm_name})

    install(TARGETS ${ufsm_shared_name} DESTINATION lib)
endif()

install(DIRECTORY ${ufsm_include_dir}/ DESTINATION include)

# ufsm test executable
if (UFSM_BUILD_TESTS)
    add_subdirectory(test)
endif()
