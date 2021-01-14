#include "SistemaParticulas.h"
#include "ExportadorSaida.h"
#include "MetodoAvanca.h"

class ModeloTensao;
class ModeloEletrofisiologico;

#ifndef _resolvedor_edo_h_
#define _resolvedor_edo_h_



class ResolvedorEDO
{
    public:
        ResolvedorEDO();
        ~ResolvedorEDO();
        double getPotencial(double t);
        double getDeltaT();
        void setDeltaT(double dt);
        int getNumPassos();
        void setNumPassos(int np);
        double getTempoT();
        void setTempoT(double tt);
        double getTempoI();
        void setTempoI(double ti);
        double** getMatrizForca();
        void setMatrizForca(double** m);
        void imprimeMatrizForca();
        int getNumLinhas();
        void setNumLinhas(int nl);
        void avanca(SistemaParticulas* s, ExportadorSaida* exp);
        void calculaForcaAtiva();
    private:
        double delta_t;
        int num_passos;
        double tempo_total;
        double tempo_inicial;
        double** matrizForcaAtiva; // Matriz com força ativa por unidade discretizada matriz[Npassos][2] primeira coluna tempo, segunda força
        int numLinhasForca;
        double* potencial;
        MetodoAvanca* metodo;
        ModeloEletrofisiologico* modeloEletro;
        ModeloTensao* modeloT;

        
};

#endif