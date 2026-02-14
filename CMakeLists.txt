cmake_minimum_required(VERSION 3.16)
project(iustz_ranking_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(iustz_game ${GAME_SOURCES})

target_include_directories(iustz_game PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Headers"
    "${CMAKE_CURRENT_SOURCE_DIR}/external"
)
