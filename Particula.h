#ifndef _particula_h_
#define _particula_h_

class Particula
{
    private:
        int indiceParticula; 
        double massa;    // massa
        double elas; //constante elastica - lei de hooke
        double coefDamping; // constante de atrito - viscoelastica - damping
        double* vetorPosicao; // posicao
        double* auxVetorPosicao; // posicao temporaria para calculo de AvancaVerlet
        double* vetorVelocidade; // velocidade
        double* vetorForca; // forcas
        double* comprimentoInicial;
        double* aceleracao;
        double* auxAceleracao;
    public:
        Particula();
        void setaParticula(double m, double vx, double vy, double k, double b, int d, int idI, int idJ, int ip);
        ~Particula();
        // Gets e Sets da classe
        double getMassa();
        void setMassa(double m);

        double getElas();
        void setElas(double e);

        double getCoefDamping();
        void setCoefDamping(double cd);

        double* getvetorPosicao() const;
        double& getvetorPosicaoat(int posicao) const;
        void setvetorPosicao(double* vP);
        void setvetorPosicao2(int posicao, double valor);

        double* getAuxVetorPosicao() const;
        double& getAuxVetorPosicaoat(int posicao) const;
        void setAuxVetorPosicao(double* aVP);
        void setAuxVetorPosicao2(int posicao, double valor);

        double* getVetorVelocidade();
        double getvetorVelocidadeat(int posicao);
        void setVetorVelocidade(double* v);
        void setvetorVelocidade(int posicao, double valor);

        double* getAceleracao();
        double getAceleracao(int posicao);
        void setAceleracao(double* v);
        void setAceleracao(int posicao, double valor);

        double* getAuxAceleracao();
        double getAuxAceleracao(int posicao);
        void setAuxAceleracao(double* v);
        void setAuxAceleracao(int posicao, double valor);

        double* getVetorForca();
        double& getvetorForcaat(int posicao);
        void setVetorForca(double* vF);
        void setForca(int posicao, double valor);
        void somaForcaMola(int posicao, double valor);
        void imprimeForcaMola();

        double* getComprimentoInicial();
        double getComprimentoInicialat(int posicao);
        void setComprimentoInicial(double* ci);

        void imprimePosicao();
};

#endif