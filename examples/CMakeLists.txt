# Добавление директории include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Явное указание пути к библиотеке print
add_library(print STATIC IMPORTED)
set_target_properties(print PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../libprint.a
)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

target_link_libraries(example1 print)
target_link_libraries(example2 print)

install(TARGETS example1 example2
    RUNTIME DESTINATION bin
)
