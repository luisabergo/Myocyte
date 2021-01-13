#include "ModeloTensao.h"

class ResolvedorEDO;

class ModeloA : public ModeloTensao
{
    public:
        ModeloA();
        ~ModeloA();
        void resolveModelo(ResolvedorEDO* r);
    private:
        double C0 = 0.0166015;
        double x1 = 0.0001;
        double x2 = 0.78;
        double x3 = 0.2925;
        double sigma = 0.046875;
};