
cmake_minimum_required (VERSION 3.21)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(Fire VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
#file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

#add_subdirectory(extern/vulkan)

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

#find_package(vulkan CONFIG REQUIRED)
#target_link_libraries(Fire PUBLIC
#            vulkan
#)

## -------------- IMGUI static library creation`
##
#set(IMGUI_PATH ${CMAKE_CURRENT_LIST_DIR}/external/imgui)
#file(GLOB IMGUI_GLOB
#    ${IMGUI_PATH}/imgui.h
#    ${IMGUI_PATH}/imgui.cpp
#    ${IMGUI_PATH}/imconfig.h
#    ${IMGUI_PATH}/imgui_demo.cpp
#    ${IMGUI_PATH}/imgui_draw.cpp
#    ${IMGUI_PATH}/imgui_internal.h
#    ${IMGUI_PATH}/imstb_rectpack.h
#    ${IMGUI_PATH}/imstb_textedit.h
#    ${IMGUI_PATH}/imstb_truetype.h
#    ${IMGUI_PATH}/imgui_tables.cpp
#    ${IMGUI_PATH}/imgui_widgets.cpp
#
#    # specific bindings...
#    ${IMGUI_PATH}/backends/imgui_impl_glfw.h
#    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
#    ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
#    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
#    ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)
#add_library("imgui" STATIC ${IMGUI_GLOB})
#target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
#target_link_libraries("imgui" PRIVATE glfw)
## ----------------------------------------------------------------------

#find_package(imgui CONFIG REQUIRED)
#target_link_libraries(Fire PRIVATE
#            imgui::imgui
#)