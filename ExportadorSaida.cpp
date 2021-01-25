#include "ExportadorSaida.h"
#include <fstream>
#include <iostream>
#include <string>
#include "SistemaParticulas.h"
#include "uteis.h"

using namespace std;

ExportadorSaida::ExportadorSaida()
{

}

bool ExportadorSaida::exportaVTKSistema(SistemaParticulas * s, int num_passo)
{
    int NX = s->getNx();
    int NY = s->getNy();
   // cout << "Exportando Malha para arquivo .vtk" << endl;
   // cout << "Apagando arquivos VTK" << endl;
    ofstream arqSaida;
    char nomeArqSaida[256];
    sprintf(nomeArqSaida, "saida/SistemaParticulas%d.vtk", num_passo);
    arqSaida.open(nomeArqSaida, std::ofstream::out);
    if(!arqSaida) 
    { 
        cout << "Arquivo não pode ser aberto para saída\n";
        return false;
    }
    arqSaida << "# vtk DataFile Version 2.0" << endl;
    arqSaida << "Result" << endl;
    arqSaida << "ASCII" << endl;
    arqSaida << "DATASET UNSTRUCTURED_GRID" << endl;
    arqSaida << "POINTS " << NX*NY << " float " << endl;
    for(int j=0; j<NY; j++)
    {   
        for (int i=0; i<NX; i++)
        {
            {    
                int ip = j*NX + i;
                arqSaida << scientific << s->getP(ip,0).getvetorPosicaoat(0) << " " << s->getP(ip,0).getvetorPosicaoat(1) << " " << 0.0 << endl;
            }
        }
    }
    int ncells = (NX-1)*NY + NX*(NY-1);
    // quantidade de molas transversais : 
    int cellstr = ((NX-1)*(NY-1))*2;
    ncells = ncells + cellstr;
    int i, j;
    int nmolar=0;
    int nmolad =0;
    //verificando existencia das molas 
    for(i=0; i<NX ; i++)
    {
        for(j=0; j<NY; j++)
        {
            int ip = j*NX + i;
            for(int k=0 ; k<4 ; k++)
            {
                if( (i==0 && k==3) || (i==NX-1 && k==1) || (j==0 && k==2) || (j==NY-1 && k==0))
                {  
                    continue;
                }else
                {
                    if(s->getMat(ip, k) == 'm' && (k==0||k==1))
                    { 
                        ncells--;
                    }
                }
            }
        }
    }
for(i=0; i<NX; i++)
    {  
        for(j=0; j<NY; j++)
        {
            bool condicao1 = false;
            bool condicao2 = false;
            bool condicao3 = false;
            bool condicao4 = false;
            int ip = j*NX+i;
            int ip2 = (j+1)*NX+(i+1);

            //diagonal1
            if(s->getMat(ip, 0) != 'm' ) 
                condicao1 = true;
            if(s->getMat(ip, 1) != 'm' ) 
                condicao2 = true;
            if(s->getMat(ip2, 2) != 'm' ) 
                condicao3 = true;
            if(s->getMat(ip2, 3) != 'm' ) 
                condicao4 = true;
            if(i!=NX-1 && j!=NY-1 && condicao1 && condicao2 && condicao3 && condicao4 )
                nmolad++;
            condicao1 = false;
            condicao2 = false;
            condicao3 = false;
            condicao4 = false;

            int ip3 = (j-1)*NX+(i+1);
            //diagonal2
            if(s->getMat(ip, 1) != 'm') 
                condicao1 = true;
            if(s->getMat(ip, 2) != 'm') 
                condicao2 = true;
            if(j!=0)
            {
                if(s->getMat(ip3, 0) != 'm') 
                    condicao3 = true;
                if(s->getMat(ip3, 3) != 'm') 
                    condicao4 = true;
            }
        
            if(i!=NX-1 && j!=0 && condicao1 && condicao2 && condicao3 && condicao4)
                nmolad++;


        }
    }

    ncells = ncells - (cellstr-nmolad);

    //cout << "NCELLS=" << ncells << endl;
    arqSaida << "\nCELLS " << ncells << " " << 3*ncells << endl;
    nmolad = nmolar = 0;
    //escreve molas 
    for(i=0; i<NX-1; i++)
    {  
        for(j=0; j<NY-1; j++)
        {
            int ip = j*NX+i;
            int ip2 = (j+1)*NX+(i+1);
            int ip3 = j*NX+(i+1);
            int ip4 = (j+1)*NX+i;
            //vertical
            if(s->getMat(ip, 0) != 'm' && s->getMat(ip4, 2) != 'm')
            {
                arqSaida << "2 " << ip << " " << ip4  << "\n";
                nmolar++;
            }

            //horizontal
            if(s->getMat(ip, 1)!= 'm' && s->getMat(ip3, 3)!= 'm')
            {
                arqSaida << "2 " << ip << " " << ip3 << "\n";
                nmolar++;
            }
        }

    //horizontal
        int ip = j*NX+i;
        int ip3 = j*NX+(i+1);
        if(s->getMat(ip, 1)!= 'm' && s->getMat(ip3, 3)!= 'm')
        { 
            arqSaida << "2 " << ip << " " << ip3 << "\n";
            nmolar++;
        }
    }
    
    for(j=0; j<NY-1; j++)
    {  
        int ip2 = (j+1)*NX+i;
        int ip = j*NX+i;
        //vertical
        if(s->getMat(ip, 0) != 'm' && s->getMat(ip2, 2)!= 'm')
        {
            arqSaida << "2 " << ip << " " << ip2 << "\n";
            nmolar++;
        }   
    }
    
//escreve molas diagonais
    for(i=0; i<NX; i++)
    {  
        for(j=0; j<NY; j++)
        {   
            bool condicao1 = false;
            bool condicao2 = false;
            bool condicao3 = false;
            bool condicao4 = false;
            int ip = j*NX+i;
            int ip2 = (j+1)*NX+(i+1); 
            //diagonal1
            if(s->getMat(ip, 0) != 'm') 
                condicao1 = true;
            if(s->getMat(ip, 1) != 'm') 
                condicao2 = true;
            if(s->getMat(ip2, 2) != 'm') 
                condicao3 = true;
            if(s->getMat(ip2, 3) != 'm') 
                condicao4 = true;

            if(j!=NY-1 && i!=NX-1 && condicao1 && condicao2 && condicao3 && condicao4)
            {  arqSaida << "2 " << ip << " " << ip2  << "\n";
                nmolad++;}

            condicao1 = false;
            condicao2 = false;
            condicao3 = false;
            condicao4 = false;


            int ip3 = (j-1)*NX+(i+1);
            //diagonal2
            if(s->getMat(ip,1) != 'm') 
                condicao1 = true;
            if(s->getMat(ip, 2)!= 'm') 
                condicao2 = true;
            if(j!=0)
            {
                if(s->getMat(ip3, 0) != 'm') 
                    condicao3 = true;
                if(s->getMat(ip3, 3) != 'm') 
                    condicao4 = true;
            }
            
            if(i!=NX-1 && j!=0 && condicao1 && condicao2 && condicao3 && condicao4)
            {   arqSaida << "2 " << ip<< " " << ip3 << "\n";
                nmolad++;}

        }
    }

    //cout <<"MOLAS R E MOLAS DIAG:"  << nmolar << " " << nmolad << endl;

    nmolad = ncells - nmolar;

    arqSaida << "\nCELL_TYPES " << ncells << endl;
    for(int i=0; i<ncells; i++)
        arqSaida << "3\n";

    arqSaida << "\nCELL_DATA " << ncells << endl;
    arqSaida << "SCALARS tipo int 1" << endl;
    arqSaida << "LOOKUP_TABLE default" << endl;
    for(int i=0; i<nmolar; i++)
        arqSaida << "0\n";
    for(int i=0; i<nmolad; i++)
        arqSaida << "1\n";
    
    arqSaida.close();
    //cout << "Arquivo .vtk escrito. Exportacao finalizada." << endl;
    return true;
}

//------------------------------------------------------------------------
void ExportadorSaida::salvaEnergia(SistemaParticulas * s, ofstream & arqSaida, int num_passo)
{
    int NX = s->getNx();
    int NY = s->getNy();
    int NP = s->getNp();
    double Ecin=0;
    double Prod;

    if(!arqSaida) 
    { 
        cout << "Arquivo não pode ser aberto para saída\n";
    }
    
    arqSaida <<  s->getT() << " ";

    for (int ip=0; ip<NP; ip++)
    {   
        double *v = s->getP(ip, 0).getVetorVelocidade();
        Prod = CalcProdEscalar(v,v);
        Ecin += 0.5 * s->getP(ip, 0).getMassa()*Prod;
    } 
    
    arqSaida << Ecin << endl;
}

void ExportadorSaida::salvaNo(SistemaParticulas * s, int I, int num_passo,ofstream & f)
{   
    int NX = s->getNx();
    int NY = s->getNy();
    int NP = s->getNp();

    if(!f) 
    { 
        cout << "Arquivo não pode ser aberto para saída\n";
    }
    
    f <<  s->getT() << " ";

    for (int ip=0; ip<NP; ip++)
    {   
        if(ip==I)
		f << s->getP(ip, 0).getvetorPosicaoat(0) << " "  << s->getP(ip, 0).getvetorPosicaoat(1)  << endl; 
    } 

}

void ExportadorSaida::salvaEixo(SistemaParticulas * s, ofstream & arqSaida, int num_passo)
{
    arqSaida <<  s->getT() << " ";
    arqSaida << s->getTamEixoX() << endl;
}

ExportadorSaida::~ExportadorSaida()
{

}

void ExportadorSaida::salvaRotacao(SistemaParticulas * s, ofstream & arqSaida,int num_passo)
{
    arqSaida <<  s->getT() << " ";
    arqSaida << s->medirRotacao() << endl;

}

void ExportadorSaida::salvaDeformacaoTotal(SistemaParticulas * s, ofstream & arqSaida,int num_passo)
{
    arqSaida <<  s->getT() << " ";
    arqSaida << s->medirDeformacao() << endl;
}

void ExportadorSaida::salvaEst(SistemaParticulas * s, ofstream & arqSaida, double dt)
{
    arqSaida << "Numero de pontos em X =" << s->getNx() << endl;
    arqSaida << "Numero de pontos em Y =" << s->getNy() << endl;
    arqSaida << "dt =" << dt << endl;
   // arqSaida << "Todas as particulas tem a constante viscoelastica =" << s->getElas << endl;
   // arqSaida << "Todas as particulas tem a constante elastica =  " << s->p[0].e << endl;
    //arqSaida << "Matriz de massa das partículas" << endl;

   /* for(int i=0; i<s->nx; i++)
    {
	    for(int j=0; j<s->ny; j++)
	    {
		    outFile << s-> << " " ;
	    }
        outFile << endl;
    }*/
    arqSaida << "Deformação Máxima Total= " << s->getMedidaDeformacao() << endl;
    arqSaida << "Deformação Máxima Eixo= " << s->getMedidaDeformacaoEixo() << endl;
    arqSaida << "Medida de Retorno ao Eixo= " << s->getMedidaRetorno() << endl;
    arqSaida << "Medida de Rotaçao= " << s->getMedidaRot() << endl;
}