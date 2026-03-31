add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

# Явно указываем путь к заголовкам formatter_lib
target_include_directories(example1 PRIVATE ${CMAKE_SOURCE_DIR}/formatter_lib)

# Явно указываем, что example1 зависит от formatter (чтобы formatter собрался до example1)
add_dependencies(example1 formatter)

target_link_libraries(example1 PRIVATE formatter)
target_link_libraries(example2 PRIVATE formatter_ex formatter)
