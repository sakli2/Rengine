cmake_minimum_required(VERSION 3.5) 
project(Rengine_ENGINE VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} src/engine.cpp)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC  

    PRIVATE

)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)