cmake_minimum_required(VERSION 3.5) 
project(Rengine_ENGINE VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

#exteral libaries
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/nlohmann/json)


find_package(Vulkan REQUIRED)




if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")



file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp"  "src/*/*/*/*/*.cpp")

add_library(${PROJECT_NAME}  ${SOURCES})

target_precompile_headers(${PROJECT_NAME}
  PRIVATE
    include/pch.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
        nlohmann_json
    PRIVATE
        ${VULKAN_INCLUDE_DIRS}
        glfw
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC  
        glm
        nlohmann_json
    PRIVATE
        ${Vulkan_LIBRARIES}
        glfw
)