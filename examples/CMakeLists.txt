add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

target_include_directories(example1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib)
target_link_libraries(example1 PRIVATE formatter)

target_link_libraries(example2 PRIVATE formatter_ex formatter)
