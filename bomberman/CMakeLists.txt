cmake_minimum_required(VERSION 3.20)
project(progetto_bomberman)
set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_executable(bomberman
        src/main.cpp
        src/Menu.cpp include/Menu.hpp
        src/Tempo.cpp include/Tempo.hpp
        src/Punti.cpp include/Punti.hpp
        src/fine.cpp include/fine.hpp
        src/Classifica.cpp include/Classifica.hpp
        src/Gamemaster.cpp include/Gamemaster.hpp
        src/Schermo.cpp include/Schermo.hpp
        src/Bomb.cpp include/Bomb.hpp
        src/Config.cpp include/Config.hpp
        src/Enemy.cpp include/Enemy.hpp
        src/Enemy_t1.cpp include/Enemy_t1.hpp
        src/Enemy_t2.cpp include/Enemy_t2.hpp
        src/Enemy_t3.cpp include/Enemy_t3.hpp
        src/Mappa.cpp include/Mappa.hpp
        src/Item.cpp include/Item.hpp
        src/Player.cpp include/Player.hpp
        src/GestoreLivelli.cpp include/GestoreLivelli.hpp
)
if (WIN32)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/ncurses.h "#include <curses.h>\n")
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(bomberman pdcurses)
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(bomberman ${CURSES_LIBRARIES})
endif()