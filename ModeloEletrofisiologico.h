class ResolvedorEDO;

class ModeloEletrofisiologico
{
    public:
        ModeloEletrofisiologico();
        ~ModeloEletrofisiologico();
        virtual void resolveModelo(ResolvedorEDO* r) = 0;
    private:
};
