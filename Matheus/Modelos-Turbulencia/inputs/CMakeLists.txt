# @file FemSC/headers/CMakeLists.txt  -- CMake file for the Headers module

file(GLOB inputs *.h)
file(GLOB inputs_src *.cpp)

set(INPUTS ${inputs} PARENT_SCOPE)
set(INPUTS_SRC ${inputs_src} PARENT_SCOPE)