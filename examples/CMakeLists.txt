# Путь к папке formatter_lib (там лежит print.hpp)
set(FORMATTER_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

# Явно добавляем путь к заголовкам formatter_lib для example1
target_include_directories(example1 PRIVATE ${FORMATTER_LIB_PATH})

# Линкуем библиотеки
target_link_libraries(example1 PRIVATE formatter)
target_link_libraries(example2 PRIVATE formatter_ex formatter)
