#include "ModeloTensao.h"

class ResolvedorEDO;

class ModeloA : public ModeloTensao
{
    public:
        ModeloA();
        ~ModeloA();
        void resolveModelo(ResolvedorEDO* r, double* V);
        void printSolucao();
        double k(double V);
        void normaliza();
        double* getTensaoAtiva();
        const double e0_1 = 0.0166016;
        const double x1 = 0.046875;
        const double x4 = 0.0001;
        const double x5 = 0.78;
        const double x6 = 0.2925;
        const int _Tai_ = 0;
        const int _Ta_ = 1;
    private:
        double Ta[12000];
        double Tai[12000];
};