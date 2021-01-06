
#include "MetodoAvanca.h"

#ifndef _EulerExplicito_h_
#define _EulerExplicito_h_

class EulerExplicito : public MetodoAvanca
{
    public:
        void avanca(int numPasso, SistemaParticulas* s, double dt)
        {
            double xtemp =0 , vxtemp=0, ytemp=0, vytemp=0;
            int npx = s->getNx();
            int npy = s->getNy();
            double aux;
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

                    aux = xtemp + dt*vxtemp;
                    s->getP(ip,0).setvetorPosicao2(0,aux);
                    aux = ytemp + dt*vytemp;
                    s->getP(ip,0).setvetorPosicao2(1,aux);

                    aux = vxtemp + dt*(s->getP(ip,0).getvetorForcaat(0)/ s->getP(ip,0).getMassa());
                    s->getP(ip,0).setvetorVelocidade(0,aux);
                    aux = vytemp + dt*(s->getP(ip,0).getvetorForcaat(1)/ s->getP(ip,0).getMassa());
                    s->getP(ip,0).setvetorVelocidade(1,aux);
                }
            
            }
        }  
        double tam = s->getP(s->getIpLong(1),0).getvetorPosicaoat(0) - s->getP(s->getIpLong(0),0).getvetorPosicaoat(0);
        s->setTamEixoX(tam);

        };
};

#endif