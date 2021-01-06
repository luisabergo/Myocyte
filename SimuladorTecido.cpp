#include "SimuladorTecido.h"
#include "SistemaParticulas.h"

using namespace std;

//Funcao construtora do Simulador
SimuladorTecido::SimuladorTecido()
{
    sistema = new SistemaParticulas();  // Inicializa e aloca dinamicamente uma instancia do sistema de particulas
    leitor = new LeitorEntradas();   // Inicializa e aloca dinamicamente uma instancia do leitor de entradas
    exportador = new ExportadorSaida();//Inicializa e aloca dinamicamente uma instancia do exportador de saidas
    resolvedor = new ResolvedorEDO(); //Inicializa e aloca dinamicamente uma instancia do Resolvedor de EDOs do Sistema
}

//Funcao destrutora do Simulador
SimuladorTecido::~SimuladorTecido()
{

    delete leitor;   // Chama destrutor de classe de leitor de entradas
    delete sistema; // Chama destrutor de classe de sistema de particulas
    delete exportador; // Chama destrutor de classe de exportador de saidas
    delete resolvedor;// Chama destrutor de classe de Resolvedor de EDOs do Sistema

}

//Funcao que implementa a chamada do leitor para os arquivos de malha e forca, retornando verdadeiro caso bem sucedido
bool SimuladorTecido::leituraArquivos(std::string nomeF1,std::string nomeF2)
{
    if(leitor->leituraMalha(nomeF1, sistema) && leitor->leituraForca(nomeF2, resolvedor))
        return true;
    else
        return false; 
}

 //Inicializacao do Sistema de Particulas
void SimuladorTecido::inicializaSistemaParticulas(double m, double vx, double vy, double k, double b, int d)
{
    //Chamar parametros necessarios
    sistema->init(m, vx, vy, k, b, d);
}
//Funcao que verifica consistencia do arquivo de malha de entrada
bool SimuladorTecido::verificadorArquivo()
{
    if(leitor->verificaConsistenciaArquivo(sistema))
        return true;
    else
        return false;
}
//Funcao que exporta um estado do sistema para arquivo em .VTK
bool SimuladorTecido::exportaEstadoSistema(int passo)
{
    if(exportador->exportaVTKSistema(sistema, passo))
        return true;
    else
        return false;
    
}
//Funcao que configura o resolvedor das EDOs do sistema
void SimuladorTecido::configuraResolvedor(double det, double teto, double tei)
{
    resolvedor->setDeltaT(det);
    resolvedor->setNumPassos(teto/det);
    resolvedor->setTempoT(teto);
    resolvedor->setTempoI(tei);
}

void SimuladorTecido::avancaSimulacao()
{
    resolvedor->avanca(sistema, exportador);
}