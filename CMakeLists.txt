cmake_minimum_required(VERSION 3.16)
project(iustz_ranking_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(IUSTZ_ENABLE_GUI "Build Dear ImGui GUI frontend" ON)

include(FetchContent)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADERS_DIR "${SRC_DIR}/Headers")

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
)
list(REMOVE_ITEM CORE_SOURCES
    "${SRC_DIR}/The_main.cpp"
)

add_executable(iustz_game
    "${SRC_DIR}/The_main.cpp"
    ${CORE_SOURCES}
)

target_include_directories(iustz_game PRIVATE
    "${SRC_DIR}"
    "${HEADERS_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/external"
)

if(IUSTZ_ENABLE_GUI)
# ---- GUI frontend dependencies (Dear ImGui + GLFW + OpenGL3) ----
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)

FetchContent_MakeAvailable(glfw imgui glad)

add_library(imgui_lib
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui_lib PUBLIC glfw)

if (WIN32)
    target_link_libraries(imgui_lib PUBLIC opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui_lib PUBLIC OpenGL::GL)
endif()

add_executable(iustz_gui
    src_gui/main_gui.cpp
    ${CORE_SOURCES}
)

target_include_directories(iustz_gui PRIVATE
    "${SRC_DIR}"
    "${HEADERS_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/external"
)

target_link_libraries(iustz_gui PRIVATE imgui_lib glad)

endif()
