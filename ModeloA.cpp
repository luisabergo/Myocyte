#include "ModeloA.h"
#include <math.h>
#include "ResolvedorEDO.h"
#include <iostream> 

ModeloA::ModeloA()
{

}

ModeloA::~ModeloA()
{

}

void ModeloA::avanca(double* y, double* ynew, int nPasso, double deltat, ResolvedorEDO* r )
{
    ynew[0] = y[0] + deltat*dTa(Ta,nPasso*deltat, r);
    y[0] = ynew[0];
    ynew[1] = y[1] + deltat*dTai(Ta,nPasso*deltat, r);
    y[1] = ynew[1];
    
}

void ModeloA::resolveModelo(ResolvedorEDO* r)
{
    int num_passos = 12000;
    double dt = 0.05;
    double aux;
    double y[2] = {0.0, 0.0};
    double ynovo[2];
    Ta[0] = y[0];
    Tai[0] = y[1];
    for (int k=1; k<=num_passos; k++)
    {
        this->avanca(y, ynovo, k, dt, r);
        Ta[k] = ynovo[0];
        Tai[k] = ynovo[1];

    }
    printSolucao();

}

void ModeloA::printSolucao()
{
    for(int i=0; i<12000; i++)
    {
        cout << Ta[i] << " " << Tai[i] << endl;
    }
}

double ModeloA::k(double V, double Tai)
{
    return (1./(sigma*sqrt(2*3.14))) * exp((-pow(V - 1, 2.)/(2.*pow(sigma,2.))));
}

double ModeloA::E1(double* y, double t, ResolvedorEDO* r)
{
    double V = r->getPotencial(t);

    if(V>x2 and y[_Tai_]<x3)
        return x1;
    else
        return C0;
}

double ModeloA::dTai(double* y, double t, ResolvedorEDO* r)
{
    double V = r->getPotencial(t);
    return C0*(k(V,y[_Tai_]) - y[_Tai_]);
}

double ModeloA::dTa(double* y, double t, ResolvedorEDO* r)
{
    double aux = E1(y,t,r);
    cout << y[_Tai_] - y[_Ta_] << endl;
    return E1(y,t, r)*(y[_Tai_] - y[_Ta_]);
}