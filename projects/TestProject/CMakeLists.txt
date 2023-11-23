
cmake_minimum_required (VERSION 3.26)

set(FIRE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../..")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

project(TestProject VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

file(GLOB_RECURSE     SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.h)

add_executable(TestProject
    ${SRC_FILES}
    ${INCLUDE_FILES}
)

if(MSVC)
    # disable warnings (informational warnings):
    # /wd4820 -> c4820 -> 'bytes' bytes padding added after construct 'member_name'
    # /wd4514 -> c4514 -> 'function' : unreferenced inline function has been removed
    # /wd4710 -> c4710 -> 'function' : function not inlined
    # /wd4711 -> c4711 -> function 'function' selected for inline expansion
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(TestProject PRIVATE /Wall /wd4820 /wd4514 /wd4710 /wd4711 /sdl /std:c++20 /MDd /external:anglebrackets /external:W0 /fsanitize=address)
        message(STATUS "compiler using debug options")
    else()
        target_compile_options(TestProject PRIVATE /Wall /wd4820 /wd4514 /wd4710 /wd4711 /sdl /std:c++20 /MD /external:anglebrackets /external:W0)
        message(STATUS "compiler using release options")
    endif()
else()
    target_compile_options(TestProject PRIVATE -Wall -Wextra -Wpedantic)
endif()

# define macros
target_compile_definitions(TestProject
    PRIVATE
        RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
        FENGINE_RESOURCES_PATH="${FIRE_DIRECTORY}/resources/"
)

# define include directories
target_include_directories(TestProject PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${FIRE_DIRECTORY}/src/
)

# link libraries
target_link_directories(TestProject PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

target_link_libraries(TestProject Fire)

# copy Fire engine libraries to this projects lib folder
string(REPLACE "/projects/${PROJECT_NAME}/" "/" FIRE_ARCHIVE_OUTPUT_DIR ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
string(REPLACE "/projects/${PROJECT_NAME}/" "/" FIRE_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
string(REPLACE "/projects/${PROJECT_NAME}/" "/" FIRE_RUNTIME_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(WIN32)
    add_custom_command(TARGET TestProject PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FIRE_RUNTIME_OUTPUT_DIR}/Fire.dll"
            "${FIRE_RUNTIME_OUTPUT_DIR}/Fire.pdb"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    add_custom_command(TARGET TestProject PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FIRE_ARCHIVE_OUTPUT_DIR}/Fire.lib"
            "${FIRE_ARCHIVE_OUTPUT_DIR}/Fire.exp"
            "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
else()
    # the following copies might not be valid or complete, this command is not tested since i am not using linux
    message(AUTHOR_WARNING "The Fire libs might not all be copied to this project, manually copying the library files to the /lib/$<CONFIG>/ directory might be required")
    add_custom_command(TARGET TestProject PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FIRE_LIBRARY_OUTPUT_DIR}/Fire.so" # this might be the wrong directory, change if needed
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    add_custom_command(TARGET TestProject PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FIRE_ARCHIVE_OUTPUT_DIR}/Fire.a"
            "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
endif()