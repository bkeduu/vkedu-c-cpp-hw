cmake_minimum_required(VERSION 3.0.0)
project(skyscrapers)

add_subdirectory(sky_lib)

message("SKY_LIB_INCLUDE_DIRS = ${SKY_LIB_INCLUDE_DIRS}")
message("SKY_LIB_LIBRARIES = ${SKY_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${SKY_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SKY_LIB_LIBRARIES})

add_subdirectory(tests)
