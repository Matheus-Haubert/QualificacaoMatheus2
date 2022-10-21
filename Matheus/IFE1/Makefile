MANSEC           = KSP
CLEANFILES       = rhs.vtk solution.vtk
NP               = 1
CSOURCES 		 = $(wildcard *.cpp Functions/*.cpp)
FCOMPILER        = gfortran -O2
CXXFLAGS        += -w

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
include ${PETSC_DIR}/lib/petsc/conf/test

ife: $(CSOURCES:.cpp=.o) 
	@-${CLINKER} -o $@ $^ ${PETSC_KSP_LIB} -lboost_system -std=c++11

debug: $(CSOURCES:.cpp=.o)
	@-${CLINKER} -o $@ $^ ${PETSC_KSP_LIB} -g
	@gdb debug

clearall:
	@$ rm *.o Functions/*.o *ife

run1:
	./ife

run2:
	@$ mpirun -np 2 ./ife

run4:
	@$ mpirun -np 4 ./ife

run8:
	@$ mpirun -np 8 ./ife