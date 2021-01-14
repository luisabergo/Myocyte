#include "SistemaParticulas.h"

#ifndef _MetodoAvanca_h_
#define _MetodoAvanca_h_

class MetodoAvanca
{
    public:
        MetodoAvanca(){};
        ~MetodoAvanca(){};
        virtual void avanca(int numPasso, SistemaParticulas* s, double dt)=0;
};

#endif