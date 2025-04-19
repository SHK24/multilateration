#include "RtkLibSolver.h"


extern "C" {
    int lsq(const double *A, const double *y, int n, int m, double *x, double *Q);
}
extern "C" {
    void dgemm_(char *, char *, int *, int *, int *, double *, double *,
                    int *, double *, int *, double *, double *, int *);
}

extern void matmul(const char *tr, int n, int k, int m, double alpha,
    const double *A, const double *B, double beta, double *C)
{
    int lda=tr[0]=='T'?m:n,ldb=tr[1]=='T'?k:m;

    dgemm_((char *)tr,(char *)tr+1,&n,&k,&m,&alpha,(double *)A,&lda,(double *)B,
    &ldb,&beta,C,&n);
}


extern double *mat(int n, int m)
{
    double *p;
    
    if (n<=0||m<=0) return NULL;
    if (!(p=(double *)malloc(sizeof(double)*n*m))) {
        //fatalerr("matrix memory allocation error: n=%d,m=%d\n",n,m);
    }
    return p;
}

extern int *imat(int n, int m)
{
    int *p;
    
    if (n<=0||m<=0) return NULL;
    if (!(p=(int *)malloc(sizeof(int)*n*m))) {
        //fatalerr("integer matrix memory allocation error: n=%d,m=%d\n",n,m);
    }
    return p;
}

extern int matinv(double *A, int n)
{
    double *work;
    int info,lwork=n*16,*ipiv=imat(n,1);
    
    work=mat(lwork,1);
    dgetrf_(&n,&n,A,&n,ipiv,&info);

    //info = 0;

    if (!info) dgetri_(&n,A,&n,ipiv,work,&lwork,&info);
    free(ipiv); free(work);
    return info;
}

int lsq(const double *A, const double *y, int n, int m, double *x, double *Q) {
    double *Ay;
    int info;
    
    if (m<n) return -1;
    Ay=mat(n,1);
    matmul("NN",n,1,m,1.0,A,y,0.0,Ay); /* Ay=A*y */
    matmul("NT",n,n,m,1.0,A,A,0.0,Q);  /* Q=A*A' */

    info=matinv(Q,n);

    if (!(info=matinv(Q,n))) matmul("NN",n,1,n,1.0,Q,Ay,0.0,x); /* x=Q^-1*Ay */
    free(Ay);
    return info;
}


void printMatrix(const double* array, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << array[i * m + j] << " "; // Индексация в одномерном массиве
        }
        std::cout << std::endl; // Переход на новую строку после каждой строки матрицы
    }

    fflush(stdout);
}

Vector3d RtkLibSolver::locate_rtk_lsq(const std::vector<LocatorData>& locators) {
    
    
    double *A;
    double *Ay;
    double *y;
    A = new double[locators.size() * 3];
    y = new double[locators.size()];
    int m = 3;
    int n = locators.size();
    double x[5];
    double * Q = new double[n * n];

    for(int i = 0; i < locators.size();i++) {
        A[i*3 + 0] = locators[i].position.x();
        A[i*3 + 1] = locators[i].position.y();
        A[i*3 + 2] = locators[i].position.z();
        //A[i*3 + 3] = locators[i].position.dot_square() - locators[i].distance * locators[i].distance;
        //y[i] = 0;
        y[i] = locators[i].position.dot_square() - locators[i].distance * locators[i].distance;
        int a = 10;
    }

    int info;

    Ay=mat(n,1);
    matmul("NT",m,1,n,1.0,A,y,0.0,Ay); /* Ay=A*y */
    matmul("NT",n,n,m,1.0,A,A,0.0,Q);  /* Q=A*A' */

    if (!(info=matinv(Q,m))) {
       matmul("NN",n,1,n,1.0,Q,Ay,0.0,x); /* x=Q^-1*Ay */
    }
    free(Ay);

    return { x[0], x[1], x[2] };
}
