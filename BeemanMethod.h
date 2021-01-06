#include "MetodoAvanca.h"
#include <iostream>

#ifndef _BeemanMethod_h_
#define _BeemanMethod_h_

class BeemanMethod : public MetodoAvanca
{
    public:
        void avanca(int numPasso, SistemaParticulas* s, double dt)
        {
            double xtemp =0 , vxtemp=0, ytemp=0, vytemp=0, axtemp, aytemp;
            double ax2temp=0, ay2temp=0;
            int npx = s->getNx();
            int npy = s->getNy();
            double aux, ax, ay;
            if(numPasso==0)
            {
                for (int i=0; i<npx; i++)
                {   for(int j=0; j<npy; j++)
                    {
                        int ip = j*npx + i;
                        if(s->getFix(ip)==0)
                        {
                            xtemp  = s->getP(ip,0).getvetorPosicaoat(0);
                            ytemp  = s->getP(ip,0).getvetorPosicaoat(1);
                            vxtemp = s->getP(ip,0).getvetorVelocidadeat(0);
                            vytemp = s->getP(ip,0).getvetorVelocidadeat(1);
                            axtemp = s->getP(ip,0).getAceleracao(0);
                            aytemp = s->getP(ip,0).getAceleracao(1);

                            //guardar a(t-dt) pro beeman
                            s->getP(ip,0).setAuxAceleracao(0,axtemp);
                            s->getP(ip,0).setAuxAceleracao(1,aytemp);

                            s->getP(ip,0).setvetorPosicao2(0, xtemp + dt*vxtemp);
                            s->getP(ip,0).setvetorPosicao2(1, ytemp + dt*vytemp);

                            s->getP(ip,0).setAceleracao(0, vxtemp + dt*axtemp);
                            s->getP(ip,0).setAceleracao(1, vytemp + dt*aytemp);

                            aux = vxtemp + dt*(s->getP(ip,0).getvetorForcaat(0)/ s->getP(ip,0).getMassa());
                            s->getP(ip,0).setvetorVelocidade(0,aux);
                            aux = vytemp + dt*(s->getP(ip,0).getvetorForcaat(1)/ s->getP(ip,0).getMassa());
                            s->getP(ip,0).setvetorVelocidade(1,aux);
                        }

                    }
                }

            }
            for (int i=0; i<npx; i++)
            {   
                for(int j=0; j<npy; j++)
                {    
                    int ip = j*npx + i;
                    if(s->getFix(ip)==0)
                    {
                        xtemp  = s->getP(ip,0).getvetorPosicaoat(0);
                        ytemp  = s->getP(ip,0).getvetorPosicaoat(1);
                        vxtemp = s->getP(ip,0).getvetorVelocidadeat(0);
                        vytemp = s->getP(ip,0).getvetorVelocidadeat(1);
                        //a (x -dt)
                        ax2temp = s->getP(ip,0).getAuxAceleracao(0);
                        ay2temp = s->getP(ip,0).getAuxAceleracao(1);

                        //  (a x(t))
                        axtemp = s->getP(ip,0).getAceleracao(0);
                        aytemp = s->getP(ip,0).getAceleracao(1);

                        //a(x(t+dt))
                        ax = s->getP(ip,0).getvetorForcaat(0)/ s->getP(ip,0).getMassa();
                        ay = s->getP(ip,0).getvetorForcaat(1)/ s->getP(ip,0).getMassa();

                        //metodo de beeman
                        aux = xtemp + dt*vxtemp + (1/6)*(4*axtemp -ax2temp)*dt*dt;
                        s->getP(ip,0).setvetorPosicao2(0,aux);
                        aux = ytemp + dt*vytemp + (1/6)*(4*aytemp -ay2temp)*dt*dt;
                        s->getP(ip,0).setvetorPosicao2(1,aux);
                        
                        aux = vxtemp +(1/6)*2*dt*(ax+5*axtemp-ax2temp);
                        s->getP(ip,0).setvetorVelocidade(0,aux);
                        aux = vytemp +(1/6)*2*dt*(ay+5*aytemp-ay2temp);
                        s->getP(ip,0).setvetorVelocidade(1,aux);

                        //guardar aceleracao a (x-dt)
                        s->getP(ip,0).setAuxAceleracao(0,axtemp);
                        s->getP(ip,0).setAuxAceleracao(1,aytemp);

                        //guardar a aceleracao a x(t)
                        s->getP(ip,0).setAceleracao(0,ax);
                        s->getP(ip,0).setAceleracao(1,ay);
                    }
            
            }
        }  
        double tam = s->getP(s->getIpLong(1),0).getvetorPosicaoat(0) - s->getP(s->getIpLong(0),0).getvetorPosicaoat(0);
        s->setTamEixoX(tam);

        };
};

#endif