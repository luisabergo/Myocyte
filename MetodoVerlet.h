#include "MetodoAvanca.h"

#ifndef _MetodoVerlet_h_
#define _MetodoVerlet_h_

class MetodoVerlet : public MetodoAvanca
{
    public:
        void avanca(int numPasso, SistemaParticulas* s, double dt)
        {
            double xtemp, vxtemp, ytemp, vytemp;
            double x2temp, vx2temp, y2temp, vy2temp, aux;
            int npx = s->getNx();
            int npy = s->getNy();
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

                            // guardar x(t-dt) pro verlet
                            s->getP(ip,0).setAuxVetorPosicao2(0,xtemp);
                            s->getP(ip,0).setAuxVetorPosicao2(1,ytemp);

                            s->getP(ip,0).setvetorPosicao2(0, xtemp + dt*vxtemp);
                            s->getP(ip,0).setvetorPosicao2(1, ytemp + dt*vytemp);

                            aux = vxtemp + dt*(s->getP(ip,0).getvetorForcaat(0)/ s->getP(ip,0).getMassa());
                            s->getP(ip,0).setvetorVelocidade(0,aux);
                            aux = vytemp + dt*(s->getP(ip,0).getvetorForcaat(1)/ s->getP(ip,0).getMassa());
                            s->getP(ip,0).setvetorVelocidade(1,aux);
                        }

                    }
                }

    }else{

        const double dt2 = dt*dt;

        for (int i=0; i<npx; i++)
        {   for(int j=0; j<npy; j++)
            {
                int ip = j*npx + i;
                if(s->getFix(ip)==0){
                    //x(t-dt)
                    x2temp  = s->getP(ip,0).getAuxVetorPosicaoat(0);
                    y2temp  = s->getP(ip,0).getAuxVetorPosicaoat(1);

                    // x(t)
                    xtemp = s->getP(ip,0).getvetorPosicaoat(0);
                    ytemp = s->getP(ip,0).getvetorPosicaoat(1);

                    // calcula x(t+dt)
                    s->getP(ip,0).setvetorPosicao2(0,2*xtemp - x2temp + (s->getP(ip,0).getvetorForcaat(0)/ s->getP(ip,0).getMassa())*dt2);
                    s->getP(ip,0).setvetorPosicao2(1,2*ytemp - y2temp + (s->getP(ip,0).getvetorForcaat(1)/ s->getP(ip,0).getMassa())*dt2);

                    // aproxima v(t+dt) com diferenca central
                    
                    s->getP(ip,0).setvetorVelocidade(0,(s->getP(ip,0).getvetorPosicaoat(0) - x2temp)/2.0);
                    s->getP(ip,0).setvetorVelocidade(1,(s->getP(ip,0).getvetorPosicaoat(1) - y2temp)/2.0);

                    // guardar o novox(t-dt)
                    s->getP(ip,0).setAuxVetorPosicao2(0,xtemp);
                    s->getP(ip,0).setAuxVetorPosicao2(1,ytemp);
                }

            }
        }
    }

    double tam, t1, t2;
    t1 = s->getP(s->getIpLong(1),0).getvetorPosicaoat(0);
    t2 = s->getP(s->getIpLong(0),0).getvetorPosicaoat(0);
    if(t1>t2)
        tam = t1-t2;
    else
    {
        tam = t2-t1;   
    }
    
    s->setTamEixoX(tam);
    
    };
        
};

#endif