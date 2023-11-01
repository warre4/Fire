
cmake_minimum_required (VERSION 3.21)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(Fire VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED_ON)

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
#file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_subdirectory(extern/glfw)

add_executable(Fire
#           ${SRC_FILES}
#           ${INCLUDE_FILES}

            "src/main.cpp"
            )

target_include_directories(Fire
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/
            )

target_link_libraries(
            Fire
            PUBLIC
            glfw
)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Fire PRIVATE imgui::imgui)