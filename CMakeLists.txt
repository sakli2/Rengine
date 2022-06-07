cmake_minimum_required(VERSION 3.5) 
project(Rengine_env LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(app)
add_subdirectory(editor)
add_subdirectory(engine)