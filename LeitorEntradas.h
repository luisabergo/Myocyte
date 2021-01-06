#ifndef _leitor_entradas_h_
#define _leitor_entradas_h_

#include <string>
#include "SistemaParticulas.h"
#include "ResolvedorEDO.h"

using namespace std;

class LeitorEntradas
{
    public:
        LeitorEntradas();  //Funcao construtora do Leitor
        ~LeitorEntradas(); //Funcao destrutora do Leitor
        bool leituraMalha(string nomeArqMalha, SistemaParticulas* s); // Funcao que realiza leitura da malha e inicia variáveis do Sistema
        bool leituraForca(string nomeArqForca, ResolvedorEDO* r); // Funcao que realiza leitura das forcas aplicadas
        bool verificaConsistenciaArquivo(SistemaParticulas * s);//Funcao que verifica consistencia do arquivo de caracteres
    private:
};

#endif