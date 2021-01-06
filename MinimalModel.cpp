#include "MinimalModel.h"
#include <math.h>

MinimalModel::MinimalModel()
{
    u0 = 0;
    uu = 1.58;
    thetav = 0.3;
    thetaw = 0.015;
    thetavlinha = 0.015;
    theta0 = 0.006;
    tauv1 = 60;
    tauv2 = 1150;
    tauvmais = 1.4506;
    tauw1 = 70;
    tauw2 = 20;
    kw = 65;
    uw = 0.03;
    tauwmais = 280;
    taufi = 0.11;
    tau01 = 6;
    tau02 = 6;
    taus01 = 43;
    taus02 = 0.2;
    kso = 2;
    uso = 0.65;
    taus1 = 2.7342;
    taus2 = 3;
    ks = 2.0994;
    us = 0.9087;
    tausi = 2.8723;
    tauwinf = 0.07;
    winfstar = 0.94;

    HT = 0.05;
}

MinimalModel::~MinimalModel()
{}


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

void MinimalModel::grava_matriz(ResolvedorEDO* r)
{

	int i;
	double t=0;
    for (i = 0; i < 12000; i++){
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
		if (i == 1000) u = 0.325;
		
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
    grava_matriz(r);

}