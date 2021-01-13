#include "ResolvedorEDO.h"
#include "EulerExplicito.h"
#include "MetodoVerlet.h"
#include "BeemanMethod.h"
#include "MinimalModel.h"
#include "ModeloA.h"
#include <iostream>

ResolvedorEDO::ResolvedorEDO()
{ 
    matrizForcaAtiva = nullptr;
    modeloEletro = new MinimalModel();
    modeloT = new ModeloA();
    //metodo = new EulerExplicito();
    metodo = new MetodoVerlet();
    //metodo = new BeemanMethod();
}

ResolvedorEDO::~ResolvedorEDO()
{
    if(matrizForcaAtiva != nullptr)
    {
        for(int i=0; i<numLinhasForca; i++)
        {
            if(matrizForcaAtiva[i] != nullptr)
                delete[] matrizForcaAtiva[i];
        }
        delete[] matrizForcaAtiva;
    }
    delete metodo;
    delete modeloEletro;
    delete modeloT;
}

double ResolvedorEDO::getDeltaT()
{
    return delta_t;

}

void ResolvedorEDO::setDeltaT(double dt)
{
    delta_t = dt;
}

int ResolvedorEDO::getNumPassos()
{
    return num_passos;
}

void ResolvedorEDO::setNumPassos(int np)
{
    num_passos = np;
}
double ResolvedorEDO::getTempoT()
{
    return tempo_total;
}
void ResolvedorEDO::setTempoT(double tt)
{
    tempo_total = tt;
}
double ResolvedorEDO::getTempoI()
{
    return tempo_inicial;
}
void ResolvedorEDO::setTempoI(double ti)
{
    tempo_inicial = ti;
}
double** ResolvedorEDO::getMatrizForca()
{
    return matrizForcaAtiva;
}

void ResolvedorEDO::setMatrizForca(double** m)
{
    matrizForcaAtiva = m;
}

void ResolvedorEDO::imprimeMatrizForca()
{
    cout << "Imprime Matrz de For'cas" << endl;
    for(int i=0; i<numLinhasForca; i++)
    {
        for(int j=0; j<2; j++)
        {
            std::cout << "Posicao [" << i << "][" << j << "] = " << matrizForcaAtiva[i][j] << std::endl; 
        }
    }
}
int ResolvedorEDO::getNumLinhas()
{
    return numLinhasForca;
}
void ResolvedorEDO::setNumLinhas(int nl)
{
    numLinhasForca = nl;
}

void ResolvedorEDO::avanca(SistemaParticulas* sist, ExportadorSaida* exp)
{
    system("rm -rf saida/");
    system("mkdir saida/");
    exp->exportaVTKSistema(sist, 0);
    double t, fativa;
    modeloEletro->resolveModelo(this);
    ofstream arqSaida1, arqSaida2, arqSaida3, arqSaida4, arqSaida5, arqSaida6, arqSaida7, arqSaida8;
    arqSaida1.open("saida/No.out", std::ofstream::app);
    arqSaida2.open("saida/Energia.out", std::ofstream::app);
    arqSaida3.open("saida/Eixo.out", std::ofstream::app);
    arqSaida4.open("saida/Est.out", std::ofstream::app);
    arqSaida5.open("saida/DefTotal.out", std::ofstream::app);
    arqSaida6.open("saida/RotTotal.out", std::ofstream::app);
    arqSaida7.open("saida/phaseplan.out", std::ofstream::app);
    arqSaida8.open("saida/phaseplany.out", std::ofstream::app);

    for (int k=0; k<num_passos; k++)
    {  
        sist->setT(k*delta_t);
        t = sist->getT();
        if(k%50==0)
        {    
            fativa = matrizForcaAtiva[k/50][1];
            //cout << "Tempo " << t << " Matriz " << fativa << endl;
        }
        if(k%1000==0)
            cout << "Tempo " << t << endl;
        sist->calculaForcas(t, fativa);
        metodo->avanca(k,sist, delta_t);
        if(t==168)
        {
            sist->setMedidaDeformacao(sist->medirDeformacao());
            sist->setMedidaDeformacaoEixo(sist->getTamEixoX());
            sist->setMedidaRot(sist->medirRotacao());
        }
        if(t==599)
        {
            sist->setMedidaRetorno(sist->medirDeformacao());
        }
        if(k%1000 == 0)
            exp->exportaVTKSistema(sist, k);
        exp->salvaEnergia(sist, arqSaida2, k);
        exp->salvaNo(sist, 0, k, arqSaida1, arqSaida7, arqSaida8);
        exp->salvaEixo(sist, arqSaida3, k);
        exp->salvaDeformacaoTotal(sist, arqSaida5, k);
        exp->salvaRotacao(sist, arqSaida6, k);
    }
    exp->salvaEst(sist, arqSaida4, delta_t);
    arqSaida1.close();
    arqSaida2.close();
    arqSaida3.close();
    arqSaida4.close();
    arqSaida5.close();
    arqSaida6.close();
    arqSaida7.close();
    arqSaida8.close();
}

void ResolvedorEDO::calculaForcaAtiva()
{
    modeloEletro->resolveModelo(this);
}