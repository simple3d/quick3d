cmake_minimum_required(VERSION 3.1.0)
project(quick3d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# nanogui
set(NANOGUI_BUILD_EXAMPLE  OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON   OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL        OFF CACHE BOOL " " FORCE)
add_subdirectory(thirdparty/nanogui)
add_definitions(${NANOGUI_EXTRA_DEFS})
set_target_properties(nanogui PROPERTIES FOLDER Dependencies)
set_target_properties(nanogui-obj PROPERTIES FOLDER Dependencies)
set_target_properties(glfw PROPERTIES FOLDER Dependencies)
set_target_properties(glfw_objects PROPERTIES FOLDER Dependencies)

# quick3d
list(APPEND VIEWER_INCLUDE_DIRS ${NANOGUI_EXTRA_INCS})
list(APPEND VIEWER_INCLUDE_DIRS "thirdparty/nanogui/include")
list(APPEND VIEWER_INCLUDE_DIRS "include")
include_directories(${VIEWER_INCLUDE_DIRS})

file(GLOB QUICK3D_SOURCES "src/*.cpp" "src/*.h")

# build quick3d app
add_executable(quick3d ${QUICK3D_SOURCES})
target_link_libraries(quick3d nanogui ${NANOGUI_EXTRA_LIBS})
add_custom_command(TARGET quick3d
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:nanogui> "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Copy nanogui.dll file to ${CMAKE_CURRENT_BINARY_DIR} directory" VERBATIM
)