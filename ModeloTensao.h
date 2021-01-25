class ResolvedorEDO;

class ModeloTensao
{
    public:
        ModeloTensao();
        ~ModeloTensao();
        virtual void resolveModelo(ResolvedorEDO* r, double* V) = 0;
        virtual void printSolucao() = 0;
        virtual double* getTensaoAtiva() = 0;
    private:

};
