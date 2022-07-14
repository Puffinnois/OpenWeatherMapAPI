cmake_minimum_required(VERSION 3.22)
project(WeatherAPI C)

#set(CMAKE_C_STANDARD 99)
#add_executable(WeatherAPI main.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PostgreSQL_ROOT "C:\\Program Files\\PostgreSQL\\9.4")
find_package(PostgreSQL REQUIRED)

include_directories (${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})

set(SOURCES main.c)
add_executable(PostgreSQLTest ${SOURCES})
target_link_libraries(PostgreSQLTest ${PostgreSQL_LIBRARIES})

set(SOURCE_FILES
        CMakeLists.txt
        main.c)
