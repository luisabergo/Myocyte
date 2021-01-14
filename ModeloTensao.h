class ResolvedorEDO;

class ModeloTensao
{
    public:
        ModeloTensao();
        ~ModeloTensao();
        virtual void resolveModelo(ResolvedorEDO* r) = 0;
        virtual void printSolucao() = 0;
    private:

};
