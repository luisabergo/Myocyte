#include <iostream>
#include "Particula.h"

using namespace std;

Particula::Particula()
{
    massa = 0.0;
    elas = 0.0;
    indiceParticula = 0.0;
    vetorPosicao = NULL;
    auxVetorPosicao = NULL;
    vetorVelocidade = NULL;
    vetorForca = NULL;
    comprimentoInicial = NULL;
    coefDamping = 0.0; // constante de atrito - viscoelastica - damping

}
//Funcao que seta principais parametros da particula. Alteracao->> Escrever velocidade como double* v
void Particula::setaParticula(double m, double vx, double vy, double k, double b, int d, int idI, int idJ, int ip)
{   
    massa = m;
    elas = k;
    indiceParticula = ip;
    vetorPosicao = new double[2];
    auxVetorPosicao = new double[2];
    vetorVelocidade = new double[2];
    vetorForca = new double[2];
    comprimentoInicial = new double[2];
    aceleracao = new double[2];
    auxAceleracao = new double[2];
    ///CASO HAJA ADAPTACAO PARA 3D ALTERAR ESSA FUNCAO DE INICIALIZACAO 
    vetorPosicao[0] = idI;
    vetorPosicao[1] = idJ;
    aceleracao[0] = 0;
    aceleracao[1] = 0;
    auxVetorPosicao[0] = 0.0;
    auxVetorPosicao[1] = 0.0;
    vetorVelocidade[0] = 0.0;
    vetorVelocidade[1] = 0.0;
    vetorForca[0] = 0.0;
    vetorForca[1] = 0.0;
    comprimentoInicial[0] = 0.0;
    comprimentoInicial[1] = 0.0;
    coefDamping = b; // constante de atrito - viscoelastica - damping
}

Particula::~Particula()
{
    delete[] vetorPosicao;
    delete[] auxVetorPosicao;
    delete[] vetorVelocidade;
    delete[] vetorForca;
    delete[] comprimentoInicial;
    delete[] aceleracao;
    delete[] auxAceleracao;
}

double Particula::getMassa()
{
    return this->massa;

}

void Particula::setMassa(double m)
{
    massa = m;
}

double Particula::getElas()
{
    return this->elas;
}

void Particula::setElas(double e)
{
    elas = e;
}

double Particula::getCoefDamping()
{
    return this->coefDamping;
}

void Particula::setCoefDamping(double cd)
{
    coefDamping = cd;
}

double* Particula::getvetorPosicao() const
{
    return vetorPosicao;
}

double& Particula::getvetorPosicaoat(int posicao) const
{
    return this->vetorPosicao[posicao];
}

void Particula::setvetorPosicao(double* vP)
{
    vetorPosicao = vP;
}
void Particula::setvetorPosicao2(int posicao, double valor)
{
    vetorPosicao[posicao] = valor;
}

double* Particula::getAuxVetorPosicao() const
{
    return this->auxVetorPosicao;
}

double& Particula::getAuxVetorPosicaoat(int posicao) const
{
    return this->auxVetorPosicao[posicao];
}

void Particula::setAuxVetorPosicao(double* aVP)
{
    this->auxVetorPosicao = aVP;
}

void Particula::setAuxVetorPosicao2(int posicao, double valor)
{
    this->auxVetorPosicao[posicao] = valor;
}

double* Particula::getVetorVelocidade()
{
    return this->vetorVelocidade;
}
double Particula::getvetorVelocidadeat(int posicao)
{
    return this->vetorVelocidade[posicao];
}
void Particula::setVetorVelocidade(double* v)
{
    vetorVelocidade = v;
}
void Particula::setvetorVelocidade(int posicao, double valor)
{
    vetorVelocidade[posicao] = valor;
}

double* Particula::getAceleracao()
{
    return this->aceleracao;
}

double Particula::getAceleracao(int posicao)
{
    return this->aceleracao[posicao];
}
void Particula::setAceleracao(double* v)
{
    aceleracao = v;
}
void Particula::setAceleracao(int posicao, double valor)
{
    aceleracao[posicao] = valor;
}
double* Particula::getAuxAceleracao()
{
    return this->auxAceleracao;
}
double Particula::getAuxAceleracao(int posicao)
{
    return this->auxAceleracao[posicao];
}
void Particula::setAuxAceleracao(double* v)
{
    auxAceleracao = v;
}
void Particula::setAuxAceleracao(int posicao, double valor)
{
    auxAceleracao[posicao] = valor;
}

double* Particula::getVetorForca()
{
    return this->vetorForca;
}
double& Particula::getvetorForcaat(int posicao)
{
    return this->vetorForca[posicao];
}
void Particula::setVetorForca(double* vF)
{
    vetorForca = vF;
}
double* Particula::getComprimentoInicial()
{
    return this->comprimentoInicial;
}
double Particula::getComprimentoInicialat(int posicao)
{
    return this->comprimentoInicial[posicao];
}
void Particula::setComprimentoInicial(double* ci)
{
    comprimentoInicial = ci;
}

void Particula::setForca(int posicao, double valor)
{
    vetorForca[posicao] = valor;
}

void Particula::somaForcaMola(int posicao, double valor)
{
    this->setForca(posicao, this->getvetorForcaat(posicao) + valor);
}

void Particula::imprimePosicao()
{
    
    cout << "x:" << vetorPosicao[0] << " e y:" << vetorPosicao[1] <<  endl;
}

void Particula::imprimeForcaMola()
{
    cout << "x:" << vetorForca[0] << " e y:" << vetorForca[1] <<  endl;
}