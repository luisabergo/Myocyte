#ifndef _sistemaparticulas_h_
#define _sistemaparticulas_h_

#include "Particula.h"

using namespace std;

class SistemaParticulas
{
    private:
        int nx;         // número de particulas na direcao x
        int ny;         // número de particulas na direcao y
        int np;         //numero total de particulas
        int dimensoes;   //Identifica se a simulacao seráum 2 ou 3 dimensoes
        double tempo;      // tempo
        double cmx;
        double cmy;
        int *fix;
        char** matrizChar;
        double tamEixoX;
        double medidaDeformacao;
        double medidaDeformacaoEixo;
        double medidaRetorno;
        double medidaRot;
        int ipLong[2];
        Particula** p; // vetor de particulas

        const int Viz[8][2] = { {+1,0}, // direita  0
                        {-1,0}, // esquerda 1
                        {0,+1}, // Acima 2
                        {0,-1}, //Abaixo  3
                        {+1,+1},//Diagonal acima direita  4
                        {-1,+1}, //Diagonal acima esquerda 5
                        {+1,-1},//Diagonal abaixo esquerda 6
                        {-1,-1},//Diagonal abaixo direita 7
                    };
                    
    public:
        SistemaParticulas();
        ~SistemaParticulas();
        //Imprime matriz de caracteres
        void imprimeMatrizChar();
        //Inicializa sistema de particulas ->> inserir parametros
        void init(double m1, double vx1, double vy1, double k1, double b1, int d1);
        //Funcao retorna numero de particulas na direcao x do sistema
        int getNx();
        //Funcao seta numero de particulas na direcao x do sistema
        void setNx(int n);
        //Funcao retorna numero de particulas na direcao y do sistema
        int getNy();
        //Funcao seta numero de particulas na direcao y do sistema
        void setNy(int n);
        //Funcao retorna numero de particulas total do sistema
        int getNp();
        //Funcao seta numero de particulas total do sistema
        void setNp(int n);
        //Funcao seta tempo total do sistema
        void setT(int t);
        //Funcao retorna tempo total do sistema
        double getT();
        //Funcao retorna vetor de particulas fixas do sistema
        int getFix(int indice);
        int* getFix();
        //Funcao seta vetor de particulas fixas do sistema
        void setFix(int* f);
        //Funcao retorna matriz de caracteres do sistema
        char** getMat();
        char getMat(int indicePart, int indiceCaractere);
        //Funcao seta matriz de caracteres do sistema
        void setMat(char** Kmat);
        //Funcoes que retornam vetor de particulas do sistema
        double getTamEixoX();
        void setTamEixoX(double t);
        int getIpLong(int pos);
        void setIpLong(int p, int pos);

        void setMedidaDeformacao(double md);
        double getMedidaDeformacao();

        void setMedidaRetorno(double mr);
        double getMedidaRetorno();

        void setMedidaRot(double mr);
        double getMedidaRot(); 

        void setMedidaDeformacaoEixo(double mde);
        double getMedidaDeformacaoEixo();
        
        Particula** getP2();
        Particula& getP(int posicao1, int posicao2);
        void calculaForcas(double tempo, double fativa);
        void imprimeSistema();
        double medirDeformacao();
        double medirRotacao();


};

#endif