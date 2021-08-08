cmake_minimum_required(VERSION 3.16)
project(Module27_opp2_task_1)

set(CMAKE_CXX_STANDARD 11)

option(ENABLE_TESTING "Enable the filling of names automatically" OFF)

add_executable(Module27_opp2_task_1)

target_sources(Module27_opp2_task_1
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/generate_random.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/elf_tree.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/elf_names.h

        ${CMAKE_CURRENT_SOURCE_DIR}/src/generate_random.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/elf_tree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/elf_names.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )

target_include_directories(Module27_opp2_task_1
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Module27_opp2_task_1
        PRIVATE
        ENABLE_TESTING=$<BOOL:${ENABLE_TESTING}>
        )

