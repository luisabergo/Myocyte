#include "ModeloTensao.h"

class ResolvedorEDO;

class ModeloA : public ModeloTensao
{
    public:
        ModeloA();
        ~ModeloA();
        void resolveModelo(ResolvedorEDO* r);
        void printSolucao();
        double k(double V, double Tai);
        double E1(double* y, double t, ResolvedorEDO* r);
        double dTai(double* y, double t, ResolvedorEDO* r);
        double dTa(double* y, double t, ResolvedorEDO* r);
        void avanca(double* y, double* ynew, int nPasso, double deltat, ResolvedorEDO* r );
        void normaliza();
        double* getTensaoAtiva();
        const double C0 = 0.0166015;
        const double x1 = 0.0001;
        const double x2 = 0.78;
        const double x3 = 0.2925;
        const double sigma = 0.046875;
        const int _Tai_ = 0;
        const int _Ta_ = 1;
    private:
        double Ta[12000];
        double Tai[12000];
};