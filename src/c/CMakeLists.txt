cmake_minimum_required(VERSION 3.18)
project(c C)

set(CMAKE_C_STANDARD 11)

add_executable(c listFilm.c databaseInit.c listDirector.c hashTableDirectorList.c main.c)
