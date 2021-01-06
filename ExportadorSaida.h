#ifndef _exportador_tecido_h_
#define _exportador_tecido_h_

#include "SistemaParticulas.h"
#include <fstream>


class ExportadorSaida
{
    public:
        ExportadorSaida();
        ~ExportadorSaida();
        bool exportaVTKSistema(SistemaParticulas* s, int num_passo);
        void salvaNo(SistemaParticulas * s, int I, int num_passo,ofstream & f);
        void salvaEnergia(SistemaParticulas * s, ofstream & arqSaida, int num_passo);
        void salvaEixo(SistemaParticulas * s, ofstream & arqSaida, int num_passo);
        void salvaEst(SistemaParticulas * s, ofstream & arqSaida, double dt);
        void salvaRotacao(SistemaParticulas * s, ofstream & arqSaida,int num_passo);
        void salvaDeformacaoTotal(SistemaParticulas * s, ofstream & arqSaida,int num_passo);
};

#endif