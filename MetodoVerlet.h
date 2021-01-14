#include "MetodoAvanca.h"

#ifndef _MetodoVerlet_h_
#define _MetodoVerlet_h_

class MetodoVerlet : public MetodoAvanca
{
    public:
        MetodoVerlet(){};
        ~MetodoVerlet(){};
        void avanca(int numPasso, SistemaParticulas* s, double dt);
};
#endif