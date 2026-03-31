cmake_minimum_required(VERSION 3.10)
project(solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver solver.cpp)

target_link_libraries(solver PRIVATE 
formatter_ex formatter solver_lib)

install(TARGETS solver
    RUNTIME DESTINATION bin
)
