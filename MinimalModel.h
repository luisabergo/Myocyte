#ifndef _minimal_model_h_
#define _minimal_model_h_

#include "ModeloEletrofisiologico.h"
#include "ResolvedorEDO.h"

class MinimalModel : public ModeloEletrofisiologico
{
    public:
        MinimalModel();
        ~MinimalModel();
        double H(double x, double y);
        double vnoinf(double x, double y);
        void normaliza_u();
        void resolveModelo(ResolvedorEDO* r);
        void grava_matriz(ResolvedorEDO* r);
    private:
    //PARAMETROS AJUSTADOS AO PROBLEMA
        double u0;
        double uu;
        double thetav;
        double thetaw;
        double thetavlinha;
        double theta0;
        double tauv1;
        double tauv2;
        double tauvmais;
        double tauw1;
        double tauw2;
        double kw;
        double uw;
        double tauwmais;
        double taufi;
        double tau01;
        double tau02;
        double taus01;
        double taus02;
        double kso;
        double uso;
        double taus1;
        double taus2;
        double ks;
        double us;
        double tausi;
        double tauwinf;
        double winfstar;   
    //ALOCACAO DAS SOLUCOES DA EDO
        double udef[12000];
        double vdef[12000];
        double wdef[12000];
        double sdef[12000];
        double tdef[12000];
    // DISCRETIZACAO 
        double HT;
};

#endif