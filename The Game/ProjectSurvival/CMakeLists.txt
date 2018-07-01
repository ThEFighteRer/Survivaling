cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


project("Survivaling")

add_executable(exeki elementy_stale.cpp gra.cpp gra_ruch_gracza.cpp gracz.cpp graficzny.cpp grafika.cpp main.cpp objekt.cpp przedmiot.cpp structy.cpp swiat.cpp zombie.cpp zwierzeta.cpp zwierzeta2.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")

install(TARGETS myapp DESTINATION bin)



