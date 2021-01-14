#include "SimuladorTecido.h"
#include "command_line_args.h"
#include <chrono>

using namespace std;

int main (int argc, const char* argv[])
{


    // Funcao CommandLineArgs realiza a leitura de parametros da chamada da funcao.

    CommandLineArgs::init(argc,argv); 
    string entradaArquivo = CommandLineArgs::read("-f1","none");
    string entradaForca = CommandLineArgs::read("-f2","none");

    if( strcmp(argv[1],"-h") == 0 )
    {
        cout << "Uso: ./programa [parametros]" << endl;
        cout << "\t-b  viscosidade" << endl;
        cout << "\t-dt  espaco de tempo delta T" << endl;
       // cout << "\t-nx  numero de particulas na direcao x" << endl;
       // cout << "\t-ny  numero de particulas na direcao y" << endl;
        cout << "\t-f1 Arquivo da Malha" << endl;
        cout << "\t-f2 Arquivo da Forca" << endl;
        cout << "\t-tempo_total tempo de simulacao" << endl;
        cout << "\t-k  constante elastica" << endl;
        cout << "\t-d  Numero de dimensoes" << endl;
    //cout << "\t-indI  indice onde eh aplicada uma forca" << endl;
       // cout << "\t-t0  tempo inicial de aplicacao de forca" << endl;
      //  cout << "\t-t1  tempo final de aplicacao de forca" << endl;
      //  cout << "\t-g  gravidade" << endl;
        cout << "\t-m  massa das particulas" << endl;
        cout << "\t-vx  velocidade inicial em x" << endl;
        cout << "\t-vy  velocidade inicial em y" << endl;
        cout << "\t-metodo digitar numero que identifica metodo discreto de resolucao" << endl;
        exit(1);
    }

    // Funcoes de verificacao de entradas
    if(entradaArquivo == "none")
    {
        cout << "Uso: \n ./SimuladorTecido -f2 dados/modeloa1.txt -f1 dados/celula.txt  \n" << endl;
        exit(1);
    }
    if(entradaForca =="none")
    {
        cout << "Uso: \n ./SimuladorTecido -f2 dados/modeloa1.txt -f1 dados/celula.txt  \n" << endl;
        exit(1);
    }

    //Inicializa simulador
    SimuladorTecido st;

    //Chama a funcao de leitura dos arquivos de Malha e de entrada de forcas
    if(!st.leituraArquivos(entradaArquivo,entradaForca))
        exit(1);
    
    //Chamar funcao do simulador que inicializa sistema de particulas
    double m = CommandLineArgs::read("-m", 1.0);
    double vx = CommandLineArgs::read("-vx", 0.0);
    double vy = CommandLineArgs::read("-vy", 0.0);
    double k = CommandLineArgs::read("-k",100.0);
    double b = CommandLineArgs::read("-b", 5);
    int d = CommandLineArgs::read("-d", 2);
    //int metodo = CommandLineArgs::read("-metodo", 1);
    //int prevarea = CommandLineArgs::read("-prevArea", 1);

    //Parametros : densidade do elemento em x, densidade do elemento em y
    st.inicializaSistemaParticulas(m, vx, vy, k, b, d);
   //Utilize essa parte do codigo caso a integridade do arquivo de entrada precise ser verificada
    if(!st.verificadorArquivo())
        exit(1);
    else
        cout << "Consistencia do arquivo verificada. Arquivo está escrito corretamente." << endl;
    
    //Exportando Malha para arquivo .VTK
    //Inicializa variaveis de discretizacao e tempo total da simulacao
    double delta_t = CommandLineArgs::read("-dt",0.001);
    double tempo_total = CommandLineArgs::read("-tempo_total",600);

    //Configurando resolvedor de EDOs
    st.configuraResolvedor(delta_t, tempo_total, 0.0);
    st.avancaSimulacao();

    return 0;

}
