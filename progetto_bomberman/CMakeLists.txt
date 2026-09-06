cmake_minimum_required(VERSION 4.1)
project(progetto_bomberman)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(bomberman
        main.cpp
        Menu.cpp
        Menu.hpp
        Tempo.cpp
        Tempo.hpp
        Punti.cpp
        Punti.hpp
        fine.cpp
        fine.hpp
        Classifica.cpp
        Classifica.hpp
        Gamemaster.cpp
        Gamemaster.hpp
        Schermo.cpp
        Schermo.hpp
        Bomb.hpp
        Bomb.cpp
        Config.hpp
        Config.cpp
        Enemy.cpp
        Enemy.hpp
        Enemy_t1.cpp
        Enemy_t1.hpp
        Enemy_t2.cpp
        Enemy_t2.hpp
        Enemy_t3.cpp
        Enemy_t3.hpp
        Mappa.hpp
        Mappa.cpp
        Item.cpp
        Item.hpp
        Player.cpp
        Player.hpp
        GestoreLivelli.cpp
        GestoreLivelli.hpp
)

target_link_libraries(Bomberman ${CURSES_LIBRARIES})
