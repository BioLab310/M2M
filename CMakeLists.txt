cmake_minimum_required(VERSION 3.5.0)
project(M2M VERSION 0.1.0 LANGUAGES C CXX)

configure_file(config.h.in config.h)
file (GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
