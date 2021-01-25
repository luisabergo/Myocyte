#include "ModeloA.h"
#include <math.h>
#include <iostream> 

using namespace std;
class ResolvedorEDO;

ModeloA::ModeloA()
{
    for(int i=0; i<12000; i++)
    {
        Tai[i] = 0;
        Ta[i] = 0;
    }
}

ModeloA::~ModeloA()
{

}

void ModeloA::resolveModelo(ResolvedorEDO* r, double* V)
{
    const int tamdisc = 12000;
    double tensao[tamdisc], tensao2[tamdisc], vreal[tamdisc], kv[tamdisc], e1[tamdisc];
    kv[0] = 0;
    e1[0] = 0;
    double TaAux, Ta2, d_dt_Ta2, d_dt_Ta, myCond, kta;
    TaAux = 0;
	Ta2 = 0;
    tensao2[0] = 0; 
    tensao[0] = 0;
    for (int i = 1; i < tamdisc; i++)
    {

    	kta = k(V[i]); // kTa(v) para Ta
    	kv[i] = kta;
		myCond = e0_1;//rateswitchNP(svolt[j], et_1, e0_1, e1_1); // e1(v)
		d_dt_Ta = myCond * (kta - TaAux); // Derivada de Ta
		TaAux = TaAux + 0.05*d_dt_Ta;  //Integração de Ta
		tensao[i] = TaAux;
        Ta[i] = tensao[i];
		
		//	ATUALIZAÇÕES DE TA_2
		if (V[i] > x5 && TaAux < x6) myCond = 0.0001;
		e1[i] = myCond;
		d_dt_Ta2 = myCond * (TaAux - Ta2); // Derivada de Ta2
		Ta2 = Ta2 + 0.05*d_dt_Ta2;  //Integração de Ta2

		tensao2[i] = Ta2;
        Tai[i] = tensao2[i];
	}

    int i;
    double maior, menor;
    
    maior = 0;
    menor = 100000000;
    
    for (i = 0; i < 12000; i++){
		if (tensao2[i] > maior){
			maior = tensao2[i];
		}
		if (tensao2[i] < menor){
			menor = tensao2[i];
		}
	}
	for (i = 0; i < 12000; i++){
		tensao2[i] = (tensao2[i] - menor)/(maior - menor);
	}	

}

void ModeloA::printSolucao()
{
    for(int i=0; i<12000; i++)
    {
        cout << i*0.05 << Ta[i] << endl;
    }
}

double ModeloA::k(double V)
{
    return (1/(x1*sqrt(2*3.14))) * exp((-pow(V - 1, 2)/(2*pow(x1,2))));
}

double* ModeloA::getTensaoAtiva()
{
    return Tai;
}

