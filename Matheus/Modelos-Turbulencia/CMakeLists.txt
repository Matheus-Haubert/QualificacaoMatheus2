cmake_minimum_required (VERSION 3.11.0)
project (Fluid)

list (APPEND CMAKE_MODULE_PATH "${Fluid_SOURCE_DIR}/cmake-modules")

find_package (PETSc REQUIRED)   
find_package (HDF5 REQUIRED)
find_package (METIS REQUIRED)
find_package (MPI REQUIRED)

# Essential: include our directories first otherwise we can get internal headers from some installed path
include_directories ("${Fluid_SOURCE_DIR}/include" "${Fluid_SOURCE_DIR}/include" ${PETSC_INCLUDES} ${PETSC_KSP_LIB})
add_definitions (${PETSC_DEFINITIONS})
set (Fluid_DEPENDENT_LIBRARIES "${PETSC_LIBRARIES}")
set (Fluid_LIBRARIES Fluid ${Fluid_DEPENDENT_LIBRARIES})
include_directories (${HDF5_INCLUDE_DIRS} ${HDF5_DEFINITIONS} ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
include_directories(${MPI_INCLUDE_PATH})

#hide warnings
add_definitions(-w) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#[[
If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
to Debug prior to calling PROJECT(). This assumes you're only build one type of solution
a time. If you're working with multiple solutions like Visual Studio Professional can do,
you need to comment this out.
]]
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: Debug, Release.")
else() # CMAKE_BUILD_TYPE
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug, Release.")
endif() # CMAKE_BUILD_TYPE
 
set(CMAKE_CXX_STANDARD 17)

# Eigen
include(cmake-modules/EnableEigen.cmake)
enable_eigen()

add_subdirectory(functs)
add_subdirectory(inputs)

#Specify where the headers files must be found
include_directories(
	"${PROJECT_SOURCE_DIR}/functs"
	"${PROJECT_SOURCE_DIR}/inputs"
)

add_library(Fluid_library ${FUNCTS} ${FUNCTS_SRC} ${INPUTS} ${INPUTS_SRC})
target_link_libraries(Fluid_library PRIVATE Eigen3::Eigen)

add_executable(f main.cpp)
target_link_libraries(f Fluid_library Eigen3::Eigen ${PETSC_KSP_LIB} ${PETSC_LIBRARIES} ${HDF5_LIBRARIES} ${METIS_LIBRARIES} ${MPI_LIBRARIES})