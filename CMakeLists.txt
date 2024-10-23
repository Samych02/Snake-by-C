cmake_minimum_required(VERSION 3.29)
project(Snake-by-C C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCE_FILES src/*.c)
file(GLOB INCLUDE_FILES include/*.h)

find_package(SDL2 CONFIG REQUIRED)

add_executable(Snake ${SOURCE_FILES} ${INCLUDE_FILES}
        src/game.c
        src/game.c
        include/obstacle.h
        include/border.h
        include/snake.h
        include/game.h)
target_include_directories(Snake PRIVATE include)
target_link_libraries(Snake
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
