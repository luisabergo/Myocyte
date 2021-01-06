#ifndef _modelo_eletrofisiologico_h_
#define _modelo_eletrofisiologico_h_

class ModeloEletrofisiologico
{
    public:
        ModeloEletrofisiologico();
        ~ModeloEletrofisiologico();
        virtual void resolveModelo(ResolvedorEDO* r) = 0;
    private:
        
};

#endif