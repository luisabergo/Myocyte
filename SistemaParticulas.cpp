#include <iostream>
#include "SistemaParticulas.h"
#include "uteis.h"

using namespace std;

SistemaParticulas::SistemaParticulas()
{
    nx = 0;         // número de particulas na direcao x
    ny = 0;         // número de particulas na direcao y
    np = 0;         //numero total de particulas
    cmx =0;
    cmy =0;
    dimensoes = 2;   //Identifica se a simulacao seráum 2 ou 3 dimensoes
    tempo = 0.0;      // tempo
    fix = nullptr;
    matrizChar = nullptr;
    p = nullptr; // vetor de particulas
    tamEixoX = 0.0;

}

SistemaParticulas::~SistemaParticulas()
{
    if(matrizChar != nullptr)
    {
        for(int i=0; i<np; i++)
        {
            if(matrizChar[i] != nullptr)
                delete[] matrizChar[i];
        }
        delete[] matrizChar;
    }
    if(p != nullptr)
    {
        for(int i=0; i<np; i++)
        {
            if(p[i] != nullptr)
                delete[] p[i];
        }
        delete[] p;
    }
    if(fix!=nullptr)
        delete[] fix;
}

//Imprime matriz de caracteres
void SistemaParticulas::imprimeMatrizChar()
{
    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            for(int k=0; k<4; k++)
                cout << "Posicao [" << (j*nx)+i << "][" << k << "] = " << matrizChar[(j*nx)+i][k] << endl; 
        }
    }
}

//Inicializacao do Sistema de Particulas
void SistemaParticulas::init(double m1, double vx1, double vy1, double k1, double b1, int d1)
{
    cout << "--------------Inicializando criaćão do Sistema de Partículas--------------------" << endl;
    //Cria vetor de particulas e vetor de particulas fixas com tamanho igual ao numero de particulas
    dimensoes = d1;
    int indice = 0;
    p = new Particula*[np];
    fix = new int[np];
     for(int j=0; j<ny; j++)
    {
        for(int i=0; i<nx; i++)
        {
            indice = (j*nx)+i;
            p[indice] = new Particula[1];
            p[indice][0].setaParticula(m1, vx1, vy1, k1, b1, d1, i, j, indice);
        }
    }
    //inicializa massa ponderada por molas
	double massa_total =0;
    for(int i=0; i<nx; i++)
    {    for(int j=0; j<ny; j++)
        {      
            int ip = j*nx + i;
		    double mass =0;
            for(int k=0; k<4; k++)
            {
		        if(matrizChar[ip][k] == 'm')
			    mass++;

	        }

		    if(mass==4 || mass == 3)
			    p[ip][0].setMassa(0.1);
		    if(mass==2)
			    p[ip][0].setMassa(1);
		    if(mass==1)
			    p[ip][0].setMassa(2);
		    if(mass==0)
			    p[ip][0].setMassa(4);

            massa_total += p[ip][0].getMassa();

        }

    }

    for(int i=0; i<nx; i++)
    {   
            for(int j=0; j<ny; j++)
            {
                int ip = j*nx + i;
                p[ip][0].getvetorPosicaoat(0) = (double) i;
                p[ip][0].getvetorPosicaoat(1) = (double) j;
                cmx += p[ip][0].getvetorPosicaoat(0)*p[ip][0].getMassa();
                cmy += p[ip][0].getvetorPosicaoat(1)*p[ip][0].getMassa();
            }
    }


    cmx = cmx/massa_total;
    cmy = cmy/massa_total;
    cout << "Centro de massa: " << cmx << " , " << cmy << endl;


    ipLong[0] = 250;
    ipLong[1] = 297;
    tamEixoX = p[ipLong[1]][0].getvetorPosicaoat(0) - p[ipLong[0]][0].getvetorPosicaoat(0);
    cout << "-------------------Sistema de Partículas alocado com sucesso-----------------------" << endl;

    int idy = int(cmy/1);
    int idx = int(cmx/1);

    for(int j=0; j<ny; j++)
    {
        for(int i=0; i<nx; i++)
        {
            indice = (j*nx)+i;
            if((i==idx && j == idy) /*|| (i==idx+4 && j == idy+2)*/)
                fix[indice] = 1;
            else
                fix[indice] = 0;
        }
    }

}

//Funcoes gets e sets das variaveis
int SistemaParticulas::getNx()
{
    return nx;
}
void SistemaParticulas::setNx(int n)
{
    nx = n;
}

int SistemaParticulas::getNy()
{
    return ny;
}

void SistemaParticulas::setNy(int n)
{
    ny = n;
}

int SistemaParticulas::getNp()
{
    return np;
}

void SistemaParticulas::setNp(int n)
{
    np = n;
}

void SistemaParticulas::setT(int t)
{
    tempo = t;
}

double SistemaParticulas::getT()
{
    return tempo;
}

int* SistemaParticulas::getFix()
{
    return fix;
}

void SistemaParticulas::setFix(int* f)
{
    fix = f;
}

char** SistemaParticulas::getMat()
{
    return matrizChar;
}

double SistemaParticulas::getTamEixoX()
{
    return this->tamEixoX;
}
void SistemaParticulas::setTamEixoX(double t)
{
    tamEixoX = t;
}
int SistemaParticulas::getIpLong(int pos)
{
    return this->ipLong[pos];
}
void SistemaParticulas::setIpLong(int p, int pos)
{
    this->ipLong[pos] = p;
}

char SistemaParticulas::getMat(int indicePart, int indiceCaractere)
{
    //Verifica se indice é valido na matriz
    if(indiceCaractere>=0 && indiceCaractere<4 && indicePart >= 0 && indicePart < nx*ny)
        return matrizChar[indicePart][indiceCaractere];
    else
        return 'z';
}

void SistemaParticulas::setMat(char** Kmat)
{
    matrizChar = Kmat;
}

Particula** SistemaParticulas::getP2()
{
    return p;
}

Particula& SistemaParticulas::getP(int posicao1, int posicao2)
{
    return p[posicao1][posicao2];
}

void SistemaParticulas::calculaForcas(double tempo, double fat)
{
    int k2;
    double elas, visc;
    double *pos_dif = new double[2];
    double *vel_dif = new double[2];
    double forcaCalculada;

    double karea = 0.01;
    double Area, dcx, dcy;
    double *xb = new double[2]; //BARICENTRO
    double *base = new double[2];
    double *altura = new double[2];
    double *PontoA;
    double *PontoB;
    for(int i=0; i<nx; i++)
    {   
        for(int j=0; j<ny; j++)
        {
            int ip = j*nx + i;
            int c2, c3, c4;
            elas = p[ip][0].getElas();
            visc = p[ip][0].getCoefDamping();
            // zera forcas
            p[ip][0].setForca(0, 0.0);
            p[ip][0].setForca(1, 0.0);
            double norma;
            // loop nos vizinhos
            for(int k=0; k<8; k++) 
            {
                int in, jn;
                in = i + Viz[k][0];
                jn = j + Viz[k][1];
                int ipn = jn * nx + in;

                if (in <= -1 || in >= nx || jn <= -1 || jn >= ny) 
                {
                    continue;
                }
                // diferenca do vetor posicao
                double *pos_ip = p[ip][0].getvetorPosicao();
                double *pos_vz = p[ipn][0].getvetorPosicao();
                double l0;
                CalcDifVetor(pos_dif, pos_vz, pos_ip);

                norma = CalcNorma(pos_dif);
                // diferenca do vetor velocidade
                double prodVel;
                double *vel_ip = p[ip][0].getVetorVelocidade();
                double *vel_vz = p[ipn][0].getVetorVelocidade();
                CalcDifVetor(vel_dif, vel_vz, vel_ip);
                prodVel = CalcProdEscalar(vel_dif, pos_dif);
                // forca elastica               
                // guarda no f de cada particula
                // se for na diagonal eh raiz de 2
                if (k < 4) 
                {
                    l0 = 1;
                    if (k == 0) k2 = 1;
                    if (k == 1) k2 = 3;
                    if (k == 2) k2 = 0;
                    if (k == 3) k2 = 2;

                    if(matrizChar[ip][k2] == 'm')
                        elas = 0;
                    else
                    {
                            elas = 200;
                    }
                    
                    p[ip][0].somaForcaMola(0, -elas * (norma - l0) * pos_dif[0] / norma);
                    p[ip][0].somaForcaMola(1, -(44) * (norma - l0) * pos_dif[1] / norma);
                    
                } else 
                {
                    elas = 200;
                    l0 = sqrt(2.0);
                    p[ip][0].somaForcaMola(0, -(elas) * (norma - l0) * pos_dif[0] / norma);
                    p[ip][0].somaForcaMola(1, -(elas) * (norma - l0) * pos_dif[1] / norma);
                }
                //damping
                visc = 7000*sqrt(elas*p[ip][0].getMassa());
                p[ip][0].somaForcaMola(0 , -visc * (prodVel/norma) * (pos_dif[0]/norma));
                p[ip][0].somaForcaMola(1 , -visc * (prodVel/norma) * (pos_dif[1]/norma));
            }

            if(matrizChar[ip][1] == 'm')
                p[ip][0].somaForcaMola(0, -85*fat);
            if(matrizChar[ip][3] == 'm')
                p[ip][0].somaForcaMola(0, 85*fat);

            //Obtençao dos vértices da célula

            c2 = ip +1 ;
            c3 = (j+1)*nx + i;
            if(c2>=np || c3>=np)
            {   
                continue;
            }
            //calculo do baricentro do triangulo

            xb[0] = (p[ip][0].getvetorPosicaoat(0) +p[c2][0].getvetorPosicaoat(0) + p[c3][0].getvetorPosicaoat(0)) /3;
            xb[1] = (p[ip][0].getvetorPosicaoat(1) + p[c2][0].getvetorPosicaoat(1) + p[c3][0].getvetorPosicaoat(1)) /3;
            //cálculo da area de um triangulo
            PontoB = p[ip][0].getvetorPosicao();
            PontoA = p[c2][0].getvetorPosicao();
            CalcDifVetor(base, PontoA, PontoB);
            PontoB = p[ip][0].getvetorPosicao();
            PontoA = p[c3][0].getvetorPosicao();
            CalcDifVetor(altura, PontoA, PontoB);

            double normaBase = CalcNorma(base);
            double normaAltura = CalcNorma(altura);

            Area = normaAltura*normaBase/2;

            //Cálculo da força de preservação de volume

            //NOTE QUE ESSA FORCA DEVE SER APLICADA EM UMA LINHA EM DIRECAO AO BARICENTRO


            //Calculo do vetor que direciona uma linha do ponto ao baricentro
            PontoB =  p[ip][0].getvetorPosicao();
            PontoA = xb;
            CalcDifVetor(altura, PontoA, PontoB);
            norma = CalcNorma(altura);

            dcx = (altura[0])/norma;
            dcy = (altura[1])/norma;


            p[ip][0].somaForcaMola(0, -karea*Area*dcx);
            p[ip][0].somaForcaMola(1, -karea*Area*dcy);
        }
    }
    delete[] xb;
    delete[] base;
    delete[] altura;
    delete[] pos_dif;
    delete[] vel_dif;

}

int SistemaParticulas::getFix(int indice)
{
    return fix[indice];
}

void SistemaParticulas::imprimeSistema()
{
    for(int j=0; j<ny; j++)
    {
        for(int i=0; i<nx; i++)
        {
            int ip = j*nx +i;
            cout << " Particula x:" << p[ip][0].getvetorPosicaoat(0) << " y:" <<  p[ip][0].getvetorPosicaoat(1) ;
        }
    }   cout << endl;
}

void SistemaParticulas::setMedidaDeformacao(double md)
{
    medidaDeformacao = md;
}
double SistemaParticulas::getMedidaDeformacao()
{
    return this->medidaDeformacao;
}
void SistemaParticulas::setMedidaRetorno(double mr)
{
    medidaRetorno = mr;
}
double SistemaParticulas::getMedidaRetorno()
{
    return this->medidaRetorno;
}
void SistemaParticulas::setMedidaRot(double mr)
{
    medidaRot = mr;
}
double SistemaParticulas::getMedidaRot()
{
    return this->medidaRot;
}

double SistemaParticulas::medirDeformacao()
{
    double def =0;
    int ip=0;
    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            ip = j*nx+i;
            def += p[ip][0].getvetorPosicaoat(0) - i;
        }

    }
    if(def<0)
        def = -def;
    return def;
}

void SistemaParticulas::setMedidaDeformacaoEixo(double mde)
{
    medidaDeformacaoEixo = mde;
}
double SistemaParticulas::getMedidaDeformacaoEixo()
{
    return medidaDeformacaoEixo;
}

double SistemaParticulas::medirRotacao()
{
    double rot =0, r1, r2;
    int ip = ipLong[1];
    r1 = p[ip][0].getvetorPosicaoat(0) - 49;
    r2 = p[ip][0].getvetorPosicaoat(1) - 14;
    rot = r1*r2;
    if(rot<0)
        rot = -rot;
    return rot;
}
