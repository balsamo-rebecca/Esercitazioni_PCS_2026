cmake_minimum_required(VERSION 3.20)
project(esercitazione5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(algoritmo_ordinamento es5.cpp timecounter.cpp)

## Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_bubblesort test_bubblesort.cpp timecounter.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

add_executable(test_insertionsort test_insertionsort.cpp timecounter.cpp)
add_test(NAME insertionsort COMMAND test_insertionsort)

add_executable(test_selectionsort test_selectionsort.cpp timecounter.cpp)
add_test(NAME selectionsort COMMAND test_selectionsort)

add_executable(test_mergesort test_mergesort.cpp timecounter.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp timecounter.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

add_executable(test_quickottimizzato test_quickottimizzato.cpp timecounter.cpp)
add_test(NAME quickottimizzato COMMAND test_quickottimizzato)

enable_testing()
