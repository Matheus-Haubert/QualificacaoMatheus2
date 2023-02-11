# @file FemSC/headers/CMakeLists.txt  -- CMake file for the Headers module

file(GLOB functs *.h)
file(GLOB functs_src *.cpp)

set(FUNCTS ${functs} PARENT_SCOPE)
set(FUNCTS_SRC ${functs_src} PARENT_SCOPE)