#include "Funcoes.h"

static char help[] = "Solves a tridiagonal linear system with KSP.\n\n";

#include <petscksp.h>
#include <metis.h>
#include <petscmat.h>

int Funcoes::SolveLS(matrix<float> _A, vector<float> _b, vector<float> &_x)
{
    int solver = 0; // TIPO DE SOLVER: 0 - BOOST; 1 - PETSC
                    // SOLVER: A * x = b
    if (solver == 0)
    {
        _x = _b;
        permutation_matrix<size_t> pm(_A.size1());
        lu_factorize(_A, pm);
        lu_substitute(_A, pm, _x);
    }
    else
    {
        Vec x, b;            // SOLUÇÃO APROXIMADA, RHS
        Mat A;               // MATRIZ A
        PetscErrorCode ierr; // ERROR CODE
        KSP ksp;             // LINEAR SOLVER CONTEXT
        PC pc;               // PRECONDITIONER CONTEXT
        PetscReal norm;      // NORMA DO ERRO DA SOLUÇÃO
        PetscInt i, n, its;  // CONTADOR, TAMANHO DO SISTEMA, ITERAÇÕES
        PetscMPIInt size;    //
        PetscScalar value;   // escalar do tipo PETSc
        n = _A.size1();
        _x = _b;
        PetscCallMPI(MPI_Comm_size(PETSC_COMM_WORLD, &size));
        PetscCheck(size == 1, PETSC_COMM_WORLD, PETSC_ERR_WRONG_MPI_SIZE, "This is a uniprocessor example only!");
        PetscOptionsGetInt(NULL, NULL, "-n", &n, NULL);
        // CRIANDO OS VETORES x E b:
        VecCreate(PETSC_COMM_SELF, &x);
        PetscObjectSetName((PetscObject)x, "Solution");
        VecSetSizes(x, PETSC_DECIDE, n);
        VecSetFromOptions(x);
        VecDuplicate(x, &b);
        // CRIANDO A MATRIZ A:
        MatCreate(PETSC_COMM_SELF, &A);
        MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, n, n);
        MatSetFromOptions(A);
        MatSetUp(A);
        // MONTANDO A MATRIZ A:
        for (int i = 0; i < _A.size1(); i++)
        {
            for (int j = 0; j < _A.size2(); j++)
                if (abs(_A(i, j)) >= 1.e-15)
                    value = _A(i, j), MatSetValues(A, 1, &i, 1, &j, &value, ADD_VALUES);
            if (abs(_b(i)) > 1.e-15)
                value = _b(i), VecSetValues(b, 1, &i, &value, ADD_VALUES);
        }
        MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
        MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
        // CRIANDO O SOLVER:
        KSPCreate(PETSC_COMM_SELF, &ksp);
        KSPSetOperators(ksp, A, A);
#if defined(PETSC_HAVE_MUMPS)
        KSPGetPC(ksp, &pc);
        PCSetType(pc, PCLU);
        KSPSetTolerances(ksp, 1.e-5, PETSC_DEFAULT, PETSC_DEFAULT, PETSC_DEFAULT);
#endif
        KSPSetFromOptions(ksp);
        // RESOLVENDO O SISTEMA LINEAR:
        KSPSolve(ksp, b, x);
        // REESCREVENDO O VETOR _x:
        for (int i = 0; i < _x.size(); i++)
            VecGetValues(x, 1, &i, &value), _x(i) = value;
        // VERIFICANDO A SOLUÇÃO E LIMPANDO VARIÁVEIS:
        VecNorm(x, NORM_2, &norm);
        KSPGetIterationNumber(ksp, &its);
        // PetscPrintf(PETSC_COMM_SELF, "Norm of error %g, Iterations %" PetscInt_FMT "\n", (double)norm, its);
        // check that KSP automatically handles the fact that the the new non-zero values in the matrix are propagated to the KSP solver
        MatShift(A, 2.0);
        KSPSolve(ksp, b, x);
        // DESTRUINDO VARIÁVEIS:
        VecDestroy(&x);
        VecDestroy(&b);
        MatDestroy(&A);
        KSPDestroy(&ksp);
    }
    return 0;
}
// PRINTS:
// MatView(A, PETSC_VIEWER_STDOUT_WORLD);
// VecView(b, PETSC_VIEWER_STDOUT_WORLD);
// VecView(x, PETSC_VIEWER_STDOUT_WORLD);
// KSPView(ksp, PETSC_VIEWER_STDOUT_SELF);