#include "MinimalModel.h"
#include <math.h>

MinimalModel::MinimalModel()
{
	u0 = 0.529297;
	uu = 1.74316;
	thetav = 0.0673828;
	thetaw = 0.00195313;
	thetavlinha = 0.0976563;
	theta0 = 0.932618;
	tauv1 = 57.7148;
	tauv2 = 1101.56;
	tauvmais = 1.96973;
	tauw1 = 62.9688;
	tauw2 = 13.9648;
	kw = 58.0469;
	uw = 0.59668;
	tauwmais = 273.633 ;
	taufi =  0.644532;
	tau01 = 477.344 ;
	tau02 = 14.1992;
	taus01 = 25.4492;
	taus02 = 0.253711;
	kso = 2.49609;
	uso = 0.657227;
	taus1 = 2.36621 ;
	taus2 = 11.4453 ;
	ks = 2.25586;
	us = 0.903321;
	tausi = 1.76816;
	tauwinf =  0.785157;
	winfstar = 0.500977;


    HT = 0.05;
}

MinimalModel::~MinimalModel()
{

}
double* MinimalModel::getPotencial()
{
	return udef;
}
double* MinimalModel::getW()
{
	return wdef;
}
double* MinimalModel::getV()
{
	return vdef;
}
double* MinimalModel::getS()
{
	return sdef;
}
double* MinimalModel::getT()
{
	return tdef;
}

double MinimalModel::H(double x, double y)
{
    if(x > y)
    {
		return 1;
	}
	else if (x < y)
    {
		return 0;
	}
	else return 0.5;
}

double MinimalModel::vnoinf(double x, double y)
{
    if (x < y){
		return 1;
	}
	else return 0;
}

void MinimalModel::normaliza_u(){
	int i;
    double maior, menor;
    
    maior = 0;
    menor = 100000000;
    
    for (i = 0; i < 12000; i++){
		if (udef[i] > maior){
			maior = udef[i];
		}
		if (udef[i] < menor){
			menor = udef[i];
		}
	}
	for (i = 0; i < 12000; i++){
		udef[i] = (udef[i] - menor)/(maior - menor);
	}	
}

void MinimalModel::print_matriz(ResolvedorEDO* r)
{

	int i;
	double t=0;
	//Sao printados 5 informacoes por linha
	// tempo, 
    for (i = 0; i < 12000; i++)
    {
		//cout << t << " " <<  udef[i] << " " << vdef[i] << " " << wdef[i] << " " << sdef[i] << " " << endl;
		t += HT;
	}

}
void MinimalModel::resolveModelo(ResolvedorEDO* r)
{
    //Taxas de constantes no tempo
	double tauv, tauw, taus0, taus, tau0, vinf, winf, jfi, jso, jsi;
	double du_dt, dv_dt, ds_dt, dw_dt;
	
	//Condicões iniciais
	double u  = 0;
	double v  = 1;
	double w  = 1;
	double s  = 0;
	double t  = 0;
	
	udef[0] = 0; vdef[0] = v; wdef[0] = w; sdef[0]= s; tdef[0] = t;

	int i;
	for (i = 1; i < 12000; i++){
		if (i%12000 == 1000) u += 0.325;
		
		tauv = (1 - H(u, thetavlinha))*tauv1 + H(u, thetavlinha)*tauv2;
		tauw = tauw1 + (tauw2-tauw1)*(1 + tanh(kw*(u-uw)))/2.0;
		taus0 = taus01 + (taus02-taus01)*(1 + tanh(kso*(u-uso)))/2.0;
		taus = (1 - H(u, thetaw))*taus1 + H(u, thetaw)*taus2;
		tau0 = (1 - H(u, theta0))*tau01 + H(u, theta0)*tau02;
		
		vinf = vnoinf(u, thetavlinha);
		winf = (1 - H(u, theta0))*(1 - u/tauwinf) + H(u, theta0)*winfstar;
		
		jfi = -v*H(u, thetav)*(u - thetav)*(uu - u)/taufi;
		jso = (u - u0)*(1 - H(u, thetaw))/tau0 + H(u, thetaw)/taus0;
		jsi = -H(u, thetaw)*w*s/tausi;
		
		du_dt = -(jfi +jso + jsi);
		dv_dt = (1 - H(u, thetav))*(vinf - v)/tauv - H(u, thetav)*v/tauvmais;
		dw_dt = (1 - H(u, thetaw))*(winf - w)/tauw - H(u, thetaw)*w/tauwmais;
		ds_dt = ((1 + tanh(ks*(u-us)))/2 -s)/taus;
		
		u = u + HT*du_dt;
		v = v + HT*dv_dt;
		w = w + HT*dw_dt;
		s = s + HT*ds_dt;
		t = t + HT;
		
		udef[i] = u;
		vdef[i] = v;
		wdef[i] = w;
		sdef[i] = s;
		tdef[i] = t;
    }
    
    normaliza_u();
    print_matriz(r);

}