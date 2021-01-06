#include "LeitorEntradas.h"
#include "ResolvedorEDO.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

LeitorEntradas::LeitorEntradas()
{

}

// Funcao que realiza leitura da malha e inicia variáveis do Sistema
bool LeitorEntradas::leituraMalha(string nomeArqMalha, SistemaParticulas* s)
{
    ifstream arquivoMalha;
    int NX,NY, NP;
    char** auxMatrizChar;
    arquivoMalha.open(nomeArqMalha.c_str());   //Abre o arquivo de malha
    //
    // Checar arquivos
    //
    if (!arquivoMalha)
    {    
        cout << "Arquivo de malhas não encontrado" << endl;
        return false;
    } else 
    cout << "Arquivo de malha pronto para leitura" << endl;
    
    // Leitura e armazenamento quantidade de linhas e colunas na entrada
    arquivoMalha >> NX >> NY ;
    NP = NX*NY;
    s->setNp(NP);
    cout << "Malha lida possui NX NY" << endl;
    // Armazenamento da quantidade de células em cada elemento.
    //s->setNx((2*NX)+1);
    //s->setNy((2*NY)+1);
    s->setNx(NX);
    s->setNy(NY);
    cout << s->getNx() << "\t" << s->getNy() << endl;
    cout << "Total de Partículas: " << s->getNp() << endl;

    //Alocando Memória para matriz auxiliar que irá armazenar caracteres da entrada
    auxMatrizChar = new char*[NP];
    for(int i=0; i<NP; i++)
    {
        auxMatrizChar[i] = new char[4];
    }
    //Leitura dos caracteres para matriz do sistema 
    for(int j=NY-1; j>=0; j--)
    {
        for (int i=0; i<NX; i++)
        {   
            int ip = (j)*NX +i;

            for (int k=0; k<4; k++)
            { 
                arquivoMalha >> auxMatrizChar[ip][k];
                //cout << auxMatrizChar[ip][k] << endl;
            }
        }
    }
    //Setando matriz auxiliar a matriz do sistema
    s->setMat(auxMatrizChar);
    //Fechando arquivo de entrada
    arquivoMalha.close();
    //Imprime teste caso seja necessario alguma checagem
    //s->imprimeMatrizChar();
    return true;
}

// Funcao que realiza leitura das forcas aplicadas
bool LeitorEntradas::leituraForca(string nomeArqForca, ResolvedorEDO* r)
{
    ifstream arquivoForca;
    int numLinhas;
    arquivoForca.open(nomeArqForca.c_str());   //Abre o arquivo de malha
    //
    // Checar arquivos
    //
    if (!arquivoForca)
    {    
        cout << "Arquivo de forcas não encontrado" << endl;
        return false;
    } else 
    cout << "Arquivo de forcas pronto para leitura" << endl;

    arquivoForca >> numLinhas;
    r->setNumLinhas(numLinhas);
    double** matF = new double*[numLinhas];

    for(int i=0; i<numLinhas; i++)
    {
        matF[i] = new double[2];
        arquivoForca >> matF[i][0] >> matF[i][1] ;
    }
    r->setMatrizForca(matF);
    //Funcao para imprimir e verificar arquivo de entrada
    //r->imprimeMatrizForca();
    cout << "Leitura e alocacao de forcas concluido" << endl;
    arquivoForca.close();
    return true;
}

//Funcao que verifica consistencia do arquivo de entrada
bool LeitorEntradas::verificaConsistenciaArquivo(SistemaParticulas * s)
{
    /*    Matriz de Caracteres indica:
        m - Se não há volumes na direćao indicada
        c - Se existe volume na direcao indicada

                            matrizChar[ip][0]
                                    XXX
    matrizChar[ip][3]               XXX       matrizChar[ip][1]
                                    XXX 
                            matrizChar[ip][2]

    Esta funcao indica se os valores das celulas vizinhas indicam a mesma informacao vistos de cima e da direita

                                matrizChar[ip_viz_cima][0]
                                    XXX
    matrizChar[ip][3]               XXX       matrizChar[ip][1]
                                    XXX 
                                matrizChar[ip][2]

                                matrizChar[ip][0]                                 matrizChar[ip_viz_dirt][0]
    matrizChar[ip][3]               XXX       matrizChar[ip][1]   matrizChar[ip][3]       XXX          matrizChar[ip_viz_dirt][1] 
                                    XXX                                                   XXX
                                    XXX                                                   XXX
                                matrizChar[ip][2]                                   matrizChar[ip_viz_dirt][2]
    */
    cout << "Verificando consistencia do arquivo" << endl;
    //verifica consistencia do arquivo
    int ip =0, ip_viz_cima=0, ip_viz_dirt=0;    // Variaveis que guardam indice da particula e indice de seu vizinho de cima e da direita
    bool t_viz_cima = false, t_viz_dirt = false;        //Variaveis booleanas auxiliares da funcao

    // Looping que percorre sistema em x, y e nos 4 vizinhos
    for (int i=0; i<s->getNx()-1; i++)
    {
        for(int j=0; j<s->getNy()-1; j++)
        {
            for (int k = 0; k < 4; k++) 
            {

                ip = (j * s->getNx()) + i;  // Calcula indice da particula
                ip_viz_dirt = (j * s->getNx()) + i+1;
                ip_viz_cima = ((j + 1) * s->getNx() )+ i;
                //cout << ip << endl;
                t_viz_cima = (s->getMat(ip, 0) != s->getMat(ip_viz_cima, 2));//Verifica consistencia de celula atual com vizinho de cima
                //cout << s->getMat(ip, 0)  << endl;
                //cout << s->getMat(ip_viz_cima, 2) << endl;
                t_viz_dirt = (s->getMat(ip, 1) != s->getMat(ip_viz_dirt, 3));//Verifica consistencia de celula atual com vizinho da direita

                if (t_viz_cima || t_viz_dirt) {
                    cout << "arquivo inconsistente" << endl;
                    cout << i << " " << j << " " << k << endl;
                    return false;
                }

            }
        }
    }
    return true;
}

LeitorEntradas::~LeitorEntradas()
{

}