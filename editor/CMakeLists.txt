cmake_minimum_required(VERSION 3.5) 
project(Rengine_EDITOR VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

add_executable(${PROJECT_NAME} src/EditorApp.cpp)


target_link_libraries(${PROJECT_NAME} Rengine_ENGINE)
target_include_directories(${PROJECT_NAME} PRIVATE Rengine_ENGINE})