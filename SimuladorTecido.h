#ifndef _simulador_tecido_h_
#define _simulador_tecido_h_


#include "ResolvedorEDO.h"
#include "SistemaParticulas.h"
#include "LeitorEntradas.h"
#include "ExportadorSaida.h"

class SimuladorTecido
{
    private:
        ResolvedorEDO* resolvedor;  // Ponteiro para classe que implementaa resolucao de EDOs atraves de metodos discretos
        SistemaParticulas* sistema; //Ponteiro para estrutura de dados que armazena variaveis do sistema
        LeitorEntradas* leitor;    //Ponteiro para classe que implementa leitor de entradas 
        ExportadorSaida* exportador; //Ponteiro para classe que implementa exportador de dados para VTK
    public:
        SimuladorTecido();   //Funcao construtora do Simulador
        ~SimuladorTecido(); //Funcao destrutora do Simulador
        //Funcao que implementa a chamada do leitor para os arquivos de malha e forca, retornando verdadeiro caso bem sucedido
        bool leituraArquivos(std::string nomeF1,std::string nomeF2); 
        //Inicializacao do Sistema de Particulas
        void inicializaSistemaParticulas(double m, double vx, double vy, double k, double b, int d);
        //Funcao que verifica consistencia do arquivo de malha de entrada
        bool verificadorArquivo();
        //Funcao que exporta um estado do sistema para arquivo em .VTK
        bool exportaEstadoSistema(int passo);
        //Funcao que configura o resolvedor das EDOs do sistema
        void configuraResolvedor(double det, double teto, double tei);
        void avancaSimulacao();
        
};

#endif