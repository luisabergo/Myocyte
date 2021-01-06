#include "uteis.h"

double CalcNorma(double *vet)
{   
    double Norma;
    Norma = sqrt(pow(vet[0],2) + pow(vet[1],2));
    return Norma;
}

double CalcProdEscalar(double *vet1, double *vet2)
{   
    return vet1[0]*vet2[0] + vet1[1]*vet2[1];
    }

void CalcDifVetor(double *w, double *u, double *v)
{   
    w[0] = v[0]-u[0];
    w[1] = v[1]-u[1];
}