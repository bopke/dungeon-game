cmake_minimum_required(VERSION 3.16)
project(dungeon_game C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(thirdparty/googletest)

set(Headers
        src/common.h
        src/map.h
        src/player.h
        src/game.h)

set(Sources
        src/common.c
        src/map.c
        src/player.c
        src/game.c)

add_executable(dungeon_game src/main.c ${Headers} ${Sources})

set(Test_Sources
        tests/map.cpp
        tests/player.cpp
        tests/game.cpp)

add_executable(dungeon_game_tests ${Headers} ${Sources} ${Test_Sources})

target_link_libraries(dungeon_game_tests PUBLIC
        gtest_main
        )


add_test(
        NAME dungeon_game_tests
        COMMAND dungeon_game_tests
)
